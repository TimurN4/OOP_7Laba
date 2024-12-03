#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "NPC.h"
#include "NPCFactory.h"
#include "BattleVisitor.h"

class NPCManager {
public:
    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void saveNPCs(const std::string& filename) const;
    void loadNPCs(const std::string& filename);
    void printNPCs() const;
    void startBattle(int range);
    std::vector<std::unique_ptr<NPC>>& getNPCs();

private:
    std::vector<std::unique_ptr<NPC>> npcs;
};

#endif // NPCMANAGER_H