#include<iostream>
#include "nlohmann/json.hpp"
#include "Agent.h"
#include<cpr/cpr.h>

const std::string instructions = "You are an helpful ai agent. Your role as an assistant is  to make a request to  specific github repo that your user gives you the url   and go to that repo and build a knowldge graph of the project along with the information of the  dependencies that the project is using and verify  those dependencies with their exact version that is downloaded  in the user system and notify the user the current state of the dependencies without implicitly downloading those depencies.Based on knowldge graph  assist the user in solving  issue of the project by retriving relavant files.";
const std::string model_api = "http://localhost:11434";
void createAgent(std::string repoUrl) {
   
    nlohmann::json request = {
        {"model", "gemma4:e4b"}, 
        {"messages", nlohmann::json::array({
            {
                {"role", "system"},
                {"content", instructions}
            },
            {
                {"role", "user"},
                {"content", "Analyze this repository: " + repoUrl}
            }
        })},
        {"stream", false}
    };

    auto response = cpr::Post(
        cpr::Url{"http://localhost:11434/api/chat"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{request.dump()}
    );

    if (response.error.code != cpr::ErrorCode::OK) {
        std::cerr << "Request failed: "
                  << response.error.message << '\n';
        return;
    }

    if (response.status_code != 200) {
        std::cerr << "HTTP " << response.status_code
                  << ": " << response.text << '\n';
        return;
    }

    auto result = nlohmann::json::parse(response.text);
    std::cout << result.at("message").at("content").get<std::string>()<< '\n';
}
