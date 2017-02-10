#include <iostream>
#include <exception>
#include <string>
#include <functional>
#include <map>
#include <unistd.h>

int main() {
  auto handlers = std::map<char, std::function<void()>>{};

  handlers['l'] = [&](std::string const& arg) {
    // list
  };
}
