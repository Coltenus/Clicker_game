//
// Created by Coltenus on 24.11.2022.
//

#include "SideBuilding.h"
#include <thread>

namespace g9::game_objects {
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

        SideBuilding::~SideBuilding() {};

        SideBuilding::SideBuilding(Vector2 p, Vector2 s, Color c, unsigned long long iv, unsigned int _interval, Camera2D* cm,
                                   float sp, float mo) : Building(p, s, c, iv, cm, sp, mo), interval(_interval) {}

        void SideBuilding::Show() {
            if(GetIncomeValue() > 0
               && GetPosition().y + GetSize().y >= GetCamera()->target.y - HEIGHT
               && GetPosition().y <= GetCamera()->target.y)
            {
                DrawRectangleV(GetPosition(), GetSize(), GetColor());
                DrawText(TextFormat("%d/%4.2f second(s)", GetIncomeValue(), (float)interval/1000), GetPosition().x + GetSize().x/16,
                         GetPosition().y + GetSize().y*44/100, GetSize().y/9, WHITE);
            }
        }
    } // g9