#include "../include/w64/raylib.h"
#include <stdio.h>

#include "structs.h"
#include "button.h"

///////////////////////////////////
// Global

float delta_time = 0; 
int sec = 0, min = 0, hour = 0;
flag flag_start;

mColor bg_color;

timer_modes_t mode = NONE; 
const char* mode_text[] = {"NONE", "TIMER", "STOPWATCH"};

button_t buton1;
Music badapple;

///////////////////////////////////
// Fonksiyonlar

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
            PlayMusicStream(badapple);
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

    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(500, 200, "StudyTimer - Kakam geldi versiyon");
    SetWindowIcon(LoadImage("studyt.ico"));
    SetTargetFPS(60);
    InitAudioDevice();

    flag_start = 0;
      
    bg_color = BLACK; 

    // Buton1 daha önce tanımlanmıştı
    buton1 = create_button(10, 10, 80, 40, 28, mode_text[mode], mode_change);
    button_t btn_dec_hour = create_button(10, 150, 40, 40, 28, "-h", dec_hour);
    button_t btn_dec_min = create_button(60, 150, 40, 40, 28, "-m", dec_min);
    button_t btn_dec_sec = create_button(110, 150, 40, 40, 28, "-s", dec_sec);
    button_t btn_start = create_button(160, 150, 40, 40, 28, " >", start);
    button_t btn_inc_sec = create_button(210, 150, 40, 40, 28, "+s", inc_sec);
    button_t btn_inc_min = create_button(260, 150, 40, 40, 28, "+m", inc_min);
    button_t btn_inc_hour = create_button(310, 150, 40, 40, 28, "+h", inc_hour);
    button_t btn_reset = create_button(360, 150, 85, 40, 28, "Reset", reset_time);
    button_t btn_color = create_button(405, 10, 85, 40, 28, "Color", change_bg_color);

    Image stopwatch = LoadImage("../resource/stopwatch.png");
    Image timer = LoadImage("../resource/timer.png");
    ImageResize(&stopwatch, 50, 50);
    ImageResize(&timer, 50, 50);

    //TODO: bunu alarm olarak ekle
    badapple = LoadMusicStream("../sound/alarm1.wav");
    
    while(!WindowShouldClose())
    {
        //update
        SetWindowFocused();
        switch (mode) {
        case NONE:
            UpdateMusicStream(badapple);
            flag_start = 0;
            buton1.w = MeasureText(buton1.text, buton1.font_size) + 20;
            break;
        case TIMER:
            buton1.w = MeasureText(buton1.text, buton1.font_size) + 20;
            mode_timer();
            break;
        case STOPWATCH:
            buton1.w = MeasureText(buton1.text, buton1.font_size) + 20;
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

        if(GetMouseY() < 50){
            // mod butonu
            update_button(&buton1, WHITE, GRAY);

            // renk butonu
            // TODO: fareyi üzerine getirince renk paneli açılsın.
            update_button(&btn_color, WHITE, GRAY);
        }
        else {
            if(mode == TIMER) {
                DrawTexture(LoadTextureFromImage(timer), 5, 5, WHITE);
            }
            else if(mode == STOPWATCH) {
                DrawTexture(LoadTextureFromImage(stopwatch), 5, 5, WHITE);
            }
        }
        
        

        // süre butonları
        if(GetMouseY() > 150) {
            update_button(&btn_start, WHITE, GRAY);
            update_button(&btn_dec_hour, WHITE, GRAY);
            update_button(&btn_dec_min, WHITE, GRAY);
            update_button(&btn_dec_sec, WHITE, GRAY);
            update_button(&btn_inc_sec, WHITE, GRAY);
            update_button(&btn_inc_min, WHITE, GRAY);
            update_button(&btn_inc_hour, WHITE, GRAY);
            update_button(&btn_reset, WHITE, GRAY);
            update_button(&btn_reset, WHITE, GRAY);
        }
        
        // saati çizmece
        const char* time_text = TextFormat("%02d:%02d:%02d", hour, min, sec);
        int text_width = MeasureText(time_text, 100); // Metnin genişliğini ölç
        int screen_center_x = GetScreenWidth() / 2; // Ekranın ortası
        DrawText(time_text, screen_center_x - text_width / 2, 50, 100, WHITE);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}