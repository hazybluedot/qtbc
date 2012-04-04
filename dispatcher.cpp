#include <cstdlib>
#include <cstdio>
#include <unistd.h>

int main(int argc, const char* argv[])
{
  pid_t pid;
  int fd[4];

  pipe(fd);
  pipe(fd+2);

  pid = fork();

  if (pid == 0)
    {
      /* child process */
      close(fd[0]);
      dup2(fd[1],1);
      close(fd[3]);
      dup2(fd[2],0);
      execlp("bc", "bc", NULL);
      perror("execlp bc");
      exit(1);
    } else if ( pid < 0 )
    {
      perror("fork");
      close(fd[0]);
      close(fd[1]);
      close(fd[2]);
      close(fd[3]);
      exit(1);
    } else {
    /* parent process */
    close(fd[1]);
    dup2(fd[0],0);
    close(fd[2]);
    dup2(fd[3],1);
    execlp("./qtbc-gui", "qtbc-gui", NULL);
    perror("execlp qtbc-gui");
    exit(1);
  }

  return EXIT_SUCCESS;
}
