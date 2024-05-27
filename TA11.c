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

int jugadas;

bool full= false;
bool dob = false;
bool st = false;
bool pok= false;
bool gener= false;
bool gener_dob = false;
bool serv = true;
bool jug1_full = false;
bool jug2_full = false;

int interv;
int dice[5] = {0};
int cont[6] = {0};

int jugador_2[11] ={0};
int jugador_1[11] ={0};

int test(){
    dice[0] = 1;
    dice[1] = 1;
    dice[2] = 1;
    dice[3] = 1;
    dice[4] = 1;
}
/*------------------------------------------------------------------------------*/
/*VERIDICACION*/
int count_all(){
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
}


int doble(){
    int flag = 0;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 2 && flag == 1){
            flag = 2;
        }
        else if(cont[i] == 2 && flag == 0){
            flag = 1;
        }
    }
    if(flag == 2){
        dob = true;
    }
}

int stair_(){
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
}

int Full(){
    int flag = 0;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 3){
            flag = flag + 1;
        }
        if(cont[i] == 2){
            flag = flag + 1;
        }
    }
    if(flag == 2){
        full = true;
    }
}

int poker(){
    bool flag = false;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 4){
            flag = true;
            break;
        }
    }
    if(flag == true){
        pok = true;
    }
}

int generala(){
    bool flag = false;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 5){
            flag = true;
            break;
        }
    }
    if(flag == true){
        gener = true;
    }
}

int verif(){
    count_all();
    doble();
    stair_();
    Full();
    poker();
    generala();
}
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*CONTADORES*/

void desicion(int jugador[]){
    int delet = 0;
    int renun = 0;
    int select = 0;
    int select_2 = 0;
    printf("\nIngrese 1 si desea anotar un numero.\nIngrese 2 si desea anotar doble.\nIngrese 3 si desea anotar escalera:\n");
    printf("Ingrese 4 si desea anotar Full.\nIngrese 5 si desea anotar poker.\nIngrese 6 si desea anotar generala:\n Ingrese 7 si desea anotar generala doble:\n");
    scanf("%d", &select);
    while(select < 1 || select > 7){
        printf("\nERROR");
        printf("\nIngrese 1 si desea anotar un numero.\nIngrese 2 si desea anotar doble.\nIngrese 3 si desea anotar escalera:\n");
        printf("Ingrese 4 si desea anotar Full.\nIngrese 5 si desea anotar poker.\nIngrese 6 si desea anotar generala:\n Ingrese 7 si desea anotar generala doble:\n");
        scanf("%d", &select);
    }
    switch(select) {
        case 1 :
            printf("\nIngrese que numero desea anotar del 1 al 6: ");
            scanf("%d", &select_2);
            while(select_2 < 1 || select_2 > 6){
                printf("\nERROR");
                printf("\nIngrese que numero desea anotar del 1 al 6: ");
                scanf("%d", &select_2);
            }
            if(jugador[select_2-1] != 0){
                printf("Categoria llena");
                renun = 1;
            } else {
                if(cont[select_2-1] > 1 && jugador[select_2-1] == 0){
                    jugador[select_2-1] = cont[select_2-1] * select_2;
                } else {
                    printf("\nUsted no tiene ese número se le asignará 0");
                    jugador[select_2-1] = -1;
                }
            }
            break;
        case 2:
            if(jugador[6] == 0){
                if(dob == true && serv == false && jugadas >= 1){
                    jugador[6] = 10;
                }else if(dob ==true && serv == true ){
                    jugador[6] = 15;
                }else{
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[6] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 3:
            if(jugador[7] == 0){
                if(st == true && serv == false && jugadas >= 1){
                    jugador[7] = 20;
                }else if(st == true && serv == true){
                    jugador[7] = 25;
                }else{  
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[7] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 4:
            if(jugador[8] == 0){
                if(full == true && serv == false && jugadas >= 1){
                    jugador[8] = 30;
                }else if(full == true && serv == true){
                    jugador[8] = 35;
                }else{  
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[8] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 5:
            if(jugador[9] == 0){
                if(pok == true && serv == false && jugadas >= 1){
                    jugador[9] = 40;
                }else if(pok == true && serv == true){
                    jugador[9] = 45;
                }else{  
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[9] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 6:
            if(jugador[10] == 0){
                if(gener == true && serv == false && jugadas >= 1){
                    jugador[10] = 50;
                    gener_dob = true;
                }else if(gener == true && jugadas == 0){
                    jug1_full = true;
                }else{
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[10] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 7:
            if (jugador[11] == 0 && jugador[10] != 0 && gener_dob == true) {
                jugador[11] = 100;
            } else if(jugador[11] == 0){
                printf("usted no tiene esta categoria se le asignara 0 puntos");
                jugador[11] = -1;
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
    }
    if (renun == 1) {
        int valid_input = 0; // Variable para controlar si la entrada es válida
        while (!valid_input) {
            printf("Renuncie a una categoría del 1 al 11: ");
            if (scanf("%d", &delet) == 1) {
                if (delet >= 1 && delet <= 11) {
                    if (jugador[delet - 1] == 0) {
                        printf("Se le asignará 0 puntos a esa categoría\n");
                        jugador[delet - 1] = -1;
                        valid_input = 1; // Marcar la entrada como válida y salir del bucle
                    } else {
                        printf("Error: La categoría seleccionada ya tiene un puntaje asignado. Intente de nuevo.\n");
                    }
                } else {
                    printf("Error: La categoría debe estar entre 1 y 11. Intente de nuevo.\n");
                }
            } else {
                printf("Error: Entrada no válida. Intente de nuevo.\n");
                while (getchar() != '\n'); // Limpiar el buffer del stdin en caso de entrada no válida
            }
        }
    }
}
/*------------------------------------------------------------------------------*/

void control_end_party1() {
    jug1_full = true; // Suponemos que el array está completo
    for(int i = 0; i < 12; i++) {
        if(jugador_1[i] == 0) {
            jug1_full = false; // Encontramos al menos un elemento vacío, entonces el array no está completo
            break; // No es necesario continuar verificando
        }
    }
}

void control_end_party2() {
    jug2_full = true; // Suponemos que el array está completo
    for(int i = 0; i < 12; i++) {
        if(jugador_2[i] == 0) {
            jug2_full = false; // Encontramos al menos un elemento vacío, entonces el array no está completo
            break; // No es necesario continuar verificando
        }
    }
}

void imprimirTablaPuntajes(int jugador[]) {
    printf("\n==================== TABLA DE PUNTAJES ====================\n");
    printf("| %-20s | %-10s |\n", "Categoría", "Puntaje");
    printf("-----------------------------------------------------------\n");
    printf("| %-20s | %-10d |\n", "Unos", jugador[0]);
    printf("| %-20s | %-10d |\n", "Doses", jugador[1]);
    printf("| %-20s | %-10d |\n", "Treses", jugador[2]);
    printf("| %-20s | %-10d |\n", "Cuatros", jugador[3]);
    printf("| %-20s | %-10d |\n", "Cincos", jugador[4]);
    printf("| %-20s | %-10d |\n", "Seises", jugador[5]);
    printf("| %-20s | %-10d |\n", "Doble", jugador[6]);
    printf("| %-20s | %-10d |\n", "Escalera", jugador[7]);
    printf("| %-20s | %-10d |\n", "Full", jugador[8]);
    printf("| %-20s | %-10d |\n", "Poker", jugador[9]);
    printf("| %-20s | %-10d |\n", "Generala", jugador[10]);
    printf("| %-20s | %-10d |\n", "Generala Doble", jugador[11]);
    printf("-----------------------------------------------------------\n");
}

void control_serv() {
    serv = true; // Suponemos que la tirada se realizó desde 0
    if (jugadas > 0) {
        for (int i = 0; i < 4; i++) { // Consideramos todas las tiradas realizadas
            if (dice[i] != 0) {
                serv = false; // Se realizó al menos una tirada distinta de 0
                break;
            }
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
                jugadas++;
            }
        }else{
            gen_dice();
        }
    }
    return 0;
}

int main(){
    int ex = 1; 
    while(ex == 1){
        if(jug1_full == true && jug2_full == true){
            ex = 0;
        }
            val_dice();
            //test();
            gen_dice();
            selec();
            verif();
            if(interv == 0 && jug1_full == false){
                desicion(jugador_1);
            }else if(interv == 1 && jug2_full == false){
                desicion(jugador_2);
            }
            if(interv == 0 && jug1_full == false){
                imprimirTablaPuntajes(jugador_1);
            }else if(interv == 1 && jug2_full == false){
                imprimirTablaPuntajes(jugador_2);
            }
            if (interv == 0){
                interv = 1;
            }else{
                interv = 0;
            }
            control_end_party1();
            control_end_party2();
        }
}