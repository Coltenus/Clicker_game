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
        while(isExist)
        {
            m += GetIncomeValue();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }

    SideBuilding::~SideBuilding() {
        isExist = false;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    SideBuilding::SideBuilding(Vector2 p, Vector2 s, Color c, unsigned long long iv, unsigned int _interval)
    : Building(p, s, c, iv), isExist(true), interval(_interval) {}
} // g9