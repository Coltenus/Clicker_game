//
// Created by Coltenus on 23.11.2022.
//

#include "Button.h"
#include <thread>

namespace g9::game_objects {
    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, Camera2D* cm) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(0), startIV(0), cam(cm), action1(nullptr), action2(nullptr),
    action3(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, Camera2D* cm, unsigned long long int pV, unsigned long long int stIV)
    : pos(p), size(s), text(t), height(h), col(c), priceVal(pV), startIV(stIV), cam(cm), action1(nullptr), action2(nullptr),
    action3(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(0), startIV(0), cam(nullptr), action1(nullptr), action2(nullptr),
    action3(nullptr) {}

    Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, unsigned long long int pV, unsigned long long int stIV) : pos(p),
    size(s), text(t), height(h), col(c), priceVal(pV), startIV(stIV), cam(nullptr), action1(nullptr), action2(nullptr),
    action3(nullptr) {}

    Button::~Button() {
        action1 = nullptr;
        action2 = nullptr;
        action3 = nullptr;
    }

    void Button::Show() {
        DrawRectangleV(pos, size, col);
        if(priceVal != 0)
            DrawText(TextFormat("%s(%d)", text.c_str(), priceVal),
                     pos.x + size.x/16, pos.y + size.y/2 - height/2, height, TEXT_COLOR);
        else
            DrawText(text.c_str(), pos.x + size.x/16, pos.y + size.y/2 - height/2, height, TEXT_COLOR);
    }

    void Button::SetPrice(unsigned long long int val, bool isLast) {
        priceVal = val;
        if(!isLast && text.starts_with("Buy")) {
            text.replace(text.begin(), text.begin() + 3, "Upgrade");
        }
    }

    unsigned long long Button::GetPrice() {
        return priceVal;
    }

    void Button::Click(Money &m, Building &b) {
        static Vector2 mouse;
        static bool wasZero;
        static std::string bufStr;
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
            action1(m, b, priceVal, startIV);
        }
        if(wasZero && b.GetIncomeValue() != 0)
        {
            text.replace(text.begin(), text.begin()+3, "Upgrade");
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

    void Button::SetAction(void (*act)(Money &, Building &, unsigned long long &, unsigned long long &)) {
        action1 = act;
    }

    void Button::SetAction(void (*act)(const std::vector<Button> &,
                    __gnu_cxx::__normal_iterator<Button *, std::vector<Button>> &)) {
        action2 = act;
    }

    void Button::SetAction(void (*act)(utils::MenuSelections &)) {
        action3 = act;
    }

    void Button::Click(utils::MenuSelections &mo, bool& st) {
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
            action3(mo);
            st = false;
        }
    }
} // g9