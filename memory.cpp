#include "memory.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cctype>

static std::unordered_map<std::string, std::string> programmingKnowledge;

std::string toLower(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void Memory::storeConversation(const std::string &line)
{
    std::ofstream file("data/memory.txt", std::ios::app);
    if (file.is_open())
    {
        file << line << "\n";
        file.close();
    }
}

void Memory::loadKnowledgeBase(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line, question, answer;

    while (std::getline(file, line))
    {
        if (line.find("Q: ") != std::string::npos)
        {
            question = toLower(line.substr(line.find("Q: ") + 3));
        }
        else if (line.find("A: ") != std::string::npos)
        {
            answer = line.substr(line.find("A: ") + 3);
            programmingKnowledge[question] = answer;
        }
    }
}
std::string Memory::findProgrammingAnswer(const std::string &input)
{
    std::string lower = toLower(input);
    for (const auto &pair : programmingKnowledge)
    {
        if (lower.find(pair.first) != std::string::npos || pair.first.find(lower) != std::string::npos)
            return pair.second;
    }
    return "";
}