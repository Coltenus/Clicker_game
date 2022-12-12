//
// Created by Coltenus on 26.11.2022.
//

#ifndef GAME9_COMMON_H
#define GAME9_COMMON_H

namespace g9::utils {
#define WIDTH 1600
#define HEIGHT 900
#if DEBUG
#define MONEY_VAL 2000000
#else
#define MONEY_VAL 0
#endif

    enum MenuSelections : unsigned char {
        GAMEPLAY = 1,
        MAIN_MENU,
        SETTINGS,
        CREDITS,
        EXIT
    };

    extern bool IsDarkMode;

#define BG_MENU ((g9::utils::IsDarkMode) ? DARKGRAY : LIGHTGRAY)
#define BTN_MENU GRAY
#define TEXT_COLOR ((g9::utils::IsDarkMode) ? WHITE : BLACK)
#define BG_GP ((g9::utils::IsDarkMode) ? DARKBLUE : GREEN)

}

#endif //GAME9_COMMON_H
