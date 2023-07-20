#ifndef AST_H
# define AST_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <dirent.h>

# define CMD 0
# define PLINE 1
# define WORD 2
# define REDI 3

# define BUFFER_SIZE 225

typedef struct s_word
{
	char	*text;
}			t_word;

typedef struct s_redi
{
	char	*op;
	char	*file;
}	t_redi;

typedef struct s_suff
{
	int				type;
	t_word			*word;
	t_redi			*redi;
	struct s_suff	*prev;
	struct s_suff	*next;
}	t_suff;

typedef struct s_cmd
{
	int				w_size;
	int				r_size;
	t_word			*name;
	t_suff			*suffix;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pline
{
	int		size;
	t_cmd	*now;
}	t_pline;

char		**ft_split(const char *str, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlen(const char *s);
int			ft_listlen(char **list);
char		*ft_strdup_size(char *s1, int limit_size, int start);
char		*ft_strdup(const char *s1);
int			ft_strcmp(const char *s1, const char *s2);

char **delete_char_list(char **list, char *value);
char **append_char_list(char **list, char *value);

char 		**find_path(char **envp);
char 		*find_file(char **path_list, char *command);
char 		**get_command_list(t_cmd *cmd);
void		free_char_list(char **list);
void		print_char_list(char **list);
pid_t 		cmd_exe(void *list, char **envp);
void 		exe(void *list, int type, char **envp);

void		echo(char **cmd_list, int outfile);

t_word	*new_word(char	*text);
t_redi	*new_redi(char *op, char *file);
t_suff	*new_suff(int type, char *text, char *op, char *file);
t_cmd	*new_cmd(void);

void	perror_n_exit(char *s, int status);
int		is_pipe_included(char **in);

void	*parsing_input(int type, char **in, char **env);
t_cmd	*make_cmd(char **in, char **env, int num);
t_pline	*make_pline(char **in, char **env);

void	make_suffix(t_cmd *cmd, int idx, char **in);
int		is_redirection(char *s);
t_suff	*suffix_in_quote(t_cmd *cmd, char **in);
void	remove_quote(char *s);

void	change_escape(char *s, int i, int j);
int		change_escape_util(char src, char *idx);
int		is_possible_to_env(char c);
void	replace_env(char **in, int ii, int len);
void	count_cut_point(char flag, char **in, int *ii, int *len);

int		is_sep(char n);
int		count_word(char *s);
int		get_word_len(char *s, int *idx);
char	*init_word(char *s, int *idx);
char	**split_input(char *s);

int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void 	bi_echo(char **cmd_list, int outfile);
void 	bi_cd(char **cmd_list, int outfile);
void 	bi_pwd(char **cmd_list, int outfile);
void 	bi_env(char **cmd_list, int outfile);
void 	bi_exit(char **cmd_list, int outfile);
char 	**bi_export(char **envp, char **cmd_list, int outfile);
char 	**bi_unset(char **envp, char **cmd_list, int outfile);

#endif
/*

경우 1 : pipeline 없음
ex) echo $USER > zzz; cat zzz
name : echo
suff : 	$USER
		> zzz;
		cat
		zzz

실행부((void *)cmd, CMD);

t_cmd	*cmd			cmd->name->text : "echo"
{						cmd->name->exp : NULL
	t_word *name;		
	t_suff *suffix;		
}

t_suff	*suffix					cmd->suffix->type : WORD
{								cmd->suffix->prev : NULL
	int				type;		cmd->suffix->now->text : "$USER"
	struct s_suff	*prev;		cmd->suffix->now->exp : {arg:"USER", start:1, end:5}
	void			*now;		
	struct s_suff	*next;		cmd->suffix->next->type : REDI
}								cmd->suffix->next->prev : cmd->suffix
								cmd->suffix->next->now->op : ">"
								cmd->suffix->next->now->file : "zzz;"
								
								cmd->suffix->next->next->type : WORD
								cmd->suffix->next->next->prev : cmd->suffix->next
								cmd->suffix->next->next->now->text : "cat"
								cmd->suffix->next->next->now->exp : NULL
								
								cmd->suffix->next->next->next->type : WORD
								cmd->suffix->next->next->next->prev : cmd->suffix->next->next
								cmd->suffix->next->next->next->now->text : "zzz"
								cmd->suffix->next->next->next->now->exp : NULL
								cmd->suffix->next->next->next->next : NULL

----------
경우 2 : pipeline 있음
ex) echo $USER | rev | cat > zzz
name : echo
suff : 	$USER

name : rev
suff :

name : cat
suff : 	{>, zzz}

실행부((void *)pline, PLINE);

t_pline	*pline			pline->prev : NULL
{						pline->now->name->text : "echo"
	t_cmd	*prev;		pline->now->name->exp : NULL
	t_cmd	*now;		pline->now->suffix->type : WORD
	t_cmd	*next;		pline->now->suffix->prev : NULL
}						pline->now->suffix->now->text : "$USER"
						pline->now->suffix->now->exp : {arg:"USER", start:1, end:5}

						pline->next->name->text : "rev"
						pline->next->name->exp : NULL
						pline->next->suffix : NULL

						pline->next->next->name->text : "cat"
						pline->next->next->name->exp : NULL
						pline->next->next->suffix->type : REDI
						pline->next->next->suffix->prev : NULL
						pline->next->next->suffix->now->op : ">"
						pline->next->next->suffix->now->file : "zzz;"

*/