#pragma once
#include <string>
using namespace std;

class ChatBot {
public:
    void run();

private:
    void greet();
    string getUserInput();
    string generateResponse(const string& input);
};
