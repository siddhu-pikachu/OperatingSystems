<h1 style="text-align: center;">Operating Systems - lab6 Report</h1>

## Pre-requisites for a new system call creation
the required structures for enabling a syscall_page 
It is imperative that we change we change few files for the working of any new system call that we create, the changes necessary for *flexsc_register* are given below:

- syscall.h (Defined the syscall name and its respective syscall number)
- syscall.c (Adding the pointer to the handler function we wrote)
- sysproc.c (Write the handler function)
- usys.S (Add `SYSCALL(flexsc_register)`, this will link the function handler and the pre-defined system call name)
- user.h (Defined the return type and type of input arguments the system call takes)

## Implementation of flexsc_register

The function handler for `sys_flexsc_register()` will call `kalloc()` which will return physical address of the base pointer of the syscall page. We can do the mapping in two ways:

- 1. We can either implement `p2vaddr` where we will use the physical address returned by kalloc to find the virtual address, the mmu has mapped it to in page table.
- 2. We can have a fixed virtual address and we can change the mmu such that it will always map the physical address to the virtual address when flexsc_register system call is calling kalloc
     > We use the second method and the system call will return this virtual address.

Next, we will be implementing structure of syscall-page for a process. We will be creating two structures named `syscallPage_entry` (for the syscall page entries) and `syscallPage_info` (for the information regarding the syscall page) whose code (in C) given below:
```
struct syscallPage_entry
{
    unsigned syscallNumber;
    unsigned noOfArguments;
    unsigned status;
    long argsArr[6];
    unsigned returnValue;
};

// Assuming one page is enough for one process
struct syscallPage_info
{
    unsigned noOfEntries;
    struct page_entry* entry;
    char* basePointer;
};

The below code is the function to initialize the syscall pages:

int initialize_syspages(struct syscallPage_info* p1)
{
    getPageSize();
    struct flexsc_sysentry *entries;
    for all entries
    {
        entry.status = FREE;
    }
    get p1 base pointer and store it in p1->basePointer
    info->entry = entries;
    return 0;
}

int syscall_entry()
{
    acquire(lock pointer);
    for all entries
    {
        if entry.status is FREE{
            set entry.status to BUSY;
            release( lock pointer);
            return the first entry of the page;
        }
    }
}

int flexsc_write( arguments[], number of arguments)
{
    get(freepage entry);
    vectornumber of the free entry is set to the vector number of flexsc_write;
    for all arguments in page_entry{
        set the args[i] to arguments[i];
    }
}
```
For the above code, we have to create a new file and make appropriate changes in the *makefile* to compile this extra file along with the rest. And the new file must be included in the other files to utilise the functions written in this new file.

> Another part of the flexsc_register is to turn off the trap frames. The kernel has has to use ***pushcli()*** on the core it is working so as to disable the hardware timer interrupts, thus disabling the user programs to schedule on the reserved core.

## SCHEDULING OF THE THREADS (THE THREAD LIBRARY)
This can be implemented in 3 possible ways :-

- 1) Non-rigid dynamic allocation of cores for system call processing through scheduler, no core is reserved.(reduced spatial and temporal locality). some cores are favoured to still maintain some spatilal and temporal locaity.
- 2) Rigid dynamic allocation of the cores for system call processing. few cores are always reserved for kernel to compute the systemcalls for the syscall pages. the number of cores n that will be reserved can be determined by the user (0<n<total number of cores). changes can be made in the scheduler such that these reserved cores will not be scheduled for any of the user processes.
- 3) Rigid static allocation of cores. the os designer will reserve a fixed optimal number of cores for kernel, instead of the user like in the above case.

Both 2nd and 3rd case have better use of spatial and temporal locality, but the optimality is questionable as there can be 2 flaws:

- a) If the processes are not systemcall heavy and we reserve more than enough cores for kernel. this will lead to reduced performance as the cores reserved are under utilised.
- b) If the processes are very systemcall heavy and we reserve less than needed cores for kernel. this will lead to reduced performance as the un-reserved cores are under utilised.
