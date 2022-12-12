//
// Created by Coltenus on 23.11.2022.
//

#ifndef GAME9_MONEY_H
#define GAME9_MONEY_H

#include <raylib.h>
#include <string>
#include "../utils/common.h"

namespace g9::game_objects {
        class Money {
        private:
            unsigned long long value;
            Vector2 pos;
            int height;

        public:
            Money(Vector2 p, int h) : value(MONEY_VAL), pos(p), height(h) {}
            Money(Vector2 p, int h, unsigned long long val) : value(val), pos(p), height(h) {}
            void operator+=(unsigned long long v) {value += v;}
            void operator-=(unsigned long long v) {value -= v;}
            [[nodiscard]] unsigned long long GetValue() const {return value;}
            void Show() const;
        };
    } // g9

#endif //GAME9_MONEY_H
