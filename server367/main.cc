#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <exception>
#include <cstring>

#include <unistd.h>
#include <sys/wait.h>

using std::cin;
using std::string;

auto handler = std::map<string, std::function<void(string const&)>>{};
auto running = true;

auto run_subprocess(const char *file, const char* arg) -> string {
  int fd[2];
  pipe(fd);

  auto pid = fork();

  if(pid == -1) 
    throw std::runtime_error{"error forking"};

  if(pid == 0) {
    // child
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    close(fd[0]);
    execl(file, arg, nullptr);
    throw std::runtime_error{"could not exec."};
  } 

  // parent
  close(fd[1]);
  int status;
  wait(&status);

  char buffer[10000u];
  std::memset(buffer, 0, sizeof buffer);
  read(fd[0], buffer, sizeof buffer);
  close(fd[0]);

  return buffer;
}

void populate_handlers() {
  handler["q"] = [&](string const&) {
    std::cerr << "quitting..." << std::endl;
    running = false;
  };

  handler["l"] = [&](string const&) {
    std::cout << run_subprocess("/usr/bin/ls", "ls");
  };
}

int main() {
  populate_handlers();

  string line;
  std::getline(cin, line);

  while(running && std::cin) {
    auto ss = std::stringstream{line};

    string command, arg;
    ss >> command >> arg;

    if(handler.find(command) == std::end(handler))
      std::cerr << "unrecognized command.\n";
    else 
      handler[command](arg);

    if (running)
    std::getline(cin, line);
  }
}
