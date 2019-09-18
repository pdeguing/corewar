
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "vm.h"

#define UNKNOWN_ERROR "Unknown error"
  
int         strlen_(char *str)
{
    char    *ptr;

    ptr = str;
    while (str)
        str++;
    return (str - ptr);
}

void		perror_(const char *s)
{
    char    *str;
	
	if (errno < 0)
        write(2, UNKNOWN_ERROR, strlen_(UNKNOWN_ERROR));
	else 
	{
        str = strerror(errno);
        write(2, str, strlen_(str));
    }
	(void)s;
}

int			strcmp_(const char *rdi, const char *rsi)
{
	while (*rdi == *rsi++)
		if (*rdi++ == 0)
			return (0);
	return (*(unsigned char *)rdi - *(unsigned char *)--rsi);
}

void		bzero_(void *rsi, size_t rcx)
{
	char	*rdi;

	rdi = (char *)rsi;
	while (rcx--)
	{
		*rdi = 0;
		rdi++;
	}
}

char		*strcpy_(char *rdi, const char *rsi)
{
	char	*rax;

	rax = rdi;
	while ((*rdi++ = *rsi++))
		;
	return (rax);
}
 
void        *memcpy_(void *dst, const void *src, size_t n)
{
	size_t  i;
    char    *a;
    char    *b;

	i = 0;
    a = (char *)dst;
    b = (char *)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}

void		*memset_(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = c;
	return (b);
} 

int			scmp_(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int			sverif_(char *b, char *v)
{
	int i;
	unsigned char verif = 0;

	while (*b)
	{
		i = -1;
		while (v[++i])
		{
			if (*b == v[i])
				verif = 1;
		}
		if (verif == 0)
			return (0);
		verif = 0;
		++b;
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') ||
		(str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

char	*ft_strstr(const char *s1, const char *s2)
{
	int		x;
	int		a;
	char	*p1;
	char	*p2;

	x = 0;
	p1 = (char *)s1;
	p2 = (char *)s2;
	if (!*p2)
		return ((char *)p1);
	while (p1[x])
	{
		a = 0;
		while (p1[x] == p2[a] && p1[x])
		{
			++x;
			++a;
		}
		if (!p2[a])
			return (&((char *)p1)[x - a]);
		x = (x - a) + 1;
	}
	return (NULL);
}