    #include <conio.h>
    #include <fstream>
    #include <iostream>
    #include <string>
    #include "game.h"
    #include "globals.h"
    #include "utility.h"
    #include "json.hpp"
    using json = nlohmann::json;

    PlayerCharacter player;
    EnemyCharacter enemy;
    std::string selectedArea;
    bool battleEnded = false;

    void playerTurn() {
        // Display arrowhead
        goTo(29, 10); std:: cout << " ";
        goTo(29, 11); std:: cout << " ";
        goTo(28, 10); std:: cout << "/";
        goTo(28, 11); std:: cout << "\\";

        // Do player turn
        // Get action option
        int y[] = {18, 20, 18, 20};
        int x[] = {15, 15, 36, 35};
        int optionCount = 4;
        int current = 0;
        char key;

        while (true) {
            for (int i = 0; i < optionCount; ++i) {
            // Left cursor
            goTo(x[i] - 3, y[i]);
            std::cout << (i == current ? ">" : " ");

            // Right cursor
            goTo(x[i] + length, y[i]);
            std::cout << (i == current ? "<" : " ");
            }

            key = _getch();

            // Play SFX based on key pressed
            if (key == 75 || key == 77) playSFX("navigateOption.wav", 30);
            else playSFX("selectOption.wav", 50);

            if (key == 75) { // Left Arrow
            current = (current - 1 + optionCount) % optionCount;
            } else if (key == 77) { // Right Arrow
            current = (current + 1) % optionCount;
            } else if (key == 13) { // Enter
            break;
            }

            // Play SFX based on key pressed
            if (key == 72 || key == 80) playSFX("navigateOption.wav", 30);
            else playSFX("selectOption.wav", 50);

            if (key == 72) { // Up Arrow
            current = (current - 1 + optionCount) % optionCount;
            } else if (key == 80) { // Down Arrow
            current = (current + 1) % optionCount;
            } else if (key == 13) { // Enter
            break;
            }
        }

        std::cin.get();
        goTo(28, 10); std:: cout << " ";
        goTo(28, 11); std:: cout << " ";
    }

    void enemyTurn() {
        // Display arrowhead
        goTo(31, 10); std:: cout << " ";
        goTo(31, 11); std:: cout << " ";
        goTo(32, 10); std:: cout << "\\";
        goTo(32, 11); std:: cout << "/";

        // Do enemy turn
        delayS(1);
        goTo(32, 10); std:: cout << " ";
        goTo(32, 11); std:: cout << " ";
    }

    void displayHPBar(int currentHealth, int maxHealth) {
        float tenPercent = maxHealth / 10.0f;
        int tickCount = static_cast<int>(currentHealth / tenPercent);

        // Ensure tickCount is within [0, 10]
        tickCount = std::clamp(tickCount, 0, 10);

        std::string filledBar(tickCount, '#');         // Repeat '#' tickCount times
        std::string emptyBar(10 - tickCount, '-');     // Repeat '-' for the rest

        std::cout << '[' << filledBar << emptyBar << ']';
    }

    void loadPlayer() {
        // Load character stats save file
        std::ifstream fileCharacterStats("data/characterStats.json");

        if (!fileCharacterStats.is_open()) {
            std::cerr << "Could not open characterStats.json\n";
            return;
        }

        json playerJson;
        fileCharacterStats >> playerJson;

        // Load player data
        player.name = playerJson[save]["name"];
        player.level = playerJson[save]["level"];
        player.maxHealth = playerJson[save]["maxHealth"];
        player.currentHealth = playerJson[save]["currentHealth"];
        player.basePhysicalDamage = playerJson[save]["basePhysicalDamage"];
        player.baseMagicDamage = playerJson[save]["baseMagicDamage"];
        player.baseArmor = playerJson[save]["baseArmor"];
        player.baseMagicResist = playerJson[save]["baseMagicResist"];

        // DEBUG: Display character's data
        // std::cout << std::setw(20) << "Name: " << name << '\n';
        // std::cout << std::setw(20) << "Level: " << level << '\n';
        // std::cout << std::setw(20) << "Max Health: " << maxHealth << '\n';
        // std::cout << std::setw(20) << "Current Health: " << currentHealth << '\n';
        // std::cout << std::setw(20) << "Physical Damage: " << basePhysicalDamage << '\n';
        // std::cout << std::setw(20) << "Magic Damage: " << baseMagicDamage << '\n';
        // std::cout << std::setw(20) << "Armor: " << baseArmor << '\n';
        // std::cout << std::setw(20) << "Magic Resist: " << baseMagicResist << '\n';
    }

    void loadRandomEnemy() {
        // DEBUG: Display random area & load area's enemy
        // Load save file
        std::ifstream fileEnemy("data/enemy.json");

        if (!fileEnemy.is_open()) {
            std::cerr << "Could not open enemy.json\n";
            return;
        }

        json saveEnemy;
        fileEnemy >> saveEnemy;

        // Get all area names
        std::vector<std::string> areaNames;
        for (auto& [key, value] : saveEnemy.items()) {
            areaNames.push_back(key);
        }

        // Choose random area
        int indexArea = generateRandomNumber(areaNames.size());
        selectedArea = areaNames[indexArea];

        // Get enemy list from that area
        json enemies = saveEnemy[selectedArea];

        if (enemies.empty()) {
            std::cerr << "No enemies in selected area.\n";
            return;
        }

        // Choose random enemy
        int indexEnemy = generateRandomNumber(enemies.size());
        json enemyJson = enemies[indexEnemy];

        // Load enemy data
        enemy.id = indexEnemy;
        enemy.name = enemyJson["name"];
        enemy.level = enemyJson["level"];
        enemy.maxHealth = enemyJson["maxHealth"];
        enemy.currentHealth = enemyJson["maxHealth"]; // assuming full HP at start
        enemy.basePhysicalDamage = enemyJson["basePhysicalDamage"];
        enemy.baseMagicDamage = enemyJson["baseMagicDamage"];
        enemy.baseArmor = enemyJson["baseArmor"];
        enemy.baseMagicResist = enemyJson["baseMagicResist"];

        // DEBUG: Output
        // std::cout << "Random Area: " << selectedArea << "\n";
        // std::cout << "Enemy: " << enemy["name"] << "\n";
        // std::cout << "Max Health: " << enemy["maxHealth"] << "\n";
        // std::cout << "Physical Damage: " << enemy["basePhysicalDamage"] << "\n";
        // std::cout << "Magic Damage: " << enemy["baseMagicDamage"] << "\n";
        // std::cout << "Armor: " << enemy["baseArmor"] << "\n";
        // std::cout << "Magic Resist: " << enemy["baseMagicResist"] << "\n";
        // std::cout << "Description: " << enemy["description"] << "\n";
    }

    void displayArrow(std::string direction) {
        if (direction == "left") {
            // Dislay left-side arrow
            goTo(26, 6); std:: cout << "0";
            goTo(27, 7); std:: cout << "\\";
            goTo(28, 8); std:: cout << "\\";
            goTo(29, 9); std:: cout << "\\";
            goTo(30, 10); std:: cout << "|";
            goTo(30, 11); std:: cout << "|";
            goTo(29, 12); std:: cout << "/";
            goTo(28, 13); std:: cout << "/";
            goTo(27, 14); std:: cout << "/";
            goTo(26, 15); std:: cout << "0";

        } else if (direction == "right") {
            // Dislay right-side arrow
            goTo(34, 6); std:: cout << "0";
            goTo(33, 7); std:: cout << "/";
            goTo(32, 8); std:: cout << "/";
            goTo(31, 9); std:: cout << "/";
            goTo(30, 10); std:: cout << "|";
            goTo(30, 11); std:: cout << "|";
            goTo(31, 12); std:: cout << "\\";
            goTo(32, 13); std:: cout << "\\";
            goTo(33, 14); std:: cout << "\\";
            goTo(34, 15); std:: cout << "0";
        }
    }

    void displayDivider() {
        goTo(1, 16);
        displaySpacedFormat(60, '=');
        goTo(1, 1);
    }

    void displayHeader() {
        displaySpacedFormat(60, '#');
        space(1);
        centerText('"' + selectedArea + '"');
        space(2);
        displaySpacedFormat(60, '=');
    }

    void displayPlayerStats() {
        space(1);
        moveCursor(0, 0, 3, 0); std::cout << player.name << " ( Lvl. " << player.level << " ) \n";
        moveCursor(0, 0, 3, 0); displayHPBar(player.currentHealth, player.maxHealth); space(1);
        moveCursor(0, 0, 3, 0); std::cout << player.currentHealth << " / " << player.maxHealth << "\n";
        space(1);
        moveCursor(0, 0, 4, 0); std::cout << player.basePhysicalDamage << " >" << std::setw(8) << std::setfill('-') << "< AD\n";
        moveCursor(0, 0, 4, 0); std::cout << player.baseMagicDamage << " >" << std::setw(8) << std::setfill('-') << "< AP\n";
        moveCursor(0, 0, 4, 0); std::cout << player.baseArmor << " >" << std::setw(8) << std::setfill('-') << "< DF\n";
        moveCursor(0, 0, 4, 0); std::cout << player.baseMagicResist << " >" << std::setw(8) << std::setfill('-') << "< MR\n";
    }

    void displayEnemyStats() {
        int offset = 7 - enemy.name.length();
        if (offset < 0) goTo(40 + offset, 7);
        else if (offset > 0) goTo(40 + offset, 7);

        std::cout << " ( Lvl. " << enemy.level << " ) " << enemy.name << '\n';
        goTo(47, 8); displayHPBar(enemy.currentHealth, enemy.maxHealth); space(1);
        goTo(54, 9); std::cout << enemy.currentHealth << " / " << enemy.maxHealth << "\n";

        goTo(49, 11); std::cout << "AD >" << std::setw(4) << std::setfill('-') << "< " << enemy.basePhysicalDamage;
        goTo(49, 12); std::cout <<  "AP >" << std::setw(4) << std::setfill('-') << "< " << enemy.baseMagicDamage;
        goTo(49, 13); std::cout << "DF >" << std::setw(4) << std::setfill('-') << "< " << enemy.baseArmor;
        goTo(49, 14); std::cout << "MR >" << std::setw(4) << std::setfill('-') << "< " << enemy.baseMagicResist;
    }

    void displayActions() {
        goTo(15, 18); std::cout << "[ ATTACK ]";
        goTo(15, 20); std::cout << "[ ITEMS ]";
        goTo(36, 18); std::cout << "[ SKILLS ]";
        goTo(35, 20); std::cout << "[ RETREAT ]";
        goTo(1, 22); displayFormat(60, '#');
    }

    void displayGameArea() {
        displayDivider();
        displayHeader();

        displayPlayerStats();
        displayEnemyStats();

        displayArrow("left");
        displayArrow("right");

        displayActions();
    }

    void startGame() {
        // Load player's data from .json
        loadPlayer();

        // Load random enemy from a random area
        loadRandomEnemy();

        while (!battleEnded) {
            // Display game area
            displayGameArea();

            playerTurn();
            enemyTurn();
        }

        std::cout << "Battle ended!\n";
    }