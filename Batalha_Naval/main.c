#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void limpa_ecra();

void menu(char tabuleiro[15][15][2], char frota[15][15][2], int *dim);
void menu_subopcao1(char tabuleiro[15][15][2], char frota[15][15][2],int *dim);
void menu_subopcao2(char tabuleiro[15][15][2], char frota[15][15][2], int dim, int p, int nj);
void menu_subopcao3(char tabuleiro[15][15][2], char frota[15][15][2], int dim);

void limpar_matriz (char aux[15][15][2], int dim, int nj);
void desenha_matriz (char aux[15][15][2], int dim, int nj);

void desenha_barcos(char frota[15][15][2], int dim, int p, int orientacao, int tamanho, char caracter, int nj);

int gera_orientacao();
int gera_coordenadas(int dim);
int verifica_orientacao();

void posi_frota(char frota[15][15][2], int dim, int p, int nj);

void jogar(char tabuleiro[15][15][2], char frota[15][15][2], int dim, int p, int nj);
void jogar2(char tabuleiro[15][15][2], char frota[15][15][2], int dim, int p, int nj);

int main()
{
    char tabuleiro[15][15][2], frota[15][15][2];

    int dim=12;

    /*para gerar números aleatórios*/
    srand(time(NULL));

    /*Chamada do menu inicial e submenus*/
    menu(tabuleiro,frota,&dim);

    return 0;
}

void limpa_ecra()
{
    system("CLS");
}

void menu(char tabuleiro[15][15][2], char frota[15][15][2],int *dim)
{
    char opcao;
    int p=1;
    int nj=0;

    do
    {
        /*MENU INICIAL*/
        printf("\n\t\t\t\tBatalha Naval\n");
        printf("\tMenu\n");
        printf("\n1 - Configuracoes\n");
        printf("\n2 - Jogador contra Computador\n");
        printf("\n3 - Jogador contra Jogador\n");
        printf("\n4 - Sair\n\n");
        scanf(" %c",&opcao);

        switch(opcao)
        {
        case '1':
            limpa_ecra();
            menu_subopcao1(tabuleiro, frota, dim);
            break;
        case '2':
            limpa_ecra();
            menu_subopcao2(tabuleiro,frota, *dim,p,nj);
            break;
        case '3':
            limpa_ecra();
            menu_subopcao3(tabuleiro,frota, *dim);
            break;
        case '4':
            printf("\n\t\t\t\tA sair...\n");
            break;
        default:
            limpa_ecra();
            printf("%c? Escolha invalida\n\n", opcao);
            break;
        }
    }
    while (opcao!='4');
}

void menu_subopcao1(char tabuleiro[15][15][2], char frota[15][15][2],int *dim)
{
    char subopcao1,dificuldade;

    do
    {
        printf("\n\t\t\t\tConfiguracoes\n\n");

        printf("\n1 - Dificuldade (Facil - F; Normal - N; Dificil - D):\n");
        printf("\n2 - Voltar ao menu anterior\n\n");
        scanf(" %c",&subopcao1);

        switch (subopcao1)
        {
        case '1': /*escolhendo a dificuldade do jogo, escolhe também a dimensão do tabuleiro*/
            scanf(" %c", &dificuldade);
            dificuldade = toupper(dificuldade);
            if (dificuldade == 'F')
            {
                limpa_ecra();
                *dim=10;
            }
            else if (dificuldade =='N')
            {
                limpa_ecra();
                *dim=12;
            }
            else if (dificuldade =='D')
            {
                limpa_ecra();
                *dim=15;
            }
            else
                printf("%c? Escolha invalida\n\n", dificuldade);
            break;
        case '2': /*volta ao menu anterior*/

            limpa_ecra();
            break;
        default:
            limpa_ecra();
            printf("%c? Escolha invalida\n\n", subopcao1);
            break;
        }
    } while (subopcao1!= '2');
}

void menu_subopcao2(char tabuleiro[15][15][2], char frota[15][15][2], int dim, int p, int nj)
{
    char subopcao2;
    char posicionamento;

    do
    {
        printf("\n\t\t\t\tJogador contra Computador\n\n");

        printf("\n1 - Posicionamento da Frota (Automatico - A; Manual - M):\n");
        printf("\n2 - Voltar ao menu anterior\n\n");
        scanf(" %c",&subopcao2);

        switch (subopcao2)
        {
        case '1': /*escolha do tipo do posicionamento*/
            scanf(" %c", &posicionamento);
            posicionamento = toupper(posicionamento);
            if (posicionamento == 'A')
            {
                limpa_ecra();
                p=1;
                posi_frota(frota,dim,p,0);
                system("PAUSE");
            }
            else if (posicionamento =='M')
            {
                limpa_ecra();
                p=2;
                posi_frota(frota,dim,p,0);
            }
            else
                printf("%c? Escolha invalida\n\n", posicionamento);
            /*limpa_ecra();*/
            posi_frota(frota,dim,1,1); /*Cria Frota do Computador*/
            limpa_ecra();
            printf("\t\t## Jogador contra Computador ##\n\n");

            jogar(tabuleiro,frota,dim,p,0);
            break;
        case '2': /*volta ao menu anterior*/
            limpa_ecra();
            break;
        default:
            limpa_ecra();
            printf("%c? Escolha invalida\n\n", subopcao2);
            break;
        }
    }
    while (subopcao2!= '2');
}

void menu_subopcao3(char tabuleiro[15][15][2], char frota[15][15][2], int dim)
{
    char subopcao3;
    char posicionamento;
    int p=1, nj=0;
    do
    {
        printf("\n\t\t\t\tJogador contra Jogador:\n\n");

        printf("\n1 - Posicionamento da Frota\n");
        printf("\n2 - Voltar ao menu anterior\n\n");
        scanf(" %c", &subopcao3);

        switch (subopcao3)
        {
            case '1':
                limpa_ecra();
                printf("\n\t\tJogador 1\n");
                printf("\nPosicionamento da Frota (Automatico - A; Manual - M):\n\n");
                do
                {
                    scanf(" %c", &posicionamento);
                    posicionamento = toupper(posicionamento);
                } while (posicionamento != 'A' && posicionamento != 'M');

                    if (posicionamento == 'A')
                    {
                        limpa_ecra();
                        p=1;
                        printf("\n\t->Frota Jogador 1<-\n");
                        posi_frota(frota,dim,p,0);
                    }
                    else if (posicionamento =='M')
                    {
                        limpa_ecra();
                        p=2;
                        printf("\n\t->Frota Jogador 1<-\n");
                        posi_frota(frota,dim,p,0);
                    }

                system("PAUSE");
                limpa_ecra();
                printf("\n\t\tJogador 2\n");
                printf("\nPosicionamento da Frota (Automatico - A; Manual - M):\n\n");
                do
                {
                    scanf(" %c", &posicionamento);
                    posicionamento = toupper(posicionamento);
                } while (posicionamento != 'A' && posicionamento != 'M');

                if (posicionamento == 'A')
                {
                    limpa_ecra();
                    p=1;
                    printf("\n\t->Frota Jogador 2<-\n");
                    posi_frota(frota,dim,p,1);
                }
                else if (posicionamento =='M')
                {
                    limpa_ecra();
                    p=2;
                    printf("\n\t->Frota Jogador 2<-\n");
                    posi_frota(frota,dim,p,1);
                }

                system("PAUSE");
                limpa_ecra();
                printf("\n\t\t## Jogador contra Jogador ##\n\n");
                jogar(tabuleiro,frota,dim,p,nj);
                break;
            case '2':
                limpa_ecra();
                break;
            default:
                limpa_ecra();
                printf("%c? Escolha invalida\n", subopcao3);
                break;
        }
    } while (subopcao3 != '2');
}

void limpar_matriz (char aux[15][15][2], int dim, int nj)
{
    int x,y;

    for (x=0; x<=dim; x++) /*limpa as posições da matriz criada*/
    {
        for (y=0; y<=dim; y++)
        {
            aux[x][y][nj] = ' ';
        }
    }
}

void desenha_matriz (char aux[15][15][2], int dim, int nj)
{
    int x,y;
    char pos;

    printf("     | ");

    for(x=0; x<dim; x++) /*imprime as letras do tabuleiro*/
    {
        printf("[%c]", 65+x);
    }
    printf(" | \n");
    for(y=1; y<=dim; y++) /*imprime os números do tabuleiro*/
    {
        printf("[%02d]", y);
        printf(" | ");
        for (pos=0; pos<dim; pos++)
        {
            printf(" %c ",aux[pos][y][nj]); /*imprime as posições para posteriormente poderem ser acedidas*/
        }
        printf(" |\n");
    }
}

void desenha_barcos(char frota[15][15][2], int dim, int p, int orientacao, int tamanho, char caracter, int nj)
{
    int i,x,y;
    char x1;

    do
    {
        if (p==1)
        {
            x = gera_coordenadas(dim);
            y = gera_coordenadas(dim) +1;
        }
        else
        {
            do
            {
                printf("Letra: ");
                scanf(" %c",&x1);

                x1=toupper(x1);
                x=x1-65;
            }
            while (x<0 || x>=dim);   /*verifica se a letra está dentro dos limites*/

            do
            {
                printf("Numero: ");
                scanf("%d",&y);
            }
            while (y<1 || y>dim);   /*verifica se o número está dentro dos limites*/
        }
        if (p!= 1) /* não há necessidade de no posicionamento automático mostrar o "ERRO" */
            printf("Barco fora do tabuleiro!\n");
    }
    while((x-1 + tamanho) >= dim || (y-1 + tamanho) >= dim);   /* validação para verificar se o barco se encontra dentro do tabuleiro...*/

    if (orientacao==1) /* vertical*/
    {
        for (i=0; i<tamanho; i++)
        {
            if(frota[x][y+i][nj] == ' ') /*verifica se a posição já está ocupada*/
                {
                    frota[x][y+i][nj] = caracter;
                }
        }
    }
    else /*horizontal*/
    {
        for (i=0; i<tamanho; i++)
        {
            if(frota[x+i][y][nj] == ' ') /*verifica se a posição já está ocupada*/
                {
                    frota[x+i][y][nj] = caracter;
                }

        }
    }
}

int gera_orientacao()
{
    int orienta;
    orienta = rand() % 2;
    return orienta;
}

int gera_coordenadas(int dim)
{
    int coordenadas;

    coordenadas = rand() % dim;
    return coordenadas;
}

int verifica_orientacao()
{
    char v_h;
    int orienta;

    do
    {
        printf("Orientacao (Vertical - V ou Horizontal - H\n");
        scanf(" %c",&v_h);
        v_h = toupper(v_h);
    }
    while (v_h != 'V' && v_h != 'H');

    if (v_h == 'V')
    {
        orienta = 1;
    }
    else if (v_h == 'H')
    {
        orienta = 0;
    }
    return orienta;
}

void posi_frota(char frota[15][15][2], int dim, int p, int nj)
{
    int orienta;

    limpar_matriz(frota,dim,nj);

    if (p==1)
    {
        printf("\n\t\t\t\tPosicionamento automatico\n\n");

        /*Inserir 1 Porta-Avioes*/
        orienta = gera_orientacao();
        desenha_barcos(frota,dim,p,orienta,5,'P',nj);/*Porta-Aviões*/

        /*Inserir 2 Submarinos*/

        orienta =gera_orientacao();
        desenha_barcos(frota,dim,p,orienta,4,'S',nj);/*Submarino 1*/

        orienta =gera_orientacao();
        desenha_barcos(frota,dim,p,orienta,4,'T',nj);/*Submarino 2*/

        /*Inserir 3 Destroyers*/
        orienta = gera_orientacao();
        desenha_barcos(frota,dim,p,orienta,3,'D',nj);/*Destroyer 1*/
        desenha_barcos(frota,dim,p,orienta,3,'E',nj);/*DEstroyer 2*/
        desenha_barcos(frota,dim,p,orienta,3,'F',nj);/*Destroyer 3*/

        /*Inserir 4 Botes*/
        orienta = gera_orientacao();
        desenha_barcos(frota,dim,p,orienta,1,'L',nj);/*Bote 1*/
        desenha_barcos(frota,dim,p,orienta,1,'M',nj);/*Bote 2*/
        desenha_barcos(frota,dim,p,orienta,1,'N',nj);/*Bote 3*/
        desenha_barcos(frota,dim,p,orienta,1,'O',nj);/*Bote 4*/

        desenha_matriz(frota,dim,nj);
    }
    else
    {
        printf("\t\tPosicionamento manual\n\n");

        desenha_matriz(frota,dim,nj);
        printf("\n");

        /*Inserir 1 Porta-Avioes*/
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,5,'P',nj);/*Porta-Aviões*/
        desenha_matriz(frota,dim,nj);

        /*Inserir 2 Submarinos*/
        printf("Submarino numero: 1\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,4,'S',nj);/*Submarino 1*/
        printf("Submarino numero: 2\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,4,'T',nj);/*Submarino 2*/
        desenha_matriz(frota,dim,nj);

        /*Inserir 3 Destroyers*/
        printf("Destroyer numero: 1\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,3,'D',nj);/*Destroyer 1*/
        printf("Destroyer numero: 2\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,3,'E',nj);/*Destroyer 2*/
        printf("Destroyer numero: 3\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,3,'F',nj);/*Destroyer 3*/
        desenha_matriz(frota,dim,nj);

        /*Inserir 4 Botes*/
        printf("Bote numero: 1\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,1,'L',nj);/*Bote 1*/
        printf("Bote numero: 2\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,1,'M',nj);/*Bote 2*/
        printf("Bote numero: 3\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,1,'N',nj);/*Bote 3*/
        printf("Bote numero: 4\n");
        orienta = verifica_orientacao();
        desenha_barcos(frota,dim,p,orienta,1,'O',nj);/*Bote 4*/
        desenha_matriz(frota,dim,nj);

    }
}

void jogar(char tabuleiro[15][15][2], char frota[15][15][2], int dim, int p, int nj)
{
    /* recebe como valores as definições escolhidas para iniciar o jogo, por exemplo: dificuldade , posicionamento*/
    int x,y;
    char x1;
    /* contador para verificar se um barco foi ao fundo ou não*/
    int ct_PA = 0, ct_SB1 = 0, ct_SB2 = 0, ct_DT1 = 0, ct_DT2 = 0, ct_DT3 = 0, ct_BT1 = 0, ct_BT2 = 0, ct_BT3 = 0, ct_BT4 = 0;
    /*contador para ver se todos os barcos foram ao fundo ou não*/
    int PA_total = 0, SB_total = 0, DT_total = 0, BT_total = 0,  PS_total = 26;

    int numero_jogadas = 0, numero_abatidos = 0;

    limpar_matriz(tabuleiro,dim,nj);

    while(PS_total != 0)
    {
        printf("\nTabuleiro Jogador %d\n",nj+1);
        desenha_matriz(tabuleiro,dim,nj);
        printf("\n");

        do
        {
            printf("Letra: ");
            scanf(" %c",&x1);

            x1=toupper(x1);
            x=x1-65;
        }
        while (x<0 || x>=dim);   /*verifica se a letra está dentro dos limites*/

        do
        {
            printf("Numero: ");
            scanf("%d",&y);
        }
        while (y<1 || y>dim);   /*verifica se o número está dentro dos limites*/


        if (tabuleiro[x][y][0] == 'X' || tabuleiro[x][y][0] == '0') /*verifica se a coordenada introduzida é repetida ou não*/
        {
            printf("\t\t##Coordenada Repetida##\a\a\n");
            numero_jogadas += 1;
            system("PAUSE");
        }
        else if (frota[x][y][1] == 'P') /*verifica se as coordenadas dadas pelo utilizador correspondem a alguma da frota, tendo acertado ou falhado*/
        {
            tabuleiro[x][y][0]= 'X';

            ct_PA += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'S')
        {
            tabuleiro[x][y][0] = 'X';

            ct_SB1 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'T')
        {
            tabuleiro[x][y][0] = 'X';

            ct_SB2 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'D')
        {
            tabuleiro[x][y][0] = 'X';

            ct_DT1 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }

        else if (frota[x][y][1] == 'E')
        {
            tabuleiro[x][y][0] = 'X';

            ct_DT2 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'F')
        {
            tabuleiro[x][y][0] = 'X';

            ct_DT3 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'L')
        {
            tabuleiro[x][y][0] = 'X';

            ct_BT1 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'M')
        {
            tabuleiro[x][y][0] = 'X';

            ct_BT2 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'N')
        {
            tabuleiro[x][y][0] = 'X';

            ct_BT3 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][1] == 'O')
        {
            tabuleiro[x][y][0] = 'X';

            ct_BT4 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else
        {
            tabuleiro[x][y][nj] = '0';

            numero_jogadas += 1;

            desenha_matriz(tabuleiro,dim,nj);
        }

        /*Vai acumulando o número de tiros certos em cada barco*/
        if(ct_PA == 5)
        {
            printf("\nDestruiu o Porta-Avioes\n");
            numero_abatidos += 1;
            PA_total += 1;
        }
        else if(ct_SB1 == 4)
        {
            printf("\nDestruiu o Submarino 1\n");
            numero_abatidos += 1;
            SB_total += 1;
        }
        else if(ct_SB2 == 4)
        {
            printf("\nDestruiu o Submarino 2\n");
            numero_abatidos += 1;
            SB_total += 1;
        }
        else if(ct_DT1 == 3)
        {
            printf("\nDestruiu o Destroyer 1\n");
            numero_abatidos += 1;
            DT_total += 1;
        }
        else if(ct_DT2 == 3)
        {
            printf("\nDestruiu o Destroyer 2\n");
            numero_abatidos += 1;
            DT_total += 1;
        }
        else if(ct_DT3 == 3)
        {
            printf("\nDestruiu o Destroyer 3\n");
            numero_abatidos += 1;
            DT_total += 1;
        }
        else if(ct_BT1 == 1)
        {
            printf("\nDestruiu o Bote 1\n");
            numero_abatidos += 1;
            BT_total += 1;
        }
        else if(ct_BT2 == 1)
        {
            printf("\nDestruiu o Bote 2\n");
            numero_abatidos += 1;
            BT_total += 1;
        }
        else if(ct_BT3 == 1)
        {
            printf("\nDestruiu o Bote 3\n");
            numero_abatidos += 1;
            BT_total += 1;
        }
        else if(ct_BT4 == 1)
        {
            printf("\nDestruiu o Bote 4\n");
            numero_abatidos += 1;
            BT_total += 1;
        }

        printf("\n\t\t## Numero de jogadas: %d ##\n",numero_jogadas);
        printf("\n\t\t## Em 10 Barcos ja abateu: %d ##\n",numero_abatidos);
        printf("\n\t\t## Tiros para acabar o jogo: %d ##\n",PS_total);

        if(PA_total == 1 && SB_total == 2 && DT_total == 3 && BT_total == 4)
        {
            printf("\nParabens! O jogador %d ganhou!\n",nj);
            printf("\nDestruiu toda a frota inimiga\n");
            printf("\nNumero de jogadas total: %d\n", numero_jogadas);
        }

        jogar2(tabuleiro,frota,dim,p,1);
    }
}

void jogar2(char tabuleiro[15][15][2], char frota[15][15][2], int dim, int p, int nj)
{
    /* recebe como valores as definições escolhidas para iniciar o jogo, por exemplo: dificuldade , posicionamento*/
    int x,y;
    char x1;
    /* contador para verificar se um barco foi ao fundo ou não*/
    int ct_PA = 0, ct_SB1 = 0, ct_SB2 = 0, ct_DT1 = 0, ct_DT2 = 0, ct_DT3 = 0, ct_BT1 = 0, ct_BT2 = 0, ct_BT3 = 0, ct_BT4 = 0;
    /*contador para ver se todos os barcos foram ao fundo ou não*/
    int PA_total = 0, SB_total = 0, DT_total = 0, BT_total = 0,  PS_total = 26;

    int numero_jogadas = 0, numero_abatidos = 0;

    limpar_matriz(tabuleiro,dim,nj);

    while(PS_total != 0)
    {
        printf("\nTabuleiro Jogador %d\n",nj+1);
        desenha_matriz(tabuleiro,dim,nj);
        printf("\n");

        do
        {
            printf("Letra: ");
            scanf(" %c",&x1);

            x1=toupper(x1);
            x=x1-65;
        }
        while (x<0 || x>=dim);   /*verifica se a letra está dentro dos limites*/

        do
        {
            printf("Numero: ");
            scanf("%d",&y);
        }
        while (y<1 || y>dim);   /*verifica se o número está dentro dos limites*/


        if (tabuleiro[x][y][1] == 'X' || tabuleiro[x][y][1] == '0') /*verifica se a coordenada introduzida é repetida ou não*/
        {
            printf("\t\t##Coordenada Repetida##\a\a\n");
            numero_jogadas += 1;
            system("PAUSE");
        }
        else if (frota[x][y][0] == 'P') /*verifica se as coordenadas dadas pelo utilizador correspondem a alguma da frota, tendo acertado ou falhado*/
        {
            tabuleiro[x][y][1]= 'X';

            ct_PA += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'S')
        {
            tabuleiro[x][y][1] = 'X';

            ct_SB1 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'T')
        {
            tabuleiro[x][y][1] = 'X';

            ct_SB2 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'D')
        {
            tabuleiro[x][y][1] = 'X';

            ct_DT1 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }

        else if (frota[x][y][0] == 'E')
        {
            tabuleiro[x][y][1] = 'X';

            ct_DT2 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'F')
        {
            tabuleiro[x][y][1] = 'X';

            ct_DT3 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'L')
        {
            tabuleiro[x][y][1] = 'X';

            ct_BT1 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'M')
        {
            tabuleiro[x][y][1] = 'X';

            ct_BT2 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'N')
        {
            tabuleiro[x][y][1] = 'X';

            ct_BT3 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else if (frota[x][y][0] == 'O')
        {
            tabuleiro[x][y][1] = 'X';

            ct_BT4 += 1;
            numero_jogadas += 1;
            PS_total -= 1;

            printf("\a");
            desenha_matriz(tabuleiro,dim,nj);
        }
        else
        {
            tabuleiro[x][y][0] = '0';

            numero_jogadas += 1;

            desenha_matriz(tabuleiro,dim,nj);
        }

        /*Vai acumulando o número de tiros certos em cada barco*/
        if(ct_PA == 5)
        {
            printf("\nDestruiu o Porta-Avioes\n");
            numero_abatidos += 1;
            PA_total += 1;
        }
        else if(ct_SB1 == 4)
        {
            printf("\nDestruiu o Submarino 1\n");
            numero_abatidos += 1;
            SB_total += 1;
        }
        else if(ct_SB2 == 4)
        {
            printf("\nDestruiu o Submarino 2\n");
            numero_abatidos += 1;
            SB_total += 1;
        }
        else if(ct_DT1 == 3)
        {
            printf("\nDestruiu o Destroyer 1\n");
            numero_abatidos += 1;
            DT_total += 1;
        }
        else if(ct_DT2 == 3)
        {
            printf("\nDestruiu o Destroyer 2\n");
            numero_abatidos += 1;
            DT_total += 1;
        }
        else if(ct_DT3 == 3)
        {
            printf("\nDestruiu o Destroyer 3\n");
            numero_abatidos += 1;
            DT_total += 1;
        }
        else if(ct_BT1 == 1)
        {
            printf("\nDestruiu o Bote 1\n");
            numero_abatidos += 1;
            BT_total += 1;
        }
        else if(ct_BT2 == 1)
        {
            printf("\nDestruiu o Bote 2\n");
            numero_abatidos += 1;
            BT_total += 1;
        }
        else if(ct_BT3 == 1)
        {
            printf("\nDestruiu o Bote 3\n");
            numero_abatidos += 1;
            BT_total += 1;
        }
        else if(ct_BT4 == 1)
        {
            printf("\nDestruiu o Bote 4\n");
            numero_abatidos += 1;
            BT_total += 1;
        }

        printf("\n\t\t## Numero de jogadas: %d ##\n",numero_jogadas);
        printf("\n\t\t## Em 10 Barcos ja abateu: %d ##\n",numero_abatidos);
        printf("\n\t\t## Tiros para acabar o jogo: %d ##\n",PS_total);

        if(PA_total == 1 && SB_total == 2 && DT_total == 3 && BT_total == 4)
        {
            printf("\nParabens! O jogador %d ganhou!\n",nj);
            printf("\nDestruiu toda a frota inimiga\n");
            printf("\nNumero de jogadas total: %d\n", numero_jogadas);
        }
        nj=0;
    }
}
