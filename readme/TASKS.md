# TASKS

***TODO: Show hidden files (.dotfiles)***

✅ 1. Core File Navigation

~~Directory tree traversal (recursive and iterative)~~

~~View contents of current directory~~

~~Change current directory (cd)~~

~~Go up one directory (..)~~

~~Absolute and relative path handling~~

~~Auto-expand symlinks~~

~~Display breadcrumb (e.g., /home/aziz/Documents/Projects)~~

📄 2. File Operations

Copy files and directories (with overwrite prompt)

Move/rename files and directories

Delete files

Delete directories recursively

Create new files

Create new directories

Duplicate file

    File touch (update modification timestamp)

📦 3. File Metadata and Info

File size (in KB, MB, GB, human-readable)

File permissions (rwx-style and octal)

File owner and group

Last modification time

File type detection (regular, directory, symlink, device, pipe)

    MIME type detection (optional via libmagic)

🔍 4. Search and Filtering

Search files/folders by name

Regex-based filename search

Search by extension/type

Filter by size, date modified

Recursive search

    Live search as you type

🔧 5. Terminal Interface (UI/UX)

Clear and colored UI (use ncurses or termcolor)

Two-pane (or multi-pane) interface

Keyboard shortcuts (Vim-style or customizable)

File highlighting based on type (e.g., directories blue, .cpp green)

Inline preview for text files

Custom command bar (at bottom)

Scrollable view for long file lists

Resize-aware UI

Breadcrumb or path bar on top

    Status bar (free space, number of items, current mode)

🧠 6. Modes & State Management

Normal mode (navigate)

Command mode (execute typed commands like :cp, :mv)

Visual/select mode (select multiple items)

Filter/search mode

    Configurable UI themes or layouts

📂 7. Multi-file Selection

Select one/multiple files

Invert selection

Clear selection

Perform batch operations on selected files

    Select by regex/glob pattern

🗃 8. Clipboard Support

Internal clipboard (copy/cut/paste)

Multi-copy buffer

    Persistent clipboard between sessions (optional)

🛠️ 9. File Editing / Integration

Open file in external editor (vim, nano, code)

Inline text viewer for .txt, .md, .cpp etc.

Integration with less, cat, bat

Edit permissions (chmod-like dialog)

    Hex viewer for binary files (optional)

🔐 10. Permissions and Ownership

Show file permissions in human-readable format

Change file permissions (chmod)

Change file owner/group (needs root)

    Check if user has access rights

🗑️ 11. Trash System

Implement custom Trash (like .local/share/Trash)

Soft delete (move to trash)

Restore from trash

Empty trash

    View trash contents

🔁 12. History & Navigation

Navigation history (go back/forward)

Bookmarks for folders

Recently opened files/folders

Favorite folders

    Go to previous directory (cd - behavior)

⚙️ 13. Settings and Config

Config file in ~/.config/yourfm/config.ini or JSON

Keybindings config

Default text editor

UI themes (colors)

    Custom commands/macros

💾 14. Session Management

Save last session (directory, selections)

Auto-restore session on launch

    User config profile switcher (like Git config profiles)

🧪 15. Advanced Features

File preview (images via ASCII/Unicode, optional)

Compare files (diff)

Archive handling (ZIP, TAR, etc.)

Batch rename with regex

File tagging or categorization

Scripting (run .yourfmrc on start)

Plugin support (DLL or .so loading)

File watching (inotify) to auto-refresh when directory changes

    Git integration: show repo status (unstaged, untracked, etc.)

🌍 16. Remote & Network

Open FTP/SFTP connection (via libcurl or system call)

Mount/unmount USB or remote drives

Copy to/from remote server via scp/rsync

    Show network drives

📊 17. Disk Usage Analysis

Show total size of folders

Show largest files/folders in current directory

Tree-like view of disk usage

    Graphical bars (using Unicode) to show usage

🧱 18. Error Handling & Logging

Clear error messages

Log file for operations

Debug mode

Fallback if permission denied

    Detect broken symlinks

🚀 19. Performance

Lazy loading of large folders

Asynchronous directory reading (threading)

Memory usage monitoring

Fast file search using indexing (optional)

    Caching folder listings

🧪 20. Testing & Maintenance

Unit tests (using Catch2, GoogleTest)

Integration tests (script simulated user interaction)

CI support for Linux builds

Memory leak checking (Valgrind, ASan)

    Profiling tools (gprof or perf)

🧠 21. Optional but Clever Additions

Smart open (open file with proper default app)

Syntax-aware preview for code

Terminal emulator inside the file manager

Time travel (view old versions using snapshot fs or Git)

Auto-backup on file overwrite

Fuzzy matching for filenames

    Shell autocompletion support (yourfm --complete)

📚 Suggested Libraries
Purpose	Suggested C++ Libraries
Terminal UI	ncurses, termbox, libtcod
Config parsing	nlohmann/json, inih
File system	<filesystem> (C++17), boost::filesystem
Logging	spdlog, loguru
Testing	Catch2, GoogleTest
Argument parsing	cxxopts, CLI11

make it return empty if u undo many times and reach end.
