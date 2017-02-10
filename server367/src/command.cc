#include "command.hpp"

auto Command::get_output() -> std::string {
  return output;
}

auto Command::get_return_status() -> int {
  return return_status;
}
