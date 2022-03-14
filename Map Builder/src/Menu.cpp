#include "Menu.h"

Menu::Menu()
{
    tileSymbol = ' ';
}
Menu::~Menu(){
}

void Menu::MenuCheckBox() {
    ImGui::Checkbox("Bind mario", &bind_mario);
    ImGui::Checkbox("Bind brown brick", &bind_brown_brick);
    ImGui::Checkbox("Bind coin", &bind_coin);
    ImGui::Checkbox("Bind pipe", &bind_pipe);
    ImGui::Checkbox("Bind question mark", &bind_question_mark);
}

void Menu::BindTexture() {
    if (bind_brown_brick) { tileSymbol = brown_brick; }
    else if(bind_coin) {  tileSymbol = coin; }
    else if (bind_mario) { tileSymbol = mario; }
    else if(bind_pipe) { tileSymbol = pipe; }
    else if(bind_question_mark) {  tileSymbol = question_mark; }
    else { tileSymbol = blank_space; }
}
char Menu::PassTile() {
    return tileSymbol;
}

