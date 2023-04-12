int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	int		fd3;
	char	*t;
	char	*u;
	char	*v;
	int		i;

	i = 0;
	fd = open("text1.txt", O_RDONLY);
	fd1 = open("text2.txt", O_RDONLY);
	fd2 = open("text3.txt", O_RDONLY);
	t = malloc(sizeof(char) * 1);
	t[0] = '\0';
	u = malloc(sizeof(char) * 1);
	u[0] = '\0';
	v = malloc(sizeof(char) * 1);
	v[0] = '\0';
	
	while (t != NULL)
	{
		free(t);
		free (u);
		free (v);
		printf("APPEL %d :\n", i);
		t = get_next_line(fd);
		printf("%s", t);
		printf("APPEL %d :\n", i);
		u = get_next_line(fd1);
		printf("%s", u);
		printf("APPEL %d :\n", i);
		v = get_next_line(fd2);
		printf("%s", v);
		i++;
	}
	free(t);
	free (u);
	free (v);
}