#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

void	addback_node(t_list **lst, t_list *news);
t_list	*new_node(char *content);
int search_newline(t_list *list);
int string_length(t_list *list);
char *string_malloc(t_list *list, char *str, int len);
void	clear_node(t_list **lst);
char   *save_string(t_list *list);
char *create_string(t_list **list, int fd);
char *get_next_line(int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);

#endif