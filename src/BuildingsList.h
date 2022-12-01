//
// Created by Coltenus on 29.11.2022.
//

#ifndef GAME9_BUILDINGSLIST_H
#define GAME9_BUILDINGSLIST_H

#include <raylib.h>
#include <vector>
#include <thread>
#include "Building.h"
#include "Button.h"
#include "Actions.h"
#include "Money.h"

namespace g9 {

#define BUTTON_POS {1275, 50}
#define BUTTON_SIZE {300, 50}
#define BUTTON_TEXT_HEIGHT 20
#define BUILD_POS_X (WIDTH / 2 - 50)
#define MBUILD_SIZE {100, 100}
#define SBUILD_SIZE {120, 100}
#define BUILD_SPEED 6
#define MBUILD_OFFSET 2.5
#define SBUILD_OFFSET 2

    class BuildingsList
    {
    private:
        std::vector<game_objects::Building*> list;
        std::vector<game_objects::Button> buttons;
        int countOfElements;
        Camera2D* cam;
        game_objects::Money* money;
        BuildingsList(Camera2D*, game_objects::Money*);

    public:
        BuildingsList(BuildingsList&) = delete;
        void operator=(BuildingsList&) = delete;
        ~BuildingsList();
        static BuildingsList* object;
        static BuildingsList* CreateList(Camera2D*, game_objects::Money*);
        __gnu_cxx::__normal_iterator<game_objects::Button*, std::vector<game_objects::Button>> GetFirstButton();
        game_objects::Building* operator[](int);
        void Move();
        long long GetDistanceBetweenButtons(__gnu_cxx::__normal_iterator<game_objects::Button *,
                                            std::vector<game_objects::Button>>&);
        std::vector<game_objects::Button>& GetButtons();
        void AddNewBuilding(std::vector<std::thread*>&,
                __gnu_cxx::__normal_iterator<game_objects::Button *, std::vector<game_objects::Button>>&);
        void Check();
        bool CheckZeroIV();
        void Show();
    };

} // g9

#endif //GAME9_BUILDINGSLIST_H
