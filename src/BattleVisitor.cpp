#include "BattleVisitor.h"
#include <cmath>
#include <iostream>

BattleVisitor::BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs) : range(range), npcs(npcs), logFile("log.txt") {}

void BattleVisitor::visit(Bandit& bandit) {
    if (!bandit.isAlive()) return;
    for (auto& other : npcs) {
        if (other->getType() == "Elf" && other->isAlive()) {
            Elf& elf = dynamic_cast<Elf&>(*other);
            double distance = std::sqrt(std::pow(bandit.getX() - elf.getX(), 2) + std::pow(bandit.getY() - elf.getY(), 2));
            if (distance <= range) {
                std::cout << "Bandit " << bandit.getName() << " kills Elf " << elf.getName() << std::endl;
                killedList.push_back(elf.getName());
                elf.setAlive(false);
                logFile << "Elf " << elf.getName() << " was killed by Bandit " << bandit.getName() << std::endl;
            }
        }
    }
}

void BattleVisitor::visit(WanderingKnight& knight) {
    if (!knight.isAlive()) return;
    for (auto& other : npcs) {
        if (other->getType() == "Bandit" && other->isAlive()) {
            Bandit& bandit = dynamic_cast<Bandit&>(*other);
            double distance = std::sqrt(std::pow(knight.getX() - bandit.getX(), 2) + std::pow(knight.getY() - bandit.getY(), 2));
            if (distance <= range) {
                std::cout << "WanderingKnight " << knight.getName() << " kills Bandit " << bandit.getName() << std::endl;
                killedList.push_back(bandit.getName());
                bandit.setAlive(false);
                logFile << "Bandit " << bandit.getName() << " was killed by WanderingKnight " << knight.getName() << std::endl;
            }
        }
    }
}

void BattleVisitor::visit(Elf& elf) {
    if (!elf.isAlive()) return;
    for (auto& other : npcs) {
        if (other->getType() == "WanderingKnight" && other->isAlive()) {
            WanderingKnight& knight = dynamic_cast<WanderingKnight&>(*other);
            double distance = std::sqrt(std::pow(elf.getX() - knight.getX(), 2) + std::pow(elf.getY() - knight.getY(), 2));
            if (distance <= range) {
                std::cout << "Elf " << elf.getName() << " kills WanderingKnight " << knight.getName() << std::endl;
                killedList.push_back(knight.getName());
                knight.setAlive(false);
                logFile << "WanderingKnight " << knight.getName() << " was killed by Elf " << elf.getName() << std::endl;
            }
        }
    }
}

void BattleVisitor::printKilledList() const {
    std::cout << "Killed list:" << std::endl;
    for (const auto& name : killedList) {
        std::cout << name << std::endl;
    }
}