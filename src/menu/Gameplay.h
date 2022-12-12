//
// Created by Coltenus on 02.12.2022.
//

#ifndef GAME9_GAMEPLAY_H
#define GAME9_GAMEPLAY_H

#include "../game_objects.h"
#include "MenuOption.h"

namespace g9 {

    class Gameplay : public MenuOption {
    private:
        game_objects::Money* money;
        BuildingsList* bl;
        __gnu_cxx::__normal_iterator<game_objects::Button *, std::vector<game_objects::Button>>* butIter;
        game_objects::Button *butP, *butN;
        game_objects::Button *butBack;
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
