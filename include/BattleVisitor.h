#ifndef BATTLEVISITOR_H
#define BATTLEVISITOR_H

#include <vector>
#include <memory>
#include "NPC.h"

class BattleVisitor {
public:
    BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs);
    void visit(Bandit& bandit);
    void visit(WanderingKnight& knight);
    void visit(Elf& elf);

private:
    int range;
    std::vector<std::unique_ptr<NPC>>& npcs;
};

#endif // BATTLEVISITOR_H