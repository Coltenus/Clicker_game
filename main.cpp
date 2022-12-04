#include <raylib.h>
#include <thread>
#include "src/common.h"
#include "src/Money.h"
#include "src/Button.h"
#include "src/BuildingsList.h"
#include "src/Saves.h"
#include "src/Gameplay.h"
#include "src/MainMenu.h"

g9::BuildingsList* g9::BuildingsList::object = nullptr;
g9::utils::Saves* g9::utils::Saves::object = nullptr;
g9::Gameplay* g9::Gameplay::object = nullptr;
g9::MainMenu* g9::MainMenu::object = nullptr;

int main() {
    setbuf(stdout, nullptr);
    auto* sv = g9::utils::Saves::CreateSaves();
    sv->AddSave(5, false);
    bool isShouldExit = false;
    g9::utils::MenuSelections menu_opt = g9::utils::MAIN_MENU;
    InitWindow(WIDTH, HEIGHT, "Moving buildings");
    SetTargetFPS(60);
    Image icon = LoadImage("res/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    std::vector<std::thread*> existingThreads;
    g9::MenuOption* mo = g9::MainMenu::CreateMainMenu(&existingThreads, &isShouldExit, &menu_opt);
    auto changeOption = [&]() {
        switch (menu_opt) {
            case g9::utils::MAIN_MENU:
                delete mo;
                mo = g9::MainMenu::CreateMainMenu(&existingThreads, &isShouldExit, &menu_opt);
                break;
            case g9::utils::GAMEPLAY:
                delete mo;
                mo = g9::Gameplay::CreateGameplay(&existingThreads, &isShouldExit, &menu_opt);
                sv->PullSettings(*mo);
                break;
            case g9::utils::SETTINGS:
                break;
            case g9::utils::CREDITS:
                break;
            case g9::utils::EXIT:
                isShouldExit = true;
                break;
        }
    };
    while (!isShouldExit)
    {
        mo->Update();
        if(!mo->GetStatus())
            changeOption();
        if(WindowShouldClose())
            isShouldExit = true;
    }
    CloseWindow();
    if(sv != nullptr)
    {
        delete sv;
        sv = nullptr;
    }
    if(mo != nullptr)
    {
        delete mo;
        mo = nullptr;
    }
    existingThreads.erase(existingThreads.begin(), existingThreads.end());
    return 0;
}
