#include "Observer.h"

FileObserver::FileObserver(const std::string& filename) : file(filename) {}

void FileObserver::update(const std::string& event) {
    file << event << std::endl;
}

void ScreenObserver::update(const std::string& event) {
    std::cout << event << std::endl;
}