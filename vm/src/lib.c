
#include <errno.h>
#include <unistd.h>
#include <string.h>


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

 