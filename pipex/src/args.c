/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:38:19 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/17 14:23:17 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	ft_count_args(char *args)
{
	unsigned int	count;
	char			*temp;

	temp = ft_strtrim(args, " ");
	count = 0;
	while (*args)
	{
		if (*args == ' ')
			count++;
		while (*args == ' ')
			args++;
		if (*args == '\'' || *args == '"')
			args += ft_strchr_i(args + 1, *args) + 1;
		if (*args && *args != ' ')
			args++;
	}
	if (*args != ' ')
		count++;
	free(temp);
	return (count);
}

static int	push_element(char **cmd_arg, char *args, int start, int len)
{
	unsigned int	pos;

	pos = 0;
	while (cmd_arg[pos] != NULL)
		pos++;
	cmd_arg[pos] = ft_substr(args, start, len);
	if (cmd_arg[pos] == NULL)
		ft_deep_free((void **) &cmd_arg, 2);
	return (cmd_arg[pos] != NULL);
}

static int	pass_quotes(char *args, int i)
{
	int		res;

	res = 0;
	if (args[i] == '\'' || args[i] == '"')
		res = ft_strchr_i(&args[i] + 1, args[i]) + 1;
	if (res < 0)
		res = 0;
	return (res);
}

static char	**ft_parse_args(char *args)
{
	char			**cmd_arg;
	unsigned int	i;
	unsigned int	len;
	unsigned int	temp;

	cmd_arg = ft_calloc(ft_count_args(args) + 1, sizeof(char *));
	if (cmd_arg == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (args[i])
	{
		if (args[i] == ' ' && len && !push_element(cmd_arg, args, i - len, len))
			return (NULL);
		if (args[i] == ' ' && len > 0)
			len = 0;
		while (args[i] == ' ')
			i++;
		temp = pass_quotes(args, i) + 1;
		i += temp;
		len += temp;
	}
	if (len > 0 && !push_element(cmd_arg, args, i - len, len))
		return (NULL);
	return (cmd_arg);
}

char	***ft_args(char **argv, int NUM_COMMANDS)
{
	int		i;
	char	***cmd_args;

	i = 0;
	if (argv[i] == NULL || argv[i + 1] == NULL || argv[i + 2] == NULL)
		return (NULL);
	cmd_args = (char ***) malloc(sizeof(char **) * (NUM_COMMANDS + 1));
	if (cmd_args == NULL)
	{
		free(cmd_args);
		return (NULL);
	}
	while (i < NUM_COMMANDS)
	{
		cmd_args[i] = ft_parse_args(argv[i + 2]);
		if (cmd_args[i] == NULL)
			return (ft_deep_free((void **) &cmd_args, 3));
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}
