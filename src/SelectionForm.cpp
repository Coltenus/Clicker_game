//
// Created by Coltenus on 11.12.2022.
//

#include "SelectionForm.h"
#include <thread>
#include "Cmd.h"

namespace g9::menu_elements {
    SelectionForm::SelectionForm(Vector2 p, Vector2 s, short fontH)
    :
    pos(p),
    size(s),
    fontHeight(fontH),
    currentSaving(0),
    needAddSaving(false)
    {
        posB1 = {PADDING_SF_X, PADDING_SF_Y};
        sizeB1 = {(size.x - PADDING_SF_IN_X)/7, (size.y - PADDING_SF_IN_Y)/2};
        posLabel = {PADDING_SF_X + sizeB1.x + PADDING_SF_B1L, PADDING_SF_Y};
        sizeLabel = {(size.x - PADDING_SF_IN_X)/7*3, (size.y - PADDING_SF_IN_Y)/2};
        posB2 = {PADDING_SF_X + sizeB1.x + PADDING_SF_B1L + sizeLabel.x + PADDING_SF_LB2, PADDING_SF_Y};
        sizeB2 = {(size.x - PADDING_SF_IN_X)/7, (size.y - PADDING_SF_IN_Y)/2};
        posB3 = {PADDING_SF_X + sizeB1.x + PADDING_SF_B1L + sizeLabel.x + PADDING_SF_LB2 + sizeB2.x + PADDING_SF_B2B3, PADDING_SF_Y};
        sizeB3 = {(size.x - PADDING_SF_IN_X)/7*2, (size.y - PADDING_SF_IN_Y)/2};
        posInput = {PADDING_SF_X + sizeB1.x + PADDING_SF_B1L, PADDING_SF_Y + sizeLabel.y + PADDING_SF_LI};
        sizeInput = {(size.x - PADDING_SF_IN_X)/7*3, (size.y - PADDING_SF_IN_Y)/2};
        posB4 = {PADDING_SF_X + sizeB1.x + PADDING_SF_B1L + sizeLabel.x + PADDING_SF_LB2 + sizeB2.x + PADDING_SF_B2B3,
                 PADDING_SF_Y + sizeB3.y + PADDING_SF_LI};
        sizeB4 = {(size.x - PADDING_SF_IN_X)/7*0.9f, (size.y - PADDING_SF_IN_Y)/2};
        posB5 = {PADDING_SF_X + sizeB1.x + PADDING_SF_B1L + sizeLabel.x + PADDING_SF_LB2 + sizeB2.x + PADDING_SF_B2B3
                 + sizeB4.x + (size.x - PADDING_SF_IN_X)/7*0.2f, PADDING_SF_Y + sizeB3.y + PADDING_SF_LI};
        sizeB5 = {(size.x - PADDING_SF_IN_X)/7*0.9f, (size.y - PADDING_SF_IN_Y)/2};
    }

    SelectionForm *SelectionForm::CreateSelectionForm(Vector2 p, Vector2 s, short fontH) {
        if(s.x < PADDING_SF_IN_X + 35
               || s.y < PADDING_SF_IN_Y + 10)
            return nullptr;
        else return new SelectionForm(p, s, fontH);
    }

    void SelectionForm::Show() {
#if false
        DrawRectangleLines(pos.x, pos.y, size.x, size.y, TEXT_COLOR);
#endif
        short name = gd->GetName(currentSaving);
        DrawRectangleV({pos.x + posB1.x, pos.y + posB1.y}, sizeB1, BTN_MENU);
        DrawText("<=", pos.x + posB1.x + sizeB1.x*0.25,  pos.y + posB1.y + sizeB1.y*0.4, fontHeight, TEXT_COLOR);
        DrawRectangleV({pos.x + posLabel.x, pos.y + posLabel.y}, sizeLabel, BTN_MENU);
        if(name != -1)
            DrawText(std::to_string(name).c_str(), pos.x + posLabel.x + sizeLabel.x*0.35,
                     pos.y + posLabel.y + sizeLabel.y*0.4, fontHeight, TEXT_COLOR);
        else
            DrawText("No savings", pos.x + posLabel.x + sizeLabel.x*0.1,
                     pos.y + posLabel.y + sizeLabel.y*0.4, fontHeight, TEXT_COLOR);
        DrawRectangleV({pos.x + posB2.x, pos.y + posB2.y}, sizeB2, BTN_MENU);
        DrawText("=>", pos.x + posB2.x + sizeB2.x*0.35,  pos.y + posB2.y + sizeB2.y*0.4, fontHeight, TEXT_COLOR);
        DrawRectangleV({pos.x + posB3.x, pos.y + posB3.y}, sizeB3, GREEN);
        DrawText("New save", pos.x + posB3.x + sizeB3.x*0.05,  pos.y + posB3.y + sizeB3.y*0.4, fontHeight, TEXT_COLOR);
        DrawRectangleV({pos.x + posB5.x, pos.y + posB5.y}, sizeB5, GREEN);
        DrawText("Del", pos.x + posB5.x + sizeB5.x*0.2,  pos.y + posB5.y + sizeB5.y*0.35, fontHeight, TEXT_COLOR);
        if(needAddSaving) {
            DrawRectangleLines(pos.x + posInput.x, pos.y + posInput.y, sizeInput.x, sizeInput.y, TEXT_COLOR);
            DrawText(buffer.c_str(), pos.x + posInput.x + sizeInput.x*0.1,  pos.y + posInput.y + sizeInput.y*0.4,
                     fontHeight, TEXT_COLOR);
            DrawRectangleV({pos.x + posB4.x, pos.y + posB4.y}, sizeB4, GREEN);
            DrawText("Add", pos.x + posB4.x + sizeB4.x*0.1,  pos.y + posB4.y + sizeB4.y*0.35, fontHeight, TEXT_COLOR);
        }
    }

    void SelectionForm::Update(bool& isClicked) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(isClicked)
        {
            if(CheckMouseOnButton(mouse, {pos.x + posB1.x, pos.y + posB1.y}, sizeB1))
            {
                if(currentSaving > 0) {
                    currentSaving--;
                    gd->SetActive(currentSaving);
                }
            }
            else if(CheckMouseOnButton(mouse, {pos.x + posB2.x, pos.y + posB2.y}, sizeB2))
            {
                if(currentSaving+1 < (short)gd->GetLength()) {
                    currentSaving++;
                    gd->SetActive(currentSaving);
                }
            }
            else if(CheckMouseOnButton(mouse, {pos.x + posB3.x, pos.y + posB3.y}, sizeB3))
            {
                needAddSaving = !needAddSaving;
                if(!needAddSaving)
                    buffer.clear();
            }
            else if(CheckMouseOnButton(mouse, {pos.x + posB4.x, pos.y + posB4.y}, sizeB4))
            {
                if(!buffer.empty()) {
                    needAddSaving = false;
                    gd->AddElement(std::stoi(buffer), false);
                    buffer.clear();
                }
            }
            else if(CheckMouseOnButton(mouse, {pos.x + posB5.x, pos.y + posB5.y}, sizeB5))
            {
                static std::string buf;
                if(needAddSaving) {
                    if(!buffer.empty()) {
                        buf = "rmdir -Force -Recurse saves/";
                        buf += buffer;
                        short delElem = gd->FindElement(std::stoi(buffer));
                        if(delElem != -1)
                        {
                            gd->DelElement(delElem);
                            if(gd->GetLength() > 0)
                                gd->SetActive(0);
                            utils::Cmd::Execute(buf.c_str());
                        }
                    }
                } else {
                    short bufS = gd->GetName(currentSaving);
                    if(bufS != -1)
                    {
                        buf = "rmdir -Force -Recurse saves/";
                        buf += std::to_string(gd->GetName(currentSaving));
                        gd->DelElement(currentSaving);
                        if(gd->GetLength() > 0)
                            gd->SetActive(0);
                        utils::Cmd::Execute(buf.c_str());
                    }
                }
                currentSaving = 0;
                buffer.clear();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        if(needAddSaving) {
            int key = GetKeyPressed();
            if(key >= 48 && key <= 57 && buffer.length() < 10)
                buffer += (char)key;
            else if(IsKeyPressed(KEY_BACKSPACE) && !buffer.empty())
            {
                buffer.pop_back();
            }
        }
    }

    void SelectionForm::SetGlobalData(utils::Saves::GlobalData *gd) {
        this->gd = gd;
        currentSaving = gd->GetPosOfActive();
    }

    inline bool SelectionForm::CheckMouseOnButton(Vector2 m, Vector2 p, Vector2 s) {
        return m.x >= p.x && m.x <= p.x + s.x
               && m.y >= p.y && m.y <= p.y + s.y;
    }
} // menu_elements