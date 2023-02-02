#include <stdio.h>  // for printf()
#include <unistd.h> // for read() and close()
#include <fcntl.h>  // for open()
#include <stdlib.h> // for malloc() and free()

void	ft_bzero(char *s, int n)
{
	char	*ptr;

	if (s)
	{
		ptr = s + n;
		while (s != ptr)
			*s++ = '\0';
	}
}

int		ft_strlen(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s++)
		;
	return ((int)(s - tmp - 1));
}

int		where_is_newline(char *buf)
{
	char	*iter;

	if (!buf)
		return (0);
	iter = buf;
	while (*iter)
	{
		if (*iter == '\n')
			return (iter - buf);
		iter++;
	}
	return (iter - buf);
}

char	*ft_strjoin(char *s1, char *s2, int start, int end)
{
	char	*join;
	int		len_all;
	int		len_2;

	len_2 = (end - start) * (end >= start) + 0 * (end < start);
	len_all = ft_strlen(s1) + len_2;
	if (!(join = (char *)malloc(sizeof(char) * (len_all + 1))))
	{
		return (0);
	}
	ft_bzero(join, (len_all + 1));
	if (s1)
	{
		while (*s1)
			*join++ = *s1++;
	}
	while (start < end)
		*join++ = s2[start++];
	return (join - len_all);
}

int		free_if_error(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
	return (-1);
}

int		if_nl_in_rsd(char **line, char **rsd, int nl)
{
	char	*tmp;

	if (!(*line = ft_strjoin(0, *rsd, 0, nl)))
		return (free_if_error(*rsd, 0, 0));
	if (!(tmp = ft_strjoin(0, *rsd, nl + 1, ft_strlen(*rsd))))
		return (free_if_error(*line, *rsd, 0));
	free(*rsd);
	*rsd = tmp;
	return (1);
}

int		ft_tmp(char **rsd, char **buf, int nl)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(*rsd, *buf, 0, nl)))
		return (free_if_error(*buf, *rsd, 0));
	free(*rsd);
	*rsd = tmp;
	ft_bzero(*buf, (int)BUFFER_SIZE);
	return (1);
}

int		ft_tmp_rsd(char **rsd, char **buf, char **line, int nl)
{
	char	*tmp;

	ft_bzero(*rsd, ft_strlen(*rsd));
	if (!(tmp = ft_strjoin(*rsd, *buf, nl + 1, ft_strlen(*buf))))
		return (free_if_error(*line, *rsd, *buf));
	free(*rsd);
	*rsd = tmp;
	free(*buf);
	return (1);
}

int		last_gnl(char **rsd, int a, int nl)
{
	int		is_the_EOF;

	is_the_EOF = ((a < BUFFER_SIZE) && (nl == a));
	if (is_the_EOF)
	{
		free(*rsd);
		return (0);
	}
	return (1);
}


int		get_next_line(int fd, char **line)
{
	int			a;
	char		*buf;
	static char	*rsd = NULL;
	int			nl;

	if ((fd < 0) || !(line) || (BUFFER_SIZE <= 0))
		return (-1);
	if (rsd && ((nl = where_is_newline(rsd)) < ft_strlen(rsd)))
		return (if_nl_in_rsd(line, &rsd, nl));
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (free_if_error(rsd, 0, 0));
	ft_bzero(buf, (int)(BUFFER_SIZE + 1));
	if ((a = read(fd, buf, BUFFER_SIZE)) < 0)
		return (free_if_error(rsd, buf, 0));
	while ((nl = where_is_newline(buf)) == BUFFER_SIZE)
	{
		if (ft_tmp(&rsd, &buf, nl) < 1)
			return (free_if_error(buf, rsd, 0));
		if ((a = read(fd, buf, BUFFER_SIZE)) < 0)
			return (free_if_error(buf, rsd, 0));
	}
	if (!(*line = ft_strjoin(rsd, buf, 0, nl)))
		return (free_if_error(buf, rsd, 0));
	return((ft_tmp_rsd(&rsd, &buf, line, nl) < 1) ? -1 : last_gnl(&rsd, a, nl));
}

int main(void)
{
	char *line;
	int fd = open("alphabet", O_RDONLY);
	int a;
	a = get_next_line(fd, &line);
	printf("you have line '%s', gnl = %d\n", line, a);
	if (a < 0)
	{
		printf("error, gnl = %d\n", a);
		return (0);
	}
	while (a == 1)
	{
		printf("you have line '%s', gnl = %d\n", line, a);
		free(line);
		a = get_next_line(fd, &line);
	}
	printf("you have line '%s', gnl = %d\n", line, a);
	free(line);
	return (0);
}


/*int	main(void)*/
/*{*/
/*	int 	fd_test_me;*/
/*	char	*line;*/
/*	line = NULL;*/
/*	fd_test_me = open("4.txt", O_RDONLY);*/
/*	if((fd_test_me = open(argv[1], O_RDONLY)) == -1)*/
/*	{*/
/*		my_ft_putstr_fd("failed to open", 2);*/
/*		my_ft_putstr_fd(argv[1], 2);*/
/*		my_ft_putstr_fd("filedescriptor.\n", 2);*/
/*		return (0);*/
/*	}*/
/*	if (BUFFER_SIZE == 0)*/
/*		printf("gnl = %d\n", get_next_line(fd_test_me, &line));*/
/*	else*/
/*	{*/
/*		printf("gnl = %d\n", get_next_line(-1, &line));*/
/*		free(line);*/
/*		line = NULL;*/
/*		*/
/*		printf("gnl = %d\n", get_next_line(-42, &line));*/
/*		free(line);*/
/*		line = NULL;*/
/*		*/
/*		printf("gnl = %d\n", get_next_line(42, &line));*/
/*		free(line);*/
/*		line = NULL;*/
/*		*/
/*		printf("gnl = %d\n", get_next_line(42, NULL));*/
/*		free(line);*/
/*		line = NULL;*/
/*		*/
/*		printf("gnl = %d\n", get_next_line(fd_test_me, NULL));*/
/*	}*/
/*	free(line);*/
/*	line = NULL;*/
/*	close(fd_test_me);*/
/*	return (0);*/
/*}*/
