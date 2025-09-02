#include "Calculations.h"

vector<double> Calculations::calculations(json input, int daysAgo) {
    //int days = input["data"].size();

    // calculate SMA5
    double sma5;
    for (int i = daysAgo; i < daysAgo + 5; i++) {
        sma5 += double(input["data"][i]["close"]);
    }
    sma5 /= 5;

    // calculate SMA10
    double sma10;
    for (int i = daysAgo; i < daysAgo + 10; i++) {
        sma10 += double(input["data"][i]["close"]);
    }
    sma10 /= 10;

    // calculate Stochastic 14-3-3
    // The most common parameters for the Stochastic Oscillator are (14, 3, 3), which means: 14-period %K: The current closing price minus the lowest price over the last 14 periods, divided by the highest price minus the lowest price over the last 14 periods.

    double close = double(input["data"][0]["close"]);
    std::priority_queue<double> lowest;
    std::priority_queue<double, std::vector<double>, std::greater<double>> highest;
    for (int i = daysAgo; i < daysAgo + 14; i++) {
        lowest.push(double(input["data"][i]["low"]));
        highest.push(double(input["data"][i]["high"]));
    }
    double stoch = (close - lowest.top()) / (highest.top() - lowest.top());

    // calculate RSI https://www.investopedia.com/terms/r/rsi.asp
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

    for (int i = daysAgo + 1; i < daysAgo + 14; i++) {
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

    double rsi = 100 - (100 / (1 + ((averageGain + currentGain) / (averageLoss + currentLoss))));


    std::cout << "SMA5: " << sma5 << " SMA10: " << sma10 << " STOCH: " << stoch << " RSI: " << rsi << std::endl;
    return {sma5, sma10, stoch, rsi};
}

void Calculations::updatePositions() {
    // Open a long position when: SMA 5 crosses the SMA 10 line. Stochastic goes upwards. RSI is higher than 50.
    if ((_todayCalcs[STATS::SMA5] > _todayCalcs[STATS::SMA10] && _yesterdayCalcs[STATS::SMA5] <= _yesterdayCalcs[STATS::SMA10]) && (_todayCalcs[STATS::STOCH] > _yesterdayCalcs[STATS::STOCH]) && _todayCalcs[STATS::RSI] > 50) {
        _cash -= _currPrice;
        _holding++;
        std::cout << "BUYING AT " << _currPrice << std::endl;
    }


    // Open a short position when: SMA 10 crosses the SMA 5 line. Stochastic goes downwards. RSI is lower than 50.
    if ((_todayCalcs[STATS::SMA10] > _todayCalcs[STATS::SMA5] && _yesterdayCalcs[STATS::SMA10] <= _yesterdayCalcs[STATS::SMA5])&& (_todayCalcs[STATS::STOCH] < _yesterdayCalcs[STATS::STOCH]) && _todayCalcs[STATS::RSI] < 50 ) {
        _cash += _currPrice;
        _holding--;
        std::cout << "SELLING AT " << _currPrice << std::endl;
    }

    // avoid extremes
    if (_cash < -10000 && _holding > 0) {
        _cash += _currPrice;
        _holding--;
        std::cout << "SELLING AT " << _currPrice << std::endl;
    }

    if (_holding < -100) {
        _cash -= _currPrice;
        _holding++;
        std::cout << "BUYING AT " << _currPrice << std::endl;
    }
    std::cout << "UPDATED POSITIONS: CASH " << _cash << " HOLDING " << _holding << std::endl;
}