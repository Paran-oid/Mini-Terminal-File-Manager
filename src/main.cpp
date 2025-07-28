#include <ncurses.h>

#include "config.hpp"
#include "terminal.hpp"

// Main loop

int main(void) {
    terminal_init();
    TFMConfig conf;

    // TODO:
    /*
     *	Make sure rows are trackers just like in SCOOM
     *	Make sure the cursor gets updated according to the point getting clicked
     *	Create a Renderer and InputHandler class and make them do their jobs
     *	Just follow CHECLIST.md
     */

    while (1) {
        // renderer.refresh_screen(conf);
        // input.process(conf);
    }

    terminal_destroy();
    std::exit(0);
}