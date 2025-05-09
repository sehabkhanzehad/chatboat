#include "memory.hpp"
#include <fstream>

void Memory::storeConversation(const std::string& line) {
    std::ofstream file("data/memory.txt", std::ios::app);
    if (file.is_open()) {
        file << line << std::endl;
        file.close();
    }
}
