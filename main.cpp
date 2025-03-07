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
using namespace std;

// Base: Physical Attack Set
struct PhysicalAttack {
    // Stats
    string name;
    double physical_damage_dealt, magic_damage_dealt;
    double flat_armor_penetration, flat_magic_penetration;
    double percent_armor_penetration, percent_magic_penetration;
    double critical_chance, critical_damage_multiplier;

    PhysicalAttack() // Default Constructor
    : name(""), physical_damage_dealt(0), magic_damage_dealt(0),
    flat_armor_penetration(0), flat_magic_penetration(0),
    percent_armor_penetration(0), percent_magic_penetration(0),
    critical_chance(0), critical_damage_multiplier(0) {}

    PhysicalAttack // Parameterized Constructor
    (string n, double pdd = 3.0, double mdd = 0,
    double fap = 0, double fmp = 0,
    double pap = 0, double pmp = 0,
    double cc = 10, double cdm = 1.5)
    : name(n), physical_damage_dealt(pdd), magic_damage_dealt(mdd),
    flat_armor_penetration(fap), flat_magic_penetration(fmp),
    percent_armor_penetration(pap), percent_magic_penetration(pmp),
    critical_chance(cc), critical_damage_multiplier(cdm) {}
};

// Base: Magic Attack Set
struct MagicAttack {
    // Stats
    string name;
    double physical_damage_dealt, magic_damage_dealt;
    double flat_armor_penetration, flat_magic_penetration;
    double percent_armor_penetration, percent_magic_penetration;
    double critical_chance, critical_damage_multiplier;

    MagicAttack() // Default Constructor
    : name(""), physical_damage_dealt(0), magic_damage_dealt(0),
    flat_armor_penetration(0), flat_magic_penetration(0),
    percent_armor_penetration(0), percent_magic_penetration(0),
    critical_chance(0), critical_damage_multiplier(0) {}

    MagicAttack // Parameterized Constructor
    (string n, double pdd = 0, double mdd = 3.0,
    double fap = 0, double fmp = 0,
    double pap = 0, double pmp = 0,
    double cc = 10, double cdm = 1.5)
    : name(n), physical_damage_dealt(pdd), magic_damage_dealt(mdd),
    flat_armor_penetration(fap), flat_magic_penetration(fmp),
    percent_armor_penetration(pap), percent_magic_penetration(pmp),
    critical_chance(cc), critical_damage_multiplier(cdm) {}
};

// Physical: Lifesteal [1]
struct LifestealAttack : public PhysicalAttack {
    // Unique Stat
    double healing_done;

    LifestealAttack // Parameterized Constructor
    (string n, double pdd, double mdd,
    double fap, double fmp,
    double pap, double pmp,
    double cc, double cdm, double hd)
    : PhysicalAttack(n, pdd, mdd, fap, fmp, pap, pmp, cc, cdm),
      healing_done(hd) {}
};

// Physical: Defense [2]
struct DefenseAttack : public PhysicalAttack {
    // Unique Stat
    double shield_amount;

    DefenseAttack // Parameterized Constructor
    (string n, double pdd, double mdd,
    double fap, double fmp,
    double pap, double pmp,
    double cc, double cdm, double sa)
    : PhysicalAttack(n, pdd, mdd, fap, fmp, pap, pmp, cc, cdm),
      shield_amount(sa) {}
};

// Magic: Magic Buff
struct MagicUpAttack : public MagicAttack {
    // Unique Stat
    double magic_damage_up = 2.0;

    MagicUpAttack // Parameterized Constructor
    (string n, double pdd, double mdd,
    double fap, double fmp,
    double pap, double pmp,
    double cc, double cdm, double mdu)
    : MagicAttack(n, pdd, mdd, fap, fmp, pap, pmp, cc, cdm),
      magic_damage_up(mdu) {}
};

// Base: Entity
struct Entity {
    // Stats
    string name;
    int level;
    double health;
    double physical_damage;
    double magic_damage;
    double armor;
    double magic_resist;

    // Level Up Stats
    double health_up = 4.0;
    double physical_damage_up = 2.5;
    double magic_damage_up = 2.5;
    double armor_up = 0.8;
    double magic_resist_up = 0.8;

    Entity // Parameterized Constructor
    (string name, int level, double health,
    double physical_damage, double magic_damage,
    double armor, double magic_resist)
    : name(name), level(level), health(health),
    physical_damage(physical_damage), magic_damage(magic_damage),
    armor(armor), magic_resist(magic_resist) {}

    // Formatting
    static void displayFormat(int length, char symbol) {
        for (int i = 0; i < length; i++) {
            cout <<  symbol;
        }
        cout << '\n';
    }

    // Show Stats
    void showEntityStats() {
        cout << fixed << setprecision(1);
        displayFormat(33, '-');
        cout << setw(14) << "Lvl " << level << ": ";
        cout << name << '\n';
        displayFormat(33, '-');
        cout << setw(20) << "HP: " << health << '\n';
        cout << setw(20) << "Physical Damage: " << physical_damage << '\n';
        cout << setw(20) << "Magic Damage: " << magic_damage << '\n';
        cout << setw(20) << "Armor: " << armor << '\n';
        cout << setw(20) << "Magic Resist: " << magic_resist << '\n';
        displayFormat(33, '-');
    }

    // Show Levelled Up Stats
    void showEntityStatsLevelUp() {
        cout << fixed << setprecision(1);
        displayFormat(33, '-');
        cout << "Lvl " << level << ' ';
        cout << name << '\n';
        displayFormat(33, '-');
        cout << setw(19) << "HP: " << setw(5) << health << ' ' << health_up << "+ [1]\n";
        cout << setw(19) << "Physical Damage: " << setw(5) << physical_damage << ' ' << physical_damage_up << "+ [2]\n";
        cout << setw(19) << "Magic Damage: " << setw(5) << magic_damage << ' ' << magic_damage_up << "+ [3]\n";
        cout << setw(19) << "Armor: " << setw(5) << armor << ' ' << armor_up << "+ [4]\n";
        cout << setw(19) << "Magic Resist: " << setw(5) << magic_resist << ' ' << magic_resist_up << "+ [5]\n";
        displayFormat(33, '-');
    }
};

// Entity: Player
struct Player : public Entity {
    int current_xp;
    int max_xp;

    Player(int cxp = 0, int mxp = 5, int xpg = 5)
        : current_xp(cxp), max_xp(mxp), Entity("Knight", 1, 10.0, 2.0, 1.0, 2.0, 2.0) {
        physical_move = {
            // Physical Damage, Magic Damage, FAP, FMP, PAP, PMP, CC, CDM
            {1, PhysicalAttack("Sword Slash", 10.0, 0, 2, 0, 0, 0, 30, 1.75)},
            {2, DefenseAttack("Guard", 0, 0, 0, 0, 0, 0, 0, 15, 2.0)},
            {3, PhysicalAttack("Quick Strike", 1, 0, 0, 0, 10, 0, 20, 3.0)},
            {4, LifestealAttack("Blood Cry", 3, 0, 0, 0, 0, 0, 10, 10, 1.5)}
        };
    }

    // Attack Move Set
    map<int, PhysicalAttack> physical_move;
    map<int, MagicAttack> magic_move;
};

// Entity: Enemy
struct Enemy : public Entity {

    Enemy() // Default Constructor
        : Entity("Enemy", 1, 5.0, 1.0, 0, 0.5, 0.5) {}

    Enemy(string name, int level, int health, double physical_damage, double magic_damage, double armor, double magic_resist)
        : Entity(name, level, health, physical_damage, magic_damage, armor, magic_resist) {}
};

static vector<Enemy> difficulty1Enemies;
static vector<Enemy> difficulty2Enemies;
static vector<Enemy> difficulty3Enemies;
static vector<Enemy> difficulty4Enemies;
static vector<Enemy> difficulty5Enemies;
static vector<Enemy> bosses;

// Main Class
class Game {
private:
    Player player;
    Enemy enemy;
public:
    Game() : player(0, 5), enemy() {} // Add Player & Enemy

    // Current Enemy
    int current_enemy = 0;

    // Loading Animation
    static void displayLoadingAnimation(int times, int ms_delay) {
        for (int i = 0; i < times; i++) {
            cout << '.';
            this_thread::sleep_for(chrono::milliseconds(ms_delay));
        }
    }

    // Sleep Animation
    static void delay(int ms_delay) {
        this_thread::sleep_for(chrono::milliseconds(ms_delay));
    }

    static void populateEnemies() {
        // Skeleton, Slime, Goblin, Wolf, Awakened, Dryad, Elementum, Soldier, Weaver, Mage
        // Difficulty 1 Enemies
        difficulty1Enemies.emplace_back("Degraded Skeleton", 1, 5, 2, 0, 2, 0);
        difficulty1Enemies.emplace_back("Baby Slime", 1, 4, 1, 1, 1, 2);
        difficulty1Enemies.emplace_back("Thief", 1, 3, 5, 0, 0, 0);
        difficulty1Enemies.emplace_back("Pup", 1, 5, 2.5, 0, 1, 0);
        difficulty1Enemies.emplace_back("Heretic", 1, 7, 2.5, 1, 1, 1);
        difficulty1Enemies.emplace_back("Bloom Dryad", 1, 2, 0, 3, 1, 5);
        difficulty1Enemies.emplace_back("Fissurum", 1, 3, 1, 1, 5, 1);
        difficulty1Enemies.emplace_back("Apprentice Soldier", 1, 5, 4, 0, 3, 0);
        difficulty1Enemies.emplace_back("Apprentice Weaver", 1, 3, 3, 2, 2, 1);
        difficulty1Enemies.emplace_back("Apprentice Mage", 1, 4, 0, 4, 0, 3);

        // Difficulty 2 Enemies
        difficulty2Enemies.emplace_back("Old Skeleton", 2, 6, 4, 1, 4, 1);
        difficulty2Enemies.emplace_back("Slime Twins", 2, 6, 3, 3, 3, 4);
        difficulty2Enemies.emplace_back("Snatcher", 2, 5, 6, 1, 1, 1);
        difficulty2Enemies.emplace_back("Aggressive Pup", 2, 6, 4, 1, 3, 1);
        difficulty2Enemies.emplace_back("Non-believer", 2, 8, 4, 3, 3, 3);
        difficulty2Enemies.emplace_back("Dryadum", 2, 4, 1, 5, 3, 6);
        difficulty2Enemies.emplace_back("Stalagmum", 2, 5, 3, 3, 6, 3);
        difficulty2Enemies.emplace_back("Trained Soldier", 2, 6, 6, 1, 5, 1);
        difficulty2Enemies.emplace_back("Trained Weaver", 2, 5, 5, 4, 4, 3);
        difficulty2Enemies.emplace_back("Trained Mage", 2, 6, 1, 6, 1, 5);

        // Difficulty 3 Enemies
        difficulty3Enemies.emplace_back("Skeleton", 3, 7, 3, 2, 5, 1);
        difficulty3Enemies.emplace_back("Slime", 3, 7, 4, 4, 4, 5);
        difficulty3Enemies.emplace_back("Goblin", 3, 6, 7, 2, 2, 2);
        difficulty3Enemies.emplace_back("Wolf", 3, 7, 5, 2, 4, 2);
        difficulty3Enemies.emplace_back("Awakened", 10, 5, 4, 4, 4, 4);
        difficulty3Enemies.emplace_back("Dryad", 3, 5, 2, 6, 4, 7);
        difficulty3Enemies.emplace_back("Elementum", 3, 6, 4, 4, 7, 4);
        difficulty3Enemies.emplace_back("Soldier", 3, 7, 7, 2, 6, 2);
        difficulty3Enemies.emplace_back("Weaver", 3, 6, 6, 5, 5, 4);
        difficulty3Enemies.emplace_back("Mage", 3, 7, 2, 7, 2, 6);
        // Difficulty 4 Enemies
        difficulty4Enemies.emplace_back("Corrupted Skeleton", 4, 9, 5, 4, 7, 3);
        difficulty4Enemies.emplace_back("Corrupted Slime", 4, 9, 6, 6, 6, 7);
        difficulty4Enemies.emplace_back("Goblin Warrior", 4, 8, 9, 4, 4, 4);
        difficulty4Enemies.emplace_back("Aggressive Wolf", 4, 9, 7, 4, 6, 2);
        difficulty4Enemies.emplace_back("Apostle", 4, 12, 7, 6, 6, 6);
        difficulty4Enemies.emplace_back("Dryada", 4, 7, 4, 8, 6, 9);
        difficulty4Enemies.emplace_back("Elementa", 4, 8, 6, 6, 9, 6);
        difficulty4Enemies.emplace_back("Veteran Soldier", 4, 9, 9, 4, 8, 4);
        difficulty4Enemies.emplace_back("Masterweaver", 4, 8, 8, 7, 7, 6);
        difficulty4Enemies.emplace_back("Arcane Mage", 4, 9, 4, 9, 4, 8);
        // Difficulty 5 Enemies
        difficulty4Enemies.emplace_back("Lost Skeleton", 4, 12, 8, 7, 10, 6);
        difficulty4Enemies.emplace_back("Slime Queen", 4, 12, 9, 9, 9, 10);
        difficulty4Enemies.emplace_back("Goblin Chief", 4, 11, 12, 7, 7, 7);
        difficulty4Enemies.emplace_back("Aggressive Wolf", 4, 12, 10, 7, 9, 5);
        difficulty4Enemies.emplace_back("Ascendant", 4, 15, 10, 9, 9, 9);
        difficulty4Enemies.emplace_back("Ruined Dryada", 4, 10, 7, 11, 9, 12);
        difficulty4Enemies.emplace_back("Ruined Elementa", 4, 11, 9, 9, 12, 9);
        difficulty4Enemies.emplace_back("Lost Soldier", 4, 12, 12, 7, 11, 7);
        difficulty4Enemies.emplace_back("Lost Weaver", 4, 11, 11, 10, 10, 9);
        difficulty4Enemies.emplace_back("Lost Mage", 4, 12, 7, 12, 7, 11);
        // Bosses
        bosses.emplace_back("Skeletron", 5, 1000, 30, 5, 50, 50);
        bosses.emplace_back("Slime King", 10, 1200, 20, 35, 40, 40);
        bosses.emplace_back("El Goblino", 15, 1300, 30, 10, 60, 60);
        bosses.emplace_back("Cerberus", 20, 1400, 15, 45, 50, 50);
        bosses.emplace_back("God", 25, 1500, 25, 20, 55, 55);
        bosses.emplace_back("Ancient Tree", 30, 1600, 20, 10, 60, 60);
        bosses.emplace_back("Ancient Land", 35, 1700, 25, 15, 65, 65);
        bosses.emplace_back("Arthur, the First Soldier", 40, 1800, 40, 20, 70, 70);
        bosses.emplace_back("Elysia, the First Weaver", 45, 1900, 35, 25, 75, 75);
        bosses.emplace_back("Merlin, the First Mage", 50, 2000, 50, 30, 80, 80);

    }

    void displayMainMenu() {
        int choice;
        bool validChoice;

        do {
            validChoice = true;
            cout << "| A Hero's Journey |\n";
            Entity::displayFormat(20, '-');
            cout << "    [1] | Start\n";
            cout << "    [2] | Exit\n";
            Entity::displayFormat(20, '-');
            cout << ">> ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (choice < 1 || choice > 2) {
                validChoice = false;
            }
        } while (!validChoice);

        if (choice == 1) {
            system("cls");
            startGame();
        } else {
            cout << "exiting game...";
            exit(0);
        }
    }

    void startGame() {
        // Preparation
        populateEnemies();
        // RNG for Current Enemy
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, difficulty1Enemies.size() - 1);
        current_enemy = dis(gen);
        // Start Combat
        startCombat(current_enemy);
    }

    void showPlayerStats() {
        cout << "showing player stats...\n";
        cout << setw(26) << "[ PLAYER STATS ]\n";
        player.showEntityStats();
    }

    void showEnemyStats() {
        cout << "showing enemy stats...\n";
        cout << setw(26) << "[ ENEMY STATS ]\n";
        enemy.showEntityStats();
    }

    bool damageIsCrit(int move) {
        int chance = rand() % 100; // Crit Chance
        return player.physical_move[move].critical_chance > chance;
    }

    double calculateDamage(int move, bool isCrit) {
        // Base Damage
        double base_physical_damage = player.physical_move[move].physical_damage_dealt;
        double base_magic_damage = player.physical_move[move].magic_damage_dealt;

        // Flat Reduction
        double flat_reduced_armor = enemy.armor - player.physical_move[move].flat_armor_penetration;
        double flat_reduced_magic_resist = enemy.magic_resist - player.physical_move[move].flat_magic_penetration;

        // Percent Reduction
        double percent_reduced_armor = enemy.armor * player.physical_move[move].percent_armor_penetration;
        double percent_reduced_magic_resist = enemy.magic_resist * player.physical_move[move].percent_magic_penetration;

        double total_damage; // Total Damage

        if (isCrit) { // Crit Damage
            total_damage = ((base_physical_damage - (flat_reduced_armor - percent_reduced_armor))
                            + (base_magic_damage - (flat_reduced_magic_resist - percent_reduced_magic_resist)))
                            * player.physical_move[move].critical_damage_multiplier;
        } else { // Non-Crit Damage
            total_damage = (base_physical_damage - (flat_reduced_armor - percent_reduced_armor))
                            + (base_magic_damage - (flat_reduced_magic_resist - percent_reduced_magic_resist));
        }

        return total_damage;
    }


    void opponentMove() {

    }

    void startCombat(int current_enemy) {
        bool invalidMove;
        int move;

        // Initialize Entity Health
        double currentPlayerHealth;
        double currentEnemyHealth;
        double total_damage = 0;
        double total_enemy_damage = 0;
        currentPlayerHealth = player.health;  // Player's health
        currentEnemyHealth = difficulty1Enemies[current_enemy].health;

        // Encounter
        displayLoadingAnimation(3, 200);
        cout << player.name << " has encountered a " << difficulty1Enemies[current_enemy].name << "!\n";
        delay(200);
        cout << "Preparing for battle";
        displayLoadingAnimation(3, 100);
        cout << '\n';
        system("cls");

        while (currentPlayerHealth > 0 && currentEnemyHealth > 0) {
            invalidMove = false;

            // Enemy Stats
            cout << fixed << setprecision(1);
            cout << "[ Lvl. " << difficulty1Enemies[current_enemy].level << " " << difficulty1Enemies[current_enemy].name << " ]\n";
            cout << "[ HP: " << currentEnemyHealth << " / " << difficulty1Enemies[current_enemy].health << " ]\n";
            Entity::displayFormat(34, '#');
            cout << left << setw(11) << "P. Attack: " << difficulty1Enemies[current_enemy].physical_damage << " | ";
            cout << setw(14) << "M. Attack: " << difficulty1Enemies[current_enemy].magic_damage << '\n';
            cout << left << setw(11) << "Armor: " << difficulty1Enemies[current_enemy].armor << " | ";
            cout << left << setw(3) << "Magic Resist: " << difficulty1Enemies[current_enemy].magic_resist << '\n';
            Entity::displayFormat(34, '#');
            cout << '\n';

            // Player stats
            cout << "[ Lvl. " << player.level << " " << player.name << " ]\n";
            cout << "[ HP: " << currentPlayerHealth << " / " << player.health << " | " << player.current_xp << " / " << player.max_xp << " XP ]\n";
            Entity::displayFormat(34, '#');
            cout << left << setw(11) << "P. Attack: " << player.physical_damage << " | ";
            cout << setw(14) << "M. Attack: " << player.magic_damage << '\n';
            cout << left << setw(11) << "Armor: " << player.armor << " | ";
            cout << left << setw(3) << "Magic Resist: " << player.magic_resist << '\n';
            Entity::displayFormat(34, '#');

            // Display Move Set
            Entity::displayFormat(34, '-');
            cout << setw(18) << "[1] || Attack" << "[3] || Inventory\n";
            cout << setw(18) << "[2] || Magic" << "[4] || Retreat\n";
            Entity::displayFormat(34, '-');

            // Move
            cout << ">> ";
            cin >> move;

            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                invalidMove = true;
            }

            if (move < 1 || move > 4) {
                invalidMove = true;
            }

            // Player Move
            switch (move) {
                case 1: {
                    // ATTACK MENU
                    int attackMove;

                    system("cls");
                    cout << "||     ATTACK     ||\n";
                    Entity::displayFormat(20, '-');

                    int count = 1;

                    for (const auto& pair : player.physical_move) {
                        cout << "[" << count << "] || " << pair.second.name << '\n';
                        count++;
                    }

                    cout << "[" << count++ << "] || Back\n";
                    Entity::displayFormat(20, '-');
                    cout << ">> ";
                    cin >> attackMove;

                    if (attackMove == 5) {
                        system("cls");
                        break;
                    }

                    // Display Player's Pre-Move Stats
                    Entity::displayFormat(20, '-');
                    cout << difficulty1Enemies[current_enemy].name << " | HP: " << currentEnemyHealth << " / " << difficulty1Enemies[current_enemy].health << '\n';
                    Entity::displayFormat(20, '-');

                    string move_name = player.physical_move[attackMove].name;
                    bool isCrit = damageIsCrit(attackMove);
                    total_damage = calculateDamage(attackMove, isCrit);
                    currentEnemyHealth -= total_damage;
                    if (currentEnemyHealth < 0) { currentEnemyHealth = 0; }

                    // Display Player's Move
                    cout << player.name << " used " << move_name << "!\n";
                    delay(2000);

                    // Display Player's Post-Move Stats
                    cout << "\033[13;1H";
                    cout << "                                                                                         \n";
                    cout << "\033[10;1H";
                    Entity::displayFormat(20, '-');
                    cout << difficulty1Enemies[current_enemy].name << " | HP: " << currentEnemyHealth << " / " << difficulty1Enemies[current_enemy].health << '\n';
                    Entity::displayFormat(20, '-');
                    cout << "\033[13;1H";

                    // Display Player's Damage to Enemy
                    if (isCrit) {
                        cout << move_name << " dealt " << total_damage << " critical damage to " << difficulty1Enemies[current_enemy].name << "!!!";
                    } else {
                        cout << move_name << " dealt " << total_damage << " damage to " << difficulty1Enemies[current_enemy].name << '\n';
                    }
                    delay(2000);

                    if (currentEnemyHealth <= 0) {
                        system("cls");
                        cout << difficulty1Enemies[current_enemy].name << " defeated!\n";
                        delay(1000);
                        break;
                    }

                    // Clear Current
                    cout << "\033[13;1H"; // Clear Player's Move
                    cout << "                                                                                                                   \n";
                    cout << "\033[11;1H"; // Clear Player's Post-Move Stats
                    cout << "                                                                                                                   \n";

                    // Display Enemy's Move
                    cout << "\033[10;1H";
                    Entity::displayFormat(20, '-');
                    cout << player.name << " | HP: " << currentPlayerHealth << " / " << player.health << '\n';
                    Entity::displayFormat(20, '-');
                    cout << difficulty1Enemies[current_enemy].name << " attacks!\n";
                    delay(2000);

                    total_enemy_damage = difficulty1Enemies[current_enemy].physical_damage;
                    currentPlayerHealth -= total_enemy_damage;

                    cout << "\033[11;1H"; // Goto Next Line
                    cout << "                                                                                                                   \n";
                    cout << "\033[10;1H";
                    Entity::displayFormat(20, '-');
                    cout << player.name << " | HP: " << currentPlayerHealth << " / " << player.health << '\n';
                    Entity::displayFormat(20, '-');
                    cout << '\n';
                    cout << difficulty1Enemies[current_enemy].name << " dealt " << total_enemy_damage << " damage\n";
                    delay(2000);
                    break;
                }
                case 2: {
                    // MAGIC MENU
                    break;
                }
                case 3: {
                    // INVENTORY MENU
                    break;
                }
                case 4: {
                    // RETREAT MENU
                    break;
                }
                default: {
                    cout << "Invalid Move.\n";
                    system("cls");
                    break;
                }
            }
        }

        if (currentPlayerHealth <= 0) {
            cout << player.name << " has been defeated!\n";
            delay(2000);
        }

        // XP Algorithm
        int xp_gain = difficulty1Enemies[current_enemy].level * 5;
        player.current_xp += xp_gain;

        // Display XP Gain
        cout << player.name << " gained " << xp_gain << " XP!\n";
        delay(2000);

        // Level Up if XP Exceeded
        if (player.current_xp >= player.max_xp) {
            player.current_xp = player.current_xp - player.max_xp;
            player.max_xp += 3;

            system("cls");
            levelUp();
        }

        // Start Combat Again
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, difficulty1Enemies.size() - 1);
        current_enemy = dis(gen);

        system("cls");
        startCombat(current_enemy);
    }

    void levelUp() {
        int stat;
        string statName;

        // Show Level Up Stats
        cout << "Level Up!\n";
        cout << "[ " << player.name << " ]\n";
        cout << "Lvl. " << player.level << " >> Lvl. " << ++player.level << '\n';
        player.showEntityStatsLevelUp();

        //  Get Stat Upgrade
        cout << ">> ";
        cin >> stat;

        switch(stat) {
        case 1:
            player.health += player.health_up;
            statName = "HP";
            break;
        case 2:
            player.physical_damage += player.physical_damage_up;
            statName = "Physical Damage";
            break;
        case 3:
            player.magic_damage += player.magic_damage_up;
            statName = "Magic Damage";
            break;
        case 4:
            player.armor += player.armor_up;
            statName = "Armor";
            break;
        case 5:
            player.magic_resist += player.magic_resist_up;
            statName = "Magic Resist";
            break;
        default:
            cout << "Invalid Stat.\n";
            break;
        }

        // Display Upgraded Stat
        cout << statName << " upgraded!\n";
        delay(200);
        system("cls");
    }

    void backToMenu() {
        char choice;
        cout << "Back to Menu[y]?: ";
        cin >> choice;
        choice = tolower(choice);

        if (choice == 'y') {
            system("cls");
            debugMenu();
        }
        else {
            return;
        }
    }

    void debugMenu() {
        int choice;
        bool validChoice;

        do {
            validChoice = true;
            cout << "|      DEBUG MENU      |\n";
            cout << "------------------------\n";
            cout << "[1] | Show Player Stats\n";
            cout << "[2] | Show Enemy Stats\n";
            cout << "[3] | Start Combat\n";
            cout << "[4] | Level Up\n";
            cout << "[5] | Exit\n";
            cout << ">> ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            system("cls");
            switch(choice) {
            case 1:
                showPlayerStats();
                break;
            case 2:
                showEnemyStats();
                break;
            case 3:
                //
                break;
            case 4:
                levelUp();
                break;
            case 5:
                cout << "exit debugging...";
                exit(0);
                break;
            }
            backToMenu();
        } while (!validChoice);
    }
};

int main() {
    Game startProgram;
    startProgram.displayMainMenu();
    // startProgram.debugMenu();
    return 0;
}
