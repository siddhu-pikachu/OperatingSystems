#include "memlayout.h"
#include "types.h"
#include "syscall.h"
#include "user.h"



struct flex_proc {

  //struct syscallPage_info *spg;
  struct flex_syscallPage_entry *entry;
  
  // int exist_f;
  // proc()
  // {
  //   exist_f = 0;
  // }
};
struct flex_syscallPage_entry
{
    unsigned syscallNumber;
    unsigned noOfArguments;
    unsigned status;
    long argsArr[6];
    unsigned returnValue;
    int valid;
};