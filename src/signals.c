/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 00:12:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 00:12:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_prompt_sigint(int signal_number)
{
	g_signal = signal_number;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_handler(int signal_number, void (*handler)(int))
{
	struct sigaction	action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(signal_number, &action, NULL);
}

void	set_interactive_signals(void)
{
	set_signal_handler(SIGINT, handle_prompt_sigint);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	set_wait_signals(void)
{
	set_signal_handler(SIGINT, SIG_IGN);
	set_signal_handler(SIGQUIT, SIG_IGN);
}
