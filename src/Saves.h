//
// Created by Coltenus on 02.12.2022.
//

#ifndef GAME9_SAVES_H
#define GAME9_SAVES_H

#include <filesystem>
#include <unistd.h>
#include "MenuOption.h"

namespace g9::utils {

        class Saves {
        private:
            struct GlobalData {
                ~GlobalData();
                std::vector<unsigned char> name;
                std::vector<bool> active;
                std::vector<unsigned char> GetData();
                void SetData(std::vector<unsigned char>);
                void AddElement(unsigned char, bool);
                void DelElement(size_t);
                void Clear();
                unsigned char GetName(size_t);
                bool GetStatus(size_t);
                size_t GetLength();
            } gd;
            //settings struct declaration
            //pointer struct buffer declaration
            Saves();

        public:
            static Saves* object;
            static Saves* CreateSaves();
            Saves(Saves&) = delete;
            void operator=(Saves&) = delete;
            ~Saves();
            void AddSave(unsigned char, bool);
            void PullSettings(MenuOption&);
            void UpdateSettings(MenuOption&);
        };

} // g9::utils

#endif //GAME9_SAVES_H
