/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Linsio <Linsio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:42 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/03 14:46:06 by Linsio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*find_env_path(char **envp)
{
	int		i;
	char	*env_path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			return (env_path);
		}
		i++;
	}
	return (NULL);
}

char	*free_and_return(char **token_env_path, char *buffer)
{
	free_2d_array(token_env_path);
	return (buffer);
}

char	**tokenize(char **envp)
{
	char	*env_path;
	char	**token_env_path;

	env_path = find_env_path(envp);
	token_env_path = ft_split(env_path, ':');
	return (token_env_path);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**token_env_path;
	char	*buffer;
	char	*temp;
	int		j;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	token_env_path = tokenize(envp);
	j = 0;
	while (token_env_path[j])
	{
		buffer = ft_strjoin(token_env_path[j], "/");
		temp = buffer;
		buffer = ft_strjoin(temp, cmd);
		free(temp);
		if (access(buffer, F_OK | X_OK) == 0)
			return (free_and_return(token_env_path, buffer));
		else
			free(buffer);
		j++;
	}
	perror(cmd);
	exit(127);
	return (NULL);
}

t_bool	exec(char **cmd_args, char **envp)
{
	char	*cmd_with_path;

	if (!cmd_args[0])
		return (FALSE);
	cmd_with_path = find_command_path(cmd_args[0], envp);
	if (execve(cmd_with_path, cmd_args, envp) == -1)
	{
		perror("execve");
		exit(126);
	}
	return (TRUE);
}
