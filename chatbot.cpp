#include "chatbot.hpp"
#include "memory.hpp"
#include "api.hpp"
#include "markov.hpp"
#include "tfidf.hpp"
#include <iostream>
using namespace std;

void ChatBot::run()
{
    greet();

    string input;
    while (true)
    {
        cout << "\nYou: ";
        input = getUserInput();

        if (input == "exit")
            break;

        Memory::storeConversation(input);
        string response = generateResponse(input);
        Memory::storeConversation(response);

        cout << "Bot: " << response << "\n";
    }
}

void ChatBot::greet()
{
    cout << "Welcome to AI ChatBot! Type 'exit' to quit.\n";
}

string ChatBot::getUserInput()
{
    string input;
    getline(cin, input);
    return input;
}

string ChatBot::generateResponse(const string &input)
{
    if (input.find("weather") != string::npos)
        return API::getWeather("Dhaka");
    else if (input.find("news") != string::npos)
        return API::getNews();
    else
        return Markov::generateReply(input);
}
