/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:37 by weng              #+#    #+#             */
/*   Updated: 2022/01/19 13:39:47 by weng             ###   ########.fr       */
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

/* Print the data of a t_scmd struct. */
void	ft_scmd_print(t_scmd *scmd)
{
	t_list	*node;
	t_inout	*inout;

	printf("index = %d\ncount = %d\nargv: ", scmd->index, scmd->count);
	node = (scmd->argv);
	while (node != NULL)
	{
		printf("%s ", (char *) node->content);
		node = node->next;
	}
	printf("\n");
	node = scmd->infile;
	while (node != NULL)
	{
		inout = node->content;
		printf("infile: type = %d, file = %s\n", inout->type, inout->filename);
		node = node->next;
	}
	node = scmd->outfile;
	while (node != NULL)
	{
		inout = node->content;
		printf("outfile: type = %d, file = %s\n", inout->type, inout->filename);
		node = node->next;
	}
}

/* Print the data of a t_cmd struct. */
void	ft_cmd_print(t_cmd *cmd)
{
	t_list	*node;

	if (cmd == NULL)
		return ;
	printf("----------------------------------------\n");
	printf("Pipeline:\n");
	printf("cmd->valid = %d\n", cmd->valid);
	printf("cmd->count = %d\n", cmd->count);
	printf("----------------------------------------\n");
	node = cmd->scmd;
	while (node != NULL)
	{
		ft_scmd_print(node->content);
		printf("----------------------------------------\n");
		node = node->next;
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
