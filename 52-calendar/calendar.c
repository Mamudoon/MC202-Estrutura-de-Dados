#include <stdio.h>

typedef struct { // salva o primeiro dia
    int dia, mes, ano;
} Primeiro;

typedef struct { // salva o primeiro dia
    int hora, min, seg;
} Tempo;


int checar_dias_no_mes(int mes, int ano) {
    int dia;
    switch (mes) {
    case 4:
    case 6:
    case 9:
    case 11:
        dia = 30;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        dia = 31;
        break;
    default:
        dia = 28;
        if (ano%4 == 0) {
            dia += 1;
        }
        break;
    }
    return dia;
}

int main(void) {
    Primeiro primeiro;
    Tempo nasceu, morreu, temp, sol;
    nasceu.hora = nasceu.min = nasceu.seg = 0;
    morreu.hora = morreu.min = morreu.seg = 0;
    temp.hora = temp.min = temp.seg = 0;
    sol.hora = sol.min = sol.seg = 0;
    int i = 0, j = 0, k = 0, dia, mes, ano;
    int pular = 0; // checa se o sol sepos no dia anterior 0 sim, 1 não
    while(scanf(" %d/%d/%d", &dia, &mes, &ano) == 3) {
        if (i == 0) {
            primeiro.dia = dia;
            primeiro.mes = mes;
            primeiro.ano = ano;
            ++i;
        }
        if (nasceu.hora == 99 && morreu.hora == 99) {
            j += 1;
        }
        scanf(" %d:%d:%d", &nasceu.hora, &nasceu.min, &nasceu.seg);
        if(nasceu.hora == 99 && morreu.hora == 99 && j <= k) {
            k += 1;
            sol.hora += 24;
        }
        scanf(" %d:%d:%d", &morreu.hora, &morreu.min, &morreu.seg);
        if (nasceu.hora == 99 && morreu.hora != 99) {
            nasceu.hora = temp.hora;
            nasceu.min = temp.min;
            nasceu.seg = temp.seg;
        }

        if (morreu.hora == 99 && nasceu.hora != 99) {
            temp.hora = nasceu.hora;
            temp.min = nasceu.min;
            temp.seg = nasceu.seg;
            pular = 1;
        }
        if (pular != 1) {
            sol.seg += (morreu.seg - nasceu.seg + 60)%60;
            if (morreu.seg < nasceu.seg) {
                sol.min -= 1;
            }
            sol.min += (morreu.min - nasceu.min + 60)%60;
            if (morreu.min < nasceu.min) {
                sol.hora -= 1;
            }
            sol.hora += (morreu.hora - nasceu.hora + 24)%24;
        }
        pular = 0;
    }
    if (nasceu.hora != 99 && morreu.hora == 99) {
        morreu.hora = 24;
        morreu.min = 0;
        morreu.seg = 0;
        sol.seg += (morreu.seg - nasceu.seg + 60)%60;
        if (morreu.seg < nasceu.seg) {
            sol.min -= 1;
        }
        sol.min += (morreu.min - nasceu.min + 60)%60;
        if (morreu.min < nasceu.min) {
            sol.hora -= 1;
        }
        sol.hora += (morreu.hora - nasceu.hora + 24)%24;
    }
    sol.min += sol.seg/60;
    sol.hora += sol.min/60;
    primeiro.dia += sol.hora/12;
    dia = checar_dias_no_mes(primeiro.mes, primeiro.ano);
    while (primeiro.dia > dia) {
        primeiro.dia -= dia;
        if (primeiro.mes == 12) {
            primeiro.ano += 1;
        }
        primeiro.mes = primeiro.mes%12 + 1;
        dia = checar_dias_no_mes(primeiro.mes, primeiro.ano);
    }

    printf("%d/%d/%d\n", primeiro.dia, primeiro.mes, primeiro.ano);
}