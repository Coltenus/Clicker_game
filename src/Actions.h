//
// Created by Coltenus on 29.11.2022.
//

#ifndef GAME9_ACTIONS_H
#define GAME9_ACTIONS_H

#include "MainBuilding.h"
#include "SideBuilding.h"
#include "Button.h"

namespace g9::actions {

    void actionMB(game_objects::Money&, game_objects::Building&, unsigned long long&, unsigned long long&);
    void actionSB(game_objects::Money&, game_objects::Building&, unsigned long long&, unsigned long long&);

    void buttonL(const std::vector<game_objects::Button>&,
            __gnu_cxx::__normal_iterator<game_objects::Button*, std::vector<game_objects::Button>>&);
    void buttonR(const std::vector<game_objects::Button>&,
            __gnu_cxx::__normal_iterator<game_objects::Button*, std::vector<game_objects::Button>>&);

}
#endif //GAME9_ACTIONS_H
