The goal for this project is to create a minesweeper game that gives you a time limit based off of how many flags you have checked. The more flags you create, the less time you have to make your next move.
seconds per turn = 15 * (.9 ^ flags_set)

How fast can you complete the board while limiting the amount of visual aids you have?

For my sake; logging annoying errors I ran into, having had zero experience with C++:
- CMake needs to be installed on Windows in a folder with no spaces-- the default installation path is "Program Files"
- SFML does not work on the UCRT library. I had to reinstall a C library that used MSVCRT; there were linker errors when I started using the SFML font library.