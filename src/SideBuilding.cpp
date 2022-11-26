//
// Created by colte on 24.11.2022.
//

#include "SideBuilding.h"
#include <thread>

namespace g9 {
    void SideBuilding::OnClick(Money &) {

    }

    void SideBuilding::WhileExist(Money &m) {
        bool isActive = true;
        while (isActive)
        {
            if(GetIncomeValue() != 0)
                isActive = false;
        }
        while(true)
        {
            m += GetIncomeValue();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }

    SideBuilding::~SideBuilding() = default;

    SideBuilding::SideBuilding(Vector2 p, Vector2 s, Color c, unsigned long long iv, unsigned int _interval, Camera2D* cm)
    : Building(p, s, c, iv, cm), interval(_interval) {}
} // g9