/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbaek <chbaek@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:48:29 by chbaek            #+#    #+#             */
/*   Updated: 2023/07/15 18:11:32 by chbaek           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

void	print_char_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		printf("%s\n",list[i]);
		i++;
	}
	free(list);
}

void	print_cmd(void *p)
{
	t_suff	*cur;

	printf("cmd w_size : %d\n", ((t_cmd *)p)->w_size);
	printf("cmd r_size : %d\n", ((t_cmd *)p)->r_size);
	printf("cmd name : %s\n", ((t_cmd *)p)->name->text);
	printf("cmd suffix : %p\n", ((t_cmd *)p)->suffix);
	cur = ((t_cmd *)p)->suffix;
	while (cur)
	{
		printf("cmd suffix type : %d\n", cur->type);
		if (cur->type == WORD)
			printf("cmd suffix word : %s\n", cur->word->text);
		else
		{
			printf("cmd suffix redi op : %s\n", cur->redi->op);
			printf("cmd suffix redi file : %s\n", cur->redi->file);
		}
		printf("cmd suffix prev : %p\n", cur->prev);
		printf("cmd suffix next : %p\n", cur->next);
		cur =cur->next;
	}
}
