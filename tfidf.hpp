#pragma once
#include <string>

namespace TFIDF {
    double computeScore(const std::string& term, const std::string& doc);
}
