#include <memory>

#include "app.hpp"

// TODO: make cursor add char on CURSOR CURRENT POSITION FFS

int main(void) {
    auto app = std::make_unique<TFMApp>();
    app->run();
    std::exit(0);
}