// Momentum Trading
#pragma once
#include <iostream>
#include <queue>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;

class Calculations {
    private:
        double _sma5;
        double _sma10;
        double _rsi;
        double _stoch;
    public:
        Calculations(json input);
};