/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 06:50:09 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/22 12:57:55 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*Includes*/
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/*Structs*/
typedef enum e_quote
{
	UNQUOTED,
	SINGEL,
	DOUBLE,
}	t_quote;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
	int				is_delimeter_quoted;
}					t_redir;

typedef struct s_cmd
{
	t_redir			*redirs;
	char			**argv;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env			*envp;
	int				env_count;
	int				exit_status;
}					t_shell;

/*Executor*/

int					execute(t_shell *shell, t_cmd *cmd);
int					execute_external(t_shell *shell, t_cmd *cmd);
int					execute_builtin(t_shell *shell, t_cmd *cmd);
int					is_builtin(char *cmd);
char				*get_cmd_path(char *cmd, char **envp);

/*Builtins*/
int					builtin_echo(t_cmd *cmd);
int					builtin_pwd(void);
int					builtin_env(t_shell *shell);
int					builtin_cd(t_shell *shell, t_cmd *cmd);
int					builtin_export(t_shell *shell, t_cmd *cmd);
int					builtin_unset(t_shell *shell, t_cmd *cmd);
int					builtin_exit(t_shell *shell);

/*Environment*/

char				**copy_envp(char **envp);
void				free_envp(char **envp);
char				*get_env_value(char **envp, char *key);
int					set_env_value(char ***envp, char *key, char *value);
int					add_env_value(char ***envp, char *new_var);
int					remove_env_value(char ***envp, char *key);

void				free_split(char **res, int size);

/*LEXER*/
t_token				*new_token(t_type t, char *v);
t_token				*lexer_line(char *line);
void				add_back(t_token **head, t_token *new_tok);
void				print_l(t_token **head);
void				free_tokens(t_token **tokens);
int					ft_is_operation(char c);
int					ft_is_space(char c);
int					error_msg(char *token, t_shell	*shell);
int					ft_is_valid(t_token *tokens, t_shell *shell);
int					quote_error(void);
int					handle_redir_right(char *line, int i, t_token **head);
int					handle_redir_left(char *line, int i, t_token **head);
int					has_ampersand(char *s);
int					ft_is_redir(t_type type);
char				*remove_quotes(char *argv);
int					add_back_pipe(t_token	**head, t_token	*new_token);
/*PARSING*/
int					add_argv(t_cmd *current, char *word);
void				redir_add_back(t_redir **head, t_redir *new);
t_redir				*new_redir(t_type type, char *file);
int					add_redir(t_cmd *current, t_type type, char *file);
t_cmd				*new_cmd(void);
t_cmd				*parse_tokens(t_token *tokens);
void				free_cmd(t_cmd *cmd);
void				free_argv(char **argv);
void				free_redir(t_redir *redir);
int					count_arg(char **arg);
int					cmd_validation(t_cmd *cmd);
/*EXPANDER*/
int					parse_env(char *envp, char **key, char **value);
t_env				*read_env(char **envp);
char				*get_value_of_env(t_env *env, char *key);
void				free_env(t_env *env);
void				expand_tokens(t_token *tokens, t_env *env, t_shell *shell);
char				*extract_var_name(char *str);
void				expand_word(t_token *tokens, t_env *env, t_shell *shell);
t_quote				quote_states(char **current, t_quote quote);
void				appeand_exit_status(char **current, char	**result,
						t_shell	*shell);
int					quote_check(char **current, t_quote *quote);
void				appeand_string(char **result, char *str);
/*TESTING*/

void				print_redir(t_redir *redir);
char				*redir_name(t_type type);
void				print_argv(char **argv);
void				print_cmd(t_cmd *cmd);
void				print_env(t_env *env);

#endif