#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

#define MAX 50 /* Tamanho maximo de uma string */

/* Estrutura para paises */
typedef struct paises {
    int id_pais; /* Identificador do pais */
    char nome_pais[MAX]; /* Nome do pais */
    int medalha_ouro; /* Numero de medalhas de ouro */
    int medalha_prata; /* Numero de medalhas de prata */
    int medalha_bronze; /* Numero de medalhas de bronze */
    int total_medalhas; /* Total de medalhas */
};
struct paises pai;

/* Estrutura para esportes */
typedef struct esportes {
    int id_esporte; /* Identificador do esporte */
    char nome_modalidades[MAX]; /* Nome da modalidade */
};
struct esportes esp;

/* Estrutura para atletas */
typedef struct atletas {
    int id_atleta; /* Identificador do atleta */
    char nome[MAX]; /* Nome do atleta */
    char ultimo_nome[MAX]; /* Ultimo nome do atleta */
    char pais[MAX]; /* País do atleta */
    char modalidade[MAX]; /* Modalidade do atleta */
};
struct atletas atl;

/* Função para posicionar o cursor na tela */
void gotoxy (short x, short y) {
    COORD pos = {
      x,
      y
    };
    SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), pos);
}

/* Exibe cabeçalho no centro da tela com a palavra "olympics". */
void cabecalho () {
    gotoxy (19, 2);
    printf ("       _                       _          \n");
    gotoxy (19, 3);
    printf ("      | |                     (_)         \n");
    gotoxy (19, 4);
    printf ("  ___ | |_   _ _ __ ___  _ __  _  ___ ___ \n");
    gotoxy (19, 5);
    printf (" / _ \\| | | | | '_ ` _ \\| '_ \\| |/ __/ __|\n");
    gotoxy (19, 6);
    printf ("| (_) | | |_| | | | | | | |_) | | (__\\__ \\\n");
    gotoxy (19, 7);
    printf (" \\___/|_|\\__, |_| |_| |_| .__/|_|\\___|___/\n");
    gotoxy (19, 8);
    printf ("          __/ |         | |               \n");
    gotoxy (19, 9);
    printf ("         |___/          |_|               \n");
}

/* Cadastrar atleta */
void cadastrar_atleta () {
    FILE* banco_atletas; /* Arquivo para armazenar os atletas */

    cabecalho ();

    int novo_id;
    int maior_id = 0;

    banco_atletas = fopen (".//banco-de-dados//atletas.txt", "r"); // Abre o arquivo para leitura
    if (banco_atletas == NULL) { // Se o arquivo não existir, cria-o
        system ("cls");
        cabecalho ();
        gotoxy (27, 14);
        printf ("Erro ao abrir banco de dados.\n");
        gotoxy (27, 15);
        printf ("Novo arquivo criado, tente novamente.\n");
        banco_atletas = fopen (".//banco-de-dados//atletas.txt", "w");
        fclose (banco_atletas);
        gotoxy (20, 17);
        system ("pause");
        menu_atletas ();
    }

    while (!feof (banco_atletas)) { /* Enquanto não chegar ao final do arquivo */
        fscanf (banco_atletas, "%d;%s;%s;%s\n", &atl.id_atleta, &atl.nome, &atl.pais, &atl.modalidade);
        if (atl.id_atleta > maior_id) { /* Verifica se o id é maior que o maior id */
            maior_id = atl.id_atleta;
        }
    }
    novo_id = maior_id + 1; /* Novo id é o maior id encontrado + 1 */
    fclose (banco_atletas);

    banco_atletas = fopen (".//banco-de-dados//atletas.txt", "a"); /* Abre o arquivo no modo append */
    if (banco_atletas == NULL) { // Se o arquivo não existir, cria-o
        system ("cls");
        cabecalho ();
        gotoxy (27, 14);
        printf ("Erro ao abrir banco de dados.\n");
        gotoxy (27, 15);
        printf ("Novo arquivo criado, tente novamente.\n");
        banco_atletas = fopen (".//banco-de-dados//atletas.txt", "w"); // Cria o arquivo utilizando o método write.
        fclose (banco_atletas);
        gotoxy (20, 17);
        system ("pause");
        menu_atletas ();
    }

    fflush (stdin); /* Limpa o buffer de entrada */
    gotoxy (27, 14);
    printf ("Digite o nome do atleta: ");
    fgets (atl.nome, MAX, stdin); /* Lê a string até o \n */

    for (int i = 0; i < strlen (atl.nome); i++) { /* Replace de space bar para under score */
        if (atl.nome[i] == ' ') {
            atl.nome[i] = '_';
        }
    }

    fflush (stdin); /* Limpa o buffer de entrada */
    gotoxy (27, 16);
    printf ("Digite o pais do atleta: ");
    fgets (atl.pais, MAX, stdin); /* Lê a string até o \n */

    for (int i = 0; i < strlen (atl.pais); i++) { /* Replace de space bar para under score */
        if (atl.pais[i] == ' ') {
            atl.pais[i] = '_';
        }
    }

    fflush (stdin); /* Limpa o buffer de entrada */
    gotoxy (27, 17);
    printf ("Digite a modalidade do atleta: ");
    fgets (atl.modalidade, MAX, stdin); /* Lê a string até o \n */

    for (int i = 0; i < strlen (atl.modalidade); i++) { /* Replace de space bar para under score */
        if (atl.modalidade[i] == ' ') {
            atl.modalidade[i] = '_';
        }
    }

    atl.nome[strlen (atl.nome) - 1] = '\0'; /* Remove o \n do final da string */
    atl.pais[strlen (atl.pais) - 1] = '\0'; /* Remove o \n do final da string */
    atl.modalidade[strlen (atl.modalidade) - 1] = '\0'; /* Remove o \n do final da string */

    fprintf (banco_atletas, "\n%d;%s;%s;%s", novo_id, atl.nome, atl.pais, atl.modalidade); /* Escreve no arquivo */
    fclose (banco_atletas);
    system ("cls");
    menu_atletas ();
}

/* Listar atletas */
void listar_atletas () {
    FILE* banco_atletas; /* Arquivo para armazenar os atletas */

    char linha[MAX];
    char* coluna[MAX];

    cabecalho ();

    banco_atletas = fopen (".//banco-de-dados//atletas.txt", "r");
    if (banco_atletas == NULL) { // Se o arquivo não existir, cria-o
        system ("cls");
        cabecalho ();
        gotoxy (27, 14);
        printf ("Erro ao abrir banco de dados.\n");
        gotoxy (27, 15);
        printf ("Novo arquivo criado, tente novamente.\n");
        banco_atletas = fopen (".//banco-de-dados//atletas.txt", "w");
        fclose (banco_atletas);
        gotoxy (20, 17);
        system ("pause");
        menu_atletas ();
    }

    while (!feof (banco_atletas)) { /* Enquanto não chegar ao final do arquivo */
        fscanf (banco_atletas, "%d;%s;%s;%s\n", &atl.id_atleta, &linha); /* Lê o id e o nome do atleta */

        *coluna = strtok (linha, ";"); /* Separa a string em colunas guardando o ID e o primeiro nome */
        gotoxy (30, 14);
        printf ("ID: %d\n", atl.id_atleta); /* Imprime o id */

        gotoxy (30, 15);
        for (int i = 0; i < strlen (coluna[0]); i++) { /* Replace de under score para space bar */
            if (coluna[0][i] == '_') {
                coluna[0][i] = ' ';
            }
        }
        printf ("Nome: %s ", *coluna); /* Imprime o nome */

        *coluna = strtok (NULL, ";"); /* Separa a string em colunas guardando o pais */
        gotoxy (30, 16);
        for (int i = 0; i < strlen (coluna[0]); i++) { /* Replace de under score para space bar */
            if (coluna[0][i] == '_') {
                coluna[0][i] = ' ';
            }
        }
        printf ("Pais: %s\n", *coluna); /* Imprime o pais */

        *coluna = strtok (NULL, ";"); /* Separa a string em colunas guardando a modalidade */
        gotoxy (30, 17);
        for (int i = 0; i < strlen (coluna[0]); i++) { /* Replace de under score para space bar */
            if (coluna[0][i] == '_') {
                coluna[0][i] = ' ';
            }
        }
        printf ("Modalidade: %s\n", *coluna); /* Imprime a modalidade */

        gotoxy (30, 20);
        printf ("Deseja ver o proximo atleta?\n");
        gotoxy (30, 21);
        printf ("'S' para continuar\n");
        gotoxy (30, 22);
        printf ("'N' para voltar ao menu\n");
        gotoxy (30, 23);
        printf ("Digite a opcao: ");
        fflush (stdin); /* Limpa o buffer de entrada */
        char escolha = getche (); /* Lê a opção */
        if (escolha == 'N' || escolha == 'n') { /* Se a opção for não, volta ao menu de atletas */
            fclose (banco_atletas); /* Fecha o arquivo */
            menu_atletas (); /* Chama o menu de atletas */
        } else { /* Se a opção for sim, continua a listagem */
            system ("cls");
            cabecalho ();
            continue; /* Continua a listagem */
        }
    }
}

/* Procurar atletas pelo id. */
void buscar_atleta_id () {
    FILE* banco_atletas; /* Arquivo para armazenar os atletas */

    char linha[MAX];
    char* coluna[MAX];
    int id_busca;

pesquisar:

    cabecalho ();

    gotoxy (30, 14);
    printf ("Digite o ID do atleta: ");
    fflush (stdin); /* Limpa o buffer de entrada */
    scanf ("%d", &id_busca); /* Lê o id */
    system ("cls");

    cabecalho ();

    banco_atletas = fopen (".//banco-de-dados//atletas.txt", "r"); /* Abre o arquivo */
    if (banco_atletas == NULL) { // Se o arquivo não existir, cria-o
        system ("cls");
        cabecalho ();
        gotoxy (27, 14);
        printf ("Erro ao abrir banco de dados.\n");
        gotoxy (27, 15);
        printf ("Novo arquivo criado, tente novamente.\n");
        banco_atletas = fopen (".//banco-de-dados//atletas.txt", "w"); /* Cria o arquivo */
        fclose (banco_atletas);
        gotoxy (20, 17);
        system ("pause");
        menu_atletas ();
    }

    while (!feof (banco_atletas)) { /* Enquanto não chegar ao final do arquivo */
        fscanf (banco_atletas, "%d;%s;%s;%s\n", &atl.id_atleta, &linha); /* Lê o id e o nome do atleta */

        if (id_busca == atl.id_atleta) {
            *coluna = strtok (linha, ";"); /* Separa a string em colunas guardando o ID e o primeiro nome */
            gotoxy (30, 14);
            printf ("ID: %d\n", atl.id_atleta); /* Imprime o id */
            gotoxy (30, 15);
            printf ("Nome: %s ", *coluna); /* Imprime o nome */
            *coluna = strtok (NULL, ";");
            printf ("%s\n", *coluna); /* Imprime o ultimo nome */

            *coluna = strtok (NULL, ";"); /* Separa a string em colunas guardando o pais */
            gotoxy (30, 16);
            printf ("Pais: %s\n", *coluna); /* Imprime o pais */

            *coluna = strtok (NULL, ";"); /* Separa a string em colunas guardando a modalidade */
            gotoxy (30, 17);
            printf ("Modalidade: %s\n", *coluna); /* Imprime a modalidade */

            gotoxy (30, 20);
            printf ("Deseja buscar outro atleta?");
            gotoxy (30, 21);
            printf ("'S' para continuar\n");
            gotoxy (30, 22);
            printf ("'N' para voltar ao menu\n");
            gotoxy (30, 23);
            printf ("Digite a opcao: ");
            fflush (stdin);
            char escolha = getche (); /* Lê a escolha */
            if (escolha == 'N' || escolha == 'n') { /* Se a escolha for não, volta ao menu de atletas */
                fclose (banco_atletas);
                menu_atletas ();
            } else { /* Se a escolha for sim, busca outro atleta. */
                system ("cls");
                goto pesquisar; /* Vai para a linha pesquisar */
            }
        } else { /* Se o id não for encontrado, continua a listagem */
            continue; /* Continua a listagem */
        }
    }
    fclose (banco_atletas); /* Fecha o arquivo */
    system ("cls");
    cabecalho ();
    gotoxy (30, 14);
    printf ("Atleta nao encontrado\n"); /* Imprime que o atleta não foi encontrado */
    gotoxy (20, 17);
    system ("pause");
    system ("cls");
}

/* Menu de opção para atletas */
void menu_atletas () {
    system ("cls");

    int escolha_atletas;

    while (escolha_atletas != 4) {
        cabecalho ();
        gotoxy (30, 12);
        printf ("* MENU ATLETAS *");
        gotoxy (30, 14);
        printf ("[1] LISTAR ATLETAS\n");
        gotoxy (30, 15);
        printf ("[2] CONSULTAR ATLETAS POR ID\n");
        gotoxy (30, 16);
        printf ("[3] CADASTRAR NOVO ATLETA\n");
        gotoxy (30, 17);
        printf ("[4] VOLTAR PARA O MENU PRINCIPAL");
        gotoxy (30, 18);
        printf ("Escolha uma opcao: ");
        fflush (stdin);
        scanf ("%d", &escolha_atletas);

        if (escolha_atletas >= 1 && escolha_atletas <= 4) { /* Se a opção for entre 1 e 4 */
            switch (escolha_atletas) { /* Escolha a opção */
                case 1: /* Listar atletas */
                    system ("cls");
                    listar_atletas ();
                    break;

                case 2: /* Buscar atleta por id */
                    system ("cls");
                    buscar_atleta_id ();
                    break;

                case 3: /* Cadastrar novo atleta */
                    system ("cls");
                    cadastrar_atleta ();
                    break;

                case 4: /* Voltar ao menu principal */
                    main ();
                    break;
            }
        } else { /* Se a opção for inválida */
            system ("cls");
            gotoxy (30, 21);
            printf ("Opcao invalida, tente novamente\n");
        }
    }
}

void menu_ranking () {

}

void menu_calendario () {

}

void mostrar_dados_usuario () {

}

/* Função principal do programa. */
int main () {
    system ("mode 80, 25"); /* Altera o tamanho da tela */
    setlocale (LC_ALL, ".UTF8"); /* Altera o idioma para português */

    int escolha;

    while (1) { /* Enquanto o usuário não escolher a opção de sair */
        cabecalho ();
        gotoxy (30, 12);
        printf ("* MENU PRINCIPAL *");
        gotoxy (30, 14);
        printf ("[1] ATLETAS\n");
        gotoxy (30, 15);
        printf ("[2] RANKING\n");
        gotoxy (30, 16);
        printf ("[3] CALENDARIO DOS JOGOS\n");
        gotoxy (30, 17);
        printf ("[4] DADOS DO USUARIO\n");
        gotoxy (30, 18);
        printf ("[0] SAIR DA APLICACAO\n");
        gotoxy (30, 19);
        printf ("Escolha uma opcao: ");
        fflush (stdin);
        scanf ("%d", &escolha); /* Lê a opção */

        if (escolha >= 0 && escolha <= 4) { /* Se a opção for entre 0 e 4 */
            switch (escolha) { /* Escolha a opção */
                case 0: /* Sair da aplicação */
                    gotoxy (30, 21);
                    printf ("Encerrando aplicacao\n");
                    gotoxy (30, 23);
                    exit (0); /* Encerra a aplicação */
                    break;

                case 1: /* Atletas */
                    system ("cls");
                    menu_atletas ();
                    break;

                case 2: /* Ranking */
                    system ("cls");
                    gotoxy (30, 21);
                    printf ("ranking (WIP)");
                    // menu_ranking ();
                    break;

                case 3: /* Calendário */
                    system ("cls");
                    gotoxy (30, 21);
                    printf ("calendario (WIP)");
                    // menu_calendario ();
                    break;

                case 4: /* Dados do usuário */
                    system ("cls");
                    gotoxy (30, 21);
                    printf ("user (WIP)");
                    // mostrar_dados_usuario ();
                    break;
            }
        } else { /* Se a opção for inválida */
            system ("cls");
            gotoxy (30, 21);
            printf ("Opcao invalida, tente novamente.\n");
        }
    }
    return 0; /* Encerra a aplicação */
}