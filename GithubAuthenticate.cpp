#include<cpr/cpr.h>
#include<string.h>
#include "nlohmann/json.hpp"
#include "dotenv.h"
#include "GithubAuthenticate.h"

std::string authenticateGithubCredential(std::string repo_name) {
      dotenv::init();
      const std::string token = dotenv::getenv("GITHUB_PAT_TOKEN");
      if (token.empty()) {
	      std::cerr << "Authentication failed: GITHUB_PAT_TOKEN is missing or empty." << std::endl;
              return "";
      }
      cpr::Response r = cpr::Get(
		   cpr::Url{"https://api.github.com/user"},
		   cpr::Header{
		   {"Authorization","Bearer " + token},
		   {"Accept","application/json"},
		   }  
		 );
      if (r.error.code != cpr::ErrorCode::OK) {
	      std::cerr << "Authentication request failed: " << r.error.message << std::endl;
              return "";
      }
      if(r.status_code == 200) {
	      std::cout<<r.header["content-type"]<<std::endl;
	      std::cout<<"Authentication successful"<<std::endl;
              auto json = nlohmann::json::parse(r.text);
	      std::string repo_url = json["repos_url"].get<std::string>();
	      std::string full_repo_path = repo_url + "/"+repo_name;
	      std::cout<<full_repo_path<<std::endl;
	      return full_repo_path;
      } else{
	      std::cerr << "Authentication failed (HTTP " << r.status_code << ")." << std::endl;
	      std::cerr<<"Error: "<<r.text<<std::endl;
	      return "";
      }
}
