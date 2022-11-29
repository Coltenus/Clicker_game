//
// Created by colte on 29.11.2022.
//

#ifndef GAME9_ACTIONS_H
#define GAME9_ACTIONS_H

#include "MainBuilding.h"
#include "SideBuilding.h"
#include "Button.h"

namespace g9 {

    void actionMB(g9::Money&, g9::Building&, unsigned long long&, unsigned long long&);
    void actionSB(g9::Money&, g9::Building&, unsigned long long&, unsigned long long&);

    void buttonL(const std::vector<Button>&,
            __gnu_cxx::__normal_iterator<g9::Button*, std::vector<g9::Button>>&);
    void buttonR(const std::vector<Button>&,
            __gnu_cxx::__normal_iterator<g9::Button*, std::vector<g9::Button>>&);

}
#endif //GAME9_ACTIONS_H
