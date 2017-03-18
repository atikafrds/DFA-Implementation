#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

const int BrsMax = 100;
const int KolMax = 100;
const int BrsMin = 0;
const int KolMin = 0;
const int MaxInput = 10;
const int blank = -999;

int main()
{
    /* KAMUS GLOBAL */
    FILE *fileku;
    int NSymbol, NState, NFState, NInput;
    int initState, inFState, inState;
    int fstateTab[KolMax];
    int tabstates[BrsMax][KolMax];
    long int masukan;
    int arrInput[MaxInput];
    int stateNow, stateAfter;
    int i, j, idx;
    boolean inputFound, stateFound, fstateFound;

    /* ALGORITMA */
    fileku = fopen("dfa.txt", "r"); /* membuka file dengan nama fisik dfa.txt */
    fscanf(fileku, "%d", &NSymbol); /* membaca jumlah simbol dari file eksternal */
    fscanf(fileku, "%d", &NState); /* membaca jumlah state dari file eksternal */
    fscanf(fileku, "%d", &NFState); /* membaca jumlah final state dari file eksternal */
    fscanf(fileku, "%d", &initState); /* membaca start state dari file eksternal */
    /* memindahkan semua final state ke array final state */
    for (i = 1; i <= NFState; i++)
    {
        fscanf(fileku, "%d", &inFState);
        fstateTab[i] = inFState;
    }
    /* memindahkan tabel transisi dari file eksternal ke array tabstates */
    for (i = BrsMin; i <= NState; i++)
    {
        for (j = KolMin; j <= NSymbol; j++)
        {
            fscanf(fileku, "%d", &inState);
            tabstates[i][j] = inState;
        }
        getc(fileku);
    }
    /* menutup file */
    fclose(fileku);
    /* mencetak informasi mengenai DFA ke layar */
    printf("\n");
    printf("   -----------------------   \n");
    printf("     DFA VENDING MACHINE\n");
    printf("   -----------------------   \n");
    printf("\n");
    /* Q, semua state */
    printf("Q = ");
    for (i = 1; i <= NState-1; i++)
    {
        printf("q%d, ", tabstates[i][KolMin]);
    }
    printf("q%d\n", tabstates[NState][KolMin]);
    printf("\n");
    /* sigma, semua simbol yang diterima */
    printf("Sigma = {");
    for (j = 1; j <= NSymbol-1; j++)
    {
        printf("%d, ", tabstates[BrsMin][j]);
    }
    printf("%d}\n", tabstates[BrsMin][NSymbol]);
    printf("\n");
    /* Start state */
    printf("Start state = q%d\n", initState);
    printf("\n");
    /* Final state */
    printf("Final state = ");
    for(i = 1; i <= NFState-1; i++)
    {
        printf("q%d, ", fstateTab[i]);
    }
    printf("q%d\n", fstateTab[NFState]);
    printf("\n");
    /* Transition table */
    printf("     TRANSITION TABLE\n");
    printf("\n");
    for (j = KolMin; j <= NSymbol-1; j++)
    {
        if (tabstates[BrsMin][j] == blank)
        {
            printf("     | ");
        }
        else
        {
            printf("%d | ", tabstates[BrsMin][j]);
        }
    }
    printf("%d\n", tabstates[BrsMin][NSymbol]);
    for (i = BrsMin+1; i <= NState; i++)
    {
        for (j = KolMin; j <= (NSymbol-1); j++)
        {
            printf("q%d   | ", tabstates[i][j]);
        }
        printf("q%d\n", tabstates[i][NSymbol]);
    }
    printf("\n");
    /* Menerima input dari pengguna */
    printf("Masukkan input : ");
    NInput = 0;
    scanf("%d", &masukan);
    while ((masukan != 0) && (NInput <= MaxInput)) /* pembacaan input diakhiri ketika input berupa angka 0 */
    {
        NInput += 1;
        arrInput[NInput] = masukan; /* menyimpan input di sebuah array of integer arrInput */
        scanf("%d", &masukan);
    }
    /* UPDATE NILAI STATE DAN MENCETAK TRANSISI */
    stateNow = initState; /* state awal selalu q0 */
    for (idx = 1; idx <= NInput; idx++) /* proses transisi state dengan traversal untuk semua input yang diterima */
    {
        i = 1;
        stateFound = false;
        while ((i <= NState) && !(stateFound)) /* searching indeks tempat state terletak */
        {
            if (stateNow == tabstates[i][KolMin])
            {
                stateFound = true;
            }
            else
            {
                i++;
            }
        }
        j = 1;
        inputFound = false;
        while ((j <= NSymbol) && !(inputFound)) /* searching indeks tempat simbol terletak */
        {
            if (arrInput[idx] == tabstates[BrsMin][j])
            {
                inputFound = true;
            }
            else
            {
                j++;
            }
        }
        stateAfter = tabstates[i][j]; /* state hasil transisi di dapat dari matriks pada indeks yang telah dicari sebelumnya */
        printf("delta(q%d, %d) = q%d\n", stateNow, arrInput[idx], stateAfter); /* cetak proses transisi */
        stateNow = stateAfter; /* perubahan state sekarang setelah transisi */
    }
    /* MENENTUKAN APAKAH INPUT DARI PENGGUNA BERAKHIR DI FINAL STATE */
    fstateFound = false;
    i = 1;
    while ((i <= NFState) && !(fstateFound))
    {
        if (stateNow == fstateTab[i])
        {
            fstateFound = true;
        }
        else
        {
            i++;
        }
    }
    if (fstateFound)
    {
        printf("Input mencapai final state.\n");
    }
    else
    {
        printf("Input tidak mencapai final state.\n");
    }
    return 0;
}
