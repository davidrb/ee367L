#include <functional>
#include <iostream>
#include <map>

using std::cout;
using std::function;
using std::map;
using std::flush;
using std::endl;
using std::cout;
using std::string;

auto running = true;

void quit(string const&) {
  cout << "quitting..." << endl;
  running = false;
}

void list(string const&) {
  auto cmd = Command{"/usr/bin/ls", "ls"};
  cout << cmd.get_output() << flush;
}

void check(string const& filename) {
  auto cmd = Command{"/usr/bin/ls", "ls", filename.c_str()};

  if(cmd.get_return_status() == 0)
    cout << "File exists." << endl;
  else 
    cout << "File does not exist." << endl;
}

void print(string const& filename) {
  auto cmd = Command{"/usr/bin/cat", "cat", filename.c_str()};
  cout << cmd.get_output() << flush;
}

auto handler = std::map<string, std::function<void(string const&)>>{
  {"q", quit},
  {"p", print},
  {"c", check},
  {"l", list}
};
