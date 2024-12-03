// src/NPCFactory.cpp
#include "NPCFactory.h"

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Bandit") return std::make_unique<Bandit>(name, x, y);
    if (type == "WanderingKnight") return std::make_unique<WanderingKnight>(name, x, y);
    if (type == "Elf") return std::make_unique<Elf>(name, x, y);
    return nullptr;
}

std::unique_ptr<NPC> NPCFactory::loadNPC(std::ifstream& file) {
    std::string type, name;
    int x, y;
    if (file >> type >> name >> x >> y) {
        return createNPC(type, name, x, y);
    }
    return nullptr;
}