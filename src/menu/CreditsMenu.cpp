//
// Created by Coltenus on 11.12.2022.
//

#include "CreditsMenu.h"
#include "../actions/Actions.h"

namespace g9 {
    CreditsMenu::CreditsMenu(std::vector<std::thread*>* th,
                             bool* ise,
                             utils::MenuSelections* ms)
            :
            MenuOption(th, ise, ms)
    {
        active = true;
        butBack = new game_objects::Button({20, 100}, {100, 50}, "Back", 20, BTN_MENU);
        butBack->SetAction(actions::toMainMenu);
        creditsLabel = menu_elements::TextFrame::CreateTextFrame("This game was made by Coltenus.",
                                                        {WIDTH - 520, HEIGHT - 40},
                                                        {700, 50},
                                                        30);
        descriptionLabel = menu_elements::TextFrame::CreateTextFrame("This game was made by Coltenus.\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "\n"
                                                    "Easter egg",
                                                    {WIDTH/2 - 300, HEIGHT/2 - 300},
                                                    {600, 400},
                                                    30,
                                                    true);
        auto* existingThread = new std::thread([&](){
            bool isActive = active;
            while (isActive && !(*isShouldExit))
            {
                isActive = active;
                if(!isActive)
                    break;
                butBack->Click(*menuOpt, active);
                creditsLabel->Update();
                descriptionLabel->Update();
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        });
        existingThread->detach();
        curThreads++;
        existingThreads->push_back(existingThread);
        existingThread = nullptr;
    }

    CreditsMenu *CreditsMenu::CreateCreditsMenu(std::vector<std::thread *> *th, bool *ise, utils::MenuSelections *ms) {
        if(object != nullptr)
            return nullptr;
        else
        {
            object = new CreditsMenu(th, ise, ms);
            return object;
        }
    }

    CreditsMenu::~CreditsMenu() {
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
            if(creditsLabel != nullptr)
            {
                delete creditsLabel;
                creditsLabel = nullptr;
            }
            if(descriptionLabel != nullptr)
            {
                delete descriptionLabel;
                descriptionLabel = nullptr;
            }
            isShouldExit = nullptr;
            existingThreads = nullptr;
            object = nullptr;
        }
    }

    void CreditsMenu::Update() {
        if(active)
        {
            BeginDrawing();
            ClearBackground(BG_MENU);
            butBack->Show();
            creditsLabel->Show();
            descriptionLabel->Show();
            DrawText("Credits", 100, 20, 40, TEXT_COLOR);
            EndDrawing();
        }
    }
} // g9