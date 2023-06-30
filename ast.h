typedef struct s_exp
{
	char	*arg;
	int		start;
	int		end;
}			t_exp;

typedef struct s_word
{
	char	*text;
	t_exp	*exp;
}			t_word;

typedef struct s_redi
{
	char	*op;
	char	*file;
}	t_redi;

typedef struct s_suff
{
	void	*prev;
	void	*now;
	void	*next;
}	t_suff;

typedef struct s_cmd
{
	t_word	*name;
	t_suff	*suffix;
}			t_cmd;

typedef struct s_pline
{
	t_cmd	*prev;
	t_cmd	*now;
	t_cmd	*next;
}	t_pline;

typedef struct s_script
{
	void	*prev;
	void	*now;
	void	*next;
}	t_script;

/*
jsh> echo -n "$USER" > zzz
name (echo)
suffix (-n, $USER, > zzz)

script->prev : NULL
script->now : cmd
script->next : NULL

cmd->name->text : "echo"

cmd->suffix->prev : NULL
cmd->suffix->now : (word)
		word->text : "-n"
		word->exp : NULL

cmd->suffix->next : (word)
		word->text : "$USER"
		word->exp : (exp)
				exp->arg : "USER"
				exp->start : 1
				exp->end : 5

cmd->suffix->next->next : (redi)
				redi->op : ">"
				redi->file : "zzz"

----------
jsh> cat zzz | rev | ls -l -a -m -p
name (cat)
suffix (zzz)
name (rev)
suffix ()
name (ls)
suffix(-l, -a, -m, -p)

script->prev : NULL
script->now : pline
script->now : NULL

pline->prev : NULL
pline->now : cmd1
pline->next : cmd2
pline->next->next : cmd3

cmd1->name->text : "cat"
cmd1->suffix->prev : NULL
cmd1->suffix->now : (word)
		word->text : "zzz"
		word->exp : NULL
cmd1->suffix->next : NULL

cmd2->name->text : "rev"
cmd2->suffix->prev : NULL
cmd2->suffix->now : NULL
cmd2->suffix->next : NULL

cmd3->name->text : "ls"
cmd3->suffix->prev : NULL
cmd3->suffix->now : (word)
		word->text : "-l"
		word->exp : NULL
cmd3->suffix->next : (word)
		word->text : "-a"
		word->exp : NULL
cmd3->suffix->next->next : (word)
		word->text : "-m"
		word->exp : NULL
cmd3->suffix->next->next->next : (word)
		word->text : "-p"
		word->exp : NULL

*/