#include <iostream>
#include <raylib.h>
#include <vector>
#include <thread>
#include "src/common.h"
#include "src/Money.h"
#include "src/MainBuilding.h"
#include "src/SideBuilding.h"
#include "src/Button.h"
#include "src/Actions.h"

int g9::Building::buildingsCount = 0;

int main() {
    setbuf(stdout, nullptr);
    bool isShouldExit = false;
    InitWindow(WIDTH, HEIGHT, "Moving buildings");
    SetTargetFPS(60);
    Image icon = LoadImage("res/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    Camera2D cam = {{WIDTH, HEIGHT}, {WIDTH, HEIGHT}, 0, 1.f};
    float buf;
    auto* money = new g9::Money({20, 20}, 40);
    std::vector<g9::Building*> buildings = {
            new g9::MainBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 200}, {100, 100}, DARKBROWN, 1, &cam, 6, 2.5),
            new g9::SideBuilding({WIDTH / 2 - 50, HEIGHT / 2 + 300}, {120, 100}, VIOLET, 0, 5000, &cam, 6, 2)
    };
    std::vector<g9::Button> buttons = {
            g9::Button({1275, 50}, {300, 50}, "Upgrade Main Building", 20, RED, 25, 0),
            g9::Button({1275, 50}, {300, 50}, "Buy Side Building", 20, RED, 40, 2)
    };
    buttons[0].SetAction(g9::actionMB);
    buttons[1].SetAction(g9::actionSB);
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
    auto* existingThread = new std::thread([&buildings, &money](){
        buildings[1]->WhileExist(*money);
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = new std::thread([&buildings, &isShouldExit](){
        while (!isShouldExit)
        {
            for(auto& el: buildings)
            {
                el->Move();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = new std::thread([&](){
        while (!isShouldExit)
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
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = nullptr;
    while (!isShouldExit)
    {
        if(buildings[buildings.size()-1]->GetIncomeValue() != 0)
        {
            if(g9::Building::buildingsCount%5 == 0) {
                buildings.push_back(
                        new g9::MainBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 100 + 450.f * g9::Building::buildingsCount},
                                             {100, 100}, DARKBROWN, 0, &cam, 6, 2.5)
                );
                buttons.push_back(
                        g9::Button({1275, 50}, {300, 50}, "Buy Main Building", 20, RED,
                                   15 * pow(4, g9::Building::buildingsCount),
                                   pow(4, g9::Building::buildingsCount)/2)
                );
                buttons[buttons.size()-1].SetAction(g9::actionMB);
            }
            else {
                buildings.push_back(
                        new g9::SideBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 100 + 450.f * g9::Building::buildingsCount},
                                             {120, 100}, VIOLET, 0,
                                             (unsigned int)(10000.f / (g9::Building::buildingsCount+1)), &cam, 6, 2)
                );
                buttons.push_back(
                        g9::Button({1275, 50}, {300, 50}, "Buy Side Building", 20, RED,
                                   20 * pow(4, g9::Building::buildingsCount),
                                   pow(5, g9::Building::buildingsCount))
                        );
                buttons[buttons.size()-1].SetAction(g9::actionSB);
                existingThread = new std::thread([&buildings, &money](){
                    buildings[buildings.size()-1]->WhileExist(*money);
                });
                existingThread->detach();
                existingThreads.push_back(existingThread);
                existingThread = nullptr;
            }
            butIter = buttons.begin();
        }
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
    buildings.erase(buildings.cbegin(), buildings.end());
    existingThreads.erase(existingThreads.begin(), existingThreads.end());
    return 0;
}
