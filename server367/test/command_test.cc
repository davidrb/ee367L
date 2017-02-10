#include "catch.hpp"
#include "../src/command.hpp"

TEST_CASE("Runs a command and return output as string", "") {
  auto cmd = Command{"/usr/bin/ls", "ls", "WORKSPACE"};
  REQUIRE( cmd.get_output() == "WORKSPACE\n" );
  REQUIRE( cmd.get_return_status() == 0 );
}
