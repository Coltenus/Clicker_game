//
// Created by colte on 23.11.2022.
//

#ifndef GAME9_MAINBUILDING_H
#define GAME9_MAINBUILDING_H

#include "Building.h"

namespace g9 {

    class MainBuilding : public Building{
    private:
        void OnClick(Money&) override;

    public:
        MainBuilding(Vector2, Vector2, Color, unsigned long long);
        ~MainBuilding() override = default;
    };

} // g9

#endif //GAME9_MAINBUILDING_H
