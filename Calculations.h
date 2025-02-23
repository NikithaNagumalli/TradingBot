// Momentum Trading
#pragma once
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;

class Calculations {
    private:
        int sma5;
        int sma10;
        int rsi;
        int stoch;
    public:
        Calculations(json input);
};