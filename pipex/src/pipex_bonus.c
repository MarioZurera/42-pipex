/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:25:00 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/18 17:52:23 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex			*pipex;
	int				num_commands;
	int				status;

	if (argc < 5)
	{
		ft_printf(
			"Usage: %s <infile> <command1> <command2> ... %s",
			argv[0], "<commandN> <outfile>\n");
		return (0);
	}
	num_commands = (argc - 3);
	pipex = ft_init_pipex(argv, envp, &num_commands);
	if (pipex == NULL)
		exit(1);
	status = run_commands(pipex);
	free_pipex(&pipex);
	unlink("/tmp/here_doc");
	return (status);
}
