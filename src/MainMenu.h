//
// Created by colte on 02.12.2022.
//

#ifndef GAME9_MAINMENU_H
#define GAME9_MAINMENU_H

#include "MenuOption.h"
#include "Button.h"

namespace g9 {

    class MainMenu : public MenuOption {
    private:
        game_objects::Button *butStart, *butSettings, *butCredits, *butExit;
        explicit MainMenu(std::vector<std::thread*>*,
                          bool*,
                          utils::MenuSelections*);

    public:
        static MainMenu* object;
        static MainMenu* CreateMainMenu(std::vector<std::thread*>*,
                                        bool*,
                                        utils::MenuSelections*);
        ~MainMenu() override;
        MainMenu(MainMenu&) = delete;
        void operator=(MainMenu&) = delete;

        void Update() override;
    };

} // g9

#endif //GAME9_MAINMENU_H
