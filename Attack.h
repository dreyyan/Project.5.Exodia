#include <string>

// Attack > PhysicalAttack, MagicAttack, LifestealAttack
// BASE: [ ATTACK ] - [ any ability that deals damage ]
class Attack {
public:
    std::string name;
    double critical_chance, critical_damage_multiplier;

    Attack // Constructor
    (std::string n, double cc, double cdm)
    : name(n), critical_chance(cc), critical_damage_multiplier(cdm) {}

    virtual ~Attack() = default; // Virtual Destructor
};

// Attack > Physical Attack
class PhysicalAttack : public Attack {
public:    
    double physical_damage_dealt, flat_armor_penetration, percent_armor_penetration;

    PhysicalAttack // Constructor
    (std::string n, double cc, double cdm, double pdd, double fap, double pap)
    : Attack(n, cc, cdm), physical_damage_dealt(pdd), flat_armor_penetration(fap), percent_armor_penetration(pap) {}
};

// Attack > Magic Attack
class MagicAttack : public Attack {
public:
    double magic_damage_dealt, flat_magic_resist_penetration, percent_magic_resist_penetration;

    MagicAttack // Constructor
    (std::string n, double cc, double cdm, double mdd, double fmrp, double pmrp)
    : Attack(n, cc, cdm), magic_damage_dealt(mdd), flat_magic_resist_penetration(fmrp), percent_magic_resist_penetration(pmrp) {}
};

// Attack > Lifesteal Attack
class LifestealAttack : public Attack {
public:
    double health_stolen;

    LifestealAttack // Constructor
    (std::string n, double cc, double cdm, double hd)
    : Attack(n, cc, cdm), health_stolen(hd) {}
};