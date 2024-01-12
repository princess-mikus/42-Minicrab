/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:27:18 by xortega           #+#    #+#             */
/*   Updated: 2023/11/28 14:07:57 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_struct
{
	char			*buff;
	char			*temp;
	char			*rest[4096];
	int				rd;
}					t_struct;

/*
	check is a char is alphabetical, returns 1 if true
*/
int		ft_isalpha(int c);
/*
	check is a char is a digit, returns 1 if true
*/
int		ft_isdigit(int c);
/*
	check is a char is alphabetical or a digit, returns 1 if true
*/
int		ft_isalnum(int c);
/*
	check is a char is in the assci list, returns 1 if true
*/
int		ft_isascii(int c);
/*
	check is a char is printeable, returns 1 if true
*/
int		ft_isprint(int c);
/*
	gives the length of a NULL terminated string
*/
size_t	ft_strlen(const char *s);
/*
	copies the content of one NULL terminated string (src)
	into other one (dst) up to (dstsize),
	returns the new length of (dst)
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
/*
	copies the content one NULL terminated string (src) 
	into the end of other one (dst) up to (dstsize),
	returns the new length of (dst)
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/*
	search a given character (c) 
	into a NULL terminated stirng (s) from beginning to end,
	if found returns the posicion, else returns NULL
*/
char	*ft_strchr(const char *s, int c);
/*
	search a given character (c) 
	into a NULL terminated stirng (s) from end to beginning,
	if found returns the posicion, else returns NULL
*/
char	*ft_strrchr(const char *s, int c);
/*
	compare the content of two NULL terminted strings (s1) and (s2) up to (n),
	if a different character is found return its position, else returns NULL
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*
	search  for the first strict coincidence of a NULL terminted string (needle)
	into other one (haystack) up to (len),
	if found return its position, else returns NULL
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/*
	fills a NULL terminted string (str) with a character (c) up to (len),
	returns (str)
*/
void	*ft_memset(void *str, int c, size_t len);
/*
	copy the content of a NULL terminated string (src) 
	into other one (dst) up to n,
	returns (dst)
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
/*
	a more safe way of doing a memcpy, prebents some overflows, returns (dst)
*/
void	*ft_memmove(void *dst, const void *src, size_t len);
/*
	search a given character (c) into a NULL terminated stirng (s),
	if found returns the a pointer to the posicion, else returns NULL
*/
void	*ft_memchr(const void *s, int c, size_t n);
/*
	compare the content of two NULL terminted strings (s1) and (s2) up to (n),
	if a differece is found returns the difference betwen caracters,
	else returns 0
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/*
	fills a NULL terminated string (str) with '\0' up to len
*/
void	ft_bzero(void *str, size_t len);
/*
	if a character c is a lowercase letter in turns it uppercase
*/
int		ft_toupper(int c);
/*
	if a character c is a uppercase letter in turns it lowercase
*/
int		ft_tolower(int c);
/*
	turns the first instance of a number in a given NULL terminted string (str)
	into a int and returns it
*/
int		ft_atoi(const char *str);
/*
	reserve whit malloc into a string whit a (count)*(size) size
	and fills it with '\0'
*/
void	*ft_calloc(size_t count, size_t size);
/*
	create a malloc reserved NULL terminated string 
	and copy the content of (s1) into it
*/
char	*ft_strdup(const char *s1);
/*
	create a malloc reserved NULL terminated string 
	and copy the content of (s) from (start) up to (len)
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*
	create a malloc reserved NULL terminated string 
	and copies of the content of (s1) and (s2),
	(s1) after (s2), in that order
*/
char	*ft_strjoin(char const *s1, char const *s2);
/*
	create a malloc reserved NULL terminated string
	with a copy of the content of (s1),
	from the end of the first continuous coincidence in any caracter in (set) 
	to the first one
*/
char	*ft_strtrim(char const *s1, char const *set);
/*
	given a NULL terminated string and a charter (c),
	divide the string into other malloc reserved NULL terminated strings
	using the ocurrences of the caracter (c) as delimitators.
	This new strings are whitin a NULL terminated arrai** which is returned
*/
char	**ft_split(char const *s, char c);
/*
	given an int (n) create a malloc reserved NULL terminated string
	whit the int (n) written in it and returns it
	
*/
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// %%
int		ft_printf(char const *s, ...);
// %d %i
int		print_number(va_list lst);
// %u
int		print_unsigned(va_list lst);
// %x %X
int		print_hex(va_list lst, char c);
// %s
int		print_string(va_list lst);
// %c
int		print_char(va_list lst);
// %p
int		print_addres(va_list lst);
/*
 given an fd reads ultil a line feed or a NULL caracter,
 returns a malloc reserved NUll terminated string whit its content
*/
char	*get_next_line(int fd);
void	addnew(t_struct *all, int fd);
void	remember(t_struct *all, int fd);
void	cut(t_struct *all, int sh, int fd);
char	*pack(t_struct *all, int sh);
int		gnl_strlen(const char *str);
void	cpy(char *src, char **dst, int start);
void	forget(t_struct *all, int fd);
int		search(t_struct *all);
char	*shorter(t_struct *all, int sh, int fd);
#endif