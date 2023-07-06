#include "ast.h"

t_word	*new_word(char	*text)
{
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
		perror_n_exit("malloc()", EXIT_FAILURE);
	word->text = text;
	return (word);
}

t_redi	*new_redi(char *op, char *file)
{
	t_redi	*redi;

	redi = (t_redi *)malloc(sizeof(t_redi));
	if (!redi)
		perror_n_exit("malloc()", EXIT_FAILURE);
	redi->op = op;
	redi->file = file;
	return (redi);
}

t_suff	*new_suff(int type, char *text, char *op, char *file)
{
	t_suff	*suff;

	suff = (t_suff *)malloc(sizeof(t_suff));
	if (!suff)
		perror_n_exit("malloc()", EXIT_FAILURE);
	suff->type = type;
	if (type == WORD)
		suff->word = new_word(text);
	else
		suff->redi = new_redi(op, file);
	suff->prev = NULL;
	suff->next = NULL;
	return (suff);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		perror_n_exit("malloc()", EXIT_FAILURE);
	cmd->w_size = 0;
	cmd->r_size = 0;
	cmd->name = NULL;
	cmd->suffix = NULL;
	return (cmd);
}