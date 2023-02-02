#include <stdio.h>  // for printf()
#include <unistd.h> // for read()
#include <fcntl.h>  // for open()
#include <stdlib.h> // for malloc()
//если read что-то кроме еоф считал, то 1, затем функция 0 возвращает
//BUFFER_SIZE 
// Мой ГНЛ абортится, если файл заканчивается на '\n'.
// Типа в этом случае новая строка вроде бы есть, а вроде бы нет... Но для проги это повод посчитать, что не надо создавать
// лайн, поскольку на очередной итерации r = 0 и NULL в остатке, типа всё, конец. В результате, очередной лайн не 
// маллочится, а когда в тестах делается последний free, то естесн летит аборт.
// записывай "" в line при EOF


void	ft_bzero(void *s, int n)
{
/*
**       The  bzero()  function  erases  the  data  in the n bytes of the memory
**       starting at the location pointed to by s, by writing zeros (bytes  con‐
**       taining '\0') to that area.
*/
	void	*ptr;

	ptr = s + n;
	while (s != ptr)
		*(char *)s++ = '\0';
}


int		ft_strlen(char *s)
{
/*
**       The strlen() function calculates the length of the string pointed to by
**       s, excluding the terminating null byte ('\0').
**       The strlen() function returns the number of bytes in the string pointed
**       to by s.
*/
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s++ && *(s - 1) != '\n')
		printf("s1 = %s\n", s);
	printf("s1 = %s\n", s);
	return ((int)(s - tmp));
}

int		where_is_newline(char *buf)
{
/*
**	Find where in string 'buf' is located newline ('\n').
**	Parameters
**	#1.  The string.	
**	Return value: The index of '\n' in 'buf'. Length of 'buf' if there is no
**	'\n' in 'buf'.
*/
	char	*iter;

	iter = buf;
	while (*iter)
	{
		if (*iter == '\n')
			return (iter - buf);
		iter++;
	}
	return (iter - buf);
}

char	*ft_strjoin(char *s1, char *s2, int nl)
{
/*
**	Allocates (with malloc(3)) and returns a new string, which is the result of
**	the concatenation of s1 and nl bytes from s2. s1 could be NULL.
**	Params: #1.The prefix string. #2.The suffix string. #3.The number of bytes
**	to take from s2. Return value: The new string. NULL if the allocation fails.
*/
	char	*join;
	int		len;

	len = ft_strlen(s1) + nl;
	printf("ft_strlen(s1) = %d\n", ft_strlen(s1));
	printf("nl = %d\n", nl);
	printf("len = %d\n", len);
	printf("s1 = %s", s1);
	if (!(join = (char *)malloc(sizeof(char) * (len + 1))))
	{
		if (s1)			//
			free(s1);	//
		return (0);
	}
	if (s1)
	{
		while (*s1)
			*join++ = *s1++;	
	}
	while (nl--)
		*join++ = *s2++;
	*join = '\0';
	printf("len = %d\n", len);
	join -= len;
	printf("join = %p\n", join);
	printf("join = %s\n", join);
	return (join);
}

int		get_next_line(int fd, char **line)
{
	char *myline;
	int a;
	char *buf;
	static char *residue;
	int	nl;

	if ((fd < 0) | !(line) | (BUFFER_SIZE <= 0))
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	ft_bzero((void *)buf, BUFFER_SIZE + 1);
	if ((a = read(fd, buf, BUFFER_SIZE)) < 0)
		{
			free(buf);
			return (-1);
		}
//	printf("first a in gnl = %d\n", a);
	printf("buf = %s\n", buf);
	nl = where_is_newline(buf);
	printf("nl = %d\n", nl);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	while (nl == BUFFER_SIZE)
	{
		if (!(residue = ft_strjoin(residue, buf, nl)))
		{
			free(buf);
			return (-1);
		}
		
		ft_bzero((void *)buf, (int)BUFFER_SIZE);
		if ((a = read(fd, buf, BUFFER_SIZE)) < 0)
		{
			free(residue);
			free(buf);
			return (-1);
		}
		nl = where_is_newline(buf);
		printf("nl = %d\n", nl);
		printf("buf = %s\n", buf);
		printf("residue = %s\n", residue);
	}
	if (!(myline = ft_strjoin(residue, buf, nl)))
	{
		free(buf);
		return (-1);
	}
	printf("myline = %s\n", myline);
	if (!(residue = malloc(sizeof(char) * (BUFFER_SIZE - nl))))
	{
		free(buf);
		free(myline);
		return (-1);
	}
	*line = myline;
//	printf("second a in gnl = %d\n", a);
//	printf("buf before = %p\n", buf);
/*	if (a > 0)*/
/*	{*/
/*		while (a-- > 0)*/
/*		{*/
/*			*myline++ = *buf++;*/
/*//			printf("%p\n", buf);*/
/*//			printf("a = %d\n", a);*/
/*		}*/
/*		a += 2;*/
/*	}*/
/*	*myline = '\0';*/
//	buf -= ft_strlen((const char *)*line);
//	printf("buf after = %p\n", buf);
	free(buf);
//	printf("last a in gnl = %d\n", a);
	return ((a != 0));
}

int main(void)
{
	char *line;
//	char *tt;
	int fd = open("main.txt", O_RDONLY);
	int a;
	int c;
//	tt = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	a = get_next_line(fd, &line);
//	a = (int)read(fd, tt, BUFFER_SIZE);
	printf("you have line '%s', gnl = %d\n", line, a);
	if (a < 0)
	{
		printf("error, gnl = %d\n", a);
		return (0);
	}
	while (a == 1)
//	while (a > 0)
	{
		printf("you have line '%s', gnl = %d\n", line, a);
		a = get_next_line(fd, &line);
//		a = (int)read(fd, tt, BUFFER_SIZE); 
	}
	printf("you have line '%s', gnl = %d\n", line, a);
	
/*	char *a = "ytrewq";*/
/*	char *b = malloc(7);*/
/*	int n = 6;*/
/*	*/
/*	while (n--)*/
/*	{*/
/*		*b++ = *a++;*/
/*	}*/
/*	*b = '\0';*/
/*	printf("b = %s", b);*/
	return (0);
}
