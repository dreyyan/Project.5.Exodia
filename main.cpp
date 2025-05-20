#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "Entity.h"
#include "utility.h"

class Game {
public:
    // Methods
    void displayHeader() {
        std::cout <<
        "   ___       ___       ___       ___       ___       ___   \n"
        "  /\\  \\     /\\__\\     /\\  \\     /\\  \\     /\\  \\     /\\  \\  \n"
        " /::\\  \\   |::L__L   /::\\  \\   /::\\  \\   _\\:\\  \\   /::\\  \\ \n"
        "/::\\:\\__\\ /::::\\__\\ /:/\\:\\__\\ /:/\\:\\__\\ /\\/::\\__\\ /::\\:\\__\\\n"
        "\\:\\:\\/  / \\;::;/__/ \\:\\/:/  / \\:\\/:/  / \\::\\/__/  \\/\\::/  /\n"
        " \\:\\/  /   |::|__|   \\::/  /   \\::/  /   \\:\\__\\     /:/  / \n"
        "  \\/__/     \\/__/     \\/__/     \\/__/     \\/__/     \\/__/   \n";
    }

    void displayMainMenu() {
        displayFormat(60, '#');
        space(1);
        displayHeader();
        space(1);
        centerText(" ====================== [ v1.0 ] ====================== ");
        space(2);
        displayFormat(60, '#');

        space(2);
        centerText(" [---CONTINUE---] ");
        space(2);
        centerText(" [--START GAME--] ");
        space(2);
        centerText(" [-ACHIEVEMENTS-] ");
        space(2);
        centerText(" [-----EXIT-----] ");
        space(2);
        displayFormat(60, '#');
        std::cin.get();
    }
};

int main() {
    Game start_game;
    // Create player
    Player player(
        "Hero", 1, 5,
        1, 1,           // Base Physical & Magic Damage
        1, 1,           // Base Armor & Magic Resist
        2, 1, 1, 1, 1   // Base Ups
    );

    start_game.displayMainMenu();
    return 0;
}