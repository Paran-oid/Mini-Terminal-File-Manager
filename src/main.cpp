#include <cstdlib>
#include <memory>

#include "app.hpp"

int main() {
    auto app = std::make_unique<TFM::App>();
    app->run();
    std::exit(0);
}