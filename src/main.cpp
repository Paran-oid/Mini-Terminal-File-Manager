#include <memory>

#include "app.hpp"

int main(void) {
    std::unique_ptr<TFMApp> app = std::make_unique<TFMApp>();
    app->run();
    std::exit(0);
}