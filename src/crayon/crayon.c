#include "crayon.h"

void crayon_bold(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BOLD, stream);
}

void crayon_dim(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(DIM, stream);
}

void crayon_italic(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(ITALIC, stream);
}

void crayon_underline(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(UNDERLINE, stream);
}

void crayon_blink(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BLINK, stream);
}

void crayon_reversed(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(REVERSED, stream);
}

void crayon_strikethru(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(STRIKETHRU, stream);
}

void crayon_fg_black(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_BLACK, stream);
}

void crayon_fg_red(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_RED, stream);
}

void crayon_fg_green(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_GREEN, stream);
}

void crayon_fg_yellow(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_YELLOW, stream);
}

void crayon_fg_blue(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_BLUE, stream);
}

void crayon_fg_magenta(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_MAGENTA, stream);
}

void crayon_fg_cyan(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_CYAN, stream);
}

void crayon_fg_white(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_WHITE, stream);
}

void crayon_fg_gray(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(FOREGROUND_GRAY, stream);
}

void crayon_bg_black(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_BLACK, stream);
}

void crayon_bg_red(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_RED, stream);
}

void crayon_bg_green(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_GREEN, stream);
}

void crayon_bg_yellow(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_YELLOW, stream);
}

void crayon_bg_blue(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_BLUE, stream);
}

void crayon_bg_magenta(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
}

void crayon_bg_cyan(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
}

void crayon_bg_white(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_WHITE, stream);
}

void crayon_bg_gray(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(BACKGROUND_GRAY, stream);
}

void crayon_end(BORROWED FILE * stream) {
    if (!stream) {
        return;
    }
    fputs(ENDCRAYON, stream);
}


