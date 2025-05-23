#ifndef GAME_H
#define GAME_H

#include <string>

void playerTurn();
void enemyTurn();
void displayHPBar(int currentHealth, int maxHealth);
void loadPlayer();
void loadRandomEnemy();
void displayArrow(std::string direction);
void displayDivider();
void displayHeader();
void displayPlayerStats();
void displayEnemyStats();
int generateRandomNumber(int maxRange);
void displayActions();
void displayGameArea();
void startGame();

#endif