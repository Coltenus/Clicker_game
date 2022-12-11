//
// Created by Coltenus on 29.11.2022.
//

#include "BuildingsList.h"
#include "MainBuilding.h"
#include "SideBuilding.h"

namespace g9 {

    using namespace game_objects;

    BuildingsList::BuildingsList(Camera2D* c, Money* m) : countOfElements(2), cam(c), money(m) {
        list = {};
        list.push_back(new MainBuilding({BUILD_POS_X, HEIGHT / 2 - 200}, MBUILD_SIZE, DARKBROWN, 1, cam, BUILD_SPEED, MBUILD_OFFSET));
        list.push_back(new SideBuilding({BUILD_POS_X, HEIGHT / 2 + 300}, SBUILD_SIZE, VIOLET, 0, 5000, cam, BUILD_SPEED, 2));
        buttons = {};
        buttons.push_back(Button(BUTTON_POS, BUTTON_SIZE, "Upgrade Main Building", BUTTON_TEXT_HEIGHT, RED, 25, 0));
        buttons.push_back(Button(BUTTON_POS, BUTTON_SIZE, "Buy Side Building", BUTTON_TEXT_HEIGHT, RED, 40, 2));
        buttons[0].SetAction(actions::actionMB);
        buttons[1].SetAction(actions::actionSB);
    }

    BuildingsList::~BuildingsList() {
        if(object != nullptr)
        {
            list.erase(list.cbegin(), list.end());
            buttons.erase(buttons.cbegin(), buttons.end());
            cam = nullptr;
            money = nullptr;
            object = nullptr;
        }
    }

    __gnu_cxx::__normal_iterator<Button *, std::vector<Button>> BuildingsList::GetFirstButton() {
        return buttons.begin();
    }

    Building *BuildingsList::operator[](int el) {
        if(!list.empty())
            return list[el];
        else return nullptr;
    }

    void BuildingsList::Move() {
        for(auto& el: list)
            el->Move();
    }

    long long BuildingsList::GetDistanceBetweenButtons(__gnu_cxx::__normal_iterator<Button *,
                                                       std::vector<Button>>& butIter) {
        return std::distance(buttons.begin(), butIter);
    }

    std::vector<Button> &BuildingsList::GetButtons() {
        return buttons;
    }

    void BuildingsList::AddNewBuilding(std::vector<std::thread*>& eTs,
                                       __gnu_cxx::__normal_iterator<Button *, std::vector<Button>>& bI,
                                       unsigned char &cTh, bool *active) {
        countOfElements++;
        if(countOfElements%5 == 0) {
            list.push_back(
                    new MainBuilding({BUILD_POS_X, HEIGHT / 2 - 100 + 450.f * countOfElements},
                                         MBUILD_SIZE, DARKBROWN, 0, cam, BUILD_SPEED, MBUILD_OFFSET)
            );
            buttons.push_back(
                    Button(BUTTON_POS, BUTTON_SIZE, "Buy Main Building", BUTTON_TEXT_HEIGHT, RED,
                               15 * pow(4, countOfElements),
                               pow(4, countOfElements)/2)
            );
            buttons[countOfElements-1].SetAction(actions::actionMB);
        }
        else {
            list.push_back(
                    new SideBuilding({WIDTH / 2 - 50, HEIGHT / 2 - 100 + 450.f * countOfElements},
                    SBUILD_SIZE, VIOLET, 0, (unsigned int)(10000.f / countOfElements), cam,
                    BUILD_SPEED, SBUILD_OFFSET)
            );
            buttons.push_back(
                    Button(BUTTON_POS, BUTTON_SIZE, "Buy Side Building", BUTTON_TEXT_HEIGHT, RED,
                               20 * pow(4, countOfElements),
                               pow(5, countOfElements))
            );
            buttons[countOfElements-1].SetAction(actions::actionSB);
            auto eT = new std::thread([this](bool* active, int pos){
                static bool* check = active;
                while(active != nullptr && *active && object != nullptr)
                {
                    if(active != check && !(*active))
                        break;
                    else list[pos]->WhileExist(*money);
                }
            }, active, countOfElements-1);
            eT->detach();
            cTh++;
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

    BuildingsList* BuildingsList::CreateList(Camera2D *cm, Money *m) {
        if(object != nullptr)
            return nullptr;
        else {
            object = new BuildingsList(cm, m);
            return object;
        }
    }

    void BuildingsList::SetIncValue(std::vector<unsigned long long> &incVal) {
        for(int i = 0; i<countOfElements-1; i++)
            list[i]->SetIncValue(incVal[i]);
    }

    int BuildingsList::GetCountOfElements() {
        return countOfElements;
    }

    int BuildingsList::GetCountOfActElements() {
        if(!CheckZeroIV())
            return countOfElements-1;
        else return countOfElements;
    }

    std::vector<unsigned long long> BuildingsList::GetIncValues() {
        std::vector<unsigned long long> result;

        for(auto& el: list)
            if(el->GetIncomeValue() != 0)
                result.push_back(el->GetIncomeValue());

        return result;
    }

    std::vector<unsigned long long> BuildingsList::GetUpdatePrices() {
        std::vector<unsigned long long> result;

        for(auto& el: buttons)
            result.push_back(el.GetPrice());

        return result;
    }

    void BuildingsList::SetUpdatePrices(std::vector<unsigned long long> &uP) {
        for(int i = 0; i<countOfElements-1; i++)
            buttons[i].SetPrice(uP[i], false);
        buttons[countOfElements-1].SetPrice(uP[countOfElements-1], true);
    }
} // g9