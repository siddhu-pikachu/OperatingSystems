#include "memlayout.h"
#include "types.h"
#include "syscall.h"
#include "user.h"
//#include "userproc.h"
#include "flexsc_syscalls.c"

int main()
{
      struct flex_proc* thisprocess;
      char* addr = flexsc_reg();
      thisprocess->entry = addr;
      flexsc_syscalls(thisprocess->entry,0);
      while(1){
            if(thisprocess->entry->status==1){
                  break;
            }
      }
      printf(1,"%d", thisprocess->entry->returnValue);
      exit();
}