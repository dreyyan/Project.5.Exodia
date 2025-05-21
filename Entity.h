#ifndef ENTITY_H
#define ENTITY_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "Attack.h"
#include "Skill.h"

// Entity > Player, Enemy
// BASE: [ ENTITY ] - [ can either be a player or an enemy ]
class Entity {
    // Stats
    std::string name;
    int level;
    double max_health,
    current_health,
    base_physical_damage,
    base_magic_damage,
    base_armor,
    base_magic_resist;
public:
    // Skills
    std::vector<Attack*> attacks;
    std::vector<Skill*> skills;

    Entity // Constructor
    (std::string n, int l, double mh, double bpd, double bmd, double ba, double bmr)
    : name(n), level(l), max_health(mh), current_health(mh), base_physical_damage(bpd), base_magic_damage(bmd), base_armor(ba), base_magic_resist(bmr) {}

    virtual ~Entity() { // Virtual Destructor
        for (auto attack : attacks) { delete attack; attack = nullptr; }
        for (auto skill : skills) { delete skill; skill = nullptr; }
    }

protected:
    // Getters
    std::string getName() const {
        return name;
    } int getLevel() const {
        return level;
    } double getMaxHealth() const {
        return max_health;
    } double getCurrentHealth() const {
        return current_health;
    } double getBasePhysicalDamage() const {
        return base_physical_damage;
    } double getBaseMagicDamage() const {
        return base_magic_damage;
    } double getBaseArmor() const {
        return base_armor;
    } double getBaseMagicResist() const {
        return base_magic_resist;
    }

    // Setters
    void setName(const std::string& newName) {
        name = newName;
    } void setLevel(int newLevel) {
        level = newLevel;
    } void setMaxHealth(double newMaxHealth) {
        max_health = newMaxHealth;
    } void setCurrentHealth(double newCurrentHealth) {
        current_health = newCurrentHealth;
    } void setBasePhysicalDamage(double newBasePhysicalDamage) {
        base_physical_damage = newBasePhysicalDamage;
    } void setBaseMagicDamage(double newBaseMagicDamage) {
        base_magic_damage = newBaseMagicDamage;
    } void setBaseArmor(double newBaseArmor) {
        base_armor = newBaseArmor;
    } void setBaseMagicResist(double newBaseMagicResist) {
        base_magic_resist = newBaseMagicResist;
    }

    // Methods
    virtual void display_statistics() const {
        std::cout << "   [ ENTITY STATS ]" << '\n';
        std::cout << std::setw(20) << "Name: " << getName() << '\n';
        std::cout << std::setw(20) << "Level: " << getLevel() << '\n';
        std::cout << std::setw(20) << "Max Health: " << getMaxHealth() << '\n';
        std::cout << std::setw(20) << "Current Health: " << getCurrentHealth() << '\n';
        std::cout << std::setw(20) << "Physical Damage[B]: " << getBasePhysicalDamage() << '\n';
        std::cout << std::setw(20) << "Magic Damage[B]: " << getBaseMagicDamage() << '\n';
        std::cout << std::setw(20) << "Armor[B]: " << getBaseArmor() << '\n';
        std::cout << std::setw(20) << "Magic Resist[B]: " << getBaseMagicResist() << '\n';
    }
};

// Entity > Player
class Player : public Entity {
public:
    double health_up,
    physical_damage_up,
    magic_damage_up,
    armor_up,
    magic_resist_up;

    Player // Constructor
    (std::string n, int l, double mh, double bpd, double bmd, double ba, double bmr, double hu, double pdu, double mdu, double au, double mru)
    : Entity(n, l, mh, bpd, bmd, ba, bmr),
    health_up(hu), physical_damage_up(pdu), magic_damage_up(mdu),
    armor_up(au), magic_resist_up(mru) {}

protected:
    // Getters
    double getHealthUp() const {
        return health_up;
    } double getPhysicalDamageUp() const {
        return physical_damage_up;
    } double getMagicDamageUp() const {
        return magic_damage_up;
    } double getArmorUp() const {
        return armor_up;
    } double getMagicResistUp() const {
        return magic_resist_up;
    }

    // Setters
    void setHealthUp(double value) {
        health_up = value;
    } void setPhysicalDamageUp(double value) {
        physical_damage_up = value;
    } void setMagicDamageUp(double value) {
        magic_damage_up = value;
    } void setArmorUp(double value) {
        armor_up = value;
    } void setMagicResistUp(double value) {
        magic_resist_up = value;
    }

public:
    // Methods
    void display_statistics() const override {
        Entity::display_statistics();
        std::cout << "   [ PLAYER STATS ]" << '\n';
        std::cout << std::setw(20) << "Health+: " << getHealthUp() << '\n';
        std::cout << std::setw(20) << "Physical Damage+: " << getPhysicalDamageUp() << '\n';
        std::cout << std::setw(20) << "Magic Damage+: " << getMagicDamageUp() << '\n';
        std::cout << std::setw(20) << "Armor+: " << getArmorUp() << '\n';
        std::cout << std::setw(20) << "Magic Resist+: " << getMagicResistUp() << '\n';
    }
};

// Entity > Enemy
class Enemy : public Entity {
public:
    std::string type;
    int experience_reward;
    std::string item_drops;

    Enemy // Constructor
    (std::string n, int l, double mh, double bpd, double bmd, double ba, double bmr, std::string t, int er, std::string id)
    : Entity(n, l, mh, bpd, bmd, ba, bmr),
    type(t), experience_reward(er), item_drops(id) {}

protected:
    // Getters
    std::string getType() const {
        return type;
    } int getExperienceReward() const {
        return experience_reward;
    } std::string getItemDrops() const {
        return item_drops;
    }

    // Setters
    void setType(const std::string& value) {
        type = value;
    } void setExperienceReward(int value) {
        experience_reward = value;
    } void setItemDrops(const std::string& value) {
        item_drops = value;
    }

public:
    // Methods
    void display_statistics() const override {
        Entity::display_statistics();
        std::cout << "   [ ENEMY STATS ]" << '\n';
        std::cout << std::setw(20) << "Type: " << getType() << '\n';
        std::cout << std::setw(20) << "Experience Reward: " << getExperienceReward() << '\n';
        std::cout << std::setw(20) << "Item Drops: " << getItemDrops() << '\n';
    }
};

#endif