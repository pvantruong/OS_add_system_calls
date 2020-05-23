#include "get_proc_info.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 200

long get_proc_info(pid_t pid, struct procinfos * info) {
	long sys_return_value;
	sys_return_value = syscall(548, pid, info);
	return sys_return_value;
}
