#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <fstream>
#include <iostream>

class Observer {
public:
    virtual void update(const std::string& event) = 0;
    virtual ~Observer() = default;
};

class FileObserver : public Observer {
public:
    FileObserver(const std::string& filename);
    void update(const std::string& event) override;

private:
    std::ofstream file;
};

class ScreenObserver : public Observer {
public:
    void update(const std::string& event) override;
};

#endif // OBSERVER_H