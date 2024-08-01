/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:39:27 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/18 17:54:19 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	here_doc(t_pipex *pipex, char *limiter)
{
	int		fd;
	int		limiter_len;
	char	*line;

	limiter_len = ft_strlen(limiter);
	fd = open("/tmp/here_doc", O_RDWR | O_TRUNC | O_CREAT, 0600);
	if (fd < 0)
		print_error_code("/tmp/here_doc", NO_FILE_OR_DIR, pipex);
	while (true)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(line, limiter, limiter_len - 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(fd);
	fd = open("/tmp/here_doc", O_RDONLY);
	return (fd);
}
