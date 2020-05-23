#include <linux/kernel.h>
#include <asm/current.h>
#include <asm/errno.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/string.h>
 
struct proc_info { //info about a single process
    pid_t pid;  //pid of the process
    char name[16];  //file name of the program executed
};
 
 
struct procinfos { //info about processes we need
    long studentID; //for the assignment testing
    struct proc_info proc;  //process with pid or current process
    struct proc_info parent_proc;  //parent process
    struct proc_info oldest_child_proc;  //oldest child process
};

//asmlinkage long sys_get_proc_info(pid_t pid, struct procinfos * info)
SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos *, info)
{
     struct task_struct *process;
    printk (KERN_INFO "sys_get_proc_info is invoked,ID: 1814569");
    if (pid == -1) { 		//current process
        process = current;
        //(process, info);
    }
    else if (pid >= 0) {	//other process
        process = find_task_by_vpid(pid);
        if (process == NULL) return EINVAL;
        //getProcInfo(process, info);
    }
    else {return EINVAL;}

    struct task_struct *pParent, *pOldest_Child;
    struct list_head *childrenList;
    
    info[0].studentID = 1814569;

    //originated process
    (info[0].proc).pid = process->pid;
    get_task_comm((info[0].proc).name, process);
 
    //parent process
    pParent = process->parent;
    if (pParent){
        (info[0].parent_proc).pid = pParent->pid;
        get_task_comm((info[0].parent_proc).name, pParent);
    }
 
    //oldest child process
    childrenList = &process->children;
    if (list_empty(childrenList)) {
		pOldest_Child = NULL;
	}
    else 
		pOldest_Child = list_first_entry(childrenList, struct task_struct, sibling);
 
    if (pOldest_Child != NULL){
        (info[0].oldest_child_proc).pid = pOldest_Child->pid;
        get_task_comm((info[0].oldest_child_proc).name, pOldest_Child);
    }
    else {
		(info[0].oldest_child_proc).pid = -1;
		//printk(KERN_INFO "No child process founded!");
	}
    return 0;
}
