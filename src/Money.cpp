//
// Created by Coltenus on 23.11.2022.
//

#include "Money.h"

namespace g9 {
    void Money::Show() const {
        DrawEllipse(pos.x+height/4, pos.y+height/2, height/4, height/2, YELLOW);
        DrawText(std::to_string(value).c_str(),
                 pos.x + height/2 + 5, pos.y, height, BLACK);
    }
} // g9