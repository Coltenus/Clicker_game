//
// Created by colte on 11.12.2022.
//

#include "SettingsMenu.h"
#include "Actions.h"

namespace g9 {
    SettingsMenu::SettingsMenu(std::vector<std::thread*>* th,
                               bool* ise,
                               utils::MenuSelections* ms)
            :
            MenuOption(th, ise, ms)
            {
                active = true;
                butBack = new g9::game_objects::Button({20, 100}, {100, 50}, "Back", 20, GRAY);
                butBack->SetAction(actions::toMainMenu);
                auto* existingThread = new std::thread([&](){
                    bool isActive = active;
                    while (isActive && !(*isShouldExit))
                    {
                        isActive = active;
                        if(!isActive)
                            break;
                        butBack->Click(*menuOpt, active);
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
            isShouldExit = nullptr;
            existingThreads = nullptr;
            object = nullptr;
        }
    }

    void SettingsMenu::Update() {
        if(active)
        {
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            butBack->Show();
            DrawText("Settings", 100, 20, 40, BLACK);
            EndDrawing();
        }
    }
} // g9