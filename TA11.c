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
        printf("%d\r", (rand() % 5) + 1);
        fflush(stdout);
        usleep(100000);
    }
    printf("\r");
    
}

void val_dice()
{
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < 5; i++)   
    {
        dice[i] = (rand() % 6) + 1;
    }
}

int selec(){
    time_t t;
    srand((unsigned) time(&t));
    int ant = 1;
    int sel = 0;
    int sel_d = 0;
    jugadas = 0;
    // Solicitamos al usuario que ingrese un número en el rango [1, 5]
    while(jugadas <= 3)
    {
        printf("\nSu numeros de jugadas restantes es: %d \nElija cuantos dados desea tirar otra vez: \n (si no desea hacer cambios presione 0)\n",2-jugadas);
        scanf("%d", &sel);
        
        if(sel != 0)
        {
            // Validamos que el número esté en el rango [1, 5]
            while (sel < 1 || sel > 5) 
            {
                printf("El numero debe estar en el rango del 1 al 5.\n");
                printf("Elija un numero del 1 al 5: ");
                scanf("%d", &sel);
            }
            //definimos cuantos dados se volvera a tirar
            for(int i = 1; i <= sel; i++)
            {
                ant = sel_d;
                printf("elija el numero de dado que desea volver a lanzar del 1 al 5:\n");
                scanf("%d",&sel_d);
                
                if(ant != sel_d)
                {
                    dice[sel_d-1] = (rand() % 6) + 1;
                }
                //declaramos que no se pueda volver a tirar el dado 2 veces
                while(ant == sel_d)
                {
                    ant = sel_d;
                    printf("\nAVISO: \nsolo puede elejir 1 dado para volver a lanzar\n\n");
                    printf("elija el numero de dado que desea volver a lanzar del 1 al 5:\n");
                    scanf("%d",&sel_d);
                    
                    if(ant != sel_d)
                    {
                        dice[sel_d-1] = (rand() % 6) + 1;
                    }
                }
            }
            
            printf("la nueva tirada es:\n");
            //volvemos a imprimir los dados si se realizaron cambios
            for(int i = 0; i < 5; i++ )
            {
                printf("dado numero[%d] = \n",i+1);
                printf("%d \n", dice[i]);
            }
        }else{
            printf("no se realizaron cambios en la tirada");
            break;
        }
    jugadas = jugadas + 1;
    }
    return 0;
}

int main(){
    val_dice();
    
    for(int i = 0; i < 5; i++ )
    {
        printf("dado numero[%d] = \n",i+1);
        efect();
        printf("\r");
        printf("%d \n", dice[i]);
    }
    
    selec();
}
