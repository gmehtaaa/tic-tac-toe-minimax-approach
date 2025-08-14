# Tic Tac Toe — Human vs Computer (Minimax Algorithm)

## Overview
This C++ program lets you play **Tic Tac Toe** against a computer opponent that uses the **Minimax algorithm** to make optimal moves.  
You play as **X**, and the computer plays as **O**.  
The program ensures that the computer **never loses** — it will either win or force a draw.

---

## Features
- **Two-player mode** (Human vs Computer).
- Computer uses **Minimax search** to choose the best possible move.
- Prevents illegal moves by validating player input.
- Detects wins, losses, and draws in real-time.
- Displays the board after each turn.

---

## How the Algorithm Works
1. **Board Representation**:  
   - The board is stored as a `vector<char>` of size 9.  
   - Empty spaces are represented as `' '`.
   
2. **Win and Draw Detection**:  
   - Checks for 3-in-a-row horizontally, vertically, or diagonally.  
   - A draw is declared when no empty spaces remain.

3. **Move Generation**:  
   - Generates all possible moves for the current player.

4. **Minimax Evaluation**:  
   - **`X` (human)** tries to **maximize** the score.  
   - **`O` (computer)** tries to **minimize** the score.  
   - `+1` → Win for X  
   - `-1` → Win for O  
   - `0` → Draw

5. **Best Move Selection**:  
   - The computer evaluates all possible moves and picks the one with the **lowest score** for O.

---

## Example Run

**Input/Output**
Tic Tac Toe - You (X) vs Computer (O)
. . .
. . .
. . .

Enter your move (0-8): 0
X . .
. . .
. . .

Computer thinking...
X O .
. . .
. . .

Enter your move (0-8): 4
X O .
. X .
. . .

Computer thinking...
X O .
O X .
. . .

...

---

## Usage
1. **Compile the program**:
   ```bash
   g++ tictactoe_minimax.cpp -o tictactoe

## Use Case
This program can be used for:

Demonstrating Minimax search in turn-based games.

Understanding game theory and decision-making algorithms.

Creating AI opponents for simple board games.
