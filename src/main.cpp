#include <cstdlib>
#include <memory>

#include "app.hpp"

int main() {
    auto app = std::make_unique<TFMApp>();
    app->run();
    std::exit(0);
}