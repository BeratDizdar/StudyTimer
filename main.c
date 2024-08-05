#include <raylib.h>
#include <stdio.h>

#define mode_button_char_size 28
#define max_sec 59
#define max_min 59
#define max_hour 24

///////////////////////////////////
// types

typedef unsigned char byte;
typedef byte flag;

typedef enum timer_modes {
    NONE = 0,
    TIMER,
    STOPWATCH,
    MODE_COUNT,
} timer_modes_t;

// TODO: yazı rengi de ekle
typedef struct button { // buton ama her şeyde kullanılabilir. ;)
    int x, y, w, h;
    Color color_normal, color_hover;
    const char* text;
    int font_size;
    void (*on_click)();
} button_t;

///////////////////////////////////
// Global

float delta_time = 0; 
int sec = 0, min = 0, hour = 0;
flag flag_start;

Color bg_color;

timer_modes_t mode = NONE; 
const char* mode_text[] = {"NONE", "TIMER", "STOPWATCH"};

button_t buton1;

///////////////////////////////////
// Fonksiyonlar

int mouse_is_over(button_t* btn)
{
    return (btn->x < GetMouseX() && btn->x + btn->w > GetMouseX() &&
            btn->y < GetMouseY() && btn->y + btn->h > GetMouseY());
}

void draw_button(button_t* btn)
{
    Color color = mouse_is_over(btn) ? btn->color_hover : btn->color_normal;
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

void mode_timer()
{
    if(sec > max_sec)
    {
        min++;
        sec -= 60;
    }

    if(flag_start) {
        if(hour < 1 && min < 1 && sec < 1) {
            sec = 0, min = 0, hour = 0;
            mode = NONE;
            buton1.text = mode_text[mode];
        }

        delta_time += GetFrameTime();
        if(delta_time > 1){
            delta_time = 0;
            if(sec > 0) {
                sec--;
            } else if(min > 0) {
                min--;
                sec = max_sec;
            } else if(hour > 0) {
                hour--;
                min = max_min;
                sec = max_sec;
            }
        }

        if(hour < 0) hour = 0;
        if(min < 0) min = 0;
        if(sec < 0) sec = 0;         
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

///////////////////////////////////
// Buton Callbackleri

void mode_change() {
    flag_start = 0;
    mode++;
    if (mode == MODE_COUNT) {mode = 0;}
    buton1.text = mode_text[mode];
}
void change_bg_color() {
    static int current_color_index = 0;
    Color color_palette[] = {BLACK, MAGENTA, BEIGE, DARKPURPLE, DARKGREEN, RED, DARKBROWN, 
                            VIOLET, MAROON, GOLD, DARKGRAY, DARKBLUE, BLUE, GREEN, PURPLE, 
                            ORANGE, YELLOW, LIME, SKYBLUE};
    int palette_size = sizeof(color_palette) / sizeof(color_palette[0]);
    current_color_index = (current_color_index + 1) % palette_size;
    bg_color = color_palette[current_color_index];
}
void start() {
    flag_start = (flag_start) ? 0 : 1;
}

void dec_hour() {if(IsKeyDown(KEY_LEFT_SHIFT)){hour-=10;} else{hour--;}}
void dec_min() {if(IsKeyDown(KEY_LEFT_SHIFT)){min-=10;} else{min--;}}
void dec_sec() {if(IsKeyDown(KEY_LEFT_SHIFT)){sec-=10;} else{sec--;}}
void inc_sec() {if(IsKeyDown(KEY_LEFT_SHIFT)){sec+=10;} else{sec++;}}
void inc_min() {if(IsKeyDown(KEY_LEFT_SHIFT)){min+=10;} else{min++;}}
void inc_hour() {if(IsKeyDown(KEY_LEFT_SHIFT)){hour+=10;} else{hour++;}}
void reset_time() {flag_start = 0; hour = 0; min = 0; sec = 0;}

///////////////////////////////////
// Main

int main() {

    #if defined(_WIN32) || defined(_WIN64)
        // Windows-specific code
        //SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    #elif defined(__linux__)
        // Linux-specific code
        SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    #endif
    
    SetTraceLogLevel(LOG_NONE);

    InitWindow(500, 200, "StudyTimer");
    SetTargetFPS(60);

    flag_start = 0;
      
    bg_color = BLACK; 

    // Buton1 daha önce tanımlanmıştı
    buton1 = (button_t){.x = 10, .y = 10, .w = 80, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = mode_text[mode], .on_click = mode_change};

    button_t btn_dec_hour = {.x = 10, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "-h", .on_click = dec_hour};
    button_t btn_dec_min = {.x = 60, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "-m", .on_click = dec_min};
    button_t btn_dec_sec = {.x = 110, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "-s", .on_click = dec_sec};
    button_t btn_start = {.x = 160, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = " >", .on_click = start};
    button_t btn_inc_sec = {.x = 210, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "+s", .on_click = inc_sec};
    button_t btn_inc_min = {.x = 260, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "+m", .on_click = inc_min};
    button_t btn_inc_hour = {.x = 310, .y = 150, .w = 40, .h = 40, 
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "+h", .on_click = inc_hour};

    button_t btn_reset = {.x = 360, .y = 150, .w = 85, .h = 40,
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "Reset", .on_click = reset_time};

    button_t btn_color = {.x = 405, .y = 10, .w = 85, .h = 40,
        .color_normal = WHITE, .color_hover = GRAY, .font_size = 28, .text = "Color", .on_click = change_bg_color};

    while(!WindowShouldClose())
    {
        //update
        switch (mode) {
        case NONE:
            flag_start = 0;
            buton1.w = 3 * mode_button_char_size;
            break;
        case TIMER:
            buton1.w = 4 * mode_button_char_size;
            mode_timer();
            break;
        case STOPWATCH:
            buton1.w = 7 * mode_button_char_size;
            if(flag_start) {
                mode_stopwatch();
            }
            break;
        default:
            printf("update-switch hatası\n");
            break;
        }

        btn_start.text = (flag_start) ? " !>" : " >";


        // draw
        BeginDrawing();
        ClearBackground(bg_color);

        // mod butonu
        draw_button(&buton1);
        handle_button_click(&buton1);

        // renk butonu
        draw_button(&btn_color);
        handle_button_click(&btn_color);

        // süre butonları
        draw_button(&btn_start);
        handle_button_click(&btn_start);
        draw_button(&btn_dec_hour);
        handle_button_click(&btn_dec_hour);
        draw_button(&btn_dec_min);
        handle_button_click(&btn_dec_min);
        draw_button(&btn_dec_sec);
        handle_button_click(&btn_dec_sec);
        draw_button(&btn_inc_sec);
        handle_button_click(&btn_inc_sec);
        draw_button(&btn_inc_min);
        handle_button_click(&btn_inc_min);
        draw_button(&btn_inc_hour);
        handle_button_click(&btn_inc_hour);
        draw_button(&btn_reset);
        handle_button_click(&btn_reset);

        
        // saati çizmece
        DrawText(TextFormat("%02d:%02d:%02d", hour, min, sec), 50, 50, 100, WHITE);

        EndDrawing();
    }



    return 0;
}