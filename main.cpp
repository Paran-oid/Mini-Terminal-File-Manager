#include <ncurses.h>

#include "builtins.hpp"
#include "context.hpp"
#include "input.hpp"
#include "render.hpp"

int32_t main(void) {
    TFM_Context context = TFM_Context();
    register_builtins();
    ncurses_init();

    while (1) {
        TFM_screen_refresh(context);
        TFM_input_process(context);
    }

    ncurses_destroy();
    return 0;
}