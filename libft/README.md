# libft

## Project Description
**libft** is a foundational C library project developed as part of the **42 curriculum**.
The purpose of this project is to reimplement a selection of standard C library functions while also creating additional utility functions that will be reused throughout future projects.

This project strengthens the understanding of low-level programming concepts such as memory management, pointers, string manipulation, arrays, and linked lists, while enforcing clean code practices and strict coding standards.

---

## Project Objectives
- Recreate essential functions from the C standard library
- Understand how memory allocation and manipulation work internally
- Improve proficiency with pointers and data structures
- Write clean, modular, and reusable C code
- Build a personal static library to be reused in future projects

---

## Library Content
The library is organized into multiple functional parts.

---

### Part 1: Libc Functions
Reimplementation of standard C library functions.

- `ft_isalpha`
- `ft_isdigit`
- `ft_isalnum`
- `ft_isascii`
- `ft_isprint`
- `ft_strlen`
- `ft_memset`
- `ft_bzero`
- `ft_memcpy`
- `ft_memmove`
- `ft_strlcpy`
- `ft_strlcat`
- `ft_toupper`
- `ft_tolower`
- `ft_strchr`
- `ft_strrchr`
- `ft_strncmp`
- `ft_memchr`
- `ft_memcmp`
- `ft_strnstr`
- `ft_atoi`
- `ft_calloc`
- `ft_strdup`

---

### Part 2: Additional Functions
Utility functions not included in the standard C library.

- `ft_substr`
- `ft_strjoin`
- `ft_strtrim`
- `ft_split`
- `ft_itoa`
- `ft_strmapi`
- `ft_striteri`
- `ft_putchar_fd`
- `ft_putstr_fd`
- `ft_putendl_fd`
- `ft_putnbr_fd`

---

### Bonus Part: Linked List Functions
Functions for manipulating singly linked lists.

- `ft_lstnew`
- `ft_lstadd_front`
- `ft_lstsize`
- `ft_lstlast`
- `ft_lstadd_back`
- `ft_lstdelone`
- `ft_lstclear`
- `ft_lstiter`
- `ft_lstmap`

---

## Compilation
The project is compiled using a Makefile.

Available commands:
- `make` — compiles the library
- `make clean` — removes object files
- `make fclean` — removes object files and the library
- `make re` — recompiles the project from scratch

The compilation generates a static library:
