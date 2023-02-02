#include <stdio.h>  // for printf()
#include <unistd.h> // for read()
#include <fcntl.h>  // for open()
#include <stdlib.h> // for malloc()

typedef struct	s_d
{
	char		*buff;
	struct s_d	*next;
}				t_d;

typedef struct	s_fd
{
	int			fd;
	ssize_t		size;
	ssize_t		remainder_size;
	char		*remainder;
	struct s_d	*lstbuff;
	struct s_fd	*next;
}				t_fd;

t_fd			*ft_get_fd(t_fd **lst, int fd);
t_fd			*ft_clearfd(t_fd *fd, t_fd *prev, t_fd *next, t_fd *tmp);
t_fd			*ft_lstnewfd(int fd);
t_d				*ft_get_buff(t_d **lst, char *buff);
char			*ft_strdup(char const *s1);
int				get_next_line(int fd, char **line);


t_d		*ft_get_buff(t_d **lst, char *buff)
{
	t_d	*tmp;

	if (lst)
	{
		if (!(*lst) && (tmp = (t_d*)malloc(sizeof(t_d))))
		{
			tmp->next = 0;
			tmp->buff = ft_strdup(buff);
			return ((*lst = tmp));
		}
		else if (!((*lst)->next) && (tmp = (t_d*)malloc(sizeof(t_d))))
		{
			tmp->next = 0;
			tmp->buff = ft_strdup(buff);
			return (((*lst)->next = tmp));
		}
		else if ((*lst)->next)
			return (ft_get_buff(&((*lst)->next), buff));
		else
			return (0);
	}
	return (0);
}

t_fd	*ft_clearfd(t_fd *fd, t_fd *prev, t_fd *next, t_fd *tmp)
{
	while (fd)
	{
		if ((!(fd->remainder) || !(fd->remainder)[0]))
		{
			if (tmp == fd)
			{
				if (next)
					tmp = next;
				else
					tmp = 0;
			}
			if (fd->remainder)
				free(fd->remainder);
			free(fd);
			fd = (t_fd*)0;
			if (prev)
				prev->next = next;
		}
		else
			prev = fd;
		fd = next;
		if (next)
			next = next->next;
	}
	return (tmp);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	if (!(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s1[i])
	{
		ptr[i] = ((char*)s1)[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_fd	*ft_lstnewfd(int fd)
{
	t_fd *tmp;

	if ((tmp = (t_fd*)malloc(sizeof(t_fd))))
	{
		tmp->next = 0;
		tmp->size = 0;
		tmp->remainder_size = 0;
		tmp->remainder = 0;
		tmp->fd = fd;
		tmp->lstbuff = 0;
	}
	return (tmp);
}

t_fd	*ft_get_fd(t_fd **lst, int fd)
{
	if (lst)
	{
		if (!(*lst))
		{
			*lst = ft_lstnewfd(fd);
			return (*lst);
		}
		else if ((*lst)->fd == fd)
			return (*lst);
		else if ((*lst)->next)
			return (ft_get_fd(&((*lst)->next), fd));
		else
		{
			(*lst)->next = ft_lstnewfd(fd);
			return ((*lst)->next);
		}
		return (0);
	}
	return (0);
}



static int		ft_write(t_fd *fd, char **line, ssize_t i, ssize_t j)
{
	t_d		*prev_lstbuff;

	if (!(fd->lstbuff))
		return (0);
	free(*line);
	if (!(*line = (char*)malloc(sizeof(char) * fd->size + 1)))
		return (-1);
	while (i < fd->size && fd->lstbuff && (j = -1) == -1)
	{
		while ((++j) < BUFFER_SIZE && (fd->lstbuff->buff)[j])
		{
			(*line)[i] = (fd->lstbuff->buff)[j];
			i++;
		}
		prev_lstbuff = fd->lstbuff;
		if (fd->lstbuff->next)
			fd->lstbuff = fd->lstbuff->next;
		else
			break ;
		free(prev_lstbuff->buff);
		free(prev_lstbuff);
	}
	free(fd->lstbuff->buff);
	free(fd->lstbuff);
	return ((int)((*line)[i] = '\0'));
}

static int		ft_func(t_fd *fd, char *ptr, size_t bs)
{
	size_t	i;
	char	*prev_buff;
	t_d		*tmp;

	i = 0;
	if (ptr && (tmp = ft_get_buff(&(fd->lstbuff), ptr)))
	{
		while (i < bs && ptr[i])
		{
			if (ptr[i] == '\n')
			{
				ptr[i] = '\0';
				free(tmp->buff);
				tmp->buff = ft_strdup(ptr);
				fd->remainder_size = bs - i;
				prev_buff = fd->remainder;
				fd->remainder = ft_strdup(&ptr[i] + 1);
				free(prev_buff);
				return (1);
			}
			i++;
		}
		return (0);
	}
	return (-1);
}

static int		ft_remainder(t_fd *fd)
{
	int		req;

	req = 0;
	if (fd->remainder)
	{
		fd->remainder_size = 0;
		while (fd->remainder[fd->remainder_size])
			fd->remainder_size++;
		fd->size += fd->remainder_size;
		req = ft_func(fd, fd->remainder, fd->remainder_size);
		if (req == 0)
		{
			free(fd->remainder);
			fd->remainder = 0;
		}
		return (req);
	}
	return (0);
}

static int		ft_gnl(t_fd *fd, int req)
{
	char		*ptr;
	ssize_t		rb;

	if (!(ptr = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((rb = read(fd->fd, ptr, BUFFER_SIZE)) <= BUFFER_SIZE &&
			rb > 0)
	{
		fd->size += rb;
		ptr[rb] = '\0';
		if ((req = ft_func(fd, ptr, rb)) == -1)
		{
			free(ptr);
			return (-1);
		}
		else if (req == 1)
		{
			free(ptr);
			return (1);
		}
	}
	if (rb == -1)
		return (-1);
	free(ptr);
	return (req);
}

int				get_next_line(int fd, char **line)
{
	static t_fd	*s_fd;
	t_fd		*tmp;
	int			req;

	req = 0;
	if (!line)
		return (-1);
	if (!(*line = (char*)malloc(sizeof(char))))
		return (-1);
	(*line)[0] = '\0';
	if (BUFFER_SIZE < 1 || fd == -1)
		return (-1);
	if (!(tmp = ft_get_fd(&s_fd, fd)))
		return (-1);
	if ((req = ft_remainder(tmp)) == -1)
		return (-1);
	if (req == 0)
		if ((req = ft_gnl(tmp, 0)) == -1)
			return (-1);
	if (ft_write(tmp, line, 0, -1) == -1)
		return (-1);
	tmp->lstbuff = 0;
	tmp->size = 0;
	s_fd = ft_clearfd(s_fd, (t_fd*)0, s_fd->next, s_fd);
	return (req);
}

int main(void)
{
	char *line;
	int fd = open("main.txt", O_RDONLY);
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
		a = get_next_line(fd, &line);
	}
	printf("you have line '%s', gnl = %d\n", line, a);
	return (0);
}
