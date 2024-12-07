#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef WIERSZE
#define WIERSZE 8
#endif
#ifndef KOLUMNY
#define KOLUMNY 8
#endif
#ifndef DLUGOSC
#define DLUGOSC 5
#endif

bool pionpoziom(char plansza[][KOLUMNY], int w, int k, bool pion) {
    int pocz, kon;
    bool weszlo;
    bool sprawdzone = false;
    if (pion) {
        pocz = w - DLUGOSC + 1;
        kon = w;
    }
    else {
        pocz = k - DLUGOSC + 1;
        kon = k;
    }
    for (; pocz <= w && kon < (pion == true ? WIERSZE : KOLUMNY) && !sprawdzone; pocz ++, kon++) {
        if (pocz < 0) {
            continue;
        }
        weszlo = false;
        int x = pocz;
        int y = kon;
        while (x < y && (sprawdzone || !weszlo)) {
            weszlo = true;
            sprawdzone = true;
            if (pion) {
                if (plansza[x][k] != plansza[y][k] || plansza[x][k] == '-') {
                    sprawdzone = false;
                }
            }
            else {
                if (plansza[w][x] != plansza[w][y] || plansza[w][x] == '-') {
                    sprawdzone = false;
                }
            }
            x++;
            y--;
        }
    }
    return sprawdzone;
}

bool skos(char plansza[][KOLUMNY], int w, int k, bool lgora) {
    int pocz_w;
    int k_w;
    int pocz_k;
    int k_k;
    bool sprawdzone = false;
    bool weszlo;
    if (lgora) {
        pocz_w = w - DLUGOSC + 1;
        k_w = w;
        pocz_k = k - DLUGOSC + 1;
        k_k = k;
    }
    else {
        pocz_w = w + DLUGOSC - 1;
        k_w = w;
        pocz_k = k - DLUGOSC + 1;
        k_k = k;
    }
    for (; (lgora ? (pocz_w <= w) : (pocz_w >= w))  && pocz_k <= k && k_w < WIERSZE && k_k < KOLUMNY && !sprawdzone;
        pocz_w++, pocz_k++, k_k++, k_w++) {
        if (pocz_w < 0 || pocz_k < 0)
            continue;
        weszlo = false;
        int xw = pocz_w;
        int yw = k_w;
        int xk = pocz_k;
        int yk = k_k;
        if (lgora) {
            while (xw < yw && xk < yk && (sprawdzone || !weszlo)) {
                weszlo = true;
                sprawdzone = true;
                if (plansza[xw][xk] != plansza[yw][yk] || plansza[xw][xk] == '-') {
                    sprawdzone = false;
                }
                xk++;
                xw++;
                yw--;
                yk--;
            }
        }
        else {
            while (xw > yw && xk < yk && (sprawdzone || !weszlo)) {
                weszlo = true;
                sprawdzone = true;
                if (plansza[xw][xk] != plansza[yw][yk] || plansza[xw][xk] == '-') {
                    sprawdzone = false;
                }
                xk++;
                xw--;
                yw++;
                yk--;
            }
        }
    }
    return sprawdzone;
}


// czy palindrom
bool palindrom(char plansza[][KOLUMNY], int w, int k) {
    return pionpoziom(plansza, w, k, true) || pionpoziom(plansza, w, k, false)
        || skos(plansza, w, k, true) || skos(plansza, w, k, false);
}

// wypisz plansze
bool wypisz(char plansza[][KOLUMNY], int w, int k, int gracz) {
    for (int i = 0; i < WIERSZE; i++) {
        for (int j = 0; j < KOLUMNY; j++) {
            printf(" %c", plansza[i][j]);
        }
        printf("\n");
    }
    for (int x = 0; x < KOLUMNY; x++)
    {
        printf(" %c", x + 'a');
    }
    printf("\n");
     if (palindrom(plansza, w, k)) {
        printf("%i!\n", gracz);
        return false;
    }
    else {
        gracz = gracz % 2 + 1;
        printf("%i:", gracz);
        return true;
    }

}

// ruch gracza
bool ruch(int gracz, char plansza[][KOLUMNY], char dane) {
    int kolumna = dane - 'a';
    int i = WIERSZE - 1;

    while (i > 0 && plansza[i][kolumna] != '-') {
        i--;
    }
    plansza[i][kolumna] = (char)gracz + '0';

    return wypisz(plansza, i, kolumna, gracz);
}

int main() {
    int gracz = 1;
    char plansza[WIERSZE][KOLUMNY];
    for (int i = 0; i < WIERSZE; i++) {
        for (int j = 0; j < KOLUMNY; j++) {
            plansza[i][j] = '-';
            printf(" %c", plansza[i][j]);
        }
        printf("\n");
    }
    for (int x = 0; x < KOLUMNY; x++)
    {
        printf(" %c", x + 'a');
    }
    printf("\n%i:", gracz);
    char c = (char)getchar();
    bool wygrana = false;
    while (c != '.' && !wygrana) {
        getchar();
        wygrana = !ruch(gracz, plansza, c);
        gracz = gracz % 2 + 1;
        if (!wygrana) {
            c = (char)getchar();
            printf("\n");
        }
    }

    return 0;
}