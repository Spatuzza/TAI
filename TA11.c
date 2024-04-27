/*
JUEGO ✓
REGLAS ✓ 
ANOTADOR X
IA X
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int jugador_1[11] ={0};
int jugador_2[11] ={0};
bool serv = true;
int dice[5] = {0};
int jugadas;
int cont[6] = {0};

int test(){
    dice[0] = 1;
    dice[1] = 3;
    dice[2] = 3;
    dice[3] = 3;
    dice[4] = 3;
}


int _1_6(){
    memset(cont, 0, sizeof(cont));
        for(int i = 0; i<= 4; i++){
            if(dice[i] == 1){
                cont[0] = cont[0] + 1;
            }
            else if(dice[i] == 2){
                cont[1] = cont[1] + 1;
            }
            else if(dice[i] == 3){
                cont[2] = cont[2] + 1;
            }
            else if(dice[i] == 4){
                cont[3] = cont[3] + 1;
            }
            else if(dice[i] == 5){
                cont[4] = cont[4] + 1;
            }
            else if(dice[i] == 6){
                cont[5] = cont[5] + 1;
            }
        }
        for(int i = 0; i<= 5; i++){
            if(cont[i]>1){
                printf("\ntenes un %d , deseas anotarlo?",i+1);
            }
        }
}

int dob(){
    //cont[i] == 2 && flag == 1
    int dob;
    int dob_2;
    int flag = 0;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 2 && flag == 1){
            dob = i;
            flag = 2;
        }
        else if(cont[i] == 2 && flag == 0){
            dob_2 = i;
            flag = 1;
        }
    }
    if(flag == 2){
        printf("\ntenemos doble!");
    }
}

int stair_(){
    int st = false;
    // escalera normal
    int p = dice[0];
    for(int i = 1; i<= 4; i++){
        if(dice[i] > p){
            p = dice[i];
            st = true;
        }else{
            st = false;
            break;
        }
    }
    //escalera a alas
    if(dice[0] == 3 && dice[1] == 4 && dice[2] == 5 && dice[3] == 6 && dice[4] == 1){
        st = true;
    }
    if(st == true){
        printf("\ntenemos escalera");
        return 1;
    }
    return 0;
}

int Full(){
    int full = 0;
    int full_2 = 0;
    int flag = 0;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 3){
            full = i;
            flag = flag + 1;
        }
        if(cont[i] == 2){
            full_2 = i;
            flag = flag + 1;
        }
    }
    if(flag == 2){
        printf("\ntenemos Full!");
    }
}

int poker(){
    int pok = 0;
    bool flag = false;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 4){
            pok = i;
            flag = true;
            break;
        }
    }
    if(flag == true){
        printf("\ntenemos poker!");
    }
}

int generala(){
    int gener ;
    bool flag = false;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 5){
            gener = i;
            flag = true;
            break;
        }
    }
    if(flag == true){
        printf("\ntenemos GENERALA!");
    }
}

int nonserv(){
    _1_6();
    dob();
    stair_();
    Full();
    poker();
    generala();
}

int control_serv(){
    serv = true;
    for (int i = 0; i < 4; i++){
        if(dice[i] != 0){
            serv = false;
            break;
        }
    }
}

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

void reval_dice_0(){
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
    int exit= 0;
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
            cant_d++;
            }
            if(sel == 'X'){
                exit = 1;
            }
        }
        control_serv();
        reval_dice_0();
        jugadas++;
        //gen_dice();
        if(jugadas != 2){
            printf("\n\nA usted le queda %d Jugadas\n",2-jugadas);
            printf("si desea continuar presione enter si no presione cualquier otra tecla y enter....\n\n");
            s = getchar();
            if(s != '\n'){
                gen_dice();
                break;
            }else{
                printf("\n[la nueva tirada]\n");
                gen_dice();
            }
        }else{
            gen_dice();
        }
    }
    return 0;
}

int main(){
    //val_dice();
    test();
    gen_dice();
    selec();
    nonserv();
}