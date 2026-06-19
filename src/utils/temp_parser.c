#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	int		is_head;

	if (!cmd)
		return ;
	current = cmd;
	is_head = 1;
	while (current)
	{
		next = current->next;
		close_command_fds(current);
		if (current->argv)
			free_split(current->argv, -1);
		if (!is_head)
			free(current);
		is_head = 0;
		current = next;
	}
	cmd->argv = NULL;
	cmd->next = NULL;
}

static int	open_redirection_file(t_cmd *cmd, char *operator, char *file)
{
	int	fd;

	if (ft_strncmp(operator, "<", 2) == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (perror(file), 1);
		if (cmd->infile != -1)
			close(cmd->infile);
		cmd->infile = fd;
		return (0);
	}
	if (ft_strncmp(operator, ">>", 3) == 0)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(file), 1);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (0);
}

static void	remove_redirection_tokens(char **argv, int i)
{
	free(argv[i]);
	free(argv[i + 1]);
	while (argv[i + 2])
	{
		argv[i] = argv[i + 2];
		i++;
	}
	argv[i] = NULL;
	argv[i + 1] = NULL;
}

static int	is_redirection(char *arg)
{
	return (ft_strncmp(arg, ">", 2) == 0
		|| ft_strncmp(arg, ">>", 3) == 0
		|| ft_strncmp(arg, "<", 2) == 0);
}

static int	handle_redirection(t_cmd *cmd, int i)
{
	if (!cmd->argv[i + 1])
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (is_redirection(cmd->argv[i + 1]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(cmd->argv[i + 1], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (open_redirection_file(cmd, cmd->argv[i], cmd->argv[i + 1]))
		return (1);
	remove_redirection_tokens(cmd->argv, i);
	return (0);
}

static int	parse_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (is_redirection(cmd->argv[i]))
		{
			if (handle_redirection(cmd, i))
				return (1);
			i = 0;
			continue ;
		}
		i++;
	}
	return (0);
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->next = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
}

static int	is_pipe(char *arg)
{
	return (ft_strncmp(arg, "|", 2) == 0);
}

static int	count_segment_args(char **tokens, int start)
{
	int	count;

	count = 0;
	while (tokens[start + count] && !is_pipe(tokens[start + count]))
		count++;
	return (count);
}

static char	**copy_segment_argv(char **tokens, int start, int count)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		argv[i] = ft_strdup(tokens[start + i]);
		if (!argv[i])
			return (free_split(argv, i), NULL);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_cmd	*next_cmd_slot(t_cmd *head, t_cmd **tail)
{
	t_cmd	*new_cmd;

	if (!head->argv)
	{
		*tail = head;
		return (head);
	}
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	init_cmd(new_cmd);
	(*tail)->next = new_cmd;
	*tail = new_cmd;
	return (new_cmd);
}

static int	add_command_segment(t_cmd *head, t_cmd **tail,
		char **tokens, int start)
{
	t_cmd	*cmd;
	int		count;

	count = count_segment_args(tokens, start);
	if (count == 0)
		return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), 1);
	cmd = next_cmd_slot(head, tail);
	if (!cmd)
		return (1);
	cmd->argv = copy_segment_argv(tokens, start, count);
	if (!cmd->argv)
		return (1);
	if (parse_redirections(cmd))
		return (1);
	if (!cmd->argv[0])
		return (ft_putstr_fd("minishell: empty command\n", 2), 1);
	return (0);
}

static int	parse_tokens(t_cmd *head, char **tokens)
{
	t_cmd	*tail;
	int		i;

	tail = head;
	i = 0;
	while (tokens[i])
	{
		if (add_command_segment(head, &tail, tokens, i))
			return (1);
		while (tokens[i] && !is_pipe(tokens[i]))
			i++;
		if (tokens[i] && is_pipe(tokens[i]))
		{
			if (!tokens[i + 1])
				return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), 1);
			i++;
		}
	}
	return (0);
}

t_cmd	temp_parse_line(char *line)
{
	t_cmd	cmd;
	char	**tokens;

	init_cmd(&cmd);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (cmd);
	if (parse_tokens(&cmd, tokens))
	{
		free_cmd(&cmd);
		cmd.argv = NULL;
	}
	free_split(tokens, -1);
	return (cmd);
}
