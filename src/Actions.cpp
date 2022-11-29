//
// Created by colte on 29.11.2022.
//
#include "Actions.h"

namespace g9 {

    void actionMB(g9::Money &m, g9::Building &b, unsigned long long int &neededVal, unsigned long long int &startIV) {
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

    void actionSB(Money &m, Building &b, unsigned long long int &neededVal, unsigned long long int &startIV) {
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

}
