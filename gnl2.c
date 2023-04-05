#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

//Foncion qui sert a renvoyer 1 ou 0
//Renvoie dans le cas ou ma stash n'est pas remplit de -1
//Renvoie 0 si ma stash est remplit de -1
int ft_check_only_one_or_not(char *stash)
{
    int i;

    i = 0;
    while (stash[i])
    {
        if (stash[i] != -1)
            return (1);
        i++;
    }
    return (0);
}

//Check new line est une fonction qui sert a checker si il y a un '\n' ou pas renvoyer soit 1 soit 0
//Renvoie 1 si dans ma stash il y a un '\n
//Renvoie 0 si dans ma stash il n'y a pas de '\n'

int ft_check_new_line(char *stash)
{
    int i;

    i = 0;
    while (stash[i])
    {
        if (stash[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

// ft_strlen nous renvoie la taille entiere d'une chaine sans le '\0'
int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

// ft_strlen qui renvoie la taille de la chaine a partir du premier caractere apres le -1 jusquau char c donner en parametre
int ft_strlen_after_one(char *str, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] == -1)
        i++;
    while (str[i] != c)
    {
        i++;
        j++;
    }
    return (j);
}

// init_and_put_one est une fct qui remplit une chaine de caractere de -1 jusquau caractere definit en parametre 
void    init_and_put_one(char *stash, char c)
{
    int i;

    i = 0;
    while(stash[i] != c)
    {
        stash[i] = -1;
        i++;
    }
    if (stash[i] == '\n')
        stash[i] = -1;
}

// ft_join nous renvoie une nouvelle chaine qui est l'addition des deux chaines en parametres
char    *ft_join(char *buff, char *stash)
{
    int i;
    int j;
    char *new_buff;

    i = 0;
    j = 0;
    // On alloue a new_buff la taille de buff + la taille de la stash jusquau '\0'
    new_buff = (char *)malloc(sizeof(char) * ft_strlen(buff) + ft_strlen_after_one(stash, '\0') + 1);
    while (buff[i])
    {
        new_buff[i] = buff[i];
        i++;
    }
    while (stash[j] == -1)
        j++;
    while (stash[j] && stash[j] != -1)
    {
        new_buff[i] = stash[j];
        i++;
        j++;
    }
    new_buff[i] = '\0';
    //une fois les deux chaine copiees on remplit notre stash de -1 avec init_and_put_one
    init_and_put_one(stash, '\0');
    // on free notre buff
    free (buff);
    return (new_buff);
}

// ft_join_new_line va nous permettre de join deux chaine de caractere si un '\n' est detecter dans notre stash
char    *ft_join_new_line(char *buff, char *stash)
{
    int i;
    int j;
    char *new_buff;

    i = 0;
    j = 0;
    // on alloue a new buff la taille de buff et la taille de stash a partir du premier caractere apres -1 jusquau caractere definit dans le parametre
    // + 2 pour le '\n' et le '\0'
    new_buff = (char *)malloc(sizeof(char) * ft_strlen(buff) + ft_strlen_after_one(stash, '\n') + 2);
    while (buff[i])
    {
        new_buff[i] = buff[i];
        i++;
    }
    while (stash[j] == -1)
        j++;
    while (stash[j] != '\n')
    {
        new_buff[i] = stash[j];
        i++;
        j++;
    }
    new_buff[i] = '\n';
    i++;
    new_buff[j] = '\0';
    init_and_put_one(stash, '\n');
    free (buff);
    return (new_buff);
}

//Creation de la fonction get_next_line qui va lire un fd en renvoyer une ligne lu 
char    *get_next_line(int fd)
{
    char    *buff;
    static char stash[BUFFER_SIZE];

    //1) proteger
    if (fd < 0 || BUFFER_SIZE <=0)
        return (NULL);
    //2)allocation du buffer de taille 1 avec son zero terminal
    buff = (char *)malloc(sizeof(char) * 1);
    buff[0] = '\0'; 
    //3) boucle infinit avec condition de sortie
    while (1)
    {
        //1) Sortie si ma stash est remplit de -1 et que la fonction read a lu tout mon file descriptor
        if (ft_check_only_one_or_not(stash) == 0) //verifier que ma temp est remplit ou non de -1
            if (read(fd, stash, BUFFER_SIZE) == 0)
                break ;
        //2) Utilisation de ft_check_new_line en deux cas:
            // Pas de '\n' dans ma stash dans ce cas on join buff et stash
        if (ft_check_new_line(stash) == 0)
            buff = ft_join(buff, stash);
            // Un '\n est present dans la stash dans ce cas la; on join_new_line et Sortie de la boucle infinit
        if (ft_check_new_line(stash) == 1)
        {
            buff = ft_join_new_line(buff, stash);
            break ;
        }
    }
    // Suite de la premiere condition de sortie de la boucle infinie 
    // Si ma stash est remplit de -1 et que la fct read renvoie 0 alors le file decriptor a ete lu entierement
    // buff n'a donc pas ete modifier et nous allons pouvoir renvoyer NUll
    if (buff[0] == '\0')
    {
        free (buff);
        return (NULL);
    }
    // renvoie notre notre buff qui a ete modifier (Il se termine par un '\n' + '\0')
    return (buff); 
}

#include <stdio.h>
int    main(void)
{
    int    fd;
    char    *t;
    int    i;

 i = 0;
    fd = open("caca.txt", O_RDONLY);
    t = malloc(sizeof(char) * 1);
    t[0] = '\0';
    while (t != NULL)
    {
      	free(t);
        printf("APPEL %d :\n", i);
        t = get_next_line(fd);
        printf("%s", t);
        i++;
    }
	free(t);
}