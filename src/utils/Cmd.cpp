//
// Created by colte on 11.12.2022.
//

#include "Cmd.h"
#include <iostream>

namespace g9::utils {
        void Cmd::Execute(const char *command) {
            system(command);
        }
    } // utils