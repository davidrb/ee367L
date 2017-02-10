#include "command.hpp"
#include "handlers.hpp"

#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::cerr;
using std::getline;
using std::stringstream;
using std::end;

int main() {
  string line;
  getline(cin, line);

  while(running && cin) {
    auto ss = stringstream{line};

    string command, arg;
    ss >> command >> arg;

    if(handler.find(command) == end(handler))
      cerr << "unrecognized command.\n";
    else 
      handler[command](arg);

    if (running)
    getline(cin, line);
  }
}
