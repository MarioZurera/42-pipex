/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:46:47 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/18 16:31:22 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	set_in_out(int input_fd, int output_fd, t_pipex *pipex)
{
	int	res;

	res = (dup2(input_fd, STDIN_FILENO) >= 0
			&& dup2(output_fd, STDOUT_FILENO) >= 0);
	close(input_fd);
	close(output_fd);
	if (!res)
		print_error_code("dup2", MANY_FD_OPEN, pipex);
	return (res);
}

static void	exec_command(t_pipex *pipex, t_token *token, int pid, int *fd)
{
	if (pid < 0)
	{
		print_error_code(NULL, NO_CHILD_PROCESS, pipex);
		close(fd[0]);
		close(fd[1]);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (access(token->fullname, F_OK) < 0)
		{
			close(fd[1]);
			print_error_code(token->fullname, COMMAND_NOT_FOUND, pipex);
		}
		if (access(token->fullname, X_OK) < 0)
		{
			close(fd[1]);
			print_error_code(token->fullname, PERMISSION_DENIED, pipex);
		}
		close(pipex->out_fd);
		execve(token->fullname, token->args, pipex->envp);
	}
	if (pid > 0)
		pipex->pids[token->number] = pid;
}

static int	wait_commands(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	close(STDIN_FILENO);
	while (pipex->pids[i])
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WIFEXITED(status))
			WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			WTERMSIG(status);
			status += 128;
		}
		i++;
	}
	return (status);
}

static void	create_pipe(t_pipex *pipex, int fd[2])
{
	if (pipe(fd) < 0)
		print_error_code("pipe", MANY_FD_OPEN, pipex);
}

int	run_commands(t_pipex *pipex)
{
	int	i;
	int	fd[2];
	int	last_input;

	i = 0;
	last_input = pipex->in_fd;
	while (pipex->tokens[i])
	{
		create_pipe(pipex, fd);
		if (pipex->tokens[i + 1] == NULL)
		{
			close(fd[1]);
			fd[1] = pipex->out_fd;
		}
		set_in_out(last_input, fd[1], pipex);
		exec_command(pipex, pipex->tokens[i], fork(), fd);
		close(last_input);
		last_input = dup(fd[0]);
		if (last_input < 0)
			print_error_code("dup", MANY_FD_OPEN, pipex);
		close(fd[0]);
		i++;
	}
	close(last_input);
	return (wait_commands(pipex));
}
