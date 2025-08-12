#include <memory>

#include "app.hpp"

int main(void) {
    auto app = std::make_unique<TFMApp>();
    app->run();
    std::exit(0);
}