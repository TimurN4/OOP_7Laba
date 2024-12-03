#include "BattleVisitor.h"
#include <cmath>
#include <iostream>

BattleVisitor::BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs) : range(range), npcs(npcs) {}

void BattleVisitor::visit(Bandit& bandit) {
    for (auto it = npcs.begin(); it != npcs.end();) {
        if ((*it)->getType() == "Elf") {
            Elf& elf = dynamic_cast<Elf&>(*(*it));
            double distance = std::sqrt(std::pow(bandit.getX() - elf.getX(), 2) + std::pow(bandit.getY() - elf.getY(), 2));
            if (distance <= range) {
                std::cout << "Bandit " << bandit.getName() << " kills Elf " << elf.getName() << std::endl;
                it = npcs.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void BattleVisitor::visit(WanderingKnight& knight) {
    for (auto it = npcs.begin(); it != npcs.end();) {
        if ((*it)->getType() == "Bandit") {
            Bandit& bandit = dynamic_cast<Bandit&>(*(*it));
            double distance = std::sqrt(std::pow(knight.getX() - bandit.getX(), 2) + std::pow(knight.getY() - bandit.getY(), 2));
            if (distance <= range) {
                std::cout << "WanderingKnight " << knight.getName() << " kills Bandit " << bandit.getName() << std::endl;
                it = npcs.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void BattleVisitor::visit(Elf& elf) {
    for (auto it = npcs.begin(); it != npcs.end();) {
        if ((*it)->getType() == "WanderingKnight") {
            WanderingKnight& knight = dynamic_cast<WanderingKnight&>(*(*it));
            double distance = std::sqrt(std::pow(elf.getX() - knight.getX(), 2) + std::pow(elf.getY() - knight.getY(), 2));
            if (distance <= range) {
                std::cout << "Elf " << elf.getName() << " kills WanderingKnight " << knight.getName() << std::endl;
                it = npcs.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}