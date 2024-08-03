#include <raylib.h>
#include <stdio.h>

#define pixel_in_col 
#define max_sec 60
#define max_min 60
#define max_hour 24

typedef struct button {
    int x, y, w, h;
} button_t;

int mouse_is_over(button_t* btn)
{
    if(btn->x < GetMouseX() && btn->x + btn->w > GetMouseX() && btn->y < GetMouseY() && btn->y + btn->h > GetMouseY())
    {
        return 1;
    }
    return 0;
}


int main() {

    InitWindow(500, 200, "StudyTimer");
    SetTargetFPS(60);
    Font font = LoadFont("monofonto.otf");

    float delta_time = 0; 
    int sec = 0, min = 0, hour = 0;

    button_t buton1 = {.x = 10, .y = 10, .w = 30, .h = 30};

    while(!WindowShouldClose())
    {
        //update
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



        //draw
        BeginDrawing();
        ClearBackground(DARKBROWN);

        if(mouse_is_over(&buton1)) {
            DrawRectangle(buton1.x, buton1.y, buton1.w, buton1.h, DARKBLUE);
        } else {
            DrawRectangle(buton1.x, buton1.y, buton1.w, buton1.h, BLUE);
        }
        
        DrawText(TextFormat("%02d:%02d:%02d", hour, min, sec), 50, 50, 100, WHITE);

        EndDrawing();
    }



    return 0;
}