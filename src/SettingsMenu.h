//
// Created by colte on 11.12.2022.
//

#ifndef GAME9_SETTINGSMENU_H
#define GAME9_SETTINGSMENU_H

#include "MenuOption.h"
#include "Button.h"

namespace g9 {

    class SettingsMenu : public MenuOption {
    private:
        g9::game_objects::Button *butBack;
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
    };

} // g9

#endif //GAME9_SETTINGSMENU_H
