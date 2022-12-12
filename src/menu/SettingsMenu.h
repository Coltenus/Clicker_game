//
// Created by Coltenus on 11.12.2022.
//

#ifndef GAME9_SETTINGSMENU_H
#define GAME9_SETTINGSMENU_H

#include "MenuOption.h"
#include "../game_objects/Button.h"
#include "../menu_elements.h"
#include "../utils/Saves.h"

namespace g9 {

    class SettingsMenu : public MenuOption {
    private:
        game_objects::Button *butBack;
        menu_elements::SelectionForm *savingsSelect;
        menu_elements::RadioButton *darkMode;
        explicit SettingsMenu(std::vector<std::thread*>*,
        bool*,
        utils::MenuSelections*);

    public:
        static SettingsMenu* object;
        static SettingsMenu* CreateSettingsMenu(std::vector<std::thread*>*,
                                        bool*,
                                        utils::MenuSelections*);
        ~SettingsMenu() override;
        SettingsMenu(SettingsMenu&) = delete;
        void operator=(SettingsMenu&) = delete;

        void Update() override;
        void SetGlobalData(utils::Saves::GlobalData*);
    };

} // g9

#endif //GAME9_SETTINGSMENU_H
