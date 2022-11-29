//
// Created by colte on 29.11.2022.
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

#define BUTTON_POS {1275, 50}
#define BUTTON_SIZE {300, 50}
#define BUTTON_TEXT_HEIGHT 20
#define BUILD_POS_X WIDTH / 2 - 50
#define MBUILD_SIZE {100, 100}
#define SBUILD_SIZE {120, 100}
#define BUILD_SPEED 6
#define MBUILD_OFFSET 2.5
#define SBUILD_OFFSET 2

namespace g9 {

    class BuildingsList
    {
    private:
        std::vector<Building*> list;
        std::vector<Button> buttons;
        int countOfElements;
        int countOfAElements;
        Camera2D* cam;
        Money* money;

    public:
        BuildingsList(Camera2D*, Money*);
        ~BuildingsList();
        __gnu_cxx::__normal_iterator<g9::Button*, std::vector<g9::Button>> GetFirstButton();
        Building* operator[](int);
        void Move();
        long long GetDistanceBetweenButtons(__gnu_cxx::__normal_iterator<g9::Button *, std::vector<g9::Button>>&);
        std::vector<Button>& GetButtons();
        void AddNewBuilding(std::vector<std::thread*>&,
                __gnu_cxx::__normal_iterator<g9::Button *, std::vector<g9::Button>>&);
        void Check();
        bool CheckZeroIV();
        void Show();
    };

} // g9

#endif //GAME9_BUILDINGSLIST_H
