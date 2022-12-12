//
// Created by colte on 11.12.2022.
//

#include <cmath>
#include "RadioButton.h"
#include "../utils/common.h"

namespace g9::menu_elements {
    RadioButton::RadioButton(Vector2 p, Vector2 s, short fontH)
    :
    posFElement(p),
    sizeElement(s),
    fontHeight(fontH)
    {
        radius = (sizeElement.y - 2*PADDING_RB_Y)/4;
    }

    void RadioButton::SetMap(std::map<const char *, bool>& m) {
        modes = m;
        values.clear();
        for (auto& el: modes) {
            values.push_back(el.second);
        }
    }

    void RadioButton::Show() {
        float offset = 0;
        for(auto& el: modes)
        {
            DrawCircleV({posFElement.x + PADDING_RB_X + radius, posFElement.y + PADDING_RB_Y + radius + offset},
                        radius, WHITE);
            DrawText(el.first, posFElement.x + PADDING_RB_X + 2*radius + PADDING_RB_BL,
                     posFElement.y + PADDING_RB_Y + sizeElement.y*0.1f + offset,
                     fontHeight,TEXT_COLOR);
            if(utils::IsDarkMode == el.second)
                DrawCircleV({posFElement.x + PADDING_RB_X + radius, posFElement.y + PADDING_RB_Y + radius + offset},
                            radius/2, BLACK);
            offset += sizeElement.y + PADDING_RB_BB;
        }
    }

    void RadioButton::Update(bool& isClicked) {
        static const float offsetSize = sizeElement.y + PADDING_RB_BB;
        static Vector2 mouse;
        static float offset, length;
        offset = 0;
        mouse = GetMousePosition();
        if(isClicked)
        {
            length = modes.size();
            for (int i = 0; i < length; i++) {
                if(pow(mouse.x - (posFElement.x + PADDING_RB_X + radius), 2)
                + pow(mouse.y - (posFElement.y + PADDING_RB_Y + radius + offset), 2) <= pow(radius, 2))
                {
                    utils::IsDarkMode = values[i];
                }
                offset += offsetSize;
            }
        }
    }
} // menu_elements