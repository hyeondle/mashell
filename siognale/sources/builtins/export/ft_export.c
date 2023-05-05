/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:47:04 by Linsio            #+#    #+#             */
/*   Updated: 2023/04/29 05:01:02 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


// static int	check_export_input(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 		{
// 			if (i == 0 || !str[i - 1] || !ft_isalnum(str[i - 1]))
// 				return (1);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_isalnum(str[i]))
// 			return (1);
// 		i++;
// 	}
// 	if (!ft_isalpha(str[0]))
// 		return (1);
// 	return (0);
// }

// int	ft_export(t_setting **set, char **inputs)
// {
// 	int		i;
// 	char	*key;
// 	char	*err_str;
// 	char	*err_str2;

// 	i = 1;
// 	while (inputs[i])
// 	{
// 		if (check_export_input(inputs[i]))
// 		{
// 			(*set)->last_exit_status = 1;
// 			err_str = ft_strjoin("export: `", inputs[i]);
// 			err_str2 = ft_strjoin(err_str, "': not a valid identifier\n");
// 			ft_putstr_fd(err_str2, STDERR_FILENO);
// 			free(err_str);
// 			free(err_str2);
// 			return (0);
// 		}
// 		add_env(&((*set)->env_list), inputs[i], set);
// 		i++;
// 	}
// 	return (0);
// }

#include "../../../includes/minishell.h"

static int	check_export_input(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0 || !str[i - 1] || !ft_isalnum(str[i - 1]))
				return (1);
			return (0);
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	if (!ft_isalpha(str[0]))
		return (1);
	return (0);
}

static void sort_env(char **s, int i)
{
	int	k;
	int	j;

	k = 0;
	while (k < i - 1)
	{
		j = 0;
		while (j < i - 1)
		{
			if (ft_strcmp(s[j], s[j + 1]) > 0)
				ft_swap(&s[j], &s[j + 1]);
			j++;
		}
		k++;
	}
	return ;
}

static void	free_temp_env(char **temp_env)
{
	int	i;

	i = 0;
	while (temp_env[i])
	{
		free(temp_env[i]);
		temp_env[i] = NULL;
		i++;
	}
	free(temp_env);
	temp_env = NULL;
}

char	*make_export_str(char *str)
{
	char	*key;
	char	*value;
	char	*equal;
	char	*rstr;

	equal = ft_strchr(str, '=');
	key = ft_strndup(str, equal - str);
	value = ft_strdup(equal + 1);
	rstr = ft_strjoin("declare -x ", key);
	free(key);
	key = ft_strjoin(rstr, "=\"");
	free(rstr);
	rstr = ft_strjoin(key, value);
	free(value);
	value = ft_strjoin(rstr, "\"");
	free(rstr);
	free(key);
	rstr = ft_strjoin(value, "\n");
	free(value);
	return (rstr);
}
int	check_pipe(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp("|", str[i]) == 0 || ft_strcmp("<", str[i]) == 0 || ft_strcmp(">", str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
static void	export_with_no_input(char **envp)
{
	int		i;
	char	**temp_env;
	char	*str;

	i = 0;
	while (envp[i])
		i++;
	temp_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		temp_env[i] = ft_strdup(envp[i]);
		i++;
	}
	temp_env[i] = NULL;
	sort_env(temp_env, i);
	i = 0;
	while (temp_env[i])
	{
		str = make_export_str(temp_env[i]);
		ft_putstr_fd(str, STDOUT_FILENO);
		free(str);
		i++;
	}
	free_temp_env(temp_env);
}

// int	ft_export(t_setting **set, char **inputs)
// {
// 	int		i;
// 	char	*key;

// 	i = 1;
// 	if (!inputs[1])
// 		export_with_no_input((*set)->envp);
// 	while (inputs[i])
// 	{
// 		if (check_export_input(inputs[i]))
// 		{
// 			(*set)->last_exit_status = 1;
// 			printf("export : `%s': not a valid identifier\n", inputs[i]);
// 			return (0);
// 		}
// 		add_env(&((*set)->env_list), inputs[i], set);
// 		i++;
// 	}
// 	return (0);
// }

void report_error(char *c)
{
	char	*err_str;
	char	*err_str2;

	err_str = ft_strjoin("export: `", c);
	err_str2 = ft_strjoin(err_str, "': not a valid identifier\n");
	ft_putstr_fd(err_str2, STDERR_FILENO);
	free(err_str);
	free(err_str2);
}

// void	go_run_cmd(char **inputs, t_setting **set, int i)
// {
// 	char	**r_input;
// 	int		j;
// 	int		k;

// 	j = 0;
// 	while (inputs[j])
// 		j++;
// 	r_input = (char **)malloc(sizeof(char *) * (j - i + 1));
// 	k = i + 1;
// 	j = 0;
// 	while (inputs[k])
// 	{
// 		r_input[j] = ft_strdup(inputs[k]);
// 		k++;
// 		j++;
// 	}
// 	r_input[j] = NULL;
// 	run_cmd(r_input, (*set)->envp, set);
// 	free_temp_env(r_input);
// }

int	ft_export(t_setting **set, char **inputs)
{
	int		i;
	char	*key;

	i = 1;
	if (!inputs[1])
		export_with_no_input((*set)->envp);
	while (inputs[i])
	{
		if (check_pipe(inputs))
		{
			run_cmd(inputs, (*set)->envp, set);
			return (0);
		}
		else if (check_export_input(inputs[i]))
		{
			(*set)->last_exit_status = 1;
			report_error(inputs[i]);
			return (0);
		}
		
		add_env(&((*set)->env_list), inputs[i], set);
		i++;
	}
	return (0);
}
