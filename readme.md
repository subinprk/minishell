# 🐚 minishell — A Tiny Bash-like Shell in C

A minimalist shell built from scratch using C. It features a Bash-like interface, command parsing into an execution tree, process management, and signal handling — all with no external shell libraries.

![minishell screenshot](./minishell_terminal.png)

---

## 🧠 Project Overview

This 42 project aims to reimplement a simplified Bash shell with:

- Interactive command-line input
- Support for pipelines, redirections, and environment variables
- Command parsing into a **binary tree structure** for proper execution order
- Built-in commands like `cd`, `echo`, `pwd`, and `exit`
- Proper signal handling and prompt behavior like real Bash

> Parsing the Bash syntax into a binary tree and executing it sequentially was the part I enjoyed most — turning text input into an execution plan, like a mini compiler.

---

## 🛠️ Features

- ✅ Custom lexer and parser turning user input into an AST
- ✅ Redirections: `<`, `>`, `<<`, `>>`
- ✅ Piping using `|`
- ✅ Environment variable expansion (`$VAR`, `$?`)
- ✅ Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- ✅ Command history using `readline()`

---

## 🔧 Build & Run

### 🔨 Compile

```bash
make
```
### 🚀 Run
```
./minishell
```
Type any valid Bash command (or one of the builtins), and the shell will evaluate it just like Bash would.
### 🌲 Execution Tree

Commands like:
```
ls -l | grep .c > out.txt
```
Are parsed into an internal binary tree that allows recursive execution:
```
        >
       / \
      |  out.txt
     / \
  ls   grep
```

This design helped decouple parsing from execution and simplified support for future logical operators like &&, ||.
### 🧩 Key Components
Component	Description
Lexer	Tokenizes input with support for quotes and escapes
Parser	Builds binary tree based on operator precedence
Executor	Walks tree and sets up pipes/forks accordingly
Signal	Handles SIGINT, SIGQUIT cleanly
Redir	Manages I/O redirection and heredocs
Env	Maintains shell environment state dynamically
### 📚 What I Learned

  - Parsing shell grammar into a binary execution tree
  - Handling fork/execve, dup2, and file descriptors manually
  - Designing clean process flows with input/output redirection
  - Synchronizing signals and state without global data
  - Debugging interleaved processes and subtle shell behaviors

📸 Screenshot

🔮 Future Work

  - Implement logical operators (&&, ||)
  - Add wildcard (*) expansion
  - Improve heredoc memory and history handling
  - Add job control features (fg, bg, jobs)

📄 License

This project is part of the 42 curriculum and is distributed for educational purposes only.


---
