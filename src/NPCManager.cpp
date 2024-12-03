#include "NPCManager.h"
#include <fstream>
#include <iostream>

void NPCManager::addNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        std::cerr << "Coordinates out of range (0 <= x, y <= 500)" << std::endl;
        return;
    }
    npcs.push_back(NPCFactory::createNPC(type, name, x, y));
}

void NPCManager::saveNPCs(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& npc : npcs) {
        file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
    }
}

void NPCManager::loadNPCs(const std::string& filename) {
    std::ifstream file(filename);
    npcs.clear();
    std::unique_ptr<NPC> npc;
    while ((npc = NPCFactory::loadNPC(file)) != nullptr) {
        npcs.push_back(std::move(npc));
    }
}

void NPCManager::printNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << "Type: " << npc->getType() << ", Name: " << npc->getName() << ", Coords: (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
}

std::vector<std::unique_ptr<NPC>>& NPCManager::getNPCs() {
    return npcs;
}