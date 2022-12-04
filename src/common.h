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

}

#endif //GAME9_COMMON_H
