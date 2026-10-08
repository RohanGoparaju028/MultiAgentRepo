#include<iostream>
#include<filesystem>
#include "GithubAuthenticate.h"

namespace fs = std::filesystem;
const std::string folder_name = ".git";
bool isGitInitialized() {
  if(fs::exists(folder_name) &&fs::is_directory(folder_name)) {
    return true;
  } else {
    return false;
  }
}
int main() {
 bool flag = isGitInitialized();
 if(flag) {
  std::cout<<"git is initialized in the current directory"<<std::endl;
  authenticateGithubCredential();
 } else{
   std::cout<<"git is uninsitalized in the current directory"<<std::endl;
 }
 return 0;
}
