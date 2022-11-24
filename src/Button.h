//
// Created by colte on 23.11.2022.
//

#ifndef GAME9_BUTTON_H
#define GAME9_BUTTON_H

#include <raylib.h>
#include <vector>
#include "Money.h"
#include "Building.h"

namespace g9 {

    class Button {
    private:
        Vector2 pos;
        Vector2 size;
        const char* text;
        int height;
        Color col;
        unsigned long long priceVal;
        void (*action1)(Money&, Building&, unsigned long long&);
        void (*action2)(const std::vector<Button>&, __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>&);

    public:
        Button(Vector2, Vector2, const char*, int, Color);
        Button(Vector2, Vector2, const char*, int, Color, unsigned long long);
        ~Button();
        void Show();
        void SetAction(void (*)(Money&, Building&, unsigned long long&));
        void SetAction(void (*)(const std::vector<Button>&,
                __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>&));
        void Click(Money&, Building&);
        void Click(const std::vector<Button>&, __gnu_cxx::__normal_iterator<Button*, std::vector<Button>>&) const;
    };

} // g9

#endif //GAME9_BUTTON_H
