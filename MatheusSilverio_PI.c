#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define LINHAS 26
#define COLUNAS 41

#define VERMELHO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4)
#define VERDE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2)
#define AZUL SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1)
#define AMARELO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6)
#define BRANCO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

#define BACKGROUND_VERMELHO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED)
#define BACKGROUND_VERDE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN)
#define BACKGROUND_AZUL SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE)
#define BACKGROUND_AMARELO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN)
#define BACKGROUND_BRANCO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY)

typedef struct {
	int posicao;
	char letra;
	int posicaoInicial;
	int jogador;
} Pecas;

typedef struct {
	int Jogador[5];
	int Peca[17];
}TerminarStruct;

typedef struct {
    char Usuario[20];
    int jogador;
    const char *cor; // Ponteiro para a sequência de escape ANSI
    int pontos;
} Jogador;

typedef struct {
    char Jogador[20];
    int Pontos;
} PontuacaoStruct;

int i = 0;
int j = 0;

int k, l;

int cadastrado = 0;

int numero_sorteado = 0;

int numeros_sorteados_jogadores[4];
int numeros_sorteados_jogadas[4];

int jogador_maior_valor = 0;
int jogador_menor_valor = 0;

int jogadores[4];
int valores[4];

int temp_val = 0;
int temp_jog = 0;
int jogador_index = 0;

int peca_movimento = 0;

int escolha_Jogador = 0;

int peca_valida[17];

char cor[30];

int acumulador_jogadas[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// ---------------

Jogador jogadores_cadastro[4];
PontuacaoStruct pontuacoes[4];
Pecas pecas[17];
TerminarStruct Terminar;

char posicoes_matriz[80];
char posicoes_corredor_vitoria[5][6];

char Matriz_tabuleiro[LINHAS][COLUNAS] = {
	
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'.' ,'|' ,'.' ,'.' ,'.' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'*' ,'*' ,'*' ,'|' ,'.' ,'.' ,'.' ,'|' ,'$' ,'$' ,'$' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'.' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ','|' ,'.' ,'.' ,'.' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-'},
	{' ', ' ','|' ,' .' ,' .' ,'|' ,'$' ,'$' ,'|' ,' ' ,' ' ,'|' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,'|' ,' ' ,' ' ,'|' ,'*' ,'*' ,'|' ,' ' ,' ' ,'|' ,' ' ,' '},
	{'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-'},
	{' ',' ' ,'|' ,' .' ,' .' ,'|' ,' .' ,' .' ,'|' ,' .' ,' .' ,'|' ,' .' ,' .' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'|' ,'.' ,'.' ,'|' ,'.' ,'.' ,'|' ,'.' ,'.' ,'|' ,' ' ,' '},
	{' ',' ' ,'|' ,' .' ,' .' ,'|' ,' .' ,' .' ,'|' ,' .' ,' .' ,'|' ,' .' ,' .' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'|' ,'.' ,'.' ,'|' ,'.' ,'.' ,'|' ,'.' ,'.' ,'|' ,' ' ,' '},
	{'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-' ,'|' ,'-' ,'-'},
	{' ',' ' ,'|' ,' ' ,' ' ,'|' ,'*' ,'*' ,'|' ,' ' ,' ' ,'|' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,'|' ,' ' ,' ' ,'|' ,'$' ,'$' ,'|' ,'.' ,'.' ,'|' ,' ' ,' '},
	{'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-'},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'.' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'.' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'$' ,'$' ,'$' ,'|' ,'.' ,'.' ,'.' ,'|' ,'*' ,'*' ,'*' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'.' ,'.' ,'.' ,'|' ,'.' ,'.' ,'.' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,'-' ,'-' ,'-' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
	{' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,'|' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' ' ,' '},
		 
};

void Limpar_Buffer() {
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Linha_Tabuleiro_superior() {
    printf("                 %c", 201);
    for (i = 0; i < COLUNAS; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
}

void Linha_Tabuleiro_inferior() {
    printf("                 %c", 200);
    for (i = 0; i < COLUNAS; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
}

void sortear_num() {
    srand(time(NULL));
    
    linha_Menu_Superior();
    printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
    printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                 Vamos sortear a ordem de jogadores                     |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();

   for (i = 0; i < escolha_Jogador; i++) {
        numero_sorteado = (rand() % 6) + 1;
        gotoxy(45, 13 + i);
        printf("%s tirou = %i\n", jogadores_cadastro[i].Usuario, numero_sorteado);
        getch();
        numeros_sorteados_jogadores[i] = numero_sorteado;
    }  
    getch();
}

void Vez_Jogadas() {
    for (i = 0; i < escolha_Jogador; i++) {
        jogadores[i] = i;
        valores[i] = numeros_sorteados_jogadores[i];
    }

    for (i = 0; i < escolha_Jogador; i++) {
        for (j = i + 1; j < escolha_Jogador; j++) {
            if (valores[i] < valores[j]) {
                temp_val = valores[i];
                valores[i] = valores[j];
                valores[j] = temp_val;

                temp_jog = jogadores[i];
                jogadores[i] = jogadores[j];
                jogadores[j] = temp_jog;
            }
        }
    }
}

void Tabuleiro() {
	
    mapear_matriz();
    Linha_Tabuleiro_superior();
    printf("\n");

    for (i = 0; i < LINHAS; i++) {
        printf("                 %c", 186);
        for (j = 0; j < COLUNAS; j++) {
        	
            if (Matriz_tabuleiro[i][j] == 'A' || Matriz_tabuleiro[i][j] == 'B' || Matriz_tabuleiro[i][j] == 'C' || Matriz_tabuleiro[i][j] == 'D') {
                AZUL;
            } 
			else if (Matriz_tabuleiro[i][j] == 'E' || Matriz_tabuleiro[i][j] == 'F' || Matriz_tabuleiro[i][j] == 'G' || Matriz_tabuleiro[i][j] == 'H') {
            	VERMELHO;
            }
			else if (Matriz_tabuleiro[i][j] == 'I' || Matriz_tabuleiro[i][j] == 'J' || Matriz_tabuleiro[i][j] == 'K' || Matriz_tabuleiro[i][j] == 'L') {
                VERDE;
            } 
			else if (Matriz_tabuleiro[i][j] == 'M' || Matriz_tabuleiro[i][j] == 'N' || Matriz_tabuleiro[i][j] == 'O' || Matriz_tabuleiro[i][j] == 'P') {
                AMARELO;
            }

            if (j >= 0 && j < 14 && i >= 0 && i < 9) {
                BACKGROUND_AZUL;
            } 
			else if (j > 26 && j < 42 && i >= 0 && i < 9) {
                BACKGROUND_VERMELHO;
            } 
			else if (j >= 0 && j < 14 && i > 16 && i < 27) {
                BACKGROUND_VERDE;
            } 
			else if (j > 26 && j < 42 && i > 16 && i < 27) {
                BACKGROUND_AMARELO;
            }
            printf("%c", Matriz_tabuleiro[i][j]);
            BRANCO;
        }
        printf("%c\n", 186);
    }
    Linha_Tabuleiro_inferior();
}

void Tela_Vencedor() {
	linha_Menu_Superior();
	printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
	printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");                                                            
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                     Parabens Jogador %i Voce Venceu                     |\n" , Terminar.Jogador[pecas[peca_movimento].jogador]);
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");  
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");  
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
}

void capturar_peca(int num_peca) {
    int pos_inicial;
    
    if (num_peca >= 1 && num_peca <= 4) {
        pos_inicial = num_peca + 59;
        posicoes_matriz[63 + num_peca] = pecas[num_peca].letra;
    } else if (num_peca >= 5 && num_peca <= 8) {
        pos_inicial = num_peca + 59;
        posicoes_matriz[63 + num_peca] = pecas[num_peca].letra;
    } else if (num_peca >= 9 && num_peca <= 12) {
        pos_inicial = num_peca + 59;
        posicoes_matriz[63 + num_peca] = pecas[num_peca].letra;
    } else if (num_peca >= 13 && num_peca <= 16) {
        pos_inicial = num_peca + 59;
        posicoes_matriz[63 + num_peca] = pecas[num_peca].letra;
    }
    pecas[num_peca].posicao = pos_inicial;
    pecas[num_peca].posicaoInicial = 0;
}

int posicao_ocupada_por_adversario(int posicao, int num_peca) {
    for (i = 1; i <= 16; i++) {
        if (i != num_peca && pecas[i].posicao == posicao && pecas[i].jogador != pecas[num_peca].jogador) {
            return 1;
        }
    }
    return 0;
}

int posicao_ocupada_por_amigo(int posicao , int num_peca){
    for (i = 1; i <= 16; i++) {
        if (i != num_peca && pecas[i].posicao == posicao && pecas[i].jogador == pecas[num_peca].jogador) {
            return 1;
        }
    }
    return 0;
}

int encontrar_peca_na_posicao(int posicao) {
    for (i = 1; i <= 16; i++) {
        if (pecas[i].posicao == posicao) {
            return i;
        }
    }
    return -1;
}

void ordenar_pontuacoes(Jogador *p, int escolha_Jogador) {
    int i, j;
    Jogador temp;

    for (i = 0; i < escolha_Jogador; i++) {
        for (j = i + 1; j < escolha_Jogador; j++) {
            if (p[j].pontos > p[i].pontos) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void mover_pecas(int num_peca, int movimento) {
	
    char letras[] = "ABCDEFGHIJKLMNOP";
    int jogador = (num_peca - 1) / 4 + 1;
    pecas[num_peca].letra = letras[num_peca - 1];
    pecas[num_peca].jogador = jogador;

    if (pecas[num_peca].posicaoInicial == 0) {
        int posicoes_iniciais[] = {0, 11, 33, 22};
        pecas[num_peca].posicao = posicoes_iniciais[jogador - 1];
        posicoes_matriz[63 + num_peca] = ' ';
        pecas[num_peca].posicaoInicial = 1;
        posicoes_matriz[pecas[num_peca].posicao] = pecas[num_peca].letra;
    } 
	else {
        int pos_atual = pecas[num_peca].posicao;
        int nova_posicao = pos_atual + movimento;
        acumulador_jogadas[num_peca] += movimento;

        if (nova_posicao >= 44) {
            nova_posicao -= 44;
        }

        if (nova_posicao == 1 || nova_posicao == 12 || nova_posicao == 23 || nova_posicao == 34) {
            int controle = nova_posicao;

            if (nova_posicao < 24) {
                posicoes_matriz[nova_posicao] = '$';
                nova_posicao += 11;

                if ((pecas[num_peca].jogador == 2 && controle == 1) ||
                    (pecas[num_peca].jogador == 3 && controle == 23) ||
                    (pecas[num_peca].jogador == 4 && controle == 12)) {
                    acumulador_jogadas[num_peca] = 1;
                } 
				else {
                    acumulador_jogadas[num_peca] += 11;
                }
            } 
			else {
                posicoes_matriz[nova_posicao] = '$';
                nova_posicao = 1;

                if (pecas[num_peca].jogador == 1) {
                    acumulador_jogadas[num_peca] = 1;
                } 
				else {
                    acumulador_jogadas[num_peca] += 11;
                }
            }
        }

        if (posicao_ocupada_por_adversario(nova_posicao, num_peca)) {
        	
            int peca_adversaria = encontrar_peca_na_posicao(nova_posicao);
            if (nova_posicao == 0 || nova_posicao == 11 || nova_posicao == 22 || nova_posicao == 33 || nova_posicao == 6 || nova_posicao == 17 || nova_posicao == 28 || nova_posicao == 39 || nova_posicao == 32) {
                posicoes_matriz[pecas[num_peca].posicao] = pecas[peca_adversaria].letra;
            } 
			else {
                jogadores_cadastro[jogador - 1].pontos += 1;
                capturar_peca(peca_adversaria);
                acumulador_jogadas[peca_adversaria] = 0;
                gotoxy(60, 2);
                printf("Peça %c foi capturada e voltou para a posição inicial", pecas[peca_adversaria].letra);
                getch();
            }
        }

        if (acumulador_jogadas[num_peca] > 42) {
            posicoes_matriz[pecas[num_peca].posicao] = ' ';
            int nova_posicao_final = acumulador_jogadas[num_peca] - 42;
            if (nova_posicao_final <= 5) {
                posicoes_corredor_vitoria[pecas[num_peca].jogador][nova_posicao_final - movimento] = '.';
                posicoes_corredor_vitoria[pecas[num_peca].jogador][nova_posicao_final] = pecas[num_peca].letra;
                if (nova_posicao_final == 5) {
                	Terminar.Jogador[jogador] = 1;
                    Terminar.Peca[num_peca] = 1;
                    jogadores_cadastro[jogador - 1].pontos += 5;
                }
            } 
			else {
                acumulador_jogadas[num_peca] -= movimento;
                gotoxy(60, 1);
                printf("Tirou mais do que deveria, perdeu a vez");
                getch();
            }
        } 
		else {
	        if (posicao_ocupada_por_amigo(pos_atual, num_peca)) {
	            int peca_amigo = encontrar_peca_na_posicao(pos_atual);
	            posicoes_matriz[pos_atual] = pecas[peca_amigo].letra;
	            pecas[num_peca].posicao = nova_posicao;
	            posicoes_matriz[nova_posicao] = pecas[num_peca].letra;
	        }
	        else {
	        	if(pos_atual == 0 || pos_atual == 11 || pos_atual == 22 || pos_atual == 33){
		            posicoes_matriz[pos_atual] = '.';
		            pecas[num_peca].posicao = nova_posicao;
		            posicoes_matriz[nova_posicao] = pecas[num_peca].letra;        		
				}
				else if(pos_atual == 6 || pos_atual == 17 || pos_atual == 28 || nova_posicao == 39){
		            posicoes_matriz[pos_atual] = '*';
		            pecas[num_peca].posicao = nova_posicao;
		            posicoes_matriz[nova_posicao] = pecas[num_peca].letra;				
				}
				else if(pos_atual == 1 || pos_atual == 12 || pos_atual == 23 || pos_atual == 34){
		            posicoes_matriz[pos_atual] = '$';
		            pecas[num_peca].posicao = nova_posicao;
		            posicoes_matriz[nova_posicao] = pecas[num_peca].letra;	
				}
				else {
		            posicoes_matriz[pos_atual] = ' ';
		            pecas[num_peca].posicao = nova_posicao;
		            posicoes_matriz[nova_posicao] = pecas[num_peca].letra;
				}
			}
        }
    }
}

void Jogar_jogo() {
    srand(time(NULL));

    for (i = 0; i < 16; i++) {
        posicoes_matriz[64 + i] = 'A' + i;
    }
    for (i = 0; i < 17; i++) {
        Terminar.Peca[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        Terminar.Jogador[i] = 0;
    }

    int jogador_atual = 0;
    int peca_disponivel = 0;
    int peca_idx = 0;
    int peca_movimento;

    do {
        while (Terminar.Jogador[pecas[peca_idx].jogador] == 0) {
            system("cls");
            Tabuleiro();

            int numero_sorteado = (rand() % 6) + 1;
            gotoxy(60, 4 + jogador_atual);
            if(jogadores[jogador_atual] == 0){
            	AZUL;
	            printf("%s tirou no dado = %i", jogadores_cadastro[jogadores[jogador_atual]].Usuario, numero_sorteado);
			}
			else if(jogadores[jogador_atual] == 1){
				VERMELHO;
	            printf("%s tirou no dado = %i", jogadores_cadastro[jogadores[jogador_atual]].Usuario, numero_sorteado);	
			}
			else if(jogadores[jogador_atual] == 2){
				VERDE;
	            printf("%s tirou no dado = %i", jogadores_cadastro[jogadores[jogador_atual]].Usuario, numero_sorteado);
			}
			else {
				AMARELO;
	            printf("%s tirou no dado = %i", jogadores_cadastro[jogadores[jogador_atual]].Usuario, numero_sorteado);
			}
	        BRANCO;
	        getch();
            peca_disponivel = 0;

            // Verifica as peças disponíveis para mover
            for (i = 0; i < 4; i++) {
                peca_idx = (jogadores[jogador_atual]) * 4 + i + 1;
                if (pecas[peca_idx].posicaoInicial == 1 && Terminar.Peca[peca_idx] == 0) {
                    peca_disponivel = 1;
                    break;
                } 
				else if (numero_sorteado == 6 && pecas[peca_idx].posicaoInicial == 0) {
                    peca_disponivel = 1;
                    break;
                }
            }

            if (!peca_disponivel) {
                gotoxy(60, 1);
                printf("Nenhuma peca disponivel para mover", VERMELHO);
                getch();
                jogador_atual = (jogador_atual + 1) % escolha_Jogador;
                continue;
            }

            // Exibe as opções de peças para mover
            gotoxy(60, 8 + jogador_atual);
            printf("Pecas disponiveis para movimentar:");

            for (i = 0; i < 4; i++) {
                peca_idx = (jogadores[jogador_atual]) * 4 + i + 1;
                if (pecas[peca_idx].posicaoInicial == 1 && Terminar.Peca[peca_idx] == 0) {
                    gotoxy(60, 9 + jogador_atual + i);
                    printf("(%i = %c)", peca_idx, pecas[peca_idx].letra);
                } 
				else if (numero_sorteado == 6 && pecas[peca_idx].posicaoInicial == 0) {
                    gotoxy(60, 9 + jogador_atual + i);
                    printf("(%i = %c - Nova)", peca_idx, pecas[peca_idx].letra);
                }
            }

            gotoxy(60, 6 + jogador_atual);
            printf("Qual peca deseja movimentar ou ver regras (0 para regras): ");
            gotoxy(120, 6 + jogador_atual);
            scanf("%i", &peca_movimento);

            if (peca_movimento == 0) {
                system("cls");
                Tela_regras();
                getch();
                continue;
            }

            int peca_valida = 0;

            // Verifica se a entrada é um número válido
            if (peca_movimento >= 1 && peca_movimento <= 16) {
                peca_idx = peca_movimento;
                peca_valida = 1;
            }
			else {
                gotoxy(60, 23);
                printf("Entrada invalida. Perdeu a vez.", VERMELHO);
                Limpar_Buffer();
                getch();
                continue;
            }
            

            if ((peca_movimento >= 1 && peca_movimento <= 4 && pecas[peca_idx].posicaoInicial == 1 && jogadores[jogador_atual] == 0) ||
                (peca_movimento >= 5 && peca_movimento <= 8 && pecas[peca_idx].posicaoInicial == 1 && jogadores[jogador_atual] == 1) ||
                (peca_movimento >= 9 && peca_movimento <= 12 && pecas[peca_idx].posicaoInicial == 1 && jogadores[jogador_atual] == 2) ||
                (peca_movimento >= 13 && peca_movimento <= 16 && pecas[peca_idx].posicaoInicial == 1 && jogadores[jogador_atual] == 3)){
                	mover_pecas(peca_idx, numero_sorteado);
                	if (numero_sorteado == 6) {
                    	continue; // Jogador pode jogar novamente
                	}
            }
			else if((peca_movimento >= 1 && peca_movimento <= 4 && pecas[peca_idx].posicaoInicial == 0 && jogadores[jogador_atual] == 0 && numero_sorteado == 6) ||
	                (peca_movimento >= 5 && peca_movimento <= 8 && pecas[peca_idx].posicaoInicial == 0 && jogadores[jogador_atual] == 1 && numero_sorteado == 6) ||
	                (peca_movimento >= 9 && peca_movimento <= 12 && pecas[peca_idx].posicaoInicial == 0 && jogadores[jogador_atual] == 2 && numero_sorteado == 6) ||
	                (peca_movimento >= 13 && peca_movimento <= 16 && pecas[peca_idx].posicaoInicial == 0 && jogadores[jogador_atual] == 3 && numero_sorteado == 6)){
		                mover_pecas(peca_idx, numero_sorteado); // Move nova peça para o tabuleiro
		                continue; // Jogador pode jogar novamente
            } 
			else {
                gotoxy(60, 23);
                printf("Impossivel mover essa peça, Perdeu a vez", VERMELHO);
                Limpar_Buffer();
                getch();
            }

            jogador_atual = (jogador_atual + 1) % escolha_Jogador;
        }
    } while (Terminar.Jogador[pecas[peca_idx].jogador] == 0);

    system("cls");
    Tela_Vencedor();
    getch();
}

void Tela_Inicial() {
    printf("          _____            _____                    _____                   _______ \n");
    printf("         /\\    \\          /\\    \\                  /\\    \\                 /::\\    \\ \n");
    printf("        /::\\____\\        /::\\____\\                /::\\    \\               /::::\\    \\ \n");
    printf("       /:::/    /       /:::/    /               /::::\\    \\             /::::::\\    \\ \n");
    printf("      /:::/    /       /:::/    /               /::::::\\    \\           /::::::::\\    \\ \n");
    printf("     /:::/    /       /:::/    /               /:::/\\:::\\    \\         /:::/  \\:::\\    \\ \n");
    printf("    /:::/    /       /:::/    /               /:::/  \\:::\\    \\       /:::/    \\:::\\    \\ \n");
    printf("   /:::/    /       /:::/    /               /:::/    \\:::\\    \\     /:::/    / \\:::\\    \\ \n");
    printf("  /:::/    /       /:::/    /      _____    /:::/    / \\:::\\    \\   /:::/____/   \\:::\\____\\ \n");
    printf(" /:::/    /       /:::/____/      /\\    \\  /:::/    /   \\:::\\ ___\\ |:::|    |     |:::|    | \n");
    	printf("                                   A");
    	Sleep(200);
    	printf("P");
    	Sleep(200);
    	printf("E");
    	Sleep(200);
    	printf("R");
    	Sleep(200);
    	printf("T");
    	Sleep(200);
    	printf("E");
    	Sleep(200);
    	printf(" U");
    	Sleep(200);
    	printf("M");
    	Sleep(200);
        printf(" B");
    	Sleep(200);
    	printf("O");
    	Sleep(200);
    	printf("T");
    	Sleep(200);
    	printf("A");
    	Sleep(200);
    	printf("O\n");
    	Sleep(200);
    printf("\\:::\\    \\       |:::|____\\     /:::/    /\\:::\\    \\     /:::|____| \\:::\\    \\   /:::/    / \n");
    printf(" \\:::\\    \\       \\:::\\    \\   /:::/    /  \\:::\\    \\   /:::/    /   \\:::\\    \\ /:::/    / \n");
    printf("  \\:::\\    \\       \\:::\\    \\ /:::/    /    \\:::\\    \\ /:::/    /     \\:::\\    /:::/    / \n");
    printf("   \\:::\\    \\       \\:::\\    /:::/    /      \\:::\\    /:::/    /       \\:::\\__/:::/    / \n");
    printf("    \\:::\\    \\       \\:::\\__/:::/    /        \\:::\\  /:::/    /         \\::::::::/    / \n");
    printf("     \\:::\\    \\       \\::::::::/    /          \\:::\\/:::/    /           \\::::::/    / \n");
    printf("      \\:::\\    \\       \\::::::/    /            \\::::::/    /             \\::::/    / \n");
    printf("       \\:::\\____\\       \\::::/    /              \\::::/    /               \\::/____/ \n");
    printf("        \\::/    /        \\::/____/                \\::/____/                    \n");
    printf("         \\/____/                                                              \n");
    
}

void linha_Menu_Superior() {
	printf("                     %c" , 201);
	for(i=0; i<72; i++){
		printf("%c" , 205);
	}
	printf("%c" , 187);
}

void linha_Menu_Inferior() {
		printf("                     %c" , 200);
	for(i=0; i<72; i++){
		printf("%c" , 205);
	}
	printf("%c" , 188);
}

void Tela_Ranking(Jogador *p, int n) {
    int i;
    
    ordenar_pontuacoes(p, escolha_Jogador);
    // Imprime o cabeçalho do menu
    linha_Menu_Superior();
    printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
    printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                             RANKING                                    |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
    
    for (i = 0; i < n; i++) {
    	gotoxy(45, 12 + i);
        printf("%i. %s: %i pontos\n", i + 1, p[i].Usuario, p[i].pontos);
    }
    getch();
}

void Menu() {
	linha_Menu_Superior();
	printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
	printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");                                                          
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                          1. Jogar sem Cadastrar                        |\n");
    printf("                     |                          2. Cadastrar Jogador                          |\n");  
    printf("                     |                          3. Ajuda                                      |\n");
    printf("                     |                          4. Ranking                                    |\n");  
    printf("                     |                          5. Sair                                       |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
}

void Tela_Jogador() {
	linha_Menu_Superior();
	printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
	printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");                                                            
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                      Quantidade de Jogadores...                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                            2. Jogadores                                |\n");  
    printf("                     |                            3. Jogadores                                |\n");
    printf("                     |                            4. Jogadores                                |\n");  
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
}

void cadastrarJogador() {
    Limpar_Buffer();
    
    for(i = 0; i < escolha_Jogador; i++) {
    	gotoxy(40, 9 + i);
        printf("Digite o nome do jogador %i: ", i + 1);
        fgets(jogadores_cadastro[i].Usuario, 20, stdin);
        jogadores_cadastro[i].Usuario[strcspn(jogadores_cadastro[i].Usuario, "\n")] = '\0'; // Remover o '\n' do final da string
        jogadores_cadastro[i].pontos = 0; // Inicializa a pontuação do jogador
        Limpar_Buffer();
    }
    cadastrado = 1;
}

void cadastrarPontuacao() {
	system("cls");
    if (!cadastrado) {
		linha_Menu_Superior();
		printf("\n");        
	    printf("                     |                                                                        |\n");                     
	    printf("                     |                                                                        |\n");
		printf("                     |   _____                       __          _____              __        |\n");
	    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
	    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
	    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
	    printf("                     |                       |_____|                                          |\n");                                                            
	    printf("                     |                                                                        |\n");
	    printf("                     |                                                                        |\n");
	    printf("                     |                                                                        |\n");
	    printf("                     |                                                                        |\n");
	    printf("                     |              Nenhum jogador cadastrado. Realize o cadastro             |\n");  
	    printf("                     |                                                                        |\n");
	    printf("                     |                                                                        |\n");  
	    printf("                     |                                                                        |\n");
	    printf("                     |                                                                        |\n");
	    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();;
        return;
    }
    for (i = 0; i < escolha_Jogador; i++) {
        jogadores_cadastro[i].pontos += pontuacoes[i].Pontos;
    }
}

void Tela_cadastro() {
	linha_Menu_Superior();
	printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
	printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");                                                             
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");  
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
}

void Tela_ERRO() {
	linha_Menu_Superior();
	printf("\n");        
    printf("                     |                                                                        |\n");                     
    printf("                     |                                                                        |\n");
	printf("                     |   _____                       __          _____              __        |\n");
    printf("                     | _|     |.--.--..-----..-----.|  |.-----. |     |_ .--.--..--|  |.-----.|\n");
    printf("                     ||       ||  |  ||     ||  _  ||  ||  -__| |       ||  |  ||  _  ||  _  ||\n");
    printf("                     ||_______||_____||__|__||___  ||__||_____| |_______||_____||_____||_____||\n");
    printf("                     |                       |_____|                                          |\n");                                                             
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                           OPCAO INVALIDA                               |\n");
    printf("                     |                 Pressione qualquer tecla para voltar :)                |\n");  
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");  
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
}

void Tela_regras(){	
	linha_Menu_Superior();
    printf("\n");
    printf("                     |                            REGRAS                                      |\n");
    printf("                     |                                                                        |\n");
    printf("                     | 1- Os jogadores jogam em sentido horario.                              |\n");
    printf("                     | 2- Em cada turno, o jogador rola o dado e move uma peca de             |\n");
    printf("                     |    acordo com o numero que aparece.                                    |\n");
    printf("                     | 3- Uma peca so pode ser movida para fora do inicio apos                |\n");
    printf("                     |    rolar um 6.                                                         |\n");
    printf("                     | 4- Se um jogador rolar um 6, ele tem a opcao de mover uma              |\n");
    printf("                     |    peca ja em jogo ou comecar uma nova peca.                           |\n");
    printf("                     | 5- Se um jogador cair na casa '$$' vai para o '$$' seguinte,           |\n");
    printf("                     |    caso esse ultrapasse o caminho final, a peca terá que dar           |\n");
	printf("                     |    mais uma volta.                                                     |\n");
    printf("                     | 6- As pecas sao movidas em sentido horario ao longo do                 |\n");
    printf("                     |    percurso preenchido com '.' ate o meio do tabuleiro.                |\n");
    printf("                     | 7- Um jogador pode capturar uma peca adversaria movendo                |\n");
    printf("                     |    sua propria peca para o espaco ocupado pela peca                    |\n");
    printf("                     |    adversaria, enviando-a de volta ao inicio.                          |\n");
    printf("                     | 8- Se um jogador rolar um numero que levaria sua peca para             |\n");
    printf("                     |    a casa, ele deve exatamente alcancar a casa para entrar             |\n");
    printf("                     |    nela.                                                               |\n");
    printf("                     | 9- Se jogador deve rolar a sua peca para uma casa '**' ela             |\n");
    printf("                     |    não podera ser capturada, isso tambem vale para as casas            |\n");
    printf("                     |    '.' pecas tabem nao podem ser capturadas nessa casa.                |\n");
    printf("                     |10- O jogador que mover todas as quatro pecas para casa                 |\n");
    printf("                     |    primeiro vence o jogo.                                              |\n");
    printf("                     |11- Cada peca colocada no meio vale 5 pontos e cada peca                |\n");
	printf("                     |    captura 1 ponto.                                                    |\n");
	printf("                     |                                                                        |\n");
    linha_Menu_Inferior();
    getch();
}

void Tela_Saida() {
	printf("          _____            _____                    _____                   _______ \n");
    printf("         /\\    \\          /\\    \\                  /\\    \\                 /::\\    \\ \n");
    printf("        /::\\____\\        /::\\____\\                /::\\    \\               /::::\\    \\ \n");
    printf("       /:::/    /       /:::/    /               /::::\\    \\             /::::::\\    \\ \n");
    printf("      /:::/    /       /:::/    /               /::::::\\    \\           /::::::::\\    \\ \n");
    printf("     /:::/    /       /:::/    /               /:::/\\:::\\    \\         /:::/  \\:::\\    \\ \n");
    printf("    /:::/    /       /:::/    /               /:::/  \\:::\\    \\       /:::/    \\:::\\    \\ \n");
    printf("   /:::/    /       /:::/    /               /:::/    \\:::\\    \\     /:::/    / \\:::\\    \\ \n");
    printf("  /:::/    /       /:::/    /      _____    /:::/    / \\:::\\    \\   /:::/____/   \\:::\\____\\ \n");
    printf(" /:::/    /       /:::/____/      /\\    \\  /:::/    /   \\:::\\ ___\\ |:::|    |     |:::|    | \n");
    	printf("                                   A");
    	Sleep(200);
    	printf("D");
    	Sleep(200);
    	printf("E");
    	Sleep(200);
    	printf("U");
    	Sleep(200);
    	printf("S");
    	Sleep(200);
    	printf(" A");
    	Sleep(200);
    	printf("T");
    	Sleep(200);
    	printf("E");
    	Sleep(200);
        printf(" L");
    	Sleep(200);
    	printf("O");
    	Sleep(200);
    	printf("G");
    	Sleep(200);
    	printf("O");
    	Sleep(200);
    	printf(":)\n");
    	Sleep(200);
    printf("\\:::\\    \\       |:::|____\\     /:::/    /\\:::\\    \\     /:::|____| \\:::\\    \\   /:::/    / \n");
    printf(" \\:::\\    \\       \\:::\\    \\   /:::/    /  \\:::\\    \\   /:::/    /   \\:::\\    \\ /:::/    / \n");
    printf("  \\:::\\    \\       \\:::\\    \\ /:::/    /    \\:::\\    \\ /:::/    /     \\:::\\    /:::/    / \n");
    printf("   \\:::\\    \\       \\:::\\    /:::/    /      \\:::\\    /:::/    /       \\:::\\__/:::/    / \n");
    printf("    \\:::\\    \\       \\:::\\__/:::/    /        \\:::\\  /:::/    /         \\::::::::/    / \n");
    printf("     \\:::\\    \\       \\::::::::/    /          \\:::\\/:::/    /           \\::::::/    / \n");
    printf("      \\:::\\    \\       \\::::::/    /            \\::::::/    /             \\::::/    / \n");
    printf("       \\:::\\____\\       \\::::/    /              \\::::/    /               \\::/____/ \n");
    printf("        \\::/    /        \\::/____/                \\::/____/                    \n");
    printf("         \\/____/                                                              \n");
}

void mapear_matriz() {
	
	//posicoes inicias na SafeZone
	Matriz_tabuleiro[2][3] = posicoes_matriz[64];
	Matriz_tabuleiro[2][10] = posicoes_matriz[65];
	Matriz_tabuleiro[6][3] = posicoes_matriz[66];
	Matriz_tabuleiro[6][10] = posicoes_matriz[67];
	Matriz_tabuleiro[2][30] = posicoes_matriz[68];
	Matriz_tabuleiro[2][37] = posicoes_matriz[69];
	Matriz_tabuleiro[6][30] = posicoes_matriz[70];
	Matriz_tabuleiro[6][37] = posicoes_matriz[71];
	Matriz_tabuleiro[19][3] = posicoes_matriz[72];
	Matriz_tabuleiro[19][10] = posicoes_matriz[73];
	Matriz_tabuleiro[23][3] = posicoes_matriz[74];
	Matriz_tabuleiro[23][10] = posicoes_matriz[75];
	Matriz_tabuleiro[19][30] = posicoes_matriz[76];
	Matriz_tabuleiro[19][37] = posicoes_matriz[77];
	Matriz_tabuleiro[23][30] = posicoes_matriz[78];
	Matriz_tabuleiro[23][37] = posicoes_matriz[79];
	
	//posicoes no tabuleiro 
	Matriz_tabuleiro[10][4] = posicoes_matriz[0];
	Matriz_tabuleiro[10][7] = posicoes_matriz[1];
	Matriz_tabuleiro[10][10] = posicoes_matriz[2];
	Matriz_tabuleiro[10][13] = posicoes_matriz[3];
	Matriz_tabuleiro[8][16] = posicoes_matriz[4];
	Matriz_tabuleiro[6][16] = posicoes_matriz[5];
	Matriz_tabuleiro[4][16] = posicoes_matriz[6];
	Matriz_tabuleiro[2][16] = posicoes_matriz[7];
	Matriz_tabuleiro[0][16] = posicoes_matriz[8];
	Matriz_tabuleiro[0][20] = posicoes_matriz[9];
	Matriz_tabuleiro[0][24] = posicoes_matriz[10];
	Matriz_tabuleiro[2][24] = posicoes_matriz[11];
	Matriz_tabuleiro[4][24] = posicoes_matriz[12];
	Matriz_tabuleiro[6][24] = posicoes_matriz[13];
	Matriz_tabuleiro[8][24] = posicoes_matriz[14];
	Matriz_tabuleiro[10][28] = posicoes_matriz[15];
	Matriz_tabuleiro[10][31] = posicoes_matriz[16];
	Matriz_tabuleiro[10][34] = posicoes_matriz[17];
	Matriz_tabuleiro[10][37] = posicoes_matriz[18];
	Matriz_tabuleiro[10][40] = posicoes_matriz[19];
	Matriz_tabuleiro[13][40] = posicoes_matriz[20];
	Matriz_tabuleiro[15][40] = posicoes_matriz[21];
	Matriz_tabuleiro[15][37] = posicoes_matriz[22];
	Matriz_tabuleiro[15][34] = posicoes_matriz[23];
	Matriz_tabuleiro[15][31] = posicoes_matriz[24];
	Matriz_tabuleiro[15][28] = posicoes_matriz[25];
	Matriz_tabuleiro[17][24] = posicoes_matriz[26];
	Matriz_tabuleiro[19][24] = posicoes_matriz[27];
	Matriz_tabuleiro[21][24] = posicoes_matriz[28];
	Matriz_tabuleiro[23][24] = posicoes_matriz[29];
	Matriz_tabuleiro[25][24] = posicoes_matriz[30];
	Matriz_tabuleiro[25][20] = posicoes_matriz[31];
	Matriz_tabuleiro[25][16] = posicoes_matriz[32];
	Matriz_tabuleiro[23][16] = posicoes_matriz[33];
	Matriz_tabuleiro[21][16] = posicoes_matriz[34];
	Matriz_tabuleiro[19][16] = posicoes_matriz[35];
	Matriz_tabuleiro[17][16] = posicoes_matriz[36];
	Matriz_tabuleiro[15][13] = posicoes_matriz[37];
	Matriz_tabuleiro[15][10] = posicoes_matriz[38];
	Matriz_tabuleiro[15][7] = posicoes_matriz[39];
	Matriz_tabuleiro[15][4] = posicoes_matriz[40];
	Matriz_tabuleiro[15][1] = posicoes_matriz[41];
	Matriz_tabuleiro[12][1] = posicoes_matriz[42];
	Matriz_tabuleiro[10][1] = posicoes_matriz[43];
	
	// casas finais jogador 1
	Matriz_tabuleiro[12][4] = posicoes_corredor_vitoria[1][1];
	Matriz_tabuleiro[12][7] = posicoes_corredor_vitoria[1][2];
	Matriz_tabuleiro[12][10] = posicoes_corredor_vitoria[1][3];
	Matriz_tabuleiro[12][13] = posicoes_corredor_vitoria[1][4];
	Matriz_tabuleiro[12][16] = posicoes_corredor_vitoria[1][5]; // casa central no tabuleiro
	
	// casas finais jogador 2
	Matriz_tabuleiro[2][20] = posicoes_corredor_vitoria[2][1];
	Matriz_tabuleiro[4][20] = posicoes_corredor_vitoria[2][2];
	Matriz_tabuleiro[6][20] = posicoes_corredor_vitoria[2][3];
	Matriz_tabuleiro[8][20] = posicoes_corredor_vitoria[2][4];
	Matriz_tabuleiro[10][20] = posicoes_corredor_vitoria[2][5]; // casa central no tabuleiro
	
	// casas finais jogador 3
	Matriz_tabuleiro[23][20] = posicoes_corredor_vitoria[3][1];
	Matriz_tabuleiro[21][20] = posicoes_corredor_vitoria[3][2];
	Matriz_tabuleiro[19][20] = posicoes_corredor_vitoria[3][3];
	Matriz_tabuleiro[17][20] = posicoes_corredor_vitoria[3][4];
	Matriz_tabuleiro[15][20] = posicoes_corredor_vitoria[3][5]; // casa central no tabuleiro
	
	// casas finais jogador 4
	Matriz_tabuleiro[12][37] = posicoes_corredor_vitoria[4][1];
	Matriz_tabuleiro[12][34] = posicoes_corredor_vitoria[4][2];
	Matriz_tabuleiro[12][31] = posicoes_corredor_vitoria[4][3];
	Matriz_tabuleiro[12][28] = posicoes_corredor_vitoria[4][4];
	Matriz_tabuleiro[12][25] = posicoes_corredor_vitoria[4][5]; // casa central no tabuleiro
}

void Setar_Posicoes() {
	for (i = 0; i <= 79; i++) {
		if(i==0 || i==11 || i==22 || i==33){
			posicoes_matriz[i] = '.';	
		}
		else if(i==1 || i==12 || i==23 || i==34){
			posicoes_matriz[i] = '$';
		}
		else if(i==6 || i==17 || i==28 || i==39){
			posicoes_matriz[i] = '*';
		}
		else {
			posicoes_matriz[i] = ' ';
		}
	}
	
	for(i = 0; i< 5; i++){
		for(j= 0; j<6;j++){
			if(j == 5){
				posicoes_corredor_vitoria[i][j] = ' ';
			}
			else {
				posicoes_corredor_vitoria[i][j] = '.';	
			}
		}
	}
	
	for(i=0; i<18; i++){
		acumulador_jogadas[i] = 0;
	}
		
	pecas[0].posicao = posicoes_matriz[64];
	pecas[0].posicaoInicial = 0;
	pecas[1].posicao = posicoes_matriz[65];
	pecas[1].posicaoInicial = 0;
	pecas[2].posicao = posicoes_matriz[66];
	pecas[2].posicaoInicial = 0;
	pecas[3].posicao = posicoes_matriz[67];
	pecas[3].posicaoInicial = 0;
	pecas[4].posicao = posicoes_matriz[68];
	pecas[4].posicaoInicial = 0;
	pecas[5].posicao = posicoes_matriz[69];
	pecas[5].posicaoInicial = 0;
	pecas[6].posicao = posicoes_matriz[70];
	pecas[6].posicaoInicial = 0;
	pecas[7].posicao = posicoes_matriz[71];
	pecas[7].posicaoInicial = 0;
	pecas[8].posicao = posicoes_matriz[72];
	pecas[8].posicaoInicial = 0;
	pecas[9].posicao = posicoes_matriz[73];
	pecas[9].posicaoInicial = 0;
	pecas[10].posicao = posicoes_matriz[74];
	pecas[10].posicaoInicial = 0;
	pecas[11].posicao = posicoes_matriz[75];
	pecas[11].posicaoInicial = 0;
	pecas[12].posicao = posicoes_matriz[76];
	pecas[12].posicaoInicial = 0;
	pecas[13].posicao = posicoes_matriz[77];
	pecas[13].posicaoInicial = 0;
	pecas[14].posicao = posicoes_matriz[78];
	pecas[14].posicaoInicial = 0;
	pecas[15].posicao = posicoes_matriz[79];
	pecas[15].posicaoInicial = 0;
	
}

main() {
	
    Setar_Posicoes();
    int escolha_Menu = 0;
    char Usuario[50];
    char Senha[12];

    Tela_Inicial();
    getch();

    do {
        escolha_Menu = 0;
        system("cls");
        Menu();
        gotoxy(34, 11);
        scanf("%i", &escolha_Menu);

        switch (escolha_Menu) {

            case 1:
                system("cls");
                Tela_Jogador();
                scanf("%i", &escolha_Jogador);

                if (escolha_Jogador >= 2 && escolha_Jogador <= 4) {
                    sprintf(jogadores_cadastro[0].Usuario, "Jogador 1");
                    sprintf(jogadores_cadastro[1].Usuario, "Jogador 2");
                    sprintf(jogadores_cadastro[2].Usuario, "Jogador 3");
                    sprintf(jogadores_cadastro[3].Usuario, "Jogador 4");
				    
                    system("cls");
                    sortear_num();
                    Vez_Jogadas();
                    
                    Setar_Posicoes();
					
                    gotoxy(80, 11);
                    Jogar_jogo();
                    break;
                } 
				else {
                    system("cls");
                    Tela_ERRO();
                    Limpar_Buffer();
                    getch();
                    break;
                }

            case 2:
                system("cls");
                Tela_Jogador();
                scanf("%i", &escolha_Jogador);
                
                if (escolha_Jogador >= 2 && escolha_Jogador <= 4) {
                
	                system("cls");
	                Tela_cadastro();
	                Limpar_Buffer();
	                cadastrarJogador();
	                getch();
	                
                    system("cls");
                    sortear_num();
                    Vez_Jogadas();
                    
                    Setar_Posicoes();
                    gotoxy(80, 11);
                    Jogar_jogo();
                    break;
                } 
				else {
                    system("cls");
                    Tela_ERRO();
                    Limpar_Buffer();
                    getch();
                    break;
                }

            case 3:
                system("cls");
                Tela_regras();
                getch();
                break;

            case 4:
                system("cls");
                cadastrarPontuacao(escolha_Jogador);
                if(cadastrado == 1){
                	Tela_Ranking(jogadores_cadastro, escolha_Jogador);
				}
                getch();
                break;

            case 5:
                system("cls");
                Tela_Saida();
                getch();
                break;
                
            default:
                system("cls");
                Tela_ERRO();
                Limpar_Buffer();
                getch();
                break;
        }
    } while (escolha_Menu != 5);
}
