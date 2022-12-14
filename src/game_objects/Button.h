//
// Created by Coltenus on 23.11.2022.
//

#ifndef GAME9_BUTTON_H
#define GAME9_BUTTON_H

#include <raylib.h>
#include <vector>
#include "Money.h"
#include "Building.h"
#include "../utils/common.h"

namespace g9::game_objects {
        class Button {
        private:
            Vector2 pos;
            Vector2 size;
            std::string text;
            int height;
            Color col;
            unsigned long long priceVal;
            unsigned long long startIV;
            Camera2D* cam;
            void (*action1)(Money&, Building&, unsigned long long&, unsigned long long&);
            void (*action2)(const std::vector<Button>&, __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>&);
            void (*action3)(utils::MenuSelections&);

        public:
            Button(Vector2, Vector2, const char*, int, Color, Camera2D*);
            Button(Vector2, Vector2, const char*, int, Color, Camera2D*, unsigned long long, unsigned long long);
            Button(Vector2, Vector2, const char*, int, Color);
            Button(Vector2, Vector2, const char*, int, Color, unsigned long long, unsigned long long);
            ~Button();
            void Show();
            void SetPrice(unsigned long long, bool);
            unsigned long long GetPrice();
            void SetAction(void (*)(Money&, Building&, unsigned long long&, unsigned long long&));
            void SetAction(void (*)(const std::vector<Button>&,
                                    __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>&));
            void SetAction(void (*)(utils::MenuSelections&));
            void Click(Money&, Building&);
            void Click(const std::vector<Button>&, __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>&) const;
            void Click(utils::MenuSelections&, bool&);
        };
    } // g9

#endif //GAME9_BUTTON_H
