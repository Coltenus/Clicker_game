//
// Created by Coltenus on 02.12.2022.
//

#include "Saves.h"

namespace g9::utils {


    std::vector<unsigned char> Saves::GlobalData::GetData() {
        std::vector<unsigned char> data;

        for(size_t i = 0; i<name.size(); i++)
        {
            data.push_back(name[i]);
            data.push_back(static_cast<unsigned char>(active[i]));
        }

        return data;
    }

    void Saves::GlobalData::SetData(std::vector<unsigned char> data) {
        if(data.empty() && data.size()%2 != 0)
            return;
        name.clear();
        active.clear();
        for(size_t i = 0; i<data.size(); i+=2)
        {
            name.push_back(data[i]);
            active.push_back(static_cast<bool>(data[i+1]));
        }
    }

    void Saves::GlobalData::AddElement(unsigned char n, bool st) {
        name.push_back(n);
        active.push_back(st);
    }

    void Saves::GlobalData::DelElement(size_t pos) {
        if(pos < name.size())
        {
            name.erase(name.begin() + pos);
            active.erase(active.begin() + pos);
        }
    }

    unsigned char Saves::GlobalData::GetName(size_t pos) {
        return name[pos];
    }

    bool Saves::GlobalData::GetStatus(size_t pos) {
        return active[pos];
    }

    size_t Saves::GlobalData::GetLength() {
        return name.size();
    }

    Saves::GlobalData::~GlobalData() {
        name.erase(name.begin(), name.end());
        active.erase(active.begin(), active.end());
    }

    void Saves::GlobalData::Clear() {
        name.erase(name.begin(), name.end());
        active.erase(active.begin(), active.end());
    }

    Saves::Saves() {
        FILE* file;
        std::vector<unsigned char> buf;
        unsigned char* buf2 = nullptr;
        size_t len;
        if(fopen_s(&file, "gd", "rb") != 0)
        {
            fclose(file);
            gd.AddElement(1, true);
            fopen_s(&file, "gd", "wb");
            buf = gd.GetData();
            buf2 = buf.data();
            len = buf.size();
            fseek(file, 0, SEEK_SET);
            fwrite(&len, sizeof(size_t), 1, file);
            fwrite(&buf2[0], sizeof(unsigned char), len, file);
            buf2 = nullptr;
            buf.clear();
            gd.Clear();
            fclose(file);
            fopen_s(&file, "gd", "rb");
        }
        fseek(file, 0, SEEK_SET);
        fread(&len, sizeof(size_t), 1, file);
        buf2 = new unsigned char[len];
        fread(&buf2[0], sizeof(unsigned char), len, file);
        fclose(file);
        for(size_t i = 0; i<len; i++)
            buf.push_back(buf2[i]);
        buf2 = nullptr;
        gd.SetData(buf);
        buf.erase(buf.begin(), buf.end());
    }

    Saves *Saves::CreateSaves() {
        if(object != nullptr)
            return nullptr;
        else
        {
            object = new Saves;
            return object;
        }
    }

    Saves::~Saves() {
        if(object != nullptr)
        {
            FILE* file;
            std::vector<unsigned char> buf;
            unsigned char* buf2;
            size_t len;
            fopen_s(&file, "gd", "wb");
            buf = gd.GetData();
            buf2 = buf.data();
            len = buf.size();
            fseek(file, 0, SEEK_SET);
            fwrite(&len, sizeof(size_t), 1, file);
            fwrite(&buf2[0], sizeof(unsigned char), len, file);
            buf2 = nullptr;
            buf.clear();
            gd.Clear();
            fclose(file);
            object = nullptr;
        }
    }

    void Saves::AddSave(unsigned char n, bool st) {
        gd.AddElement(n, st);
    }

    void Saves::PullSettings(MenuOption &gp) {
        int num = std::distance(gd.active.begin(), std::find(gd.active.begin(), gd.active.end(), true));
        auto folderName = std::to_string(gd.name[num]);
        FILE* file;
        if(!std::filesystem::is_directory(folderName))
        {
            mkdir(folderName.c_str());
            fopen_s(&file, (folderName+std::string("/settings")+folderName).c_str(), "wb");
            //fill settings file
            fclose(file);
        }
        //check if buffer is empty, if not continue
        fopen_s(&file, (folderName+std::string("/settings")+folderName).c_str(), "rb");
        //change this check with struct check
        fseek(file, 0, SEEK_END);
        if(ftell(file) == 0)
        {
            long long buf = 1;
            fclose(file);
            fopen_s(&file, (folderName+std::string("/settings")+folderName).c_str(), "wb");
            //fill file with settings
            fclose(file);
            //fill buffer with new data
        }
        if(file != nullptr) fclose(file);
        //fill gameplay class with collected data
    }

    void Saves::UpdateSettings(MenuOption &) {
        //save settings logic, fill file with updated data
    }
} // g9::utils