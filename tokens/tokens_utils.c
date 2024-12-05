// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tokens_utils.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jesilva- <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/27 09:49:43 by jesilva-          #+#    #+#             */
// /*   Updated: 2024/11/27 09:49:47 by jesilva-         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../includes/include_builtins.h"

// bool is_delimiter(char *arg)
// {
// 	if(ft_strcmp(arg, "|") == 0 || ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, ">") == 0 || !arg)
// 		return (true);
// 	return (false);
// }

// int len_array(char **arg)
// {
// 	int i = 0;
// 	while(!is_delimiter(arg[i]))
// 		i++;
// 	return (i);
// }

// //faz o malloc na estrutura token->value
// void  handle_value(char **arg, t_token **token, char *str)
// {
// 	while(ft_strcmp(*arg, str) == 1)
// 		arg++;
// 	if (is_delimiter(*arg))
// 		(*token)->value = NULL;
// 	printf("%s -> handle value\n", *arg);
// 	int len = len_array(arg);
// 	printf("%d LEN HANDLE\n",len);
// 	if ((*token)->value == NULL)
// 		(*token)->value = ft_calloc(sizeof(char *), len);
// }

int	get_type(char *cmd)
{
	if(ft_strcmp(cmd, ">") == 0)
		return OUTPUT_REDIR;
	else if (ft_strcmp(cmd, ">>") == 0)
		return APPEND_REDIR;
	else if(ft_strcmp(cmd, "<") == 0)
		return INPUT_REDIR;
	else if(ft_strcmp(cmd, "<<") == 0)
		return HEREDOC;
	else 
		return CMD;
}

void	ft_print_array(char **cmd)
{
	int i = 0;
	while(cmd[i])
	{
	
		printf("%s ->array\n",cmd[i]);
		i++;
	}
}
