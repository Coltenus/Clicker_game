//
// Created by colte on 23.11.2022.
//

#include "Button.h"

namespace g9 {
    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, Camera2D* cm) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(0), cam(cm), action1(nullptr), action2(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, Camera2D* cm, unsigned long long int pV) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(pV), cam(cm), action1(nullptr), action2(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(0), cam(nullptr), action1(nullptr), action2(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, unsigned long long int pV) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(pV), cam(nullptr), action1(nullptr), action2(nullptr) {}

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
        static bool wasZero;
        static std::string bufStr = "";
        static Vector2 offset;
        if (cam != nullptr)
            offset = {cam->target.x - WIDTH, cam->target.y - HEIGHT};
        else
            offset = {0, 0};
        wasZero = false;
        if(b.GetIncomeValue() == 0)
            wasZero = true;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= pos.x - offset.x && mouse.x <= pos.x + size.x - offset.x
           && mouse.y >= pos.y - offset.y && mouse.y <= pos.y + size.y - offset.y)
        {
            action1(m, b, priceVal);
        }
        if(wasZero && b.GetIncomeValue() != 0)
        {
            bufStr = text;
            text = bufStr.replace(bufStr.begin(), bufStr.begin()+3, "Upgrade").c_str();
        }
    }

    void Button::Click(const std::vector<Button>& vec,
                       __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>& iter) const {
        static Vector2 mouse;
        static Vector2 offset;
        if (cam != nullptr)
            offset = {cam->target.x - WIDTH, cam->target.y - HEIGHT};
        else
            offset = {0, 0};
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= pos.x - offset.x && mouse.x <= pos.x + size.x - offset.x
           && mouse.y >= pos.y - offset.y && mouse.y <= pos.y + size.y - offset.y)
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