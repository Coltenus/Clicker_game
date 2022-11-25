#include <iostream>
#include <raylib.h>
#include <vector>
#include <thread>
#define WIDTH 1600
#define HEIGHT 900
#include "src/Money.h"
#include "src/MainBuilding.h"
#include "src/SideBuilding.h"
#include "src/Button.h"

int main() {
    int l;
    setbuf(stdout, nullptr);
    InitWindow(WIDTH, HEIGHT, "Game 9");
    auto* money = new g9::Money({20, 20}, 40);
    std::vector<g9::Building*> buildings = {
            new g9::MainBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 50}, {100, 100}, DARKBROWN, 1),
            new g9::SideBuilding({WIDTH / 2 - 50, HEIGHT / 2 + 150}, {100, 100}, VIOLET, 0, 5000)
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
    std::vector<std::thread*> existingBuildings;
    std::thread* sbExisting = new  std::thread([&buildings, &money](){
        buildings[1]->WhileExist(*money);
    });
    sbExisting->detach();
    existingBuildings.push_back(sbExisting);
    sbExisting = nullptr;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        for(auto& el: buildings)
        {
            el->check(*money);
            el->Show();
        }
        if(money != nullptr)
        {
            money->Show();
        }
        butIter->Show();
        butIter->Click(*money, *buildings[std::distance(buttons.begin(), butIter)]);
        if(butN != nullptr)
        {
            butN->Show();
            butN->Click(buttons, butIter);
        }
        if(butP != nullptr)
        {
            butP->Show();
            butP->Click(buttons, butIter);
        }
        ClearBackground(GREEN);
        EndDrawing();
    }
    CloseWindow();
    if(money != nullptr)
    {
        delete money;
        money = nullptr;
    }
    l = buildings.size();
    for(int i = l-1; i>=0; i--)
    {
        g9::Building* buf = buildings[i];
        buildings.pop_back();
        if(buf != nullptr)
            delete buf;
    }
    l = existingBuildings.size();
    for(int i = l-1; i>=0; i--)
    {
        std::thread* buf = existingBuildings[i];
        existingBuildings.pop_back();
        if(buf != nullptr)
            delete buf;
    }
    return 0;
}
