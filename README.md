```bash
minishell/
├── Makefile
├── README.md
├── src/
│   ├── minishell.c
│   ├── parser/
│   │   └── parser.c
│   ├── executor/
│   │   └── executor.c
│   ├── builtin/
│   │   └── builtin.c
│   └── utils/
│       └── utils.c
├── include/
│   ├── minishell.h // 프로그램 전체에 공통적으로 필요한 선언 및 메인 구조체
│   ├── parser.h // 파서(입력 파싱) 관련 함수와 구조체 선언
│   ├── executor.h // 명령 실행 관련 함수와 구조체 선언
│   └── builtin.h // 내장 명령어(builtin) 관련 선언
└── libft/
    └── (libft 소스 파일들)
```