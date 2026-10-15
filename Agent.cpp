#include<iostream>
#include "nlohmann/json.hpp"
#include "Agent.h"
#include<cpr/cpr.h>

const std::string message = "You are an helpful ai agent. Your role as an assistant is  to make a request to  specific github repo that your user gives you the url   and go to that repo and build a knowldge graph of the project along with the information of the  dependencies that the project is using and verify  those dependencies with their exact version that is downloaded  in the user system and notify the user the current state of the dependencies without implicitly downloading those depencies.Based on knowldge graph  assist the user in solving  issue of the project by retriving relavant files.";
const std::string model_api = "http://localhost:11434";
nlohmann::json request = {
 {"model","gemma4e2b"},
 {"message",nlohmann::json::array({message})},
 {"stream",false}
};
void createAgent() {
	cpr::Response response = cpr::Post(
			cpr::Url{model_api+"/api/chat"},
			cpr::Header{{"Content-Type","application/json"}},
			cpr::Body{({
                                 "model": "gemma4:e4b",
                                 "messages": [
                                  {"role": "user", "content": message}
                                     ],
                                   "stream": false
                        })});	
	std::cout<<response.text<<std::endl;
} 
