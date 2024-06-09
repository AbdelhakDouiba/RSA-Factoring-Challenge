#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <gmp.h>

void calc(mpz_t n);
int is_prime(mpz_t n);
void clr(mpz_t *a, mpz_t *b, mpz_t *c, mpz_t *d, mpz_t *e, mpz_t *f, mpz_t *g, mpz_t *h, mpz_t *i);
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
	mpz_t a, zero, nmoda, one, b;

	mpz_init(a);
	mpz_init(b);
	mpz_init(one);
	mpz_init(nmoda);
	mpz_init(zero);
	mpz_set_str(one, "1", 10);
	mpz_set_str(zero, "0", 10);
	mpz_set_str(a, "2", 10);
	mpz_set_str(b, "1", 10);
	while (mpz_cmp(n, a) > 0)
	{
		mpz_mod(nmoda, n, a);
		if (mpz_cmp(nmoda, zero) == 0)
		{
			mpz_tdiv_q(b, n, a);
			if (is_prime(a) == 0 && is_prime(b) == 0)
				break;
			mpz_add(a, a, one);
		}
		if (mpz_cmp(a, n) == 0)
		{
			break;
		}
	}
	gmp_printf("%Zd=%Zd*%Zd\n", n, b, a);
	clr(&a, &b, &nmoda, &one, &zero, NULL, NULL, NULL, NULL);
}

/**
*is_prime - check if a number isprime
*@n: the number
*
*Return: 0 if it prime
*/
int is_prime(mpz_t n)
{
	mpz_t two, three, i, imul, itwo, nomdi, zero, sqr, one;

	mpz_init(two);
	mpz_init(one);
	mpz_init(sqr);
	mpz_init(zero);
	mpz_init(itwo);
	mpz_init(nomdi);
	mpz_init(three);
	mpz_init(i);
	mpz_init(imul);
	mpz_set_str(zero, "0", 10);
	mpz_set_str(two, "2", 10);
	mpz_set_str(three, "3", 10);
	if (mpz_cmp(n, three) <= 0)
	{
		clr(&two, &three, &i, &imul, &itwo, &nomdi, &sqr, &zero, &one);
		return (0);
	}
	mpz_set_str(i, "5", 10);
	mpz_mul(imul, i, i);
	mpz_sqrt(sqr, n);
	while (mpz_cmp(imul, sqr) <= 0)
	{
		mpz_mod(nomdi, n, i);
		if (mpz_cmp(nomdi, zero) == 0)
		{
			clr(&two, &three, &i, &imul, &itwo, &nomdi, &sqr, &zero, &one);
			return (-1);
		}
		mpz_add(i, i, one);
		mpz_mul(imul, i, i);
	}
	clr(&two, &three, &i, &imul, &itwo, &nomdi, &sqr, &zero, &one);
	return (0);
}

/**
*clr - clear mpz variables
*@a - mpz variable
*@b - mpz variable
*@c - mpz variable
*@d - mpz variable
*@e - mpz variable
*@f - mpz variable
*@g - mpz variable
*@h - mpz variable
*@i - mpz variable
*/
void clr(mpz_t *a, mpz_t *b, mpz_t *c, mpz_t *d, mpz_t *e, mpz_t *f, mpz_t *g, mpz_t *h, mpz_t *i)
{
	mpz_clear(*a);
	mpz_clear(*b);
	mpz_clear(*c);
	mpz_clear(*d);
	mpz_clear(*e);
	mpz_clear(*f);
	mpz_clear(*g);
	mpz_clear(*h);
	mpz_clear(*i);
}



