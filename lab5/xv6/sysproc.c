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

int sys_v2paddr(void)
{
  addr *v_a, *p_a;

  if (argptr(0, (void *)&p_a, sizeof(*p_a)) < 0 || argptr(1, (void *)&v_a, sizeof(*v_a)) < 0)
  {
    return -1;
  }

  struct proc *curr_process = myproc();
  pde_t *pgdir = curr_process->pgdir;
  pde_t *pde = &pgdir[PDX(v_a)];

  if (!(*pde ^ PTE_P) || !(*pde ^ PTE_U))
  {
    return -1;
  }

  pde_t *pgtab = (pte_t *)P2V(PTE_ADDR(*pde));
  pde_t *pte = &pgtab[PTX(v_a)];

  if (!(*pte ^ PTE_P) || !(*pte ^ PTE_U))
  {
    return -1;
  }

  *p_a = PTE_ADDR(*pte) | PTE_FLAGS(v_a);
  return 0;
}

// int
// sys_v2paddr(void) {
//     addr *v_a, *p_a;

//     static_assert(sizeof(*v_a) < 0,-1);
//     static_assert(sizeof(*p_a) < 0,-1);
//     return 0;
// }
//  is this correct???