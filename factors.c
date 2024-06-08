#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <elf.h>

void calc(unsigned long long int n);

/**
*main - calclate the factorization
*@ac: argument count
*@av: argument vector
*
*Return: 0 if the progrma success
*/
int main(int ac, char **av)
{
	int fd_o, fd_r = 1, BUFFERSIZE = 1024;
	char *buff, *number;

	fd_o = open(av[1], O_RDONLY);
	if (fd_o == -1)
		return (-1);
	buff = (char *)malloc(sizeof(char) * BUFFERSIZE);
	if (buff == NULL)
	{
		close(fd_o);
		return (-1);
	}
	while (fd_r > 0)
	{
		fd_r = read(fd_o, buff, BUFFERSIZE);
		BUFFERSIZE += fd_r;
		if (fd_r > 0)
		{
			buff = (char *)realloc(buff, BUFFERSIZE);
			if (buff == NULL)
			{
				free(buff);
				close(fd_o);
				return (-1);
			}
		}
	}
	number = strtok(buff, "\n");
	while (number != NULL)
	{
		calc(strtoll(number, NULL, 10));
		number = strtok(NULL, "\n");
	}
	free(buff);
	close(fd_o);
	return (0);
}

/**
*calc - calculate and print the factor for the number
*@n: the number
*/
void calc(unsigned long long int n)
{
	unsigned long long int a = 2;

	while (n % a != 0 && a <= n)
		a++;
	printf("%lld=%lld*%lld\n", n, n / a, a);
}
