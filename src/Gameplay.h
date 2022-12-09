//
// Created by colte on 02.12.2022.
//

#ifndef GAME9_GAMEPLAY_H
#define GAME9_GAMEPLAY_H

#include "Money.h"
#include "BuildingsList.h"
#include "Button.h"
#include "MenuOption.h"

namespace g9 {

    class Gameplay : public MenuOption {
    private:
        g9::game_objects::Money* money;
        g9::BuildingsList* bl;
        __gnu_cxx::__normal_iterator<game_objects::Button *, std::vector<game_objects::Button>>* butIter;
        g9::game_objects::Button *butP, *butN;
        g9::game_objects::Button *butBack;
        explicit Gameplay(std::vector<std::thread*>*,
                          bool*,
                          utils::MenuSelections*);
        Gameplay(std::vector<std::thread*>*,
                 bool*,
                 utils::MenuSelections*,
                 unsigned long long,
                 int,
                 std::vector<unsigned long long>&,
                 std::vector<unsigned long long>&);

    public:
        static Gameplay* object;
        static Gameplay* CreateGameplay(std::vector<std::thread*>*,
                                        bool*,
                                        utils::MenuSelections*);
        static Gameplay* CreateGameplay(std::vector<std::thread*>*,
                                        bool*,
                                        utils::MenuSelections*,
                                        unsigned long long,
                                        int,
                                        std::vector<unsigned long long>&,
                                        std::vector<unsigned long long>&);
        ~Gameplay() override;
        Gameplay(Gameplay&) = delete;
        void operator=(Gameplay&) = delete;

        void Update() override;
        unsigned long long GetMoney();
        int GetActBuildings();
        std::vector<unsigned long long> GetIncValues();
        std::vector<unsigned long long> GetUpdatePrices();
    };

} // g9

#endif //GAME9_GAMEPLAY_H
