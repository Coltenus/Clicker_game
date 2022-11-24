//
// Created by colte on 23.11.2022.
//

#ifndef GAME9_MONEY_H
#define GAME9_MONEY_H

#include <raylib.h>
#include <string>

namespace g9 {

    class Money {
    private:
        unsigned long long value;
        Vector2 pos;
        int height;

    public:
        Money(Vector2 p, int h) : value(0), pos(p), height(h) {}
        void operator+=(unsigned long long v) {value += v;}
        void operator-=(unsigned long long v) {value -= v;}
        unsigned long long GetValue() {return value;}
        void Show() {
            DrawEllipse(pos.x+height/4, pos.y+height/2, height/4, height/2, YELLOW);
            DrawText(std::to_string(value).c_str(),
                     pos.x + height/2 + 5, pos.y, height, BLACK);
        }
    };

} // g9

#endif //GAME9_MONEY_H
