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
            MenuOption(th, ise, ms),
            butStart(nullptr)
            {}

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
            //existingThreads = nullptr;
            if(butStart != nullptr)
            {
                delete butStart;
                butStart = nullptr;
            }
            isShouldExit = nullptr;
            object = nullptr;
        }
    }

    void MainMenu::Start() {
        active = true;
        butStart = new g9::game_objects::Button({WIDTH/2 - 100, HEIGHT * 0.25f}, {200, 100}, "Start", 35, GRAY);
        butStart->SetAction(actions::toGameplay);
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
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        });
        existingThread->detach();
        curThreads++;
        existingThreads->push_back(existingThread);
        existingThread = nullptr;
    }

    void MainMenu::Update() {
        if(active)
        {
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            butStart->Show();
            EndDrawing();
        }
    }

} // g9