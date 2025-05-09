#include "api.hpp"

std::string API::getWeather(const std::string& location) {
    return "The weather in " + location + " is sunny with 30°C.";
}

std::string API::getNews() {
    return "Here are today's top news headlines...";
}
