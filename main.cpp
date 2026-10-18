#include<iostream>
#include<filesystem>
#include "GithubAuthenticate.h"
#include "Agent.h"

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
  std::string repo_path = authenticateGithubCredential("BitMesh"); // BitMesh is an example and in the near future I will move away from hard encoding to dynamic repo name.
  
  if(repo_path == "") {
   std::cerr<<"Error while authenticating Github "<<std::endl;
  } else {
    std::cout<<repo_path<<std::endl;
    createAgent(repo_path);
  }
 } else{
   std::cout<<"git is uninsitalized in the current directory"<<std::endl;
 }
 return 0;
}
