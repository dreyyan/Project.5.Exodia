#ifndef GLOBALS_H
#define GLOBALS_H

struct PlayerCharacter {
  std::string name;
  int level;
  double maxHealth;
  double currentHealth;
  double basePhysicalDamage;
  double baseMagicDamage;
  double baseArmor;
  double baseMagicResist;
};

struct EnemyCharacter {
  int id;
  std::string name;
  int level;
  double maxHealth;
  double currentHealth;
  double basePhysicalDamage;
  double baseMagicDamage;
  double baseArmor;
  double baseMagicResist;
};

extern PlayerCharacter player;
extern EnemyCharacter enemy;
extern int save;

#endif