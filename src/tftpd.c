#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
   	printf("%s", argv[0]);
   	printf(argc);
   	return argc;
}