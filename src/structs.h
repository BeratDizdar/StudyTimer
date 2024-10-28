#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

// TODO: yazı rengi de ekle
typedef struct button { // buton ama her şeyde kullanılabilir. ;)
    int x, y, w, h;
    int font_size;
    const char* text;
    void (*on_click)();
} button_t;

typedef enum timer_modes {
    NONE = 0,
    TIMER,
    STOPWATCH,
    MODE_COUNT,
} timer_modes_t;


typedef struct app {

} app_t;


#endif