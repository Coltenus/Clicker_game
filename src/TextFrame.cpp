//
// Created by colte on 11.12.2022.
//

#include "TextFrame.h"

namespace g9::menu_elements {
        TextFrame::TextFrame(const char *t, Vector2 p, Vector2 s, short fontH)
        :
        pos(p),
        size(s),
        fontHeight(fontH),
        fElement(0),
        lineNeeded(false)
        {
            short offset = 0;
            short length = 0;
            while (t[length] != '\0')
            {
                length++;
            }
            maxLength = (size.x - 2 * PADDING_X) / (fontHeight * 0.6f);
            maxRowCount = (size.y - 2 * PADDING_Y) / (fontHeight + 2);
            for (int i = 0, r = -1; i < length; i++) {
                if(t[i] == '\n')
                {
                    text.push_back(std::string());
                    r++;
                    offset += (i-offset) % maxLength;
                }
                else if((i-offset) % maxLength == 0)
                {
                    text.push_back(std::string() + t[i]);
                    r++;
                }
                else
                {
                    text[r] += t[i];
                }
            }
            rowCount = text.size();
        }

        TextFrame::TextFrame(const char *t, Vector2 p, Vector2 s, short fontH, bool lN)
        :
        TextFrame(t, p, s, fontH)
        {
            lineNeeded = lN;
        }

        void TextFrame::Show() {
            static short lElement;
            lElement = fElement + maxRowCount;
            if(lineNeeded)
                DrawRectangleLines(pos.x, pos.y, size.x, size.y, BLACK);
            for (int i = fElement; i < rowCount && i < lElement; i++) {
                DrawText(text[i].c_str(),
                         pos.x + PADDING_X,
                         pos.y + PADDING_Y + (i-fElement) * (fontHeight + 2),
                         fontHeight,
                         BLACK);
            }
        }

        void TextFrame::Update() {
            static float buf;
            if(lineNeeded && rowCount > maxRowCount && (buf = GetMouseWheelMove()) != 0)
            {
                if(buf > 0 && fElement > 0)
                    fElement--;
                else if(buf < 0 && fElement + maxRowCount < (short)text.size())
                    fElement++;
            }
        }
    } // menu_elements