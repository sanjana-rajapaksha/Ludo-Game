# Ludo Game (Console-Based)

A C-language implementation of the classic Ludo board game for 2–4 players, playable via the command line.

## 🎮 Features

- Console-based gameplay for 4 players: Yellow, Blue, Red, and Green
- Dice rolling with automatic move selection
- Movement of pieces across the board and into the home column
- Piece capturing logic implemented
- Auto selection of the first player based on dice rolls
- Turn-based play with logic for 6s and multiple dice rolls
- Position tracking of each piece with clear status updates

## 🧠 Game Logic

- Each player gets a turn to roll the dice.
- Rolling a 6 allows either:
  - Bringing a new piece onto the board (if under 4 total out-of-base),
  - Or re-rolling (up to 3 times max if 6s keep occurring).
- Pieces move according to dice rolls and enter the home straight once they complete a full board lap.
- A piece reaching the end of the home column scores a point for that player.
- Capturing sends opponent's pieces back to their base.

## 🛠️ Compilation

To compile the game:

```bash
gcc -o ludo ludo18.c
