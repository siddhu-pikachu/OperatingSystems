#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[])
{
      printf(1, "number of initial fork count %d\n", getcount(SYS_fork));
      if (fork() == 0)
      {
            mkdir("myhome");
            int fd = open("neehal.txt",0);
            close(fd);
            printf(1, "Child fork count %d\n", getcount(SYS_fork));
            printf(1, "Child write count %d\n", getcount(SYS_write));
            printf(1, "Child process id: %d\n", getpid());
      }
      else
      {
            wait();
            write(1, "my testcase", 11);
            printf(1, "Parent fork count %d\n", getcount(SYS_fork));
            printf(1, "Parent write count %d\n", getcount(SYS_write));
            printf(1, "Parent process id: %d\n", getpid());
      }
      printf(1, "count of: \n");
      printf(1, "chdir is %d\n", getcount(SYS_chdir));
      printf(1, "close is %d\n", getcount(SYS_close));
      printf(1, "exec is %d\n", getcount(SYS_exec));
      printf(1, "exit is %d\n", getcount(SYS_exit));
      printf(1, "fstat is %d\n", getcount(SYS_fstat));
      printf(1, "getcount is %d\n", getcount(SYS_getcount));
      printf(1, "wait is %d\n", getcount(SYS_wait));
      printf(1, "pipe is %d\n", getcount(SYS_pipe));
      printf(1, "read is %d\n", getcount(SYS_read));
      printf(1, "kill is %d\n", getcount(SYS_kill));
      printf(1, "getpid is %d\n", getcount(SYS_getpid));
      printf(1, "sbrk is %d\n", getcount(SYS_sbrk));
      printf(1, "sleep is %d\n", getcount(SYS_sleep));
      printf(1, "uptime is %d\n", getcount(SYS_uptime));
      printf(1, "open is %d\n", getcount(SYS_open));
      printf(1, "write is %d\n", getcount(SYS_write));
      printf(1, "mkdir is %d\n", getcount(SYS_mkdir));
      printf(1, "mknod is %d\n", getcount(SYS_mknod));
      printf(1, "unlink is %d\n", getcount(SYS_unlink));
      printf(1, "link is %d\n", getcount(SYS_link));

      exit();
}