#include "memlayout.h"
#include "types.h"
#include "syscall.h"
#include "user.h"

void printer(addr* v_a)
{
      addr* p_a;
      int res = v2paddr(&p_a, v_a);
      if (res == 0)
      {
            printf(1, "0x%x is the physical address of 0x%x (virtual address)\n", p_a, v_a);
      }
      else
      {
            printf(1, "Virtual address passed is invalid\n");
      }
}

char var2 = 'a';

int main()
{
      addr* p_a;

      addr* v_add = (addr*) 0xFFF9;
      printer(v_add);

      addr* extmem = (void*)(KERNBASE + EXTMEM);
      printer(extmem);

      int var1 = 999;
      addr* v_a = (addr*)(&var1);
      printer(v_a);

      p_a = 0;
      v_a = (addr*)(&var2);
      printer(v_a);

      p_a = 0;
      int* ptr = (int*)malloc(sizeof(int));
      if (ptr == 0)
      {
            printf(1, "Memory allocation failed\n");
            exit();
      }
      else
      {
            v_a = (addr*)(&ptr);
            printer(v_a);
      }
      exit();
}