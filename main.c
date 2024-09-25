#include "include/minishell.h"

int main ()
{
	char	*input = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if(*input)
			add_history(input);

		//printf("%s\n", input);
		//val_sintax(input);
		get_tokens(input);
		//t_token **tokens = tokenize(const char *input)

	}
	
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <signal.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// // Definições de token (a serem implementadas conforme necessário)
// typedef enum e_token_type {
//     TOKEN_WORD,
//     TOKEN_PIPE,
//     TOKEN_REDIRECT_IN,
//     TOKEN_REDIRECT_OUT,
//     TOKEN_REDIRECT_APPEND,
//     TOKEN_EOF,
// } t_token_type;

// typedef struct s_token {
//     t_token_type type;
//     char *value;
// } t_token;

// // Funções de tokenização e parsing (a serem implementadas)
// Token **tokenize(const char *input);
// void parse_and_execute(Token **tokens);

// // Função para tratar sinais como Ctrl-C
// void signal_handler(int signum) {
//     if (signum == SIGINT) {
//         // Limpar a linha e exibir um novo prompt
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }

// int main(void) {
//     char *input = NULL;
//     struct sigaction sa;

//     // Configura o tratamento de sinais
//     sa.sa_handler = signal_handler;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = SA_RESTART; // Permite que chamadas de sistema sejam reiniciadas
//     sigaction(SIGINT, &sa, NULL);

//     // Loop principal do shell
//     while (1) {
//         // Mostrar o prompt e ler a entrada do usuário com readline
//         input = readline("minishell> ");
//         if (!input) {  // Tratamento para Ctrl-D (EOF)
//             printf("exit\n");
//             break;
//         }

//         // Adiciona o comando ao histórico se não estiver vazio
//         if (*input) {
//             add_history(input);
//         }

//         // Tokenizar a entrada
//         Token **tokens = tokenize(input);
//         if (!tokens) {
//             fprintf(stderr, "Error: Failed to tokenize input.\n");
//             free(input);
//             continue;
//         }

//         // Parsear e executar os comandos
//         parse_and_execute(tokens);

//         // Limpar tokens após uso
//         // TODO: Adicionar função para liberar tokens

//         // Limpar input
//         free(input);
//     }

//     // Limpeza final
//     rl_clear_history();
//     return 0;
// }
