/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullname_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:13:46 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/18 17:16:04 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
/**
 * @brief Get an array with the possible paths.
 * @param envp The environment variables of the process.
 * @return An array with the possible paths
*/
static char	**ft_get_paths(char **envp)
{
	int		i;
	char	**paths;
	char	*temp;

	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 4) != 0)
		envp++;
	paths = ft_split((*envp) + ft_strlen("PATH="), ':');
	i = -1;
	while (paths[++i])
	{
		temp = paths[i];
		if (paths && paths[i] && paths[i][ft_strlen(paths[i]) - 1] != '/')
			paths[i] = ft_strjoin(temp, "/");
		free(temp);
		if (paths && paths[i] == NULL)
			ft_deep_free((void **) &paths, 2);
	}
	return (paths);
}

/**
 * @brief Get the name of the commands.
 * @param argc Amount of parameters pass to the program.
 * @param argv The array of parameters pass to the program.
 * @param NUM_COMMANDS Number of commands to be executed.
 * @return An array of strings with the name of the commands.
 * @note Take into consideration that the argv contains the program name,
 * in file and out file.
*/
static char	**ft_get_names(char **argv, int NUM_COMMANDS)
{
	int		i;
	int		j;
	char	**cmd_names;

	i = 0;
	j = 0;
	cmd_names = (char **) malloc(sizeof(char *) * (NUM_COMMANDS + 1));
	if (!cmd_names || !argv[i] || !argv[i + 1] || !argv[i + 2])
	{
		free(cmd_names);
		return (NULL);
	}
	while (i < NUM_COMMANDS)
	{
		j = 0;
		while (ft_isspace(argv[i + 2][j]))
			j++;
		cmd_names[i] = ft_substr(argv[i + 2], j,
				ft_strchr_i(&argv[i + 2][j], ' '));
		if (cmd_names[i] == NULL)
			return (ft_deep_free((void **) &cmd_names, 2));
		i++;
	}
	cmd_names[i] = NULL;
	return (cmd_names);
}

static char	*get_fullname(char *cmd_name, char **paths)
{
	int		i;
	char	*fullname;

	i = 0;
	fullname = NULL;
	while (paths[i] != NULL && fullname == NULL)
	{
		fullname = ft_strjoin(paths[i], cmd_name);
		if (fullname == NULL)
			return (cmd_name);
		if (access(fullname, F_OK) == -1)
		{
			free(fullname);
			fullname = NULL;
		}
		i++;
	}
	if (fullname == NULL)
		fullname = ft_strdup(cmd_name);
	return (fullname);
}

static char	**ft_cmd_fullname(char **cmd_names, char **paths, int NUM_COMMANDS)
{
	int		i;
	char	**cmd_fullname;

	cmd_fullname = (char **) malloc(sizeof(char *) * (NUM_COMMANDS + 1));
	if (cmd_names == NULL || paths == NULL || cmd_fullname == NULL)
	{
		ft_deep_free((void **) &cmd_names, 2);
		ft_deep_free((void **) &paths, 2);
		free(cmd_fullname);
		return (NULL);
	}
	i = -1;
	while (cmd_names[++i] != NULL)
	{
		cmd_fullname[i] = get_fullname(cmd_names[i], paths);
	}
	cmd_fullname[i] = NULL;
	ft_deep_free((void **) &cmd_names, 2);
	ft_deep_free((void **) &paths, 2);
	return (cmd_fullname);
}

char	**ft_fullname(char **argv, char **envp, int NUM_COMMANDS)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		argv++;
	return (ft_cmd_fullname(ft_get_names(argv, NUM_COMMANDS),
			ft_get_paths(envp), NUM_COMMANDS));
}
