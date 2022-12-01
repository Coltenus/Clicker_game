//
// Created by Coltenus on 23.11.2022.
//

#ifndef GAME9_MONEY_H
#define GAME9_MONEY_H

#include <raylib.h>
#include <string>

#if DEBUG
#define MONEY_VAL 2000000
#else
#define MONEY_VAL 0
#endif

namespace g9::game_objects {
        class Money {
        private:
            unsigned long long value;
            Vector2 pos;
            int height;

        public:
            Money(Vector2 p, int h) : value(MONEY_VAL), pos(p), height(h) {}
            void operator+=(unsigned long long v) {value += v;}
            void operator-=(unsigned long long v) {value -= v;}
            [[nodiscard]] unsigned long long GetValue() const {return value;}
            void Show() const;
        };
    } // g9

#endif //GAME9_MONEY_H
