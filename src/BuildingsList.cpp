//
// Created by colte on 29.11.2022.
//

#include "BuildingsList.h"
#include "MainBuilding.h"
#include "SideBuilding.h"

namespace g9 {
    BuildingsList::BuildingsList(Camera2D* c, Money* m) : countOfElements(2), countOfAElements(1), cam(c), money(m) {
        list = {};
        list.push_back(new MainBuilding({BUILD_POS_X, HEIGHT / 2 - 200}, MBUILD_SIZE, DARKBROWN, 1, cam, BUILD_SPEED, MBUILD_OFFSET));
        list.push_back(new SideBuilding({BUILD_POS_X, HEIGHT / 2 + 300}, SBUILD_SIZE, VIOLET, 0, 5000, cam, BUILD_SPEED, 2));
        buttons = {};
        buttons.push_back(Button(BUTTON_POS, BUTTON_SIZE, "Upgrade Main Building", BUTTON_TEXT_HEIGHT, RED, 25, 0));
        buttons.push_back(Button(BUTTON_POS, BUTTON_SIZE, "Buy Side Building", BUTTON_TEXT_HEIGHT, RED, 40, 2));
        buttons[0].SetAction(actionMB);
        buttons[1].SetAction(actionSB);
    }

    BuildingsList::~BuildingsList() {
        list.erase(list.cbegin(), list.end());
        buttons.erase(buttons.cbegin(), buttons.end());
        cam = nullptr;
        money = nullptr;
    }

    __gnu_cxx::__normal_iterator<g9::Button *, std::vector<g9::Button>> BuildingsList::GetFirstButton() {
        return buttons.begin();
    }

    Building *BuildingsList::operator[](int el) {
        return list[el];
    }

    void BuildingsList::Move() {
        for(auto& el: list)
            el->Move();
    }

    long long BuildingsList::GetDistanceBetweenButtons(__gnu_cxx::__normal_iterator<g9::Button *,
                                                       std::vector<g9::Button>>& butIter) {
        return std::distance(buttons.begin(), butIter);
    }

    std::vector<Button> &BuildingsList::GetButtons() {
        return buttons;
    }

    void BuildingsList::AddNewBuilding(std::vector<std::thread*>& eTs,
                                       __gnu_cxx::__normal_iterator<g9::Button *, std::vector<g9::Button>>& bI) {
        countOfElements++;
        if(countOfElements%5 == 0) {
            list.push_back(
                    new MainBuilding({BUILD_POS_X, HEIGHT / 2 - 100 + 450.f * countOfElements},
                                         MBUILD_SIZE, DARKBROWN, 0, cam, BUILD_SPEED, MBUILD_OFFSET)
            );
            buttons.push_back(
                    g9::Button(BUTTON_POS, BUTTON_SIZE, "Buy Main Building", BUTTON_TEXT_HEIGHT, RED,
                               15 * pow(4, countOfElements),
                               pow(4, countOfElements)/2)
            );
            buttons[countOfElements-1].SetAction(actionMB);
        }
        else {
            list.push_back(
                    new SideBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 100 + 450.f * countOfElements},
                    SBUILD_SIZE, VIOLET, 0, (unsigned int)(10000.f / countOfElements), cam,
                    BUILD_SPEED, SBUILD_OFFSET)
            );
            buttons.push_back(
                    g9::Button(BUTTON_POS, BUTTON_SIZE, "Buy Side Building", BUTTON_TEXT_HEIGHT, RED,
                               20 * pow(4, countOfElements),
                               pow(5, countOfElements))
            );
            buttons[countOfElements-1].SetAction(actionSB);
            auto eT = new std::thread([&](){
                list[countOfElements-1]->WhileExist(*money);
            });
            eT->detach();
            eTs.push_back(eT);
            eT = nullptr;
        }
        bI = buttons.begin();
    }

    void BuildingsList::Check() {
        for(auto& el: list)
        {
            el->check(*money);
        }
    }

    bool BuildingsList::CheckZeroIV() {
        return list[countOfElements-1]->GetIncomeValue() != 0;
    }

    void BuildingsList::Show() {
        for(auto& el: list)
        {
            el->Show();
        }
    }
} // g9