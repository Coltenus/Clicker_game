//
// Created by Coltenus on 11.12.2022.
//

#ifndef GAME9_CREDITSMENU_H
#define GAME9_CREDITSMENU_H

#include "MenuOption.h"
#include "../game_objects/Button.h"
#include "../menu_elements/TextFrame.h"

namespace g9 {

    class CreditsMenu : public MenuOption {
    private:
        game_objects::Button *butBack;
        menu_elements::TextFrame *creditsLabel, *descriptionLabel;
        explicit CreditsMenu(std::vector<std::thread*>*,
        bool*,
        utils::MenuSelections*);

    public:
        static CreditsMenu* object;
        static CreditsMenu* CreateCreditsMenu(std::vector<std::thread*>*,
                                                bool*,
                                                utils::MenuSelections*);
        ~CreditsMenu() override;
        CreditsMenu(CreditsMenu&) = delete;
        void operator=(CreditsMenu&) = delete;

        void Update() override;
    };

} // g9

#endif //GAME9_CREDITSMENU_H
