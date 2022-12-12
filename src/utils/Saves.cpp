//
// Created by Coltenus on 02.12.2022.
//

#include "Saves.h"
#include "../menu/Gameplay.h"

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

    short Saves::GlobalData::GetName(size_t pos) {
        if(!name.empty())
            return name[pos];
        else return -1;
    }

    bool Saves::GlobalData::GetStatus(size_t pos) {
        if(!active.empty())
            return active[pos];
        else return false;
    }

    size_t Saves::GlobalData::GetLength() {
        return name.size();
    }

    Saves::GlobalData::~_GlobalData() {
        name.erase(name.begin(), name.end());
        active.erase(active.begin(), active.end());
    }

    void Saves::GlobalData::Clear() {
        name.erase(name.begin(), name.end());
        active.erase(active.begin(), active.end());
    }

    void Saves::GlobalData::SetActive(size_t pos) {
        active[GetPosOfActive()] = false;
        active[pos] = true;
    }

    size_t Saves::GlobalData::GetPosOfActive() {
        return std::distance(active.begin(), std::find(active.begin(), active.end(), true));
    }

    short Saves::_GlobalData::FindElement(unsigned char el) {
        auto buf = name.end();
        if((buf = std::find(name.begin(), name.end(), el)) != name.end())
        {
            return std::distance(name.begin(), buf);
        }
        else
        {
            return -1;
        }
    }

    Saves::Saves() : ss(nullptr) {
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
            fwrite(&IsDarkMode, sizeof(IsDarkMode), 1, file);
            fwrite(&len, sizeof(size_t), 1, file);
            fwrite(&buf2[0], sizeof(unsigned char), len, file);
            buf2 = nullptr;
            buf.clear();
            gd.Clear();
            fclose(file);
            fopen_s(&file, "gd", "rb");
        }
        fseek(file, 0, SEEK_SET);
        fread(&IsDarkMode, sizeof(IsDarkMode), 1, file);
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
            size_t len;
            fopen_s(&file, "gd", "wb");
            buf = gd.GetData();
            len = buf.size();
            fseek(file, 0, SEEK_SET);
            fwrite(&IsDarkMode, sizeof(IsDarkMode), 1, file);
            fwrite(&len, sizeof(size_t), 1, file);
            fwrite(buf.data(), sizeof(buf[0]), buf.size(), file);
            buf.clear();
            gd.Clear();
            fclose(file);
            if(ss != nullptr)
            {
                delete ss;
                ss = nullptr;
            }
            object = nullptr;
        }
    }

    void Saves::AddSave(unsigned char n) {
        gd.AddElement(n, false);
    }

    void Saves::PullSettings(MenuOption **gp,
                             std::vector<std::thread*>* th,
                             bool* ise,
                             utils::MenuSelections* ms) {
        bool isNew = false;
        bool isCorrect = true;
        int num = std::distance(gd.active.begin(), std::find(gd.active.begin(), gd.active.end(), true));
        auto folderName = std::to_string(gd.name[num]);
        FILE* file;
        if(ss != nullptr) delete ss;
        ss = new struct SaveSettings;
        auto bufD = ss->GetData();
        unsigned char* bufUCP = nullptr;
        char* bufCP = new char[3];
        std::string bufCP2 = "SET";
        if(!std::filesystem::is_directory(std::string("saves/")))
            mkdir(std::string("saves/").c_str());
        if(!std::filesystem::is_directory(std::string("saves/")+folderName))
        {
            mkdir((std::string("saves/")+folderName).c_str());
            fopen_s(&file, (std::string("saves/")+folderName+std::string("/settings")+folderName).c_str(), "wb");
            fwrite(bufCP2.c_str(), sizeof(char), 3, file);
            fwrite(bufD.data(), sizeof(bufD[0]), bufD.size(), file);
            fclose(file);
            isNew = true;
        }
        if(!isNew)
        {
            fopen_s(&file, (std::string("saves/")+folderName+std::string("/settings")+folderName).c_str(), "rb");
            fseek(file, 0, SEEK_END);
            num = ftell(file);
            if(num >= 23)
            {
                fseek(file, 0, SEEK_SET);
                fread(&bufCP[0], sizeof(char), 3, file);
                for(int i = 0; i<3; i++)
                    if(bufCP[i] != bufCP2[i])
                        isCorrect = false;
                if(isCorrect)
                {
                    fseek(file, 3, SEEK_SET);
                    bufUCP = new unsigned char[num-3];
                    fread(&bufUCP[0], sizeof(unsigned char), num-3, file);
                    bufD = {};
                    for(int i = 0; i<num-3; i++)
                        bufD.push_back(bufUCP[i]);
                    ss->SetData(bufD);
                }
            }
        }
        if(file != nullptr) fclose(file);
        if(bufUCP != nullptr)
        {
            delete[] bufUCP;
            bufUCP = nullptr;
        }
        delete[] bufCP;
        bufCP = nullptr;
        *gp = Gameplay::CreateGameplay(th, ise, ms, ss->moneyValue,
                                      ss->countOfActBuildings, ss->buildingsValue, ss->updatePrices);
    }

    void Saves::UpdateSettings(MenuOption *gp) {
        if(ss != nullptr)
        {
            int num = std::distance(gd.active.begin(), std::find(gd.active.begin(), gd.active.end(), true));
            auto folderName = std::to_string(gd.name[num]);
            FILE* file;
            std::string bufCP2 = "SET";
            ss->moneyValue = reinterpret_cast<Gameplay*>(gp)->GetMoney();
            ss->countOfActBuildings = reinterpret_cast<Gameplay*>(gp)->GetActBuildings();
            ss->buildingsValue = reinterpret_cast<Gameplay*>(gp)->GetIncValues();
            ss->updatePrices = reinterpret_cast<Gameplay*>(gp)->GetUpdatePrices();
            auto bufD = ss->GetData();
            fopen_s(&file, (std::string("saves/")+folderName+std::string("/settings")+folderName).c_str(), "wb");
            fwrite(bufCP2.c_str(), sizeof(char), 3, file);
            fwrite(bufD.data(), sizeof(bufD[0]), bufD.size(), file);
            fclose(file);
            delete ss;
            ss = nullptr;
        }
    }

    Saves::GlobalData *Saves::GetGlobalData() {
        return &gd;
    }

    std::vector<unsigned char> Saves::SaveSettings::GetData() {
        std::vector<unsigned char> result;

        for(int i = 0; i<8; i++)
            result.push_back((moneyValue >> i*8) % 256);

        for(int i = 0; i<4; i++)
            result.push_back((countOfActBuildings >> i*8) % 256);

        for(int i = 0; i<countOfActBuildings; i++)
            for(int j = 0; j<8; j++)
                result.push_back((buildingsValue[i] >> j*8) % 256);

        for(int i = 0; i<countOfActBuildings+1; i++)
            for(int j = 0; j<8; j++)
                result.push_back((updatePrices[i] >> j*8) % 256);

        return result;
    }

    Saves::SaveSettings::SaveSettings() {
        moneyValue = MONEY_VAL;
        countOfActBuildings = 1;
        buildingsValue = {1};
        updatePrices = {25, 40};
    }

    void Saves::SaveSettings::SetData(std::vector<unsigned char>& data) {
        moneyValue = 0;
        for(int i = 0; i<8; i++)
        {
            moneyValue += data[i] << i*8;
        }
        countOfActBuildings = 0;
        for(int i = 0; i<4; i++)
        {
            countOfActBuildings += data[8 + i] << i*8;
        }
        buildingsValue = {};
        for(int i = 0; i<countOfActBuildings; i++)
        {
            buildingsValue.push_back(0);
            for(int j = 0; j<8; j++)
            {
                buildingsValue[i] += data[12 + i*8 + j] << j*8;
            }
        }
        updatePrices = {};
        for(int i = 0; i<countOfActBuildings+1; i++)
        {
            updatePrices.push_back(0);
            for(int j = 0; j<8; j++)
            {
                updatePrices[i] += data[12 + 8*countOfActBuildings + i*8 + j] << j*8;
            }
        }
    }

    unsigned long long Saves::SaveSettings::GetMoneyValue() {
        return moneyValue;
    }

    int Saves::SaveSettings::GetCountOfActBuildings() {
        return countOfActBuildings;
    }

    const std::vector<unsigned long long> &Saves::SaveSettings::GetBuildingsValue() {
        return buildingsValue;
    }

    const std::vector<unsigned long long> &Saves::SaveSettings::GetUpdatePrices() {
        return updatePrices;
    }
} // g9::utils