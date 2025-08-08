#include <memory>

#include "app.hpp"

// TODO:
/*
         seperate concerns for commands:
        ✅ Better Architecture: Split by Domain

		Here’s a clean modular way to structure it:

		src/
		├── commands/
		│   ├── CommandHandler.hpp / cpp            ← Main parser (dispatches based on
		input) │   ├── FileCommandHandler.hpp / cpp        ← Handles ls, cd, cat, mkdir,
		etc. │   ├── UserCommandHandler.hpp / cpp        ← For whoami, passwd, login...
		│   ├── SystemCommandHandler.hpp / cpp      ← For time, shutdown, clear...

		Each class handles a category of commands. Example:
		📁 FileCommandHandler

			ls_func()

			cd_func()

			mkdir_func()

			touch_func()

			cat_func()

		📁 UserCommandHandler

			whoami_func()

			login_func()

		📁 SystemCommandHandler

			clear_func()

			time_func()
*/

int main(void) {
    std::unique_ptr<TFMApp> app = std::make_unique<TFMApp>();
    app->run();
    std::exit(0);
}