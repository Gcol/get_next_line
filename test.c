#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

int main()
{
	char	*line_fd0;
	int		p_fd0[2];
	int		fd0 = 0;
	int		out_fd0 = dup(fd0);

	char	*line_fd1;
	int		p_fd1[2];
	int		fd1 = 1;
	int		out_fd1 = dup(fd1);

	char	*line_fd2;
	int		p_fd2[2];
	int		fd2 = 2;
	int		out_fd2 = dup(fd2);

	char	*line_fd3;
	int		p_fd3[2];
	int		fd3 = 3;
	int		out_fd3 = dup(fd3);

	pipe(p_fd0);
	dup2(p_fd0[1], fd0);
	write(fd0, "aaa\nbbb\n", 8);
	dup2(out_fd0, fd0);
	close(p_fd0[1]);

	pipe(p_fd1);
	dup2(p_fd1[1], fd1);
	write(fd1, "111\n222\n", 8);
	dup2(out_fd1, fd1);
	close(p_fd1[1]);

	pipe(p_fd2);
	dup2(p_fd2[1], fd2);
	write(fd2, "www\nzzz\n", 8);
	dup2(out_fd2, fd2);
	close(p_fd2[1]);

	pipe(p_fd3);
	dup2(p_fd3[1], fd3);
	write(fd3, "888\n999\n", 8);
	dup2(out_fd3, fd3);
	close(p_fd3[1]);

	get_next_line(p_fd0[0], &line_fd0);
	printf("Result = %d\n",ft_strcmp(line_fd0, "aaa"));
	printf("Result = %s\n",line_fd0);

	get_next_line(p_fd1[0], &line_fd1);
	printf("result = %d\n",ft_strcmp(line_fd1, "111"));
	printf("Result = %s\n",line_fd1);

	get_next_line(p_fd2[0], &line_fd2);
	printf("result = %d\n",ft_strcmp(line_fd2, "www"));
	printf("Result = %s\n",line_fd2);

	get_next_line(p_fd3[0], &line_fd3);
	printf("result = %d\n",ft_strcmp(line_fd3, "888"));
	printf("Result = %s\n",line_fd3);

	get_next_line(p_fd0[0], &line_fd0);
	printf("result = %d\n",ft_strcmp(line_fd0, "bbb"));
	printf("Result = %s\n",line_fd0);

	get_next_line(p_fd1[0], &line_fd1);
	printf("Result = %d\n",ft_strcmp(line_fd1, "222"));
	printf("Result = %s\n",line_fd1);

	get_next_line(p_fd2[0], &line_fd2);
	printf("Result = %d\n",ft_strcmp(line_fd2, "zzz"));
	printf("Result = %s\n",line_fd2);

	get_next_line(p_fd3[0], &line_fd3);
	printf("Result = %d\n",ft_strcmp(line_fd3, "999"));
	printf("Result = %s\n",line_fd3);
	return (0);
}
