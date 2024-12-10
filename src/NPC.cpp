#include "../include/NPC.h"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y), alive(true) {}

std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
bool NPC::isAlive() const { return alive; }
void NPC::setAlive(bool alive) { this->alive = alive; }
void NPC::setX(int x) { this->x = x; }
void NPC::setY(int y) { this->y = y; }

// Bandit
Bandit::Bandit(const std::string& name, int x, int y) : NPC(name, x, y) {}
std::string Bandit::getType() const { return "Bandit"; }
int Bandit::getMoveDistance() const { return 10; } // Расстояние хода
int Bandit::getKillDistance() const { return 10; } // Расстояние убийства

// WanderingKnight
WanderingKnight::WanderingKnight(const std::string& name, int x, int y) : NPC(name, x, y) {}
std::string WanderingKnight::getType() const { return "WanderingKnight"; }
int WanderingKnight::getMoveDistance() const { return 30; } // Расстояние хода
int WanderingKnight::getKillDistance() const { return 10; } // Расстояние убийства

// Elf
Elf::Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}
std::string Elf::getType() const { return "Elf"; }
int Elf::getMoveDistance() const { return 10; } // Расстояние хода
int Elf::getKillDistance() const { return 50; } // Расстояние убийства