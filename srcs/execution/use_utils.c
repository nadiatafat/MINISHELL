#include "minishell.h"


void	ft_puterror(char *cmd, char *cmd2, char *error)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (cmd2)
	{
		write(2, cmd2, ft_strlen(cmd2));
		write(2, ": ", 2);
	}
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

char **ft_add_to_array(char **arr, char *str)
{
    char **new_arr;
    int i;
    int size;

    size = 0;
    if (arr)
        while (arr[size])
            size++;
    new_arr = malloc(sizeof(char *) * (size + 2));
    if (!new_arr)
        return (NULL);
    i = 0;
    while (i < size)
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[i] = str;
    new_arr[i + 1] = NULL;
    if (arr)
        free(arr);
    return (new_arr);
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size, int free_flag)
{
    void *new_ptr;

    (void)old_size;
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, old_size);
        if (free_flag)
            free(ptr);
    }
    return (new_ptr);
}

void ft_free_tab(char **tab)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}




/*
void ft_reset_signals_for_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
*/
