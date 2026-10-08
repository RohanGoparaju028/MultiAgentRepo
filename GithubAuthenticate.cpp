#include<cpr/cpr.h>
#include "dotenv.h"
#include "GithubAuthenticate.h"
using namespace std;

void authenticateGithubCredential() {
      dotenv::init();
      const string token = dotenv::getenv("GITHUB_PAT_TOKEN");
      if (token.empty()) {
        cerr << "Authentication failed: GITHUB_PAT_TOKEN is missing or empty." << endl;
        return;
      }
      cpr::Response r = cpr::Get(
		   cpr::Url{"https://api.github.com/user"},
		   cpr::Header{
		   {"Authorization","Bearer " + token},
		   {"Accept","application/vnd.github+json"},
		   {"User-Agent","My-Cpp-Github-App"}
		   }  
		 );
      if (r.error.code != cpr::ErrorCode::OK) {
        cerr << "Authentication request failed: " << r.error.message << endl;
        return;
      }
      if(r.status_code == 200) {
       cout<<"Authentication successful"<<endl;
       cout<<r.text<<endl;
       return;
      } else{
        cerr << "Authentication failed (HTTP " << r.status_code << ")." << endl;
	cerr<<"Error: "<<r.text<<endl;
      }
}
