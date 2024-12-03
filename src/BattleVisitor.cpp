#include "BattleVisitor.h"
#include <cmath>
#include <iostream>

BattleVisitor::BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs) : range(range), npcs(npcs) {}

void BattleVisitor::visit(Bandit& bandit) {
    for (auto& other : npcs) {
        if (other->getType() == "Elf") {
            Elf& elf = dynamic_cast<Elf&>(*other);
            double distance = std::sqrt(std::pow(bandit.getX() - elf.getX(), 2) + std::pow(bandit.getY() - elf.getY(), 2));
            if (distance <= range) {
                // Логика сражения: разбойник убивает эльфа
                std::cout << "Bandit " << bandit.getName() << " kills Elf " << elf.getName() << std::endl;
            }
        }
    }
}

void BattleVisitor::visit(WanderingKnight& knight) {
    for (auto& other : npcs) {
        if (other->getType() == "Bandit") {
            Bandit& bandit = dynamic_cast<Bandit&>(*other);
            double distance = std::sqrt(std::pow(knight.getX() - bandit.getX(), 2) + std::pow(knight.getY() - bandit.getY(), 2));
            if (distance <= range) {
                // Логика сражения: рыцарь убивает разбойника
                std::cout << "WanderingKnight " << knight.getName() << " kills Bandit " << bandit.getName() << std::endl;
            }
        }
    }
}

void BattleVisitor::visit(Elf& elf) {
    for (auto& other : npcs) {
        if (other->getType() == "WanderingKnight") {
            WanderingKnight& knight = dynamic_cast<WanderingKnight&>(*other);
            double distance = std::sqrt(std::pow(elf.getX() - knight.getX(), 2) + std::pow(elf.getY() - knight.getY(), 2));
            if (distance <= range) {
                // Логика сражения: эльф убивает рыцаря
                std::cout << "Elf " << elf.getName() << " kills WanderingKnight " << knight.getName() << std::endl;
            }
        }
    }
}