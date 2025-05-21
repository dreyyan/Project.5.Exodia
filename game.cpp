#include <fstream>
#include <iostream>
#include <string>
#include "game.h"
#include "globals.h"
#include "json.hpp"
using json = nlohmann::json;

void startGame() {
    // Load save file
    std::ifstream fileCharacterStats("data/characterStats.json");

    if (!fileCharacterStats.is_open()) {
        std::cerr << "Could not open characterStats.json\n";
        return;
    }

    json save;
    fileCharacterStats >> save;

    // Get character's data from 'characterStats.json'
    std::string name = save[::save]["name"];
    int level = save[::save]["level"];
    double maxHealth = save[::save]["maxHealth"];
    double currentHealth = save[::save]["currentHealth"];
    double basePhysicalDamage = save[::save]["basePhysicalDamage"];
    double baseMagicDamage = save[::save]["baseMagicDamage"];
    double baseArmor = save[::save]["baseArmor"];
    double baseMagicResist = save[::save]["baseMagicResist"];

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