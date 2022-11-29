//
// Created by Coltenus on 23.11.2022.
//

#ifndef GAME9_BUILDING_H
#define GAME9_BUILDING_H

#include <raylib.h>
#include <cmath>
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
        float speed;
        float moveOffset;
        float angle = 0;

    public:
        static int buildingsCount;
        Building(Vector2 p, Vector2 s, Color c, unsigned long long iv, Camera2D* cm, float sp, float mo)
        : pos(p), size(s), col(c), incVal(iv), cam(cm), speed(sp), moveOffset(mo) {}
        virtual ~Building() noexcept = default;
        [[nodiscard]] Vector2 GetPosition() {return pos;}
        [[nodiscard]] Vector2 GetSize() {return size;}
        [[nodiscard]] Color GetColor() {return col;}
        void SetColor(Color c) {col = c;}
        [[nodiscard]] unsigned long long GetIncomeValue() const {return incVal;}
        void IncreaseIncValByVal(unsigned long long val) {incVal += val;}
        void IncreaseIncVal(float val) {if(val >= 1) incVal *= val;}
        Camera2D* GetCamera() {return cam;}
        void check(Money& m) {
            static Vector2 mouse;
            mouse = GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
            && incVal > 0
            && mouse.x >= pos.x - cam->target.x + WIDTH && mouse.x <= pos.x + size.x - cam->target.x + WIDTH
            && mouse.y >= pos.y - cam->target.y + HEIGHT && mouse.y <= pos.y + size.y - cam->target.y + HEIGHT)
            {
                OnClick(m);
            }
        }
        virtual void OnClick(Money&) = 0;
        virtual void WhileExist(Money&) = 0;
        virtual void Show() {
            if(incVal > 0
               && pos.y + size.y >= cam->target.y - HEIGHT
               && pos.y <= cam->target.y)
                DrawRectangleV(pos, size, col);
        }
        void Move() {
            if(incVal > 0)
            {
                pos.x += speed * cos((1/moveOffset) * angle);
                pos.y += speed * sin(moveOffset * angle);
                angle += (0.0004 + moveOffset * 0.0013) * speed;
            }
        }
    };

} // g9

#endif //GAME9_BUILDING_H
