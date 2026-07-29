*This project has been created as part of the 42 curriculum by moatieh, malmarad.*

# minishell

## Description

`minishell` is a small interactive shell written in C. It is an educational reimplementation of a focused subset of Bash: it reads a command line, turns it into commands and redirections, expands environment variables, and runs the result through built-ins or external programs.

The project practises the Unix process model and the foundations of a command interpreter: parsing, environment management, file descriptors, redirections, pipes, `fork`, `execve`, and `waitpid`. The prompt is `minishell$ ` and command history is provided through GNU Readline.

## Features

- Interactive prompt with command history.
- Execution of external commands found through `PATH`.
- Built-ins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Environment-variable expansion, including `$?`, with quote-aware expansion: variables expand outside quotes and inside double quotes, but not inside single quotes.
- Single and double quotes for grouping arguments.
- Pipelines with `|`.
- Interactive signal handling for Ctrl-C, Ctrl-D, and Ctrl-backslash.
- Input redirection (<), heredocs (<<), output truncation (>), and output append (>>).
- Basic syntax validation for misplaced pipes, redirections, quotes, and unsupported `&&` / `&` operators.
- Lines beginning with `#` are treated as comments.

## Instructions

### Requirements

- A POSIX-compatible Unix-like system (the project is developed for Linux).
- A C compiler and `make`.
- GNU Readline development files.

On Debian/Ubuntu, install the build prerequisites with:

```sh
sudo apt install build-essential libreadline-dev
```

### Build

From the repository root, run:

```sh
make
```

This builds the bundled `libft` static library and creates the `minishell` executable in the repository root. The project is compiled with `-Wall -Wextra -Werror` and linked with Readline.

Other Makefile targets are:

```sh
make clean    # Remove object files
make fclean   # Remove object files, libft archive, and the executable
make re       # Rebuild everything from scratch
```

### Run

```sh
./minishell
```

Exit with `exit` or by sending end-of-file (`Ctrl-D`).

### Examples

```sh
minishell$ echo "Hello, $USER"
minishell$ export PROJECT=minishell
minishell$ echo "$PROJECT" | tr a-z A-Z
minishell$ ls -la | grep '\\.c$' > sources.txt
minishell$ cat < sources.txt >> combined.txt
minishell$ echo $?
```

## Project structure

| Path | Purpose |
| --- | --- |
| `src/main.c` | Readline loop, shell state, and command lifecycle. |
| `parser/` | Lexing, syntax validation, parsing, quote removal, and variable expansion. |
| `src/executor/` | External-command execution, pipelines, redirections, and exit-status handling. |
| `src/builtins/` | Shell built-in commands. |
| `src/env/` | Copying and updating the shell environment. |
| `includes/minishell.h` | Shared types and function declarations. |
| `libft/` | Project utility library used by minishell. |

## Implementation notes

Each entered line follows this flow:

```text
Readline input -> lexer -> syntax validation -> expansion -> parser
-> heredoc collection -> redirection preparation -> execution -> status update
```

For pipelines, each command is executed in a separate child process connected by pipe file descriptors. Built-ins that need to alter the shell environment (`cd`, `export`, `unset`, and `exit`) execute in the parent process when they are not part of a pipeline.

## Resources

- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) - line editing and history API used by the interactive prompt.
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - reference for shell language behaviour and built-in command semantics.
- [Linux man-pages](https://man7.org/linux/man-pages/) - references for `fork(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`, `open(2)`, and `waitpid(2)`.
- [The Linux Programming Interface](https://man7.org/tlpi/) by Michael Kerrisk - background on Unix processes, file descriptors, and signals.

### Use of AI

An AI assistant was used to review requirements, diagnose parser and executor behaviour, assist with implementation of expansion, signals, heredocs, redirections, pipelines, and memory cleanup, and run build, behavioural, and Valgrind tests. The authors reviewed the changes and remain responsible for the project.

## Authors

- moatieh
- malmarad
