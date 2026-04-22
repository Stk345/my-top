/*
** EPITECH PROJECT, 2025
** my strlen
** File description:
** show string lenght
*/

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){;
        i++;
    }
    return (i);
}
