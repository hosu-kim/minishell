```bash
minishell/                      # Project root directory
├── Makefile                    # Build rules (compile & link) and clean targets
├── include/                    # Public headers for all modules
│   └── minishell.h             # “Umbrella” header: shared macros, types, and module includes
├── src/                        # All implementation files
│   ├── minishell.c             # Entry point: init shell state, main loop (read → dispatch → cleanup)
│   ├── lexer/                  # Lexer module: splits raw input into tokens
│   │   ├── lexer.c             # Tokenization logic (quotes, escapes, word boundaries)
│   │   └── lexer.h             # t_token type, token enums, lex_input prototype
│   ├── parser/                 # Parser module: builds command structures from tokens
│   │   ├── parser.c            # Grammar validation, redirection and pipe handling
│   │   └── parser.h            # t_cmd struct, parse_tokens prototype
│   ├── expander/               # Expander module: variable and meta‑token substitution
│   │   ├── expander.c          # Implements $VAR, $?, $$, quote rules, here‑doc control
│   │   └── expander.h          # expand_cmds prototype
│   ├── executor/               # Executor module: runs commands and pipelines
│   │   ├── executor.c          # fork/pipe/dup2 logic, PATH search, status collection
│   │   └── executor.h          # execute_cmds prototype
│   ├── builtin/                # Built‑in commands implementation
│   │   ├── cd.c                # Change directory
│   │   ├── echo.c              # Echo arguments
│   │   ├── pwd.c               # Print working directory
│   │   ├── export.c            # Set environment variables
│   │   ├── unset.c             # Unset environment variables
│   │   ├── env.c               # Print environment
│   │   └── exit.c              # Exit shell
│   └── signal/                 # Signal handling logic
│       ├── signal.c            # SIGINT / SIGQUIT handlers
│       └── signal.h            # setup_signals, reset_signals prototypes
├── utils/                      # Minimal helper implementations
│   ├── mem.c                   # Safe allocators: xmalloc, xcalloc (exit on failure)
│   ├── str.c                   # Basic string utilities: xstrdup, xstrlen, xstrcmp
│   ├── error.c                 # Error reporting: error_exit, perror wrappers
│   └── utils.h                 # Prototypes for all utils and shared macros
└── README.md                   # Project overview
```
```bash
+---------------------+     +----------------------+
|      main.c         | --> |        lexer.c       |
| (Input, Prompt,     |     | (Tokenization)       |
| Signal Handler Reg.)|     +----------+-----------+
+--------+------------+                |
         |                            | (Token List)
         | (Signal -> Handler Call)   v
         |                          +----------+-----------+
         |                          |       parser.c       |
         |                          | (Syntax Analysis,    |
         |                          |  Structure Creation) |
+--------v------------+             +----------+-----------+
|     signal.c        |                          |
| (Signal Handlers    |                          | (Command Structure)
|  Definition)        |                          v
+---------------------+                          +----------+-----------+
                                      |      expander.c      |
                                      | (Var/Quote Expansion)|
                                      +----------+-----------+
                                                   |
                                                   | (Final Command Struct)
                                                   v
                                      +----------+-----------+
                                      |      executor.c      |
                                      | (Command Execution)  |---+
                                      +----------+-----------+   |
                                                   |               | (If Built-in)
                                                   | (External Cmd Exec) v
                                                   |            +----------+-----------+
                                                   +----------> |       builtin.c      |
                                                                | (Built-in Cmd Impl.) |
                                                                +----------------------+
```