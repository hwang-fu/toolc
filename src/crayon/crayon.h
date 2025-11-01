#pragma once

#include <stdio.h>

#include "generic.h"

#define BOLD                "\033[1m"
#define DIM                 "\033[2m"
#define ITALIC              "\033[3m"
#define UNDERLINE           "\033[4m"
#define BLINK               "\033[5m"
#define REVERSED            "\033[7m"
#define STRIKETHRU          "\033[9m"

#define BLACK               "\033[30m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define YELLOW              "\033[33m"
#define BLUE                "\033[34m"
#define MAGENTA             "\033[35m"
#define CYAN                "\033[36m"
#define WHITE               "\033[37m"
#define GRAY                "\033[90m"

#define FOREGROUND_BLACK    "\033[30m"
#define FOREGROUND_RED      "\033[31m"
#define FOREGROUND_GREEN    "\033[32m"
#define FOREGROUND_YELLOW   "\033[33m"
#define FOREGROUND_BLUE     "\033[34m"
#define FOREGROUND_MAGENTA  "\033[35m"
#define FOREGROUND_CYAN     "\033[36m"
#define FOREGROUND_WHITE    "\033[37m"
#define FOREGROUND_GRAY     "\033[90m"

#define BACKGROUND_BLACK    "\033[40m"
#define BACKGROUND_RED      "\033[41m"
#define BACKGROUND_GREEN    "\033[42m"
#define BACKGROUND_YELLOW   "\033[43m"
#define BACKGROUND_BLUE     "\033[44m"
#define BACKGROUND_WHITE    "\033[47m"
#define BACKGROUND_GRAY     "\033[100m"

#define ENDCRAYON            "\033[0m"

#define CRAYON_TO_BOLD(x)           BOLD        x ENDCRAYON
#define CRAYON_TO_DIM(x)            DIM         x ENDCRAYON
#define CRAYON_TO_ITALIC(x)         ITALIC      x ENDCRAYON
#define CRAYON_TO_UNDERLINE(x)      UNDERLINE   x ENDCRAYON
#define CRAYON_TO_BLINK(x)          BLINK       x ENDCRAYON
#define CRAYON_TO_REVERSED(x)       REVERSED    x ENDCRAYON
#define CRAYON_TO_STRIKETHRU(x)     STRIKETHRU  x ENDCRAYON

#define CRAYON_TO_BLACK(x)          BLACK       x ENDCRAYON
#define CRAYON_TO_RED(x)            RED         x ENDCRAYON
#define CRAYON_TO_GREEN(x)          GREEN       x ENDCRAYON
#define CRAYON_TO_YELLOW(x)         YELLOW      x ENDCRAYON
#define CRAYON_TO_BLUE(x)           BLUE        x ENDCRAYON
#define CRAYON_TO_MAGENTA(x)        MAGENTA     x ENDCRAYON
#define CRAYON_TO_CYAN(x)           CYAN        x ENDCRAYON
#define CRAYON_TO_WHITE(x)          WHITE       x ENDCRAYON
#define CRAYON_TO_GRAY(x)           GRAY        x ENDCRAYON

#define CRAYON_TO_NO_EFFECT(x)      ENDCRAYON   x ENDCRAYON

void crayon_bold(BORROWED FILE * stream);
void crayon_dim(BORROWED FILE * stream);
void crayon_italic(BORROWED FILE * stream);
void crayon_underline(BORROWED FILE * stream);
void crayon_blink(BORROWED FILE * stream);
void crayon_reversed(BORROWED FILE * stream);
void crayon_strikethru(BORROWED FILE * stream);

void crayon_fg_black(BORROWED FILE * stream);
void crayon_fg_red(BORROWED FILE * stream);
void crayon_fg_green(BORROWED FILE * stream);
void crayon_fg_yellow(BORROWED FILE * stream);
void crayon_fg_blue(BORROWED FILE * stream);
void crayon_fg_magenta(BORROWED FILE * stream);
void crayon_fg_cyan(BORROWED FILE * stream);
void crayon_fg_white(BORROWED FILE * stream);
void crayon_fg_gray(BORROWED FILE * stream);

void crayon_bg_black(BORROWED FILE * stream);
void crayon_bg_red(BORROWED FILE * stream);
void crayon_bg_green(BORROWED FILE * stream);
void crayon_bg_yellow(BORROWED FILE * stream);
void crayon_bg_blue(BORROWED FILE * stream);
void crayon_bg_magenta(BORROWED FILE * stream);
void crayon_bg_cyan(BORROWED FILE * stream);
void crayon_bg_white(BORROWED FILE * stream);
void crayon_bg_gray(BORROWED FILE * stream);

void crayon_end(BORROWED FILE * stream);
