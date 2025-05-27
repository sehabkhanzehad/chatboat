#include "chatbot.hpp"
#include "memory.hpp"
#include "api.hpp"
#include "markov.hpp"
#include "tfidf.hpp"
#include <iostream>
#include <ctime>
using namespace std;

void ChatBot::run()
{
    greet();
    Memory::loadKnowledgeBase("data/extra_programming_data.txt");
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
    // Convert input to lowercase for case-insensitive matching
    string lower = input;
    for (char &c : lower)
        c = tolower(c);

    if (lower.find("weather") != std::string::npos)
        return API::getWeather("Dhaka");

    else if (lower.find("news") != std::string::npos)
        return API::getNews();

    else if (lower.find("time") != std::string::npos)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "Current time is %I:%M %p.", ltm);
        return buffer;
    }

    else if (lower.find("date") != std::string::npos)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "Today's date is %A, %d %B %Y.", ltm);
        return buffer;
    }

    else if (lower.find("joke") != std::string::npos)
    {
        std::string jokes[] = {
            "Why don't scientists trust atoms? Because they make up everything!",
            "Why did the computer go to therapy? It had too many bytes of trauma.",
            "Parallel lines have so much in common... it’s a shame they’ll never meet."};
        int i = rand() % 3;
        return jokes[i];
    }

    else if (lower.find("hello") != std::string::npos || lower.find("hi") != std::string::npos)
        return "Hello there! How can I assist you today?";

    else if (lower.find("who are you") != std::string::npos)
        return "I'm your simple C++ AI chatbot created to help you learn and explore!";

    else if (lower.find("bye") != std::string::npos || lower.find("goodbye") != std::string::npos)
        return "Goodbye! Have a great day.";

    else
    {
        std::string programmingAnswer = Memory::findProgrammingAnswer(input);
        if (!programmingAnswer.empty())
            return programmingAnswer;
        return Markov::generateReply(input);
    }
}
