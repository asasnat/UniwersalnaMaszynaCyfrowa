# Uniwersalna Maszyna Cyfrowa
For the 2024 OLC CodeJam, I wanted to make a game where you perform maintenance on a room of 60's era computers. However, after discovering that my code had nightmarish memory leakage problems due to having to toy with raw pointers in many different places, I decided to pull out of the jam.

# Final state of the game
You can walk around a room with boxes painted annoying colors - the player (blue) and the computers (green). Every now and then, a computer will experience a failure, which is indicated by it flashing red and green. You can walk up to a broken computer and press space to attempt to fix it. The computer would pop up one of several puzzles, the completion of which will mark the computer as fixed. However, the only puzzle implemented at this point (a wire connecting puzzle) is non-functional, so the game cannot actually be played. Losing the game (by letting a computer stay broken for more than 60 seconds) results in the game spamming "FUCK YOU" in the console to signify a game over.
![image](https://github.com/user-attachments/assets/8e898674-80f8-44fa-81b7-4703b10e4557)

# Name
UMC (short for Uniwersalna Maszyna Cyfrowa) was an early line of computers produced by the Polish company Elrwo in the 1960's.

# Build instructions
Don't
