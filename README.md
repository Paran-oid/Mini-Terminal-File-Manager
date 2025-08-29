# Terminal File Manager (TFM)

**Terminal File Manager (TFM)** is a modular, extensible file manager for the terminal, written in modern C++. It aims to provide a full-featured, responsive, and user-friendly file management experience entirely within your terminal window.

<img width="1450" height="320" alt="Screenshot from 2025-08-29 16-27-36" src="https://github.com/user-attachments/assets/5a3777d2-702a-493b-a4a9-e80cf9f1735d" />

## Features

- **Full Terminal UI**: Navigate and manage files and directories from a robust terminal interface.
- **Modular Design**: Core components like file management, command handling, rendering, input, and dialogs are separated for easier maintenance and extensibility.
- **Efficient Rendering**: Fast, smooth redraws using a custom renderer that efficiently updates only what’s needed.
- **Command-Line Integration**: Powerful command line for executing file operations and custom commands.
- **Cross-Platform**: Uses CMake and Curses/Ncurses for compatibility on Linux and other UNIX-like systems.
- **Rich Command System**: Supports command history, parsing, execution, and mapping.
- **Robust Navigation**: Scroll, jump, and manipulate rows and files with intuitive keyboard shortcuts.

## Architecture

TFM is organized into several core modules:
- **App**: Orchestrates all modules and manages the application's lifecycle.
- **Renderer**: Handles drawing and updating the UI based on current state.
- **FileManager**: Encapsulates all file-related operations, following a repository pattern.
- **Input**: Deals with keyboard input and command handling.
- **Rows**: Manages the visible rows (files, directories, etc.) in the UI.
- **Dialogs**: Manages user prompts and confirmations.

## Build & Install

### Requirements

- C++23 compatible compiler (e.g., GCC 13+, Clang 16+)
- [CMake](https://cmake.org/) 3.10+
- [Ncurses/Curses](https://invisible-island.net/ncurses/)
- [Doxygen](https://www.doxygen.nl/) (optional, for documentation)

### Steps

```bash
git clone https://github.com/Paran-oid/Terminal-File-Manager.git
cd Terminal-File-Manager
mkdir build && cd build
cmake ..
make
./TFM  # Run the Terminal File Manager
```

## Usage

- Use arrow keys (or configured shortcuts) to navigate files and directories.
- Enter commands in the command line at the bottom for advanced operations.
- Supports common file operations like copy, move, delete, etc. (see documentation for full list).

## Documentation

- Generate API docs with Doxygen:
  ```bash
  doxygen Doxyfile
  ```
  Docs will be available in the `docs/` directory.

## Contributing

Pull requests and feature suggestions are welcome! Please open an issue first to discuss what you would like to change or add.

## License

[MIT License](LICENSE)

---
