// #include "types.h"
// #include "defs.h"
// #include "param.h"
// #include "memlayout.h"
// #include "mmu.h"
// #include "proc.h"
// #include "x86.h"
// #include "spinlock.h"

// int main()
// {
//     char *mem;
//     mem = flexsc_reg();
//     // mem = kalloc();
//     // page->entry = mem; // if possible we can use sbrk() instead of kalloc to initialize a page table in the user address space
//     //       // each entry is a set of values from the structure syscallPage_entry, whose size is 32bytes.
//     //                               // so 4096/32 = 128 entries
//     // //puschcli(); //is it more optimal to do it here?
//     // char* something;
//     //char *addr = 0;
//     // memset(mem, 0, PGSIZE);
//     // mappages(page->pgdir, *addr, PGSIZE, V2P(mem), PTE_W|PTE_U);
//     //memmove(mem, something, (int)addr);
//     exit();
//     //return addr;
// }