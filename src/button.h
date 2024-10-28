#ifndef BUTTON_H
#define BUTTON_H

#include "structs.h"

button_t create_button(int x, int y, int w, int h, int font_size, const char* text, void (*on_click)()) 
{
    button_t btn = (button_t){x, y, w, h, font_size, text, on_click};
    return btn;
}

int mouse_is_over(button_t* btn)
{
    return (btn->x < GetMouseX() && btn->x + btn->w > GetMouseX() &&
            btn->y < GetMouseY() && btn->y + btn->h > GetMouseY());
}

void draw_button(button_t* btn, mColor normal, mColor hover)
{
    Color color = mouse_is_over(btn) ? hover : normal;
    DrawRectangle(btn->x, btn->y, btn->w, btn->h, color);
    DrawText(btn->text, btn->x + (btn->h - btn->font_size) / 2, btn->y + (btn->h - btn->font_size) / 2, btn->font_size, BLACK);
}

void handle_button_click(button_t* btn) {
    if (mouse_is_over(btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (btn->on_click != NULL) {
            btn->on_click();
        }
    }
}

void update_button(button_t* btn, mColor normal, mColor hover)
{
    draw_button(btn, normal, hover);
    handle_button_click(btn);
}


#endif