// Momentum Trading
#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Calculations {
    private:;
        vector<double> _todayCalcs;
        vector<double> _yesterdayCalcs;
        //vector<double> _dayBeforeYesterdayCalcs;
        double _currPrice;
        int _holding = 0;
        double _cash = 0;

        void updatePositions();
        vector<double> calculations(json input, int daysAgo = 0);

        enum STATS {
            SMA5 = 0,
            SMA10 = 1,
            STOCH = 2,
            RSI = 3
        };

    public:
        Calculations(json input) {
            _currPrice = input["data"][0]["close"]; // not really, but for now until can get real time data
            _todayCalcs = calculations(input);
            _yesterdayCalcs = calculations(input, 1);
            //_dayBeforeYesterdayCalcs = calculations(input, 2);
            updatePositions();
        }
};