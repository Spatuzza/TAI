
//hola
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int dice[5] = {0};
int jugadas;

void efect() {
    int i;
    srand(time(NULL));
    // Simulando el efecto de la ruleta
    for(i = 0; i < 20; i++) {
        printf("%d   %d   %d   %d   %d\r", (rand() % 5) + 1, (rand() % 5) + 1, (rand() % 5) + 1, (rand() % 5) + 1, (rand() % 5) + 1, (rand() % 5) + 1);
        fflush(stdout);
        usleep(100000);
    }
    printf("\r");
    
}
int gen_dice(){
    printf("los dados sacados son:\n");
    printf("A   B   C   D   E  \n");
    efect();
    printf("\r");
    printf("%d   %d   %d   %d   %d",dice[0],dice[1],dice[2],dice[3],dice[4]);
}

void reval_dice(){
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i <= 5; i++){
        if(dice[i] == 0){
            dice[i] = (rand() % 6) + 1;
    }
    }
}

int val_dice()
{
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < 5; i++){
        dice[i] = (rand() % 6) + 1;
    }
}

int selec(){
    time_t t;
    srand((unsigned) time(&t));
    char s;
    char sel;
    int cant_d;
    int exit = 0;
    jugadas = 0;
    while(jugadas != 2)
    {
        exit = 0;
        while(cant_d <= 5 && !exit){
            cant_d = 1;
            printf("\ningrese el numero de letra del dado que desea volver a lanzar \nX para terminar la jugada\n");
            scanf("%c",&sel);
            // lee y descarta todos los caracteres en el buffer de entrada hasta que encuentra el carácter de nueva línea
            while(getchar() != '\n');
            // Corrovoramos que sea una letra valida sino hacemos que la vuelva a ingresar
            if (sel != 'A' && sel != 'B' && sel != 'C' && sel != 'D' && sel != 'E'&& sel != 'X') {
                printf("[ERROR]\nPor favor, ingrese una letra valida.\n");
                continue;
            }
            switch(sel) {
            case 'A':
                dice[0] = 0;
                break;
            case 'B':
                dice[1] = 0;
                break;
            case 'C':
                dice[2] = 0;
                break;
            case 'D':
                dice[3] = 0;
                break;
            case 'E':
                dice[4] = 0;
                break;
            }
            reval_dice();
            cant_d++;
            if(sel == 'X'){
                exit = 1;
            }
        }
        jugadas++;
        printf("\n[la nueva tirada]\n");
        gen_dice();
        if(jugadas != 2){
            printf("\n\nA usted le queda %d Jugadas\n",2-jugadas);
            printf("si desea continuar presione enter si no presione cualquier otra tecla....\n\n");
            s = getchar();
            if(s != '\n'){
                break;
            }else{
                system("cls");
            }
        }
    }
    return 0;
}

int main(){
    val_dice();
    gen_dice();
    selec();
}
