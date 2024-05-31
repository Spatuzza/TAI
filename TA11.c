/*
JUEGO ✓
REGLAS ✓ 
ANOTADOR ✓ 
IA ✓ 
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Declaración de variables globales
int jugadas;
bool full = false;
bool dob = false;
bool st = false;
bool pok= false;
bool gener= false;
bool gener_dob = false;
bool serv = true;
bool jug1_full = false;
bool jug2_full = false;
bool iaplay = false; //bandera para saber si la pc esta jugando o no para evitar inconvenientes

int select_2 = 0;
int select = 0;
int interv;
int dice[5] = {0};
int cont[6] = {0};


int jugador_2[11] ={0};
int jugador_1[11] ={0};

bool isNumber(const char *str) {
    // Verifica si la cadena está vacía
    if (*str == '\0') {
        return false;
    }
    // Recorre cada carácter de la cadena
    while (*str) {
        // Verifica si cada carácter es un dígito
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

/*------------------------------------------------------------------------------*/
/*VERIFICACION*/
int count_all(){// funcion para saber que numeros se repiten 
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

//categoria doble
int doble(){
    int flag = 0;
    dob = false;
    for(int i = 0; i<= 5; i++){
        if(cont[i] == 2){
            flag = flag + 1;
        }
    }
    if(flag == 2){
        dob = true;
    }
}
// categoria escalera
int stair_(){
    // escalera normal
    st = false;
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

// categoria full
int Full(){
    full = false;
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
// categoria poker
int poker(){
    pok = false;
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
//categoria generala
int generala(){
    gener = false;
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
//verificacion de todas las categorias
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
    char input[10];
    if(iaplay == false){
    while (1) {
        printf("\nIngrese 1 si desea anotar un numero.\nIngrese 2 si desea anotar doble.\nIngrese 3 si desea anotar escalera:\n");
        printf("Ingrese 4 si desea anotar Full.\nIngrese 5 si desea anotar poker.\nIngrese 6 si desea anotar generala:\n");
        printf("Ingrese 7 si desea anotar generala doble:\n");
        
        // Lee la entrada como una cadena
        scanf("%s", input);
        
        // Verifica si la entrada es un número
        if (isNumber(input)) {
            // Convierte la cadena a un número entero
            select = atoi(input);
            
            // Verifica si el número está en el rango válido
            if (select >= 1 && select <= 7) {
                break;
            }
        }
        
        printf("\nERROR: Entrada invalida. Por favor, ingrese un número entre 1 y 7.\n");
    }
    }
    // casos de seleccion de categorias del 1 al 7
    switch(select) {
        case 1 :// caso 1 ingresar numeros
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
            } else {//cargar el puntaje del 1 al 6 si no esta vacio
                if(cont[select_2-1] > 1 && jugador[select_2-1] == 0){
                    jugador[select_2-1] = cont[select_2-1] * select_2;
                } else {// si esta vacio cancelar la categoria 
                    printf("\nUsted no tiene ese número se le asignará 0");
                    jugador[select_2-1] = -1;
                }
            }
            break;
        case 2:
            if(jugador[6] == 0){// cargar los dobles 
                if(dob == true && serv == false && jugadas >= 1){
                    jugador[6] = 10;
                }else if(dob ==true && serv == true ){
                    jugador[6] = 15;
                }else{//no se podia cargar doble
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[6] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 3:
            if(jugador[7] == 0){// cargar escalera
                if(st == true && serv == false && jugadas >= 1){
                    jugador[7] = 20;
                }else if(st == true && serv == true){
                    jugador[7] = 25;
                }else{  
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[7] = -1;
                }
            }else{//no se podia cargar escalera
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 4:
            if(jugador[8] == 0){// cargar categoria full
                if(full == true && serv == false && jugadas >= 1){
                    jugador[8] = 30;
                }else if(full == true && serv == true){
                    jugador[8] = 35;
                }else{
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[8] = -1;
                }
            }else{//no se podia cargar full
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 5:
            if(jugador[9] == 0){//cargar categoria poker 
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
            if(jugador[10] == 0){// cargar categoria generala 
                if(gener == true && serv == false && jugadas >= 1){
                    jugador[10] = 50;
                    gener_dob = true;
                }else if(gener == true && serv == true){
                    jug1_full = true;
                    jug2_full = true;
                }else{
                    printf("usted no tiene esta categoria se le asignara 0 puntos");
                    jugador[10] = -1;
                }
            }else{
                printf("categoria llena");
                renun = 1;
            }
            break;
        case 7:// cargar categoria generala doble
            if (jugador[11] == 0 && jugador[10] != 0 && gener_dob == true && gener == true) {
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
    if (renun == 1) {// si no se pudo cargar una categoria se le obliga a renunciar a una categoria al jugador
        int valid_input = 0; // Variable para controlar si la entrada es válida
        while (!valid_input) {
            printf("Renuncie a una categoria del 1 al 12: ");
            if (scanf("%d", &delet) == 1) {
                if (delet >= 1 && delet <= 12) {
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
    select = 0;
    select_2 = 0;
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

void imprimirTablaPuntajes(int jugador[]) {// imprimir tabla de los jugadores
    int tempJugador[12];
    int total = 0;

    for (int i = 0; i < 12; i++) {
        tempJugador[i] = (jugador[i] == -1) ? 0 : jugador[i];
    }

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

    for (int i = 0; i < 12; i++) {
        total += tempJugador[i];
    }

    printf("| %-20s | %-10s |\n", "Total", "");
    printf("-----------------------------------------------------------\n");
    printf("| %-20s | %-10d |\n", "", total);
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

int gen_dice(){ // imprimir los dados
    printf("los dados sacados son:\n");
    printf("A   B   C   D   E  \n");
    efect();
    printf("\r");
    printf("%d   %d   %d   %d   %d",dice[0],dice[1],dice[2],dice[3],dice[4]);
}

void reval_dice_0(){// revaluar las posiciones de los dados = 0
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i <= 5; i++){
        if(dice[i] == 0){
            dice[i] = (rand() % 6) + 1;
    }
    }
}

int val_dice() //randomizar la primera tirada de los dados 
{
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < 5; i++){
        dice[i] = (rand() % 6) + 1;
    }
}

int selec(){// funcion para seleccionar los dados para lanzarlos
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
            switch(sel) { // seleccion de categorias 
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
        control_serv();// controlas si fue servida o no la jugada
        reval_dice_0();// reevaluar los dados hechos 0
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

int pc(){// jugadas de la pc
    select = 0;
    bool may_2 = false;
    may_2 = false;
    for (int i = 0; i < 6; i++){ // buscar si hay pares de numeros 
        if(cont[i] > 1 && jugador_2[i] == 0){
            may_2 = true;
            break;
        }
    }
        if(gener_dob == true && gener == true && jugador_2[11]){
            select = 7;
            printf("\nLA PC ANOTA GENERALA DOBLE\n");
        }
        else if(gener == true && jugador_2[10] == 0){
            select = 6;
            printf("\nLA PC ANOTA GENERALA \n");
        }else if(pok == true && jugador_2[9] == 0){
            select = 5;
            printf("\nLA PC ANOTA POKER\n");
        }else if(full == true&& jugador_2[8] == 0){
            select = 4;
            printf("\nLA PC ANOTA FULL\n");
        }else if(st == true && jugador_2[7] == 0){
            select = 3;
            printf("\nLA PC ANOTA ESCALERA\n");
        }else if(dob == true && jugador_2[6] == 0){
            select = 2;
            printf("\nLA PC ANOTA DOBLE\n");
        }else if(may_2 == true){
        select = -1;
        for(int i = 0; i < 6; i++){ 
            if(cont[i] > 1){
                jugador_2[i] = cont[i] * (i + 1);  
                printf("\nLA PC ANOTA %d \n",i+1);
                break;
            }
        }
        }
}

void renun_pc(){ //funcion para que la pc renuncie a una categoria aleatoriamente
    time_t t;
    srand((unsigned) time(&t));
    int random;
    if (select == 0) {
        printf("la computadora renunciara a una categoria\n");
        while (1) {
            random = rand() % 12;   // Genera un número entre 0 y 4 inclusive
            if (jugador_2[random] == 0) {
                jugador_2[random] = -1;  // Asigna -1 en lugar de comparar
                break;
            }
        }
    }
}

int player_vs_player(){ // funcion para ejecutar jugador vs jugador 
    char s;
    int ex = 1;
    while (ex == 1) {// corrovorar que la jugada sigue hasta que se acaben las categorias
        if (jug1_full && jug2_full ==  false) {
            ex = 0;
            printf("El juego ha terminado.\n");
            break;
        }
        // inicializar la jugada
        val_dice(); 
        gen_dice();
        selec();
        verif();
        if (interv == 0 && jug1_full == false) {//turno de jugador 1 
            printf("\nTurno de Jugador 1\n");
            desicion(jugador_1);
            printf("JUGADOR 1");
            imprimirTablaPuntajes(jugador_1);
        } else if (interv == 1 && jug2_full == false) {//turno de jugador 2
            printf("\nTurno de Jugador 2\n");
            desicion(jugador_2);
            printf("JUGADOR 2");
            imprimirTablaPuntajes(jugador_2);
        }
        // Cambio de turno
        if (interv == 0) {
            interv = 1;
        } else {
            interv = 0;
        }
        // Control de fin de partida
        control_end_party1();
        control_end_party2();
    }
    // finalizar la partida
    printf("Gracias por jugar.\n");
    printf("presione enter para cerrar....\n\n");
    s = getchar();
    return 0;
}

int player_vs_pc(){
    char s;
    time_t t;
    srand((unsigned) time(&t));
    int jugadas_pc = 0;
    int ex = 1;
    while (ex == 1) { // corrovorar que la jugada sigue hasta que se acaben las categorias
        if (jug1_full && jug2_full) {
            ex = 0;
            printf("El juego ha terminado.\n");
            break;
        }
        if (interv == 0 && !jug1_full) {
            iaplay = false;
            // inicializar la jugada para jugaro 1
            val_dice();
            gen_dice();
            selec();
            verif();
            printf("\nTurno de Jugador 1\n");
            desicion(jugador_1);
            printf("JUGADOR 1");
            imprimirTablaPuntajes(jugador_1);
        } else if (interv == 1 && !jug2_full) {
            jugadas_pc = 0;
            iaplay = true;
            val_dice();
            while(jugadas_pc != 3){// la pc tendra 3 jugadas disponibles
                // inicializar la jugada para la pc
                gen_dice();
                verif();
                printf("\nTurno de IA\n");
                pc();
                if(select == 0) {
                    for(int i = 0; i < 5; i++){
                        dice[i] = (rand() % 6) + 1;
                    }
                }else{
                    break;;
                }
                jugadas_pc = jugadas_pc + 1;
            }
            if(select == 0){
                renun_pc();
            }
            desicion(jugador_2);
            printf("JUGADOR 2");
            imprimirTablaPuntajes(jugador_2);
        }
        // Cambio de turno
        if (interv == 0) {
            interv = 1;
        } else {
            interv = 0;
        }
        // Control de fin de partida
        control_end_party1();
        control_end_party2();
    }
    // finalizar la partida
    printf("Gracias por jugar.\n");
    printf("presione enter para cerrar....\n\n");
    s = getchar();
    return 0;
}

int main(){ 
    int choise; //creacion de vaiable de eleccion
    printf("ingrese 1 si desea jugar 1vs1 o 2 si desea jugar vs la maquina\n");
    scanf("%d", &choise);
    while (choise != 1 && choise != 2) {
        printf("Ingrese 1 si desea jugar 1vs1 o 2 si desea jugar vs la maquina\n");
        scanf("%d", &choise);
    }
    if(choise == 1){
        player_vs_player();
    }else{
        player_vs_pc();
    }
}