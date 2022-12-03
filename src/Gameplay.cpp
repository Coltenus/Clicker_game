//
// Created by colte on 02.12.2022.
//

#include "Gameplay.h"
#include <mutex>

namespace g9 {
    Gameplay::Gameplay(std::vector<std::thread*>* th,
                       bool* ise,
                       utils::MenuSelections* ms)
        :
        MenuOption(th, ise, ms),
        money(nullptr),
        bl(nullptr),
        butIter(nullptr),
        butP(nullptr),
        butN(nullptr),
        butBack(nullptr)
        {}

    Gameplay *Gameplay::CreateGameplay(std::vector<std::thread*>* th,
                                       bool* ise,
                                       utils::MenuSelections* ms) {
        if(object != nullptr)
            return nullptr;
        else
        {
            object = new Gameplay(th, ise, ms);
            return object;
        }
    }

    Gameplay::~Gameplay() {
        if(object != nullptr)
        {
            while (!existingThreads->empty())
            {
                delete *(existingThreads->begin());
                existingThreads->erase(existingThreads->begin());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            //existingThreads = nullptr;
            if(money != nullptr)
            {
                delete money;
                money = nullptr;
            }
            if(bl != nullptr)
            {
                delete bl;
                bl = nullptr;
            }
            if(butP != nullptr)
            {
                delete butP;
                butP = nullptr;
            }
            if(butN != nullptr)
            {
                delete butN;
                butN = nullptr;
            }
            if(butBack != nullptr)
            {
                delete butBack;
                butBack = nullptr;
            }
            butIter = nullptr;
            isShouldExit = nullptr;
            object = nullptr;
        }
    }

    void Gameplay::Start() {
        active = true;
        money = new game_objects::Money({20, 20}, 40, MONEY_VAL);
        bl = BuildingsList::CreateList(&cam, money);
        butIter = new __gnu_cxx::__normal_iterator<game_objects::Button *, std::vector<game_objects::Button>>;
        *butIter = bl->GetFirstButton();
        butP = new g9::game_objects::Button({1325, 120}, {50, 50}, "<=", 20, BLUE);
        butP->SetAction(g9::actions::buttonL);
        butN = new g9::game_objects::Button({1475, 120}, {50, 50}, "=>", 20, BLUE);
        butN->SetAction(g9::actions::buttonR);
        butBack = new g9::game_objects::Button({20, 100}, {100, 50}, "Back", 20, GRAY);
        butBack->SetAction(actions::toMainMenu);
        auto* existingThread = new std::thread([&](){
            std::mutex m;
            while(object != nullptr && !existingThreads->empty() && bl != nullptr && (*bl)[1] != nullptr)
            {
                if(object == nullptr || bl == nullptr)
                    m.lock();
                else (*bl)[1]->WhileExist(*money);
            }
        });
        existingThread->detach();
        curThreads++;
        existingThreads->push_back(existingThread);
        existingThread = new std::thread([&](){
            std::mutex m;
            while (object != nullptr && !(*isShouldExit))
            {
                if(object == nullptr || bl == nullptr)
                    m.lock();
                else if(active)
                {
                    bl->Move();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
        });
        existingThread->detach();
        curThreads++;
        existingThreads->push_back(existingThread);
        existingThread = new std::thread([&](){
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
                (*butIter)->Click(*money, *(*bl)[bl->GetDistanceBetweenButtons(*butIter)]);
                butN->Click(bl->GetButtons(), *butIter);
                butP->Click(bl->GetButtons(), *butIter);
                butBack->Click(*menuOpt, active);
                bl->Check();
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
            }
        });
        existingThread->detach();
        curThreads++;
        existingThreads->push_back(existingThread);
        existingThread = nullptr;
    }

    void Gameplay::Update() {
        if(active)
        {
            if(bl->CheckZeroIV())
            {
                bl->AddNewBuilding(*existingThreads, *butIter, curThreads);
            }
            BeginDrawing();
            ClearBackground(GREEN);
            BeginMode2D(cam);
            bl->Show();
            EndMode2D();
            money->Show();
            (*butIter)->Show();
            butN->Show();
            butP->Show();
            butBack->Show();
            EndDrawing();
        }
    }
} // g9