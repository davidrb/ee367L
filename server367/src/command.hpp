#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>

class Command {
public:
  template<typename... Args>
  Command(std::string const& binary, Args... args) {
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
      execl(binary.c_str(), args..., nullptr);
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

    output = buffer;
  }

  auto get_output() -> std::string; 

private:
  std::string output;
};

#endif
