#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>
#include "HTTPRequest.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "statics.h"
#include "Calculations.h"


using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;

int main() {
    // string ACCESS_KEY = "57aa70039190e85498cdb195118fb9ec";
    // string SYM = "AAPL";
    // string URL = "http://api.marketstack.com/v1/eod?access_key=" + ACCESS_KEY + "&symbols=" + SYM;
    // cout << URL << endl;

    // WSADATA wsaData;
    // if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    //     std::cerr << "WSAStartup failed." << std::endl;
    //     cout << "WSAStartup failed." << endl;
    //     return 1;
    // }

    // try {
    //     http::Request request{URL};
    //     const http::Response response = request.send("GET");
    //     string response_body = string(response.body.begin(), response.body.end());
    //     json data = json::parse(response_body);

    //     cout << "response body: " << response_body << endl;
    //     cout << "in try" << endl;
    // } catch (const std::exception& e) {
    //     cout << "Exception caught: " << e.what() << endl;
    // }

    // WSACleanup();
    json mockData = json::parse(reponseBody);
    cout << mockData["pagination"]["limit"] << endl;
    Calculations c = Calculations(mockData);
    return 0;
}