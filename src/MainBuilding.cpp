//
// Created by colte on 23.11.2022.
//

#include "MainBuilding.h"

namespace g9 {
    void MainBuilding::OnClick(Money &m) {
        m += GetIncomeValue();
    }

    MainBuilding::MainBuilding(Vector2 p, Vector2 s, Color c, unsigned long long iv, Camera2D* cm)
    : Building(p, s, c, iv, cm) {}

    void MainBuilding::WhileExist(Money &) {

    }

    MainBuilding::~MainBuilding() = default;
} // g9