#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 64

char funzioneScelta[][MAXLEN] = {"cos(x)", "sin(x)", "sqrt(x)", "log(x)", "exp(x)"};

// funzioni matematiche da integrare
float coseno(float);
float seno(float);
float radQuad(float);
float logaritmo(float);
float esp(float);

// funzioni per il calcolo dell'integrale
float puntoMedio(float (*)(float), float, float, int);
float cavalieriSimpson(float (*)(float), float, float, int);

void main() {
    char scelta[MAXLEN], A[MAXLEN], B[MAXLEN], ACC[MAXLEN];
    float a, b, acc, tmp;
    float in, i2n, im, i2m;
    int n, m, s;

    printf("Programma per il calcolo del valore di un integrale usando il metodo del punto medio ed il metodo di Cavalieri/Simpson.\n");
    printf("Quale funzione si desidera valutare? (digitare il numero corrispondente)\n"
            "1. cos(x)\n"
            "2. sin(x)\n"
            "3. sqrt(x)\n"
            "4. log(x)\n"
            "5. exp(x)\n");
    printf("> ");
    // verifica che l'opzione scelta sia valida
    do {
        scanf("%s", scelta);
        if(atoi(scelta) < 1 || atoi(scelta) > 5) {
            printf("Inserire un numero da 1 a 5.\n");
            printf("> ");
        }
    } while(atoi(scelta) < 1 || atoi(scelta) > 5);
    s = atoi(scelta);

    do {
        // verifica che il primo estremo sia valido
        printf("Inserire il primo estremo:\n");
        printf("> ");
        do {
            scanf("%s", A);
            a = strtof(A, NULL);
            if(strcmp(A, "0") == 0)
                break;
            if(a == 0.0F) {
                printf("Inserire un numero.\n");
                printf("> ");
            }
        } while(a == 0.0F);

        // verifica che il secondo estremo sia valido
        printf("Inserire il secondo estremo:\n");
        printf("> ");
        do {
            scanf("%s", B);
            b = strtof(B, NULL);
            if(strcmp(B, "0") == 0)
                break;
            if(b == 0.0F) {
                printf("Inserire un numero.\n");
                printf("> ");
            }
        } while(b == 0.0F); 
        // verifica che gli estremi non siano uguali
        if(a == b) {
            printf("Gli estremi devono essere diversi.\n");
        } 
    } while(a == b);
    // scambia gli estremi
    if (a > b) {
        tmp = a;
        a = b;
        b = tmp;
    }

    // verifica che il l'accuratezza sia valida
    printf("Inserire l'accuratezza:\n");
    printf("> ");
    do {
        scanf("%s", ACC);
        acc = strtof(ACC, NULL);
        if(acc <= 0.0F) {
            printf("Inserire un numero positivo.\n");
            printf("> ");
        }
    } while(acc <= 0.0F);

    // calcolo con il metodo del punto medio
    n = 1;
    while(1) {
        switch(s) {
            case 1:
                in = puntoMedio(coseno, a, b, n);
                i2n = puntoMedio(coseno, a, b, 2*n);
                break;
            case 2:
                in = puntoMedio(seno, a, b, n);
                i2n = puntoMedio(seno, a, b, 2*n);
                break;
            case 3:
                in = puntoMedio(radQuad, a, b, n);
                i2n = puntoMedio(radQuad, a, b, 2*n);
                break;
            case 4:
                in = puntoMedio(logaritmo, a, b, n);
                i2n = puntoMedio(logaritmo, a, b, 2*n);
                break;
            case 5:
                in = puntoMedio(esp, a, b, n);
                i2n = puntoMedio(esp, a, b, 2*n);
                break;
        }     
        if((fabs(in-i2n) < acc))
            break;
        n = 2*n;
    } 
    printf("L'integrale di %s calcolato con il metodo del punto medio (%d sottointervalli) vale %f.\n", funzioneScelta[s-1], n, i2n);

    // calcolo con il metodo Cavalieri-Simpson
    m = 2;
    while(1) {
        switch(s) {
            case 1:
                im  = cavalieriSimpson(coseno, a, b, m);
                i2m = cavalieriSimpson(coseno, a, b, 2*m);
                break;
            case 2:
                im = cavalieriSimpson(seno, a, b, m);
                i2m = cavalieriSimpson(seno, a, b, 2*m);
                break;
            case 3:
                im = cavalieriSimpson(radQuad, a, b, m);
                i2m = cavalieriSimpson(radQuad, a, b, 2*m);
                break;
            case 4:
                im = cavalieriSimpson(logaritmo, a, b, m);
                i2m = cavalieriSimpson(logaritmo, a, b, 2*m);
                break;
            case 5:
                im = cavalieriSimpson(esp, a, b, m);
                i2m = cavalieriSimpson(esp, a, b, 2*m);
                break;
        }  
        if((fabs(im-i2m) < acc))
            break;
        m = 2*m;
    }
    printf("L'integrale di %s calcolato con il metodo di Cavalieri/Simpson (%d sottointervalli) vale %f.\n", funzioneScelta[s-1], m, i2m);
}

float coseno(float x) {
    return cos(x);
}

float seno(float x) {
    return sin(x);
}

float radQuad(float x) {
    return sqrt(x);
}

float logaritmo(float x) {
    return log(x);
}

float esp(float x) {
    return exp(x);
}

float puntoMedio(float funzione(float), float a, float b, int n) {
    float somma = 0.;
    float h, x_i, x_i1;

    h = (b-a)/n;
    for (int i = 0; i < n; i++) {
        x_i = a+i*h;
        x_i1 = x_i+h;
        somma = somma + funzione((x_i+x_i1)/2);
    }
    somma = somma*h;
    return somma;
}

float cavalieriSimpson(float funzione(float), float a, float b, int m) {
    float somma = 0.;
    float h, x_i;

    h = (b-a)/m;
    for (int i = 0; i <= m; i++) {
        x_i = a+i*h;
        if (i == 0 || i == m)
            somma = somma + funzione(x_i);
        else {
            if (i%2 == 0)
                somma = somma + 2*funzione(x_i); 
            else
                somma = somma + 4*funzione(x_i);
        }
    }

    somma = somma*h/3;
    return somma;
}