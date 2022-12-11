//
// Created by colte on 11.12.2022.
//

#ifndef GAME9_TEXTFRAME_H
#define GAME9_TEXTFRAME_H

#include <string>
#include <raylib.h>
#include <vector>

namespace g9::menu_elements {
#define PADDING_X 5
#define PADDING_Y 5

        class TextFrame {
        private:
            std::vector<std::string> text;
            Vector2 pos, size;
            short fontHeight, maxLength, maxRowCount, fElement, rowCount;
            bool lineNeeded;

        public:
            TextFrame(const char*, Vector2, Vector2, short);
            TextFrame(const char*, Vector2, Vector2, short, bool);
            void Show();
            void Update();
        };

    } // menu_elements

#endif //GAME9_TEXTFRAME_H
