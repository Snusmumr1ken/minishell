#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int		main(void)
{
	struct stat buf;
	if (stat("src", &buf) == -1)
		return (0);
	if (S_ISREG(buf.st_mode))
		printf("Это обычный файл\n");
	else if (S_ISDIR(buf.st_mode))
		printf("Это каталог\n");
	return (0);
}
