Casino Simulation Game

This project simulates a casino environment where players can engage in various games such as BlackJack, Roulette, and Slot Machine. Players can bet, win, or lose money while playing these games. The casino keeps track of top players and their balances.


1. Getting Started


Prerequisites:
A C++ compiler (GCC, Clang, etc.)

2. Game Rules

BlackJack
Players are dealt two cards and aim to get a total value of 21 without exceeding it.
Players can choose to 'hit' (take another card) or 'stand' (end their turn).
The dealer also takes cards, but must stand on 17 or higher.
Aces can count as 1 or 11, face cards are worth 10, and other cards are worth their face value.
Roulette
Players can bet on a single number, a color (Red/Black), or whether the number is odd or even.
If the player's bet matches the outcome, they win a payout based on the type of bet.
Slot Machine
Players bet an amount and spin the slot machine.
Payouts are based on the symbols that line up on the reels.

3. Features

Player Class: Manages player information including name and money.
Game Class: Base class for all games, managing common functionalities like betting.
SlotMachine Class: Derived from Game, simulates a slot machine game.
BlackJack Class: Derived from Game, simulates a blackjack game.
Ruletka Class: Derived from Game, simulates a roulette game.
Casino Class: Manages top players and their balances.

4. Dependencies

This project uses standard C++ libraries:
<iostream>
<string>
<vector>
<unordered_map>
<limits>
<fstream>
<algorithm>

5. How to Play

Run the compiled executable.
Enter your name when prompted.
Choose a game from the interface:
1: Play BlackJack
2: Play Roulette
3: Play Slot Machine
4: Show your balance
5: Show top players
6: Exit
Follow the game-specific instructions to place bets and play.

6. File Structure

main.cpp: The main source file containing all game logic and classes.
top_players.txt: File used to store the top players' names and balances.
