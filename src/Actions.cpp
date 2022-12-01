//
// Created by Coltenus on 29.11.2022.
//
#include "Actions.h"

namespace g9::actions {
        void actionMB(game_objects::Money &m, game_objects::Building &b,
                      unsigned long long int &neededVal, unsigned long long int &startIV) {
            static unsigned long long curVal;
            curVal = m.GetValue();
            if(neededVal != 0 && curVal >= neededVal)
            {
                m -= neededVal;
                neededVal *= 1.2;
                if(b.GetIncomeValue() == 0 && startIV != 0)
                    b.IncreaseIncValByVal(startIV);
                else if(b.GetIncomeValue() > 10)
                    b.IncreaseIncVal(1.1);
                else
                    b.IncreaseIncValByVal(1);
            }
        }

        void actionSB(game_objects::Money &m, game_objects::Building &b,
                      unsigned long long int &neededVal, unsigned long long int &startIV) {
            static unsigned long long curVal;
            curVal = m.GetValue();
            if(neededVal != 0 && curVal >= neededVal)
            {
                m -= neededVal;
                neededVal *= 1.4;
                if(b.GetIncomeValue() == 0 && startIV != 0)
                    b.IncreaseIncValByVal(startIV);
                else if(b.GetIncomeValue() > 0)
                    b.IncreaseIncVal(1.5);
                else
                    b.IncreaseIncValByVal(2);
            }
        }

        void buttonL(const std::vector<game_objects::Button> &vec,
                     __gnu_cxx::__normal_iterator<game_objects::Button *, std::vector<game_objects::Button>> &iter) {
            if(iter != vec.begin())
                iter -= 1;
        }

        void buttonR(const std::vector<game_objects::Button> &vec,
                     __gnu_cxx::__normal_iterator<game_objects::Button *, std::vector<game_objects::Button>> &iter) {
            if(iter + 1 != vec.end())
                iter += 1;
        }
    }
