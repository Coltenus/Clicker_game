//
// Created by colte on 24.11.2022.
//

#ifndef GAME9_SIDEBUILDING_H
#define GAME9_SIDEBUILDING_H

#include "Building.h"

namespace g9 {

    class SideBuilding : public Building {
    private:
        unsigned int interval;
        void OnClick(Money&) override;

    public:
        SideBuilding(Vector2, Vector2, Color, unsigned long long, unsigned int, Camera2D*, float, float);
        ~SideBuilding() override;
        void WhileExist(Money&) override;
        void Show() override;
    };

} // g9

#endif //GAME9_SIDEBUILDING_H
