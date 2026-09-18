# 01 — Guessing Number Game

A console-based number guessing game written in C, featuring three game modes, difficulty levels, warmer/colder hints, and persistent high score tracking.

Part of the [C-PROJECTS](../) repository.

---

## Features

**Single Player** — Pick a difficulty and guess the secret number before your attempts run out.

| Difficulty | Range | Attempts |
|------------|-------|----------|
| Easy       | 1–50  | 10 |
| Medium     | 1–100 | 7  |
| Hard       | 1–200 | 6  |
| Extreme    | 1–500 | 5  |

- Greater / smaller feedback after every guess
- Warmer / colder hints based on how your distance from the answer changes
- Time taken and attempts used shown on a win
- A beep on game over

**Reverse Mode** — You think of a number, the computer guesses it. Uses binary search over the range you choose, so it converges in about `log₂(n)` guesses. Respond with `h` (higher), `l` (lower) or `c` (correct): any other input is flagged as an attempt to cheat.

**Multiplayer Mode** — Two players alternate turns on a custom range. First correct guess wins; per-player attempt counts and total time are reported.

**High Score** — The lowest single-player attempt count is stored in `highscore.txt` and compared on every completed round.

**Input Validation** — Non-numeric input is rejected and re-prompted instead of breaking the input stream.

**Colored Output** _ Colored terminal output via ANSI escape code macros for menus and feedback.
---

## Project Structure

```
01-Guessing-Number-Game/
├── .gitignore         # Ignores the compiled binary
├── README.md
├── guessing_game.c    # Complete source
└── highscore.txt      # Best single-player score (auto-created)  
```

---

## Build & Run

Requires **GCC (MinGW)** on **Windows** — the project uses `windows.h` for `Beep()` and ANSI escape codes for colored output.

```bash
gcc guessing_game.c -o a.exe
a.exe
```

> If colors show as raw escape codes, use Windows Terminal or Command Prompt on Windows 10+, where ANSI sequences are supported by default.

---

## How It Works

| Component | Purpose |
|-----------|---------|
| `main()` | Menu loop and mode dispatch, with playagain prompt |
| `playgame()` | Single-player round; returns attempts used; beep on losing |
| `reversemode()` | Binary-search guessing by the computer; handles cheating |
| `multiplayermode()` | Turn-based two-player round; first to guess wins |
| `getvalidint()` | Safe integer input with buffer flush |
| `updatehighscore()` | Reads/writes `highscore.txt` |
| `print_menu()` / `mainmenu()` | Formatted console UI |

---

## Possible Improvements

- Replace `rand()` seeding on every menu entry with a single `srand()` call in `main()`
- Store separate high scores per difficulty
- Cross-platform build by replacing `windows.h` and `Beep()`

---

**Developer:** Piyush Verma · Haryana, India
