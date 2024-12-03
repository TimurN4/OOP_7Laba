#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include <memory>
#include <fstream>
#include "NPC.h"

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y);
    static std::unique_ptr<NPC> loadNPC(std::ifstream& file);
};

#endif 