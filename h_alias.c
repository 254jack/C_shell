#include "shell.h"

void p_a(Alias *alias_list)
{
    Alias *curr_a = alias_list;

    while (curr_a != NULL)
    {
        printf("alias %s='%s'\n", curr_a->name, curr_a->value);
        curr_a = curr_a->next;
    }
}

Alias *f_a(Alias *alias_list, const char *name)
{
    Alias *curr_a = alias_list;

    while (curr_a != NULL)
    {
        if (strcmp(curr_a->name, name) == 0)
            return curr_a;

        curr_a = curr_a->next;
    }

    return NULL;
}

void add_a(Alias **alias_list, const char *name, const char *value)
{
    Alias *new_a = (Alias *)malloc(sizeof(Alias));
    if (new_a == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_a->name = strdup(name);
    new_a->value = strdup(value);
    new_a->next = NULL;

    new_a->next = *alias_list;
    *alias_list = new_a;
}

void update_a(Alias *alias, const char *value)
{
    free(alias->value);
    alias->value = strdup(value);
}

void d_a(Alias *alias_list)
{
    Alias *curr_a = alias_list;
    while (curr_a != NULL)
    {
        Alias *next = curr_a->next;
        free(curr_a->name);
        free(curr_a->value);
        free(curr_a);
        curr_a = next;
    }
}
