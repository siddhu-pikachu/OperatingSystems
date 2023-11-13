#include "flexsc_syscalls.h"
#include "memlayout.h"
#include "types.h"
#include "syscall.h"
#include "user.h"

int flexsc_syscalls(struct flex_syscallPage_entry * entry, int num)
{

      // write an entry in the syscall page
      //syscall_pg_va = 0x01234560;
      //s_page = (flexsc_entry *)syscall_pg_va;

      //for (int i = 0; i < 128; i++)
      //{
            // if (s_page[i].valid)
            // {
            //       // set the record appropriately
            // }
            entry->valid = 1;
            if( entry->valid ){
                  entry->syscallNumber = 0;
                  entry->status = 0;
            }
      //}
      while(entry->status!=1){
            
      }
      // spin till return value is set
      return entry->returnValue;
      //return s_page[i].retval;
}
