#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
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

class Game
{
public:
    // Methods
    void displayHeader()
    {
        std::cout << "   ___       ___       ___       ___       ___       ___   \n"
                     "  /\\  \\     /\\__\\     /\\  \\     /\\  \\     /\\  \\     /\\  \\  \n"
                     " /::\\  \\   |::L__L   /::\\  \\   /::\\  \\   _\\:\\  \\   /::\\  \\ \n"
                     "/::\\:\\__\\ /::::\\__\\ /:/\\:\\__\\ /:/\\:\\__\\ /\\/::\\__\\ /::\\:\\__\\\n"
                     "\\:\\:\\/  / \\;::;/__/ \\:\\/:/  / \\:\\/:/  / \\::\\/__/  \\/\\::/  /\n"
                     " \\:\\/  /   |::|__|   \\::/  /   \\::/  /   \\:\\__\\     /:/  / \n"
                     "  \\/__/     \\/__/     \\/__/     \\/__/     \\/__/     \\/__/   \n";
    }

    void displayContinueMenu()
    {
        std::cout << "displaying 'continue' menu...\n";
    }

    void displayStartMenu()
    {
        std::ifstream fileSaveFiles("data/saveFiles.json");

        if (!fileSaveFiles.is_open())
        {
            std::cerr << "Could not open saveFiles.json\n";
            return;
        }

        json data;
        fileSaveFiles >> data;

        for (int i = 0; i < data.size(); ++i)
        {
            centerText("[ SAVE #" + std::to_string(i + 1) + " ]");
            space(1);
            displaySpacedFormat(60, '=');

            // Get data from 'saveFiles.json'
            std::string characterName = data[i]["characterName"];
            int level = data[i]["level"];
            int progress = data[i]["progress"];
            std::string saveTimestamp = data[i]["saveTimestamp"];
            int playtimeDuration = data[i]["playtimeDuration"];
            // std::vector<std::string> achievements = data[i]["achievements"];

            // Display savefiles
            std::cout << std::setw(16) << "Name  ||  " << characterName << '\n';
            delayMs(50);
            std::cout << std::setw(16) << "Lvl.  ||  " << level << '\n';
            delayMs(50);
            std::cout << std::setw(16) << "Progress  ||  " << progress << '\n';
            delayMs(50);
            std::cout << std::setw(16) << "Last Saved  ||  " << saveTimestamp << '\n';
            delayMs(50);
            std::cout << std::setw(16) << "Duration  ||  " << playtimeDuration << '\n';
            delayMs(50);
        }
        displayFormat(60, '=');

        // Get main menu option
        int y[] = {1, 8, 15};
        int x[] = {26, 26, 26};
        int selectedSaveFile = getOption(3, "vertical", 11, x, y);

        clearScreen(); // Clear console screen before navigating

        // Load save file
        std::ifstream fileCharacterStats("data/characterStats.json");

        if (!fileCharacterStats.is_open())
        {
            std::cerr << "Could not open characterStats.json\n";
            return;
        }

        json save;
        fileCharacterStats >> save;

        // Get character's data from 'characterStats.json'
        std::string name = save[selectedSaveFile]["name"];
        int level = save[selectedSaveFile]["level"];
        int maxHealth = save[selectedSaveFile]["maxHealth"];
        int currentHealth = save[selectedSaveFile]["currentHealth"];
        int basePhysicalDamage = save[selectedSaveFile]["basePhysicalDamage"];
        int baseMagicDamage = save[selectedSaveFile]["baseMagicDamage"];
        int baseArmor = save[selectedSaveFile]["baseArmor"];
        int baseMagicResist = save[selectedSaveFile]["baseMagicResist"];

        // DEBUG: Display character's data
        // std::cout << std::setw(20) << "Name: " << name << '\n';
        // std::cout << std::setw(20) << "Level: " << level << '\n';
        // std::cout << std::setw(20) << "Max Health: " << maxHealth << '\n';
        // std::cout << std::setw(20) << "Current Health: " << currentHealth << '\n';
        // std::cout << std::setw(20) << "Physical Damage: " << basePhysicalDamage << '\n';
        // std::cout << std::setw(20) << "Magic Damage: " << baseMagicDamage << '\n';
        // std::cout << std::setw(20) << "Armor: " << baseArmor << '\n';
        // std::cout << std::setw(20) << "Magic Resist: " << baseMagicResist << '\n';

        // Start game
    }

    void displayAchievementsMenu()
    {
        std::cout << "displaying 'achievements' menu...\n";
    }

    void displayMainMenu()
    {
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

        // Get main menu option
        int y[] = {14, 16, 18, 20};
        int x[] = {24, 24, 24, 24};
        int option_selected = getOption(4, "vertical", 16, x, y);

        clearScreen(); // Clear console screen before navigating

        // Navigate based on selected option
        switch (option_selected)
        {
        case 0:
        {
            Game::displayContinueMenu();
            break;
        }
        case 1:
        {
            Game::displayStartMenu();
            break;
        }
        case 2:
        {
            Game::displayAchievementsMenu();
            break;
        }
        case 3:
        {
            exit(0);
        }
        }
        std::cin.get();
    }
};

int main()
{
    // 1. Create instance of 'Game'
    Game start_game;

    // 2. Play background music
    playBackgroundMusic("backgroundMusic.wav", 100);

    // 3. Hide cursor
    hideCursor();

    // 4. Display game main menu
    start_game.displayMainMenu();
    return 0;
}