#include <stdio.h>
#include <stdlib.h>

/*int main()
{

    char *temp;
    char *env_var = "$HOME";

    if (env_var[0] == '$')
        //temp = getenv(env_var + 1);
        temp = getenv("HOME");

    if (temp != NULL) {
        printf("Valor da variável de ambiente: %s\n", temp);
    } else {
        printf("Variável de ambiente não encontrada.\n");
    }

    return 0;
}*/

/*#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    char cwd[PATH_MAX];

    // Mudar o diretório para dois níveis acima
    if (chdir("42CC") == 0) {
        // Verificar o diretório atual
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Diretório atual: %s\n", cwd);
        } else {
            perror("Erro ao obter o diretório atual");
        }
    } else {
        perror("Erro ao mudar de diretório");
    }
    return 0;
}*/

