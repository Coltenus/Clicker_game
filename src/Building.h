//
// Created by colte on 23.11.2022.
//

#ifndef GAME9_BUILDING_H
#define GAME9_BUILDING_H

#include <raylib.h>
#include <math.h>
#include "Money.h"
#include "common.h"

namespace g9 {

    class Building {
    private:
        Vector2 pos;
        Vector2 size;
        Color col;
        unsigned long long incVal;
        Camera2D* cam;
        float angle = 0;

    public:
        Building(Vector2 p, Vector2 s, Color c, unsigned long long iv, Camera2D* cm)
        : pos(p), size(s), col(c), incVal(iv), cam(cm) {}
        virtual ~Building() noexcept = default;
        [[nodiscard]] Vector2 GetPosition() {return pos;}
        [[nodiscard]] Vector2 GetSize() {return size;}
        [[nodiscard]] Color GetColor() {return col;}
        void SetColor(Color c) {col = c;}
        [[nodiscard]] unsigned long long GetIncomeValue() const {return incVal;}
        void IncreaseIncValByVal(unsigned long long val) {incVal += val;}
        void check(Money& m) {
            static Vector2 mouse;
            mouse = GetMousePosition();
            if(incVal > 0
            && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
            && mouse.x >= pos.x - cam->target.x + WIDTH && mouse.x <= pos.x + size.x - cam->target.x + WIDTH
            && mouse.y >= pos.y - cam->target.y + HEIGHT && mouse.y <= pos.y + size.y - cam->target.y + HEIGHT)
            {
                OnClick(m);
            }
        }
        virtual void OnClick(Money&) = 0;
        virtual void WhileExist(Money&) = 0;
        void Show() {
            if(incVal > 0)
                DrawRectangleV(pos, size, col);
        }
        void Move(float speed, float moveOffset) {
            if(incVal > 0)
            {
                pos.x += speed * cos((1/moveOffset) * angle);
                pos.y += speed * sin(moveOffset * angle);
                angle += (0.003 + (moveOffset - 2) * 0.0013) * speed;
            }
        }
    };

} // g9

#endif //GAME9_BUILDING_H
