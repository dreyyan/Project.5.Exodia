#include <fstream>
#include <iostream>
#include <string>
#include "game.h"
#include "globals.h"
#include "utility.h"
#include "json.hpp"
using json = nlohmann::json;

void displayHPBar(int currentHealth, int maxHealth) {
    
}

void loadRandomEnemy() {

}

void displayGameArea() {

}

void startGame() {
    // Load character stats save file
    std::ifstream fileCharacterStats("data/characterStats.json");

    if (!fileCharacterStats.is_open()) {
        std::cerr << "Could not open characterStats.json\n";
        return;
    }

    json player;
    fileCharacterStats >> player;

    // Get character's data from 'characterStats.json'
    std::string name = player[save]["name"];
    int level = player[save]["level"];
    double maxHealth = player[save]["maxHealth"];
    double currentHealth = player[save]["currentHealth"];
    double basePhysicalDamage = player[save]["basePhysicalDamage"];
    double baseMagicDamage = player[save]["baseMagicDamage"];
    double baseArmor = player[save]["baseArmor"];
    double baseMagicResist = player[save]["baseMagicResist"];

    // DEBUG: Display character's data
    // std::cout << std::setw(20) << "Name: " << name << '\n';
    // std::cout << std::setw(20) << "Level: " << level << '\n';
    // std::cout << std::setw(20) << "Max Health: " << maxHealth << '\n';
    // std::cout << std::setw(20) << "Current Health: " << currentHealth << '\n';
    // std::cout << std::setw(20) << "Physical Damage: " << basePhysicalDamage << '\n';
    // std::cout << std::setw(20) << "Magic Damage: " << baseMagicDamage << '\n';
    // std::cout << std::setw(20) << "Armor: " << baseArmor << '\n';
    // std::cout << std::setw(20) << "Magic Resist: " << baseMagicResist << '\n';

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
    std::string selectedArea = areaNames[indexArea];

    // Get enemy list from that area
    json enemies = saveEnemy[selectedArea];

    if (enemies.empty()) {
        std::cerr << "No enemies in selected area.\n";
        return;
    }

    // Choose random enemy
    int indexEnemy = generateRandomNumber(enemies.size());
    json enemy = enemies[indexEnemy];

    // DEBUG OUTPUT
    // std::cout << "Random Area: " << selectedArea << "\n";
    // std::cout << "Enemy: " << enemy["name"] << "\n";
    // std::cout << "Max Health: " << enemy["maxHealth"] << "\n";
    // std::cout << "Physical Damage: " << enemy["basePhysicalDamage"] << "\n";
    // std::cout << "Magic Damage: " << enemy["baseMagicDamage"] << "\n";
    // std::cout << "Armor: " << enemy["baseArmor"] << "\n";
    // std::cout << "Magic Resist: " << enemy["baseMagicResist"] << "\n";
    // std::cout << "Description: " << enemy["description"] << "\n";

    // displayGameArea();
    // DEBUG: Move this logic to displayGameArea()

    // Display divider
    displayVLine(30, 6, 20, '|');
    goTo(1, 1);

    // Display header
    displaySpacedFormat(60, '#');
    space(1);
    centerText(selectedArea);
    space(2);
    displaySpacedFormat(60, '#');

    // Display battle area
    space(1);
    moveCursor(0, 0, 10, 0); std::cout << name << " [ Lvl. " << level << " ] \n";
    displayHPBar(currentHealth, maxHealth);
    moveCursor(0, 0, 10, 0); std::cout << currentHealth << " / " << maxHealth << " HP\n";
    space(1);
    displaySpacedFormat(60, '#');

    // Display player's stats
    space(1);
    moveCursor(0, 0, 18, 0); std::cout << basePhysicalDamage << ' ' << std::setw(8) << std::setfill('-') << " AD\n";
    moveCursor(0, 0, 18, 0); std::cout << baseMagicDamage << ' ' << std::setw(8) << std::setfill('-') << " AP\n";
    moveCursor(0, 0, 18, 0); std::cout << baseArmor << ' ' << std::setw(8) << std::setfill('-') << " DF\n";
    moveCursor(0, 0, 18, 0); std::cout << baseMagicResist << ' ' << std::setw(8) << std::setfill('-') << " MR\n";
}