#include "Calculations.h"

Calculations::Calculations(json input) {
    //int days = input["data"].size();

    // calculate SMA5
    for (int i = 0; i < 5; i++) {
        _sma5 += double(input["data"][i]["close"]);
    }
    _sma5 /= 5;

    // calculate SMA10
    for (int i = 0; i < 10; i++) {
        _sma10 += double(input["data"][i]["close"]);
    }
    _sma10 /= 10;

    // calculate Stochastic 14-3-3
    // The most common parameters for the Stochastic Oscillator are (14, 3, 3), which means: 14-period %K: The current closing price minus the lowest price over the last 14 periods, divided by the highest price minus the lowest price over the last 14 periods.

    double close = double(input["data"][0]["close"]);
    std::priority_queue<double> lowest;
    std::priority_queue<double, std::vector<double>, std::greater<double>> highest;
    for (int i = 0; i < 14; i++) {
        lowest.push(double(input["data"][i]["low"]));
        highest.push(double(input["data"][i]["high"]));
    }
    _stoch = (close - lowest.top()) / (highest.top() - lowest.top());

    // calculate RSI
    double averageGain = 0;
    double averageLoss = 0;
    double currentGain = 0;
    double currentLoss = 0;

    double currentOpen = double(input["data"][0]["open"]);
    double currentClose = double(input["data"][0]["close"]);

    if (currentOpen < currentClose) {
        currentGain += currentClose - currentOpen;
    } else {
        currentLoss += currentOpen - currentClose;
    }

    for (int i = 1; i < 14; i++) {
        double open = double(input["data"][i]["open"]);
        double close = double(input["data"][i]["close"]);

        if (open < close) {
            averageGain += close - open;
        } else {
            averageLoss += open - close;
        }
    }

    // averageGain /= 13;
    // averageLoss /= 13;

    _rsi = 100 - (100 / (1 + ((averageGain + currentGain) / (averageLoss + currentLoss))));


    std::cout << "SMA5: " << _sma5 << " SMA10: " << _sma10 << " STOCH: " << _stoch << " RSI: " << _rsi << std::endl;
}