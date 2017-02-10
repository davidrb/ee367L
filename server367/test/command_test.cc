#include "catch.hpp"
#include "../src/command.hpp"

TEST_CASE("Returns output as string", "") {
  auto cmd = Command{"/usr/bin/ls", "ls", "WORKSPACE"};
  REQUIRE( cmd.get_output() == "WORKSPACE\n" );
}

TEST_CASE("Returns successful status") {
  auto cmd = Command{"/usr/bin/ls", "ls"};
  REQUIRE( cmd.get_return_status() == 0 );

  cmd = Command{"/usr/bin/ls", "ls", "non-existant"};
  REQUIRE( cmd.get_return_status() != 0 );
}
