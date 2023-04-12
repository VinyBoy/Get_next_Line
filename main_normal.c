int    main(void)
{
    int    fd;
    char    *t;
    int    i;

 	i = 1;
    fd = open("test", O_RDONLY);
    t = malloc(sizeof(char) * 1);
    t[0] = '\0';
    while (t != NULL)
    {
      	free(t);
        printf("APPEL %d : \t\n", i);
        t = get_next_line(fd);
        printf("%s\t", t);
        i++;
    }
	free(t);
}