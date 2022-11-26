#include <iostream>
#include <raylib.h>
#include <vector>
#include <thread>
#include "src/common.h"
#include "src/Money.h"
#include "src/MainBuilding.h"
#include "src/SideBuilding.h"
#include "src/Button.h"

int main() {
    setbuf(stdout, nullptr);
    bool isShouldExit = false;
    bool newIteration = false;
    InitWindow(WIDTH, HEIGHT, "Moving buildings");
    SetTargetFPS(60);
    Image icon = LoadImage("res/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    Camera2D cam = {{WIDTH, HEIGHT}, {WIDTH, HEIGHT}, 0, 1.f};
    float buf;
    auto* money = new g9::Money({20, 20}, 40);
    std::vector<g9::Building*> buildings = {
            new g9::MainBuilding({750, HEIGHT / 2 - 200}, {100, 100}, DARKBROWN, 1, &cam),
            new g9::SideBuilding({WIDTH / 2 - 50, HEIGHT / 2 + 150}, {100, 100}, VIOLET, 0, 5000, &cam)
    };
    std::vector<g9::Button> buttons = {
            g9::Button({1275, 50}, {300, 50}, "Upgrade Main Building", 20, RED, 25),
            g9::Button({1275, 50}, {300, 50}, "Buy Side Building", 20, RED, 40)
    };
    buttons[0].SetAction([](g9::Money& m, g9::Building& b, unsigned long long& neededVal){
        static unsigned long long curVal;
        curVal = m.GetValue();
        if(neededVal != 0 && curVal >= neededVal)
        {
            m -= neededVal;
            neededVal *= 1.2;
            b.IncreaseIncValByVal(1);
        }
    });
    buttons[1].SetAction([](g9::Money& m, g9::Building& b, unsigned long long& neededVal){
        static unsigned long long curVal;
        curVal = m.GetValue();
        if(neededVal != 0 && curVal >= neededVal)
        {
            m -= neededVal;
            neededVal *= 1.2;
            b.IncreaseIncValByVal(2);
        }
    });
    auto butIter = buttons.begin();
    auto* butP = new g9::Button({1325, 120}, {50, 50}, "<=", 20, BLUE);
    butP->SetAction([](const std::vector<g9::Button>& vec,
                       __gnu_cxx::__normal_iterator<g9::Button*, std::vector<g9::Button>>& iter){
        if(iter != vec.begin())
            iter -= 1;
    });
    auto* butN = new g9::Button({1475, 120}, {50, 50}, "=>", 20, BLUE);
    butN->SetAction([](const std::vector<g9::Button>& vec,
                       __gnu_cxx::__normal_iterator<g9::Button*, std::vector<g9::Button>>& iter){
        if(iter + 1 != vec.end())
            iter += 1;
    });
    std::vector<std::thread*> existingThreads;
    std::thread* existingThread = new std::thread([&buildings, &money](){
        buildings[1]->WhileExist(*money);
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = new std::thread([&buildings, &isShouldExit](){
        while (!isShouldExit)
        {
            buildings[0]->Move(6, 2.5);
            buildings[1]->Move(6, 2);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = new std::thread([&](){
        while (!isShouldExit)
        {
            if(newIteration)
            {
                if((buf = GetMouseWheelMove()) != 0)
                {
                    if(cam.target.y >= HEIGHT)
                        cam.target.y -= buf*100;
                }
                if(cam.target.y < HEIGHT)
                    cam.target.y = HEIGHT;
                butIter->Click(*money, *buildings[std::distance(buttons.begin(), butIter)]);
                butN->Click(buttons, butIter);
                butP->Click(buttons, butIter);
                for(auto& el: buildings)
                {
                    el->check(*money);
                }
                newIteration = false;
            }
        }
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = nullptr;
    while (!isShouldExit)
    {
        newIteration = true;
        BeginDrawing();
        ClearBackground(GREEN);
        BeginMode2D(cam);
        for(auto& el: buildings)
        {
            el->Show();
        }
        EndMode2D();
        money->Show();
        butIter->Show();
        butN->Show();
        butP->Show();
        EndDrawing();
        if(WindowShouldClose())
            isShouldExit = true;
    }
    CloseWindow();
    if(money != nullptr)
    {
        delete money;
        money = nullptr;
    }
    for(auto& el: buildings)
        delete el;
    buildings.clear();
    for(auto& el: existingThreads)
        delete el;
    existingThreads.clear();
    return 0;
}
