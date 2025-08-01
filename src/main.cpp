#include <memory>

#include "app.hpp"
#include "terminal.hpp"

int main(void) {
    terminal_init();

    std::unique_ptr<TFMApp> app = std::make_unique<TFMApp>();
    app->run();

    terminal_destroy();

    std::exit(0);
}