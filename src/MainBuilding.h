//
// Created by Coltenus on 23.11.2022.
//

#ifndef GAME9_MAINBUILDING_H
#define GAME9_MAINBUILDING_H

#include "Building.h"

namespace g9 {

    class MainBuilding : public Building{
    private:
        void OnClick(Money&) override;
        void WhileExist(Money&) override;

    public:
        MainBuilding(Vector2, Vector2, Color, unsigned long long, Camera2D*, float, float);
        ~MainBuilding() override;
        void Show() override;
    };



} // g9

#endif //GAME9_MAINBUILDING_H
