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
	      std::string username = json.at("login").get<std::string>();
              std::string full_repo_path ="https://api.github.com/repos/" + username + "/" + repo_name;
	      cpr::Response repo_exist = cpr::Get(
			      cpr::Url{full_repo_path},
			      cpr::Header{
			       {"Authorization","Bearer " + token},
			       {"Accept", "application/vnd.github+json"},
                               {"User-Agent", "repo-checker"}
			      },
			      cpr::Timeout{1000}
			      );
	      if(repo_exist.status_code != 200) {
	       std::cout<<repo_name<<" does not exist";

	      }
	      else{
	        std::cout<<"Repo Exist"<<std::endl;
	      } 
	      return full_repo_path;
      } else{
	      std::cerr << "Authentication failed (HTTP " << r.status_code << ")." << std::endl;
	      std::cerr<<"Error: "<<r.text<<std::endl;
	      return "";
      }
}
