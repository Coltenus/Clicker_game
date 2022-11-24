//
// Created by colte on 23.11.2022.
//

#ifndef GAME9_BUILDING_H
#define GAME9_BUILDING_H

#include <raylib.h>
#include "Money.h"

namespace g9 {

    class Building {
    private:
        Vector2 pos;
        Vector2 size;
        Color col;
        unsigned long long incVal;

    public:
        Building(Vector2 p, Vector2 s, Color c, unsigned long long iv) : pos(p), size(s), col(c), incVal(iv) {}
        virtual ~Building() = default;
        [[nodiscard]] Vector2 GetPosition() {return pos;}
        [[nodiscard]] Vector2 GetSize() {return size;}
        [[nodiscard]] Color GetColor() {return col;}
        void SetColor(Color c) {col = c;}
        [[nodiscard]] unsigned long long GetIncomeValue() const {return incVal;}
        void IncreseIncValByVal(unsigned long long val) {incVal += val;}
        void check(Money& m) {
            static Vector2 mouse;
            mouse = GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
            && mouse.x >= pos.x && mouse.x <= pos.x + size.x
            && mouse.y >= pos.y && mouse.y <= pos.y + size.y)
            {
                OnClick(m);
            }
        }
        virtual void OnClick(Money&) = 0;
        void Show() {
            DrawRectangleV(pos, size, col);
        }
    };

} // g9

#endif //GAME9_BUILDING_H
