#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <gmp.h>

void calc(mpz_t n);

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
	mpz_t num;

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
		mpz_init(num);
		mpz_set_str(num, (const char *)number, 10);
		calc(num);
		number = strtok(NULL, "\n");
		mpz_clear(num);
	}
	free(buff);
	close(fd_o);
	return (0);
}

/**
*calc - calculate and print the factor for the number
*@n: the number
*/
void calc(mpz_t n)
{
	int flag = 1;
	mpz_t a, zero, nmoda, one;

	mpz_init(a);
	mpz_init(one);
	mpz_init(nmoda);
	mpz_init(zero);
	mpz_set_str(one, "1", 10);
	mpz_set_str(zero, "0", 10);
	mpz_set_str(a, "2", 10);
	while (flag)
	{
		mpz_mod(nmoda, n, a);
		if (mpz_cmp(nmoda, zero) != 0)
			mpz_add(a, a, one);
		else
		{
			flag = 0;
			break;
		}
	}
	mpz_tdiv_q(one, n, a);
	gmp_printf("%Zd=%Zd*%Zd\n", n, one, a);
	mpz_clear(nmoda);
	mpz_clear(a);
	mpz_clear(one);
	mpz_clear(zero);
}
