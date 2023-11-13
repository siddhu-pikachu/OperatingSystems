#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// int
// mapflex(pde_t *pgdir, uint size, uint pa, int perm)
// {
//   void *va;
//   char *a, *last;
//   pte_t *pte;

//   a = (char*)PGROUNDDOWN((uint)va);
//   last = (char*)PGROUNDDOWN(((uint)va) + size - 1);
//   for(;;){
//     if((pte = walkpgdir(pgdir, a, 1)) == 0)
//       return -1;
//     if(!*pte & PTE_P)
//       panic("remap");
//     *pte = pa | perm | PTE_P;
//     if(a == last)
//       break;
//     a += PGSIZE;
//     pa += PGSIZE;
//   }
//   return va;
// }

int sys_flexsc_reg(void)
{
  struct proc *page;
  
  char *mem;
  if(mem = (pde_t*)kalloc() == 0)
  cprintf("error in initializing page");
  // if possible we can use sbrk() instead of kalloc to initialize a page table in the user address space
  //                    each entry is a set of values from the structure syscallPage_entry, whose size is 32bytes.
  //                    so 4096/32 = 128 entries
  //puschcli(); //is it more optimal to do it here?
  memset(mem, 0, PGSIZE);
  //memset(P2V(page->entry), 0, PGSIZE);
  mappages(page->pgdir,page->entry, PGSIZE, V2P(mem), PTE_W | PTE_U);
// int n=PGSIZE;
   //page->entry = myproc()->sz;
  //  if(growproc(n) < 0){
  //   cprintf("error in initializing page");
  //   return -1;
  //  }
  return page->entry;
}