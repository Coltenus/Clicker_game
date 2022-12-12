//
// Created by Coltenus on 11.12.2022.
//

#ifndef GAME9_SELECTIONFORM_H
#define GAME9_SELECTIONFORM_H

#include <string>
#include <raylib.h>
#include <vector>
#include "../utils/Saves.h"

namespace g9::menu_elements {
#define PADDING_SF_X 5
#define PADDING_SF_Y 5
#define PADDING_SF_B1L 10
#define PADDING_SF_LB2 10
#define PADDING_SF_B2B3 10
#define PADDING_SF_LI 10
#define PADDING_SF_IN_X (2*PADDING_SF_X + PADDING_SF_B1L + PADDING_SF_LB2 + PADDING_SF_B2B3)
#define PADDING_SF_IN_Y (2*PADDING_SF_Y + PADDING_SF_LI)

        class SelectionForm {
        private:
            Vector2 pos, size, posB1, sizeB1, posLabel, sizeLabel, posB2, sizeB2,
            posB3, sizeB3, posInput, sizeInput, posB4, sizeB4, posB5, sizeB5;
            short fontHeight, currentSaving;
            bool needAddSaving;
            utils::Saves::GlobalData* gd;
            std::string buffer;
            SelectionForm(Vector2, Vector2, short);

        public:
            static SelectionForm* CreateSelectionForm(Vector2, Vector2, short);
            ~SelectionForm() = default;
            void Show();
            void Update(bool&);
            void SetGlobalData(utils::Saves::GlobalData*);
            static inline bool CheckMouseOnButton(Vector2, Vector2, Vector2);
        };

    } // menu_elements

#endif //GAME9_SELECTIONFORM_H
