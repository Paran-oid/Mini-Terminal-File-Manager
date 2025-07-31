#include "app.hpp"
#include "terminal.hpp"

int main(void) {
    terminal_init();

    TFMApp app;
    app.run();

    terminal_destroy();

    std::exit(0);
}