//
// Created by colte on 23.11.2022.
//

#include "Button.h"

namespace g9 {
    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(0), action1(nullptr), action2(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, unsigned long long int pV) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(pV), action1(nullptr), action2(nullptr) {}

    Button::~Button() {
        action1 = nullptr;
        action2 = nullptr;
    }

    void Button::Show() {
        DrawRectangleV(pos, size, col);
        if(priceVal != 0)
            DrawText(TextFormat("%s(%d)", text, priceVal),
                     pos.x + size.x/16, pos.y + size.y/2 - height/2, height, BLACK);
        else
            DrawText(text, pos.x + size.x/16, pos.y + size.y/2 - height/2, height, BLACK);
    }

    void Button::Click(Money &m, Building &b) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= pos.x && mouse.x <= pos.x + size.x
           && mouse.y >= pos.y && mouse.y <= pos.y + size.y)
        {
            action1(m, b, priceVal);
        }
    }

    void Button::Click(const std::vector<Button>& vec,
                       __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>& iter) const {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= pos.x && mouse.x <= pos.x + size.x
           && mouse.y >= pos.y && mouse.y <= pos.y + size.y)
        {
            action2(vec, iter);
        }
    }

    void Button::SetAction(void (*act)(Money &, Building &, unsigned long long &)) {
        action1 = act;
    }

    void Button::SetAction(void (*act)(const std::vector<Button> &,
                    __gnu_cxx::__normal_iterator<Button *, std::vector<Button>> &)) {
        action2 = act;
    }
} // g9