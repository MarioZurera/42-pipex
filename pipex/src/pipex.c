/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:25:00 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/18 16:39:04 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex			*pipex;
	int				num_commands;
	int				status;

	if (argc != 5)
	{
		ft_printf("Usage: %s <infile> <command1> <command2> <outfile>\n",
			argv[0]);
		return (0);
	}
	num_commands = (argc - 3);
	pipex = ft_init_pipex(argv, envp, &num_commands);
	if (pipex == NULL)
		exit(1);
	status = run_commands(pipex);
	free_pipex(&pipex);
	return (status);
}
