//
// Created by colte on 11.12.2022.
//

#ifndef GAME9_RADIOBUTTON_H
#define GAME9_RADIOBUTTON_H

#include <raylib.h>
#include <map>
#include <string>
#include <vector>

namespace g9::menu_elements {
#define PADDING_RB_X 2
#define PADDING_RB_Y 2
#define PADDING_RB_BL 20
#define PADDING_RB_BB 10

        class RadioButton {
        private:
            std::vector<bool> values;
            std::map<const char*, bool> modes;
            Vector2 posFElement, sizeElement;
            short fontHeight, radius;

        public:
            RadioButton(Vector2, Vector2, short);
            void SetMap(std::map<const char*, bool>&);
            void Show();
            void Update(bool&);
        };

    } // menu_elements

#endif //GAME9_RADIOBUTTON_H
