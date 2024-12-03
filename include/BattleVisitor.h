#ifndef BATTLEVISITOR_H
#define BATTLEVISITOR_H

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "NPC.h"

class BattleVisitor {
public:
    BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs);
    void visit(Bandit& bandit);
    void visit(WanderingKnight& knight);
    void visit(Elf& elf);
    void printKilledList() const;

private:
    int range;
    std::vector<std::unique_ptr<NPC>>& npcs;
    std::vector<std::string> killedList;
    std::ofstream logFile;
};

#endif // BATTLEVISITOR_H