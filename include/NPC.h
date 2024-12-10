#ifndef NPC_H
#define NPC_H

#include <string>

class NPC {
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;
    virtual std::string getType() const = 0;
    std::string getName() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    void setAlive(bool alive);
    void setX(int x);
    void setY(int y);

    // Новые методы для расстояния хода и убийства
    virtual int getMoveDistance() const = 0;
    virtual int getKillDistance() const = 0;

protected:
    std::string name;
    int x, y;
    bool alive;
};

class Bandit : public NPC {
public:
    Bandit(const std::string& name, int x, int y);
    std::string getType() const override;
    int getMoveDistance() const override;
    int getKillDistance() const override;
};

class WanderingKnight : public NPC {
public:
    WanderingKnight(const std::string& name, int x, int y);
    std::string getType() const override;
    int getMoveDistance() const override;
    int getKillDistance() const override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    std::string getType() const override;
    int getMoveDistance() const override;
    int getKillDistance() const override;
};

#endif