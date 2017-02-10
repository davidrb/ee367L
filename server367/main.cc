#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <exception>
#include <cstring>

#include <unistd.h>
#include <sys/wait.h>

#include "src/command.hpp"

using std::cin;
using std::string;

auto handler = std::map<string, std::function<void(string const&)>>{};
auto running = true;

void populate_handlers() {
  handler["q"] = [&](string const&) {
    std::cerr << "quitting..." << std::endl;
    running = false;
  };

  handler["l"] = [&](string const&) {
    std::cout << Command{"/usr/bin/ls", "ls"}.get_output() << std::flush;
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
