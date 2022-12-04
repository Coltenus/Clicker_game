//
// Created by colte on 02.12.2022.
//

#include "MainMenu.h"
#include "Actions.h"

namespace g9 {
    MainMenu::MainMenu(std::vector<std::thread*>* th,
                       bool* ise,
                       utils::MenuSelections* ms)
            :
            MenuOption(th, ise, ms)
            {
                active = true;
                butStart = new g9::game_objects::Button({WIDTH/2 - 100, HEIGHT * 0.20f}, {200, 100}, "Start", 35, GRAY);
                butStart->SetAction(actions::toGameplay);
                butSettings = new g9::game_objects::Button({WIDTH/2 - 100, HEIGHT * 0.35f}, {200, 100}, "Settings", 35, GRAY);
                butSettings->SetAction(actions::toGameplay);
                butCredits = new g9::game_objects::Button({WIDTH/2 - 100, HEIGHT * 0.5f}, {200, 100}, "Credits", 35, GRAY);
                butCredits->SetAction(actions::toGameplay);
                butExit = new g9::game_objects::Button({WIDTH/2 - 100, HEIGHT * 0.65f}, {200, 100}, "Exit", 35, GRAY);
                butExit->SetAction(actions::Exit);
                auto* existingThread = new std::thread([&](){
                    std::mutex m;
                    float buf;
                    while (object != nullptr && active && !(*isShouldExit))
                    {
                        if(object == nullptr)
                            m.lock();
                        if((buf = GetMouseWheelMove()) != 0)
                        {
                            if(cam.target.y >= HEIGHT)
                                cam.target.y -= buf*100;
                        }
                        if(cam.target.y < HEIGHT)
                            cam.target.y = HEIGHT;
                        butStart->Click(*menuOpt, active);
                        butSettings->Click(*menuOpt, active);
                        butCredits->Click(*menuOpt, active);
                        butExit->Click(*menuOpt, active);
                        std::this_thread::sleep_for(std::chrono::milliseconds(15));
                    }
                });
                existingThread->detach();
                curThreads++;
                existingThreads->push_back(existingThread);
                existingThread = nullptr;
            }

    MainMenu *MainMenu::CreateMainMenu(std::vector<std::thread *> *th, bool *ise, utils::MenuSelections *ms) {
        if(object != nullptr)
            return nullptr;
        else
        {
            object = new MainMenu(th, ise, ms);
            return object;
        }
    }

    MainMenu::~MainMenu() {
        if(object != nullptr)
        {
            while (!existingThreads->empty())
            {
                delete *(existingThreads->begin());
                existingThreads->erase(existingThreads->begin());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if(butStart != nullptr)
            {
                delete butStart;
                butStart = nullptr;
            }
            if(butSettings != nullptr)
            {
                delete butSettings;
                butSettings = nullptr;
            }
            if(butCredits != nullptr)
            {
                delete butCredits;
                butCredits = nullptr;
            }
            if(butExit != nullptr)
            {
                delete butExit;
                butExit = nullptr;
            }
            isShouldExit = nullptr;
            existingThreads = nullptr;
            object = nullptr;
        }
    }

    void MainMenu::Update() {
        if(active)
        {
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            butStart->Show();
            butSettings->Show();
            butCredits->Show();
            butExit->Show();
            EndDrawing();
        }
    }

} // g9