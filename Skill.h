#include <string>

// Skill > DefenseSkill, HealingSkill, BuffSkill, DebuffSkill
// BASE: [ SKILL ] - [ any ability that does not deal damage (buffs, debuffs, heals, etc.) ]
class Skill {
public:
    std::string name;
    double critical_chance;

    Skill // Constructor
    (std::string n, double cc)
    : name(n), critical_chance(cc) {}

    virtual ~Skill() = default; // Virtual Destructor
};

// Skill > Defense Skill
class DefenseSkill : public Skill {
public:
    double shield_amount;

    DefenseSkill // Constructor
    (std::string n, double cc, double sa)
    : Skill(n, cc), shield_amount(sa) {}
};

// Skill > Healing Skill
class HealingSkill : public Skill {
public:
    double healing_done;

    HealingSkill // Constructor
    (std::string n, double cc, double hd)
    : Skill(n, cc), healing_done(hd) {}
};

// Skill > Buff Skill
class BuffSkill : public Skill {
public:
    double physical_attack_boost, magic_attack_boost,
    flat_armor_boost, flat_magic_resist_boost,
    percent_armor_boost, percent_magic_resist_boost;

    BuffSkill // Constructor
    (std::string n, double cc, double pab, double mab, double fab, double fmrb, double pab1, double pmrb)
    : Skill(n, cc), physical_attack_boost(pab), magic_attack_boost(mab),
    flat_armor_boost(fab), flat_magic_resist_boost(fmrb),
    percent_armor_boost(pab1), percent_magic_resist_boost(pmrb) {}
};

// Skill > Debuff Skill
class DebuffSkill : public Skill {
public:
    double physical_attack_reduction, magic_attack_reduction,
    flat_armor_reduction, flat_magic_resist_reduction,
    percent_armor_reduction, percent_magic_resist_reduction;

    DebuffSkill // Constructor
    (std::string n, double cc, double pab, double mab, double fab, double fmrb, double pab1, double pmrb)
    : Skill(n, cc), physical_attack_reduction(pab), magic_attack_reduction(mab),
    flat_armor_reduction(fab), flat_magic_resist_reduction(fmrb),
    percent_armor_reduction(pab1), percent_magic_resist_reduction(pmrb) {}
};