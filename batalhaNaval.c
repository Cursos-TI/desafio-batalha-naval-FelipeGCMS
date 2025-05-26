#include <stdio.h>

int main() {
    /* 1) Cria e inicializa o tabuleiro 10×10 com água (0) */
    int tabuleiro[10][10];
    int linha, coluna;
    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 0;
        }
    }

    /* 2) Posiciona quatro navios de tamanho 3 */
    int tamanhoNavio = 3;
    /* Navio horizontal */
    int linhaNavH = 1, colNavH = 1;
    /* Navio vertical */
    int linhaNavV = 4, colNavV = 7;
    /* Navio diagonal principal (↓→) */
    int linhaNavD1 = 2, colNavD1 = 3;
    /* Navio diagonal secundária (↓←) */
    int linhaNavD2 = 6, colNavD2 = 8;

    int d;
    /* Marca navios no tabuleiro (valor 3) */
    for (d = 0; d < tamanhoNavio; d++) {
        tabuleiro[linhaNavH][colNavH + d] = 3;
        tabuleiro[linhaNavV + d][colNavV] = 3;
        tabuleiro[linhaNavD1 + d][colNavD1 + d] = 3;
        tabuleiro[linhaNavD2 + d][colNavD2 - d] = 3;
    }

    /* 3) Define matrizes de área de efeito (5×5) */
    int areaCone[5][5];
    int areaCruz[5][5];
    int areaOctaedro[5][5];
    int meio = 2;  /* centro das matrizes 5×5 */

    /* 3.1) Constroi área de cone (topo no meio, expandindo para baixo) */
    for (linha = 0; linha < 5; linha++) {
        for (coluna = 0; coluna < 5; coluna++) {
            /* só as 3 primeiras linhas formam o cone */
            if (linha < 3 &&
                coluna >= meio - linha &&
                coluna <= meio + linha) {
                areaCone[linha][coluna] = 1;
            } else {
                areaCone[linha][coluna] = 0;
            }
        }
    }

    /* 3.2) Constroi área de cruz (linha e coluna centrais) */
    for (linha = 0; linha < 5; linha++) {
        for (coluna = 0; coluna < 5; coluna++) {
            if (linha == meio || coluna == meio) {
                areaCruz[linha][coluna] = 1;
            } else {
                areaCruz[linha][coluna] = 0;
            }
        }
    }

    /* 3.3) Constroi área de octaedro (losango) */
    for (linha = 0; linha < 5; linha++) {
        for (coluna = 0; coluna < 5; coluna++) {
            int dLinha = linha - meio;
            int dColuna = coluna - meio;
            if (dLinha < 0) dLinha = -dLinha;
            if (dColuna < 0) dColuna = -dColuna;
            /* soma das distâncias ≤ meio gera o losango */
            if (dLinha + dColuna <= meio) {
                areaOctaedro[linha][coluna] = 1;
            } else {
                areaOctaedro[linha][coluna] = 0;
            }
        }
    }

    /* 4) Pontos de origem no tabuleiro para cada habilidade */
    int origConeLin = 2, origConeCol = 7;
    int origCruzLin = 3, origCruzCol = 2;
    int origOctLin  = 7, origOctCol  = 4;

    /* 5) Sobrepõe cada área de efeito ao tabuleiro, marcando com 5 */
    for (linha = 0; linha < 5; linha++) {
        for (coluna = 0; coluna < 5; coluna++) {
            int alvoLin, alvoCol;

            /* cone */
            if (areaCone[linha][coluna] == 1) {
                alvoLin = origConeLin + (linha - meio);
                alvoCol = origConeCol + (coluna - meio);
                if (alvoLin >= 0 && alvoLin < 10 &&
                    alvoCol >= 0 && alvoCol < 10) {
                    tabuleiro[alvoLin][alvoCol] = 5;
                }
            }

            /* cruz */
            if (areaCruz[linha][coluna] == 1) {
                alvoLin = origCruzLin + (linha - meio);
                alvoCol = origCruzCol + (coluna - meio);
                if (alvoLin >= 0 && alvoLin < 10 &&
                    alvoCol >= 0 && alvoCol < 10) {
                    tabuleiro[alvoLin][alvoCol] = 5;
                }
            }

            /* octaedro */
            if (areaOctaedro[linha][coluna] == 1) {
                alvoLin = origOctLin + (linha - meio);
                alvoCol = origOctCol + (coluna - meio);
                if (alvoLin >= 0 && alvoLin < 10 &&
                    alvoCol >= 0 && alvoCol < 10) {
                    tabuleiro[alvoLin][alvoCol] = 5;
                }
            }
        }
    }

    /* 6) Exibe o tabuleiro com:
        0 = água
        3 = navio
        5 = área de habilidade
    */
    /* cabeçalho de colunas */
    printf("   ");
    for (coluna = 0; coluna < 10; coluna++) {
        printf("%2d ", coluna);
    }
    printf("\n");

    /* cada linha */
    for (linha = 0; linha < 10; linha++) {
        printf("%2d ", linha);
        for (coluna = 0; coluna < 10; coluna++) {
            printf(" %d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}