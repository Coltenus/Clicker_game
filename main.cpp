#include <raylib.h>
#include <thread>
#include "src/common.h"
#include "src/Money.h"
#include "src/Button.h"
#include "src/Actions.h"
#include "src/BuildingsList.h"

g9::BuildingsList* g9::BuildingsList::object = nullptr;

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
    auto* money = new g9::game_objects::Money({20, 20}, 40);
    auto* bl = g9::BuildingsList::CreateList(&cam, money);
    auto butIter = bl->GetFirstButton();
    auto* butP = new g9::game_objects::Button({1325, 120}, {50, 50}, "<=", 20, BLUE);
    butP->SetAction(g9::actions::buttonL);
    auto* butN = new g9::game_objects::Button({1475, 120}, {50, 50}, "=>", 20, BLUE);
    butN->SetAction(g9::actions::buttonR);
    std::vector<std::thread*> existingThreads;
    auto* existingThread = new std::thread([&bl, &money](){
        (*bl)[1]->WhileExist(*money);
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = new std::thread([&bl, &isShouldExit](){
        while (!isShouldExit)
        {
            bl->Move();
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
            butIter->Click(*money, *(*bl)[bl->GetDistanceBetweenButtons(butIter)]);
            butN->Click(bl->GetButtons(), butIter);
            butP->Click(bl->GetButtons(), butIter);
            bl->Check();
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    });
    existingThread->detach();
    existingThreads.push_back(existingThread);
    existingThread = nullptr;
    while (!isShouldExit)
    {
        if(bl->CheckZeroIV())
        {
            bl->AddNewBuilding(existingThreads, butIter);
        }
        BeginDrawing();
        ClearBackground(GREEN);
        BeginMode2D(cam);
        bl->Show();
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
    existingThreads.erase(existingThreads.begin(), existingThreads.end());
    if(bl != nullptr)
    {
        delete bl;
        bl = nullptr;
    }
    return 0;
}
