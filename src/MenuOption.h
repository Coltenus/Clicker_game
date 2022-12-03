//
// Created by colte on 02.12.2022.
//

#ifndef GAME9_MENUOPTION_H
#define GAME9_MENUOPTION_H

#include <raylib.h>
#include <thread>
#include <vector>
#include "common.h"

namespace g9 {

    class MenuOption {
    public:
        std::vector<std::thread*>* existingThreads;
        unsigned char curThreads;
        Camera2D cam;
        bool* isShouldExit;
        utils::MenuSelections* menuOpt;
        bool active;
        explicit MenuOption(std::vector<std::thread*>* th,
                            bool* ise,
                            utils::MenuSelections* ms)
                :
                existingThreads(th),
                curThreads(0),
                cam({{WIDTH, HEIGHT}, {WIDTH, HEIGHT}, 0, 1.f}),
                isShouldExit(ise),
                menuOpt(ms),
                active(false)
        {}
        virtual ~MenuOption() = default;
        MenuOption(MenuOption&) = delete;
        void operator=(MenuOption&) = delete;
        virtual void Start() = 0;
        virtual void Update() = 0;
        bool GetStatus() const {return active;}
        void SetStatus(bool st) {active = st;}
    };

} // g9

#endif //GAME9_MENUOPTION_H
