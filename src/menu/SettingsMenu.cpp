//
// Created by Coltenus on 11.12.2022.
//

#include "SettingsMenu.h"
#include "../actions/Actions.h"

namespace g9 {
    SettingsMenu::SettingsMenu(std::vector<std::thread*>* th,
                               bool* ise,
                               utils::MenuSelections* ms)
            :
            MenuOption(th, ise, ms)
            {
                active = true;
                butBack = new game_objects::Button({20, 100}, {100, 50}, "Back", 20, BTN_MENU);
                butBack->SetAction(actions::toMainMenu);
                savingsSelect = menu_elements::SelectionForm::CreateSelectionForm(
                        {WIDTH/2 - 200, HEIGHT/2 - 200}, {400, 150}, 20);
                darkMode = new menu_elements::RadioButton({WIDTH/2 - 100, HEIGHT/2 + 50}, {200, 50}, 20);
                std::map<const char*, bool> bufMap{{"Light", false}, {"Dark", true}};
                darkMode->SetMap(bufMap);
                auto* existingThread = new std::thread([&](){
                    bool isActive = active;
                    bool isLeftMouseClicked = false;
                    while (isActive && !(*isShouldExit))
                    {
                        isActive = active;
                        if(!isActive)
                            break;
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                            isLeftMouseClicked = true;
                        else isLeftMouseClicked = false;
                        butBack->Click(*menuOpt, active);
                        savingsSelect->Update(isLeftMouseClicked);
                        darkMode->Update(isLeftMouseClicked);
                        std::this_thread::sleep_for(std::chrono::milliseconds(15));
                    }
                });
                existingThread->detach();
                curThreads++;
                existingThreads->push_back(existingThread);
                existingThread = nullptr;
            }

    SettingsMenu *SettingsMenu::CreateSettingsMenu(std::vector<std::thread *> *th, bool *ise, utils::MenuSelections *ms) {
        if(object != nullptr)
            return nullptr;
        else
        {
            object = new SettingsMenu(th, ise, ms);
            return object;
        }
    }

    SettingsMenu::~SettingsMenu() {
        if(object != nullptr)
        {
            while (!existingThreads->empty())
            {
                delete *(existingThreads->begin());
                existingThreads->erase(existingThreads->begin());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if(butBack != nullptr)
            {
                delete butBack;
                butBack = nullptr;
            }
            if(savingsSelect != nullptr)
            {
                delete savingsSelect;
                savingsSelect = nullptr;
            }
            if(darkMode != nullptr)
            {
                delete darkMode;
                darkMode = nullptr;
            }
            isShouldExit = nullptr;
            existingThreads = nullptr;
            object = nullptr;
        }
    }

    void SettingsMenu::Update() {
        if(active)
        {
            BeginDrawing();
            ClearBackground(BG_MENU);
            butBack->Show();
            DrawText("Choose saving", WIDTH/2 - 100, HEIGHT/2 - 250, 30, TEXT_COLOR);
            savingsSelect->Show();
            DrawText("Color mode", WIDTH/2 - 80, HEIGHT/2, 30, TEXT_COLOR);
            darkMode->Show();
            DrawText("Settings", 100, 20, 40, TEXT_COLOR);
            EndDrawing();
        }
    }

    void SettingsMenu::SetGlobalData(utils::Saves::GlobalData *gd) {
        savingsSelect->SetGlobalData(gd);
    }
} // g9