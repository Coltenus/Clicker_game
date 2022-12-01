//
// Created by Coltenus on 23.11.2022.
//

#include "MainBuilding.h"

namespace g9::game_objects {
        void MainBuilding::OnClick(Money &m) {
            m += GetIncomeValue();
        }

        MainBuilding::MainBuilding(Vector2 p, Vector2 s, Color c, unsigned long long iv, Camera2D* cm, float sp, float mo)
                : Building(p, s, c, iv, cm, sp, mo) {}

        void MainBuilding::WhileExist(Money &) {

        }

        void MainBuilding::Show() {
            if(GetIncomeValue() > 0
               && GetPosition().y + GetSize().y >= GetCamera()->target.y - HEIGHT
               && GetPosition().y <= GetCamera()->target.y)
            {
                DrawRectangleV(GetPosition(), GetSize(), GetColor());
                DrawText(TextFormat("%d/click", GetIncomeValue()), GetPosition().x + GetSize().x/16,
                         GetPosition().y + GetSize().y*44/100, GetSize().y/9, WHITE);
            }
        }

        MainBuilding::~MainBuilding() {};
    } // g9