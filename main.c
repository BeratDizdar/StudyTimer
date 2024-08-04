#include <raylib.h>
#include <stdio.h>

#define mode_button_char_size 28
#define max_sec 60
#define max_min 60
#define max_hour 24

///////////////////////////////////
// types

typedef enum timer_modes{
    NONE = 0,
    TIMER,
    STOPWATCH,
    MODE_COUNT,
} timer_modes_t;

typedef struct button {
    int x, y, w, h;
} button_t;

///////////////////////////////////
// Global

float delta_time = 0; 
int sec = 0, min = 0, hour = 0;
timer_modes_t mode = NONE; 

///////////////////////////////////
// Fonksiyonlar

int mouse_is_over(button_t* btn)
{
    if(btn->x < GetMouseX() && btn->x + btn->w > GetMouseX() && btn->y < GetMouseY() && btn->y + btn->h > GetMouseY())
    {
        return 1;
    }
    return 0;
}

void draw_button(button_t* btn, Color button_color)
{
    DrawRectangle(btn->x, btn->y, btn->w, btn->h, button_color);
}

void draw_button_text(const char* str, button_t* btn, int font_size, Color color)
{
    DrawText(str, btn->x + (btn->h - font_size) / 2, btn->y + (btn->h - font_size) / 2, font_size, color);
}

void mode_timer()
{
    if(hour < 1 && min < 1 && sec < 1) {
        sec = 0, min = 0, hour = 0;
        mode = NONE;
        return;
    }

    delta_time += GetFrameTime();
    if(delta_time > 1){
        delta_time = 0;
        if(sec > 0) {
            sec--;
        } else if(min > 0) {
            min--;
            sec = 59;
        } else if(hour > 0) {
            hour--;
            min = 59;
            sec = 59;
        }
    }
}

void mode_stopwatch()
{
    delta_time += GetFrameTime();
    if(delta_time > 1){
        sec++;
        delta_time = 0;
    }
    if(sec > max_sec){
        min++;
        sec = 0;
    }
    if(sec > max_min){
        hour++;
        min = 0;
    }
}

int main() {

    InitWindow(500, 200, "StudyTimer");
    SetTargetFPS(60);

      
    Color bg_color = DARKBROWN; 

    button_t buton1 = {.x = 10, .y = 10, .w = 80, .h = 40};

    button_t dec_hour = {.x = 10, .y = 150, .w = 40, .h = 40};
    button_t dec_min = {.x = 60, .y = 150, .w = 40, .h = 40};
    button_t dec_sec = {.x = 110, .y = 150, .w = 40, .h = 40};
    button_t inc_sec = {.x = 160, .y = 150, .w = 40, .h = 40};
    button_t inc_min = {.x = 210, .y = 150, .w = 40, .h = 40};
    button_t inc_hour = {.x = 260, .y = 150, .w = 40, .h = 40};

    while(!WindowShouldClose())
    {
        //update
        switch (mode) {
        case NONE:
            buton1.w = 3 * mode_button_char_size;
            bg_color = BLACK;
            break;
        case TIMER:
            buton1.w = 4 * mode_button_char_size;
            bg_color = RED;
            mode_timer();
            break;
        case STOPWATCH:
            buton1.w = 7 * mode_button_char_size;
            bg_color = DARKBROWN;
            mode_stopwatch();
            break;
        default:
            printf("update-switch hatası\n");
            break;
        }



        // draw
        BeginDrawing();
        ClearBackground(bg_color);

        // mod butonu
        if(mouse_is_over(&buton1)) {
            draw_button(&buton1, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mode++;
                if(mode == MODE_COUNT) {
                    mode = 0;
                }
            }
        } else {
            draw_button(&buton1, WHITE);
        }
        DrawText(TextFormat("%s", (mode == 0) ? "NONE" : 
                                (mode == 1) ? "TIMER" : "STOPWATCH" ), buton1.x + 6, buton1.y + 6, buton1.h - 12, BLACK);

        // dec_hour 
        if(mouse_is_over(&dec_hour)) {
            draw_button(&dec_hour, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                hour--;
            }
        } else {
            draw_button(&dec_hour, WHITE);
        }
        draw_button_text("-h", &dec_hour, 28, BLACK);

        // dec_min 
        if(mouse_is_over(&dec_min)) {
            draw_button(&dec_min, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                min--;
            }
        } else {
            draw_button(&dec_min, WHITE);
        }
        draw_button_text("-m", &dec_min, 28, BLACK);

        // dec_sec 
        if(mouse_is_over(&dec_sec)) {
            draw_button(&dec_sec, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                sec--;
            }
        } else {
            draw_button(&dec_sec, WHITE);
        }
        draw_button_text("-s", &dec_sec, 28, BLACK);

        // inc_sec 
        if(mouse_is_over(&inc_sec)) {
            draw_button(&inc_sec, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                sec++;
            }
        } else {
            draw_button(&inc_sec, WHITE);
        }
        draw_button_text("+s", &inc_sec, 28, BLACK);

        // inc_min
        if(mouse_is_over(&inc_min)) {
            draw_button(&inc_min, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                min++;
            }
        } else {
            draw_button(&inc_min, WHITE);
        }
        draw_button_text("+m", &inc_min, 28, BLACK);

        // inc_hour 
        if(mouse_is_over(&inc_hour)) {
            draw_button(&inc_hour, GRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                hour++;
            }
        } else {
            draw_button(&inc_hour, WHITE);
        }
        draw_button_text("+h", &inc_hour, 28, BLACK);

        
        // saati çizmece
        DrawText(TextFormat("%02d:%02d:%02d", hour, min, sec), 50, 50, 100, WHITE);

        EndDrawing();
    }



    return 0;
}