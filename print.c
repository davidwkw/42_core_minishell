/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:37 by weng              #+#    #+#             */
/*   Updated: 2022/01/11 09:30:11 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print the length and content of the individual token. */
void	ft_token_print(t_list *token)
{
	char	*content;

	while (token != NULL)
	{
		content = token->content;
		printf("len = %ld: %s\n", ft_strlen(content), content);
		token = token->next;
	}
}

/* Print the data of a t_cmd struct. */
void	ft_cmd_print(t_cmd *cmd)
{
	t_list	*scmd_lst;
	t_list	*argv;
	int		i;

	if (cmd == NULL)
		return ;
	printf("cmd->count = %d\n", cmd->count);
	printf("cmd->infile = %s\n", cmd->infile);
	printf("cmd->outfile = %s\n", cmd->outfile);
	printf("cmd->outfile_flag = %d\n", cmd->outfile_flag);
	scmd_lst = cmd->scmd_lst;
	i = 0;
	while (scmd_lst != NULL)
	{
		argv = ((t_scmd *) scmd_lst->content)->argv;
		printf("scmd %d: ", i);
		while (argv != NULL)
		{
			printf("%s ", (char *) argv->content);
			argv = argv->next;
		}
		printf("\n");
		scmd_lst = scmd_lst->next;
		i++;
	}
}

/* Prints the content of a 'ptree' node. */
static void	ft_ptree_print_aux(t_ptree *ptree)
{
	printf("\n");
	if (ptree->type == TOKEN)
		printf("%s\n", (char *) ptree->content);
	else if (ptree->type == CMD)
		ft_cmd_print(ptree->content);
	else
		printf("Error: Unexpected ptree node type.\n");
	printf("\n");
}

/* Print the content of 'ptree' using postfix traversal. */
void	ft_ptree_print(t_ptree *ptree)
{
	ft_ptree_apply_postfix(ptree, ft_ptree_print_aux);
}
