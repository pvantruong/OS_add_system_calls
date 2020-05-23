#include <get_proc_info.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t mypid = getpid();
	int child_pid = fork();
if(child_pid != 0) {
	printf("Our PID: %d\n", mypid);
	struct procinfos info;
	if(get_proc_info(mypid, &info) == 0){
		printf("Below are the result from our get_proc_info: \n");
		printf("Student ID: %ld\n", info.studentID);
		printf("PID & name of current process: %d, %s\n", (info.proc).pid, info.proc.name);
		printf("PID & name of parrent process: %d, %s\n", (info.parent_proc).pid, info.parent_proc.name);
	        printf("PID & name of child process: %d, %s\n", (info.oldest_child_proc).pid, info.oldest_child_proc.name);
	}
	return 0;
}
}	
		

