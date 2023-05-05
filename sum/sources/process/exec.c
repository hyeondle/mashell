/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:42 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/05 19:53:32 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/minishell.h"

// char	*find_command_path(char *cmd, char **envp)
// {
// 	char	**token_env_path;
// 	char	*buffer;
// 	char	*temp;
// 	int		j;

// 	if (access(cmd, F_OK | X_OK) == 0)
// 		return (cmd);
// 	token_env_path = tokenize(envp);
// 	j = 0;
// 	while (token_env_path[j])
// 	{
// 		buffer = ft_strjoin(token_env_path[j], "/");
// 		temp = buffer;
// 		buffer = ft_strjoin(temp, cmd);
// 		free(temp);
// 		if (access(buffer, F_OK | X_OK) == 0)
// 			return (free_and_return(token_env_path, buffer));
// 		else
// 			free(buffer);
// 		j++;
// 	}
// 	// ft_putstr_fd(" command not found\n", 2);
// 	ft_putstr_fd("error\n", 2);
// 	exit(127);
// 	return (NULL);
// }

// t_bool	exec(char **cmd_args, char **envp, t_setting **set)
// {
// 	char	*cmd_with_path;

// 	if (!cmd_args[0])
// 		return (FALSE);
// 	if (ft_strcmp("echo", cmd_args[0]) != 0 && ft_strcmp("env", cmd_args[0]) != 0 && ft_strcmp("export", cmd_args[0]) != 0)
// 	{
// 		cmd_with_path = find_command_path(cmd_args[0], envp);
// 		if (execve(cmd_with_path, cmd_args, envp) == -1)
// 		{
// 			ft_putstr_fd("exec error\n", 2);
// 			exit(126);
// 		}
// 	}
// 	else
// 	{
// 		if (ft_strcmp("export", cmd_args[0]) == 0)
// 		{
// 			ft_export(set, cmd_args);
// 			exit(0);
// 		}
// 		go_execute(cmd_args, set, cmd_args[0]);
// 	}
// 	return (TRUE);
// }

void	check_perm_dir(char **cmd_args, char **envp)
{
	struct stat	sb;

	if (cmd_args[0][0] == '.' || cmd_args[0][0] == '/')
	{
		if (stat(cmd_args[0], &sb) != -1)
		{
			if ((sb.st_mode & S_IFMT) == S_IFDIR)
				putstr_exit(" is a directory\n", 2, 126);
			else if (!(sb.st_mode & S_IXUSR))
				putstr_exit(" Permission denied\n", 2, 126);
		}
	}
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**token_env_path;
	char	*buffer;
	char	*temp;
	int		j;

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
	if (cmd[0] == '.' || cmd[0] =='/')
		putstr_exit(" No such file or directory\n", 2, 127);
	else
		putstr_exit(" command not found\n", 2, 127);
	return (NULL);
}



t_bool	exec(char **cmd_args, char **envp, t_setting **set)
{
	char		*cmd_with_path;
	// struct stat	sb;

	if (!cmd_args[0])
		return (FALSE);
	if (ft_strcmp("echo", cmd_args[0]) != 0 && ft_strcmp("env", cmd_args[0]) != 0 && ft_strcmp("export", cmd_args[0]) != 0)
	{
		// if (cmd_args[0][0] == '.' || cmd_args[0][0] == '/')
		// {
		// 	if (stat(cmd_args[0], &sb) != -1)
		// 	{
		// 		if ((sb.st_mode & S_IFMT) == S_IFDIR)
		// 			putstr_exit(" is a directory\n", 2, 126);
		// 		else if (!(sb.st_mode & S_IXUSR))
		// 			putstr_exit(" Permission denied\n", 2, 126);
		// 	}
		// }
		check_perm_dir(cmd_args, envp);
		cmd_with_path = find_command_path(cmd_args[0], envp);
		if (execve(cmd_with_path, cmd_args, envp) == -1)
			putstr_exit("exec_error\n", 2, 127);
	}
	else
	{
		if (ft_strcmp("export", cmd_args[0]) == 0)
		{
			ft_export(set, cmd_args);
			exit(0);
		}
		go_execute(cmd_args, set, cmd_args[0]);
	}
	return (TRUE);
}

