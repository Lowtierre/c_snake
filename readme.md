# 🐍 Snake Game

A classic terminal-based Snake game written in C. Cross-platform compatible with Windows, Linux, and macOS.

## Features

- Terminal-based graphics using ANSI escape codes
- Score tracking with persistent high scores saved to `score.txt`
- Cross-platform support (Windows, Linux, macOS)

## Requirements

- **GCC** compiler (or any C compiler)
  - Windows: [MinGW](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/)
  - Linux: `sudo apt install gcc` (Debian/Ubuntu) or `sudo dnf install gcc` (Fedora)
  - macOS: `xcode-select --install`

## Download

### Option 1: Clone with Git

```bash
git clone https://github.com/Lowtierre/snake.git
cd snake
```

### Option 2: Download ZIP

1. Click the green **Code** button on GitHub
2. Select **Download ZIP**
3. Extract the archive
4. Open a terminal in the extracted folder

## Compile

### Windows (Command Prompt or PowerShell)

```bash
gcc snake.c -o snake.exe
```

### Linux / macOS

```bash
gcc snake.c -o snake
```

## Run

### Windows

```bash
.\snake.exe
```

### Linux / macOS

```bash
./snake
```

## Controls

| Key | Action     |
| --- | ---------- |
| ↑   | Move Up    |
| ↓   | Move Down  |
| ←   | Move Left  |
| →   | Move Right |

## How to Play

1. Enter your username when prompted
2. Use arrow keys to control the snake
3. Eat the fruits (██) to grow longer
4. Avoid hitting the walls or your own body
5. Try to beat your high score!

## File Structure

```
snake/
├── snake.c      # Main source code
├── score.txt    # High scores (auto-generated)
└── readme.md    # This file
```

## License

MIT License - Feel free to use and modify!
