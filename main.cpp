#include <iostream>
#include <raylib.h>
#define WIDTH 1600
#define HEIGHT 900
#include "src/Money.h"
#include "src/MainBuilding.h"
#include "src/Button.h"

int main() {
    setbuf(stdout, nullptr);
    InitWindow(WIDTH, HEIGHT, "Game 9");
    auto* money = new g9::Money({20, 20}, 40);
    auto* mb = new g9::MainBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 50}, {100, 100}, DARKBROWN, 1);
    std::vector<g9::Button> buttons = {
            g9::Button({1275, 50}, {300, 50}, "Upgrade Main Building", 20, RED, 25),
            g9::Button({1275, 50}, {300, 50}, "Upgrade Side Building", 20, RED)
    };
    for(auto& el: buttons)
        el.SetAction([](g9::Money& m, g9::Building& b, unsigned long long& neededVal){
            static unsigned long long curVal;
            curVal = m.GetValue();
            if(neededVal != 0 && curVal >= neededVal)
            {
                m -= neededVal;
                neededVal *= 1.2;
                b.IncreseIncValByVal(1);
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
    while (!WindowShouldClose())
    {
        BeginDrawing();
        if(mb != nullptr)
        {
            mb->check(*money);
            mb->Show();
        }
        if(money != nullptr)
        {
            money->Show();
        }
        butIter->Show();
        butIter->Click(*money, *mb);
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
    if(mb != nullptr)
    {
        delete mb;
        mb = nullptr;
    }
    if(money != nullptr)
    {
        delete money;
        money = nullptr;
    }
    return 0;
}
