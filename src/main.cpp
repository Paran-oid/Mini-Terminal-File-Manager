#include <ncurses.h>

#include "config.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "terminal.hpp"

// Main loop

int main(void) {
    terminal_init();
    TFMConfig conf;
    TFMRenderer renderer(conf);
    TFMInput input(conf);

    // TODO:
    /*
     *	Make sure rows are trackers just like in SCOOM
     *	Make sure the cursor gets updated according to the point getting
     *clicked Create a Renderer and InputHandler class and make them do
     *their jobs Just follow CHECKLIST.md
     */
    while (1) {
        renderer.display();
        if (input.process() == 2) {
            break;
        }
    }

    terminal_destroy();
    std::exit(0);
}