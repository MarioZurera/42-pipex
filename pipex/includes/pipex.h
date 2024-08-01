/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:25:22 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/18 16:56:15 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/wait.h>

enum e_error_code
{
	NO_CHILD_PROCESS = 10,
	MANY_FD_OPEN = 24,
	PERMISSION_DENIED = 126,
	COMMAND_NOT_FOUND = 127,
	NO_FILE_OR_DIR = 128
};

typedef struct s_token
{
	char	*fullname;
	char	**args;
	int		number;
}	t_token;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	**envp;
	int		*pids;
	char	*limiter;
	t_token	**tokens;
}	t_pipex;

/**
 * @brief Print n strings.
 * @param n_params Number of strings to be printed.
*/
void	print_error(unsigned int n_params, ...);

/**
 * @brief Print an error message and exit the program with the error code.
 * @param name Name of the error.
 * @param code Error code.
 * @param pipex The pipex structure.
*/
void	print_error_code(char *name, int code, t_pipex *pipex);

/**
 * @brief Get the fullname of the commands.
 * @param argv Name of the arguments, received by the program.
 * @param envp Environment variables in this terminal session.
 * @param NUM_COMMANDS Number of commands to be executed.
 * @return The absolute paths to the binaries of the commands.
*/
char	**ft_fullname(char **argv, char **envp, int NUM_COMMANDS);

/**
 * @brief Get the arguments of the commands.
 * @param argv Name of the arguments received by the program.
 * @param NUM_COMMANDS Number of commands to be executed.
 * @return An array with the arguments of the commands as a matrix per command.
*/
char	***ft_args(char **argv, int NUM_COMMANDS);

/**
 * @brief Initialize the pipex structure.
 * @param argv Name of the arguments received by the program.
 * @param envp Environment variables in this terminal session.
 * @param NUM_COMMANDS Number of commands to be executed.
 * @return A pointer to the pipex structure.
*/
t_pipex	*ft_init_pipex(char **argv, char **envp, int *NUM_COMMANDS);

/**
 * @brief Free the pipex structure.
 * @param pipex The pipex structure to be freed.
*/
void	free_pipex(t_pipex **pipex);

/**
 * @brief Run the commands.
 * @param pipex The pipex structure with the commands to be executed.
 * @return The status of the execution.
*/
int		run_commands(t_pipex *pipex);

/**
 * @brief Execute the here document operation.
 * @param pipex The pipex structure with the commands to be executed.
 * @param limiter The limiter to stop the here document.
 * @return The file descriptor to the here document.
*/
int		here_doc(t_pipex *pipex, char *limiter);

int		main(int argc, char **argv, char **envp);

#endif /* PIPEX_H */
