//PROGRAMA QUE CALCULA LA FUNCIÓN QUE PIDIÓ PIRELLI PARA LOS NEUMÁTICOS C5, C4 Y C3. NO VALE PARA EL C2 Y EL C1
#include <stdio.h>
#define CARRERAS 2
#define LEN 2
#define NEUMATICOS 150
void calcularInversa2x2(float m[CARRERAS][LEN], float mAux[CARRERAS][LEN], float mAux2[CARRERAS][LEN]);
float calcularDeterminante2x2(float m[CARRERAS][LEN]);
int main(){
    int j, vueltas;
    float m[CARRERAS][LEN], mAux[CARRERAS][LEN], mAux2[CARRERAS][LEN], velocidad[NEUMATICOS], velocidaddef[NEUMATICOS], tiempo[NEUMATICOS], vDef[NEUMATICOS], tiempodef[NEUMATICOS];
    float tvuelta, masa, deformacion, tiempofinal, constante, steerangle, radio, posicion[NEUMATICOS], posiciondef[NEUMATICOS];
    //Pido el número de vueltas:
    printf("Escribe el numero de vueltas que lleva el neumatico: ");
    scanf("%d", &vueltas);
    while(vueltas < 1){
        printf("Vueltas >=1\n");
        printf("Escribe el numero de vueltas que lleva el neumatico: ");
        scanf("%d", &vueltas);
    }
    //Pido el tiempo por vuelta:
    printf("Escribe el tiempo por vuelta: ");
    scanf("%f", &tvuelta);
    //Pido la velocidad:
    printf("Escribe la velocidad en t=0: ");
    scanf("%f", &velocidad[0]);
            for(j=1; j<(int)tvuelta; j++){
            //Pido el ángulo del volante:
            printf("Escribe el angulo del volante: ");
            scanf("%f", &steerangle);
            if(steerangle > -3.5 && steerangle < 3.5){//Si estoy en recta
                //Pido la velocidad en cada tiempo:
                printf("Escribe la velocidad en t=%d: ", j);
                scanf("%f", &velocidad[j]);
                //Relleno la matriz con el tiempo:
                m[0][j-1] = vueltas*(j-0.999);
                m[0][j] = -1/(vueltas*(j-0.999)*vueltas*(j-0.999));
                m[1][j-1] = vueltas*j;
                m[1][j] = -1/(vueltas*j*vueltas*j);
                //Calculo el término independiente:
                velocidaddef[j-1] = velocidad[j-1] + velocidad[j-1]*(j-0.999);
                velocidaddef[j] = velocidad[j] + velocidad[j-1]*j;
                //Calculo la solución:
                calcularInversa2x2(m, mAux, mAux2);
                vDef[j-1]=mAux2[j-1][j-1]*velocidaddef[j-1]+mAux2[j-1][j]*velocidaddef[j];
                vDef[j]=mAux2[j][j-1]*velocidaddef[j-1]+mAux2[j][j]*velocidaddef[j];
                //Calculo la aceleración:
                printf("Aceleracion longitudinal: %f+%f/t^3\n", vDef[j-1], 2*vDef[j]);
                //Pido la masa:
                printf("Escribe la masa del coche en t=&d: ", j);
                scanf("%f", &masa);
                //Pido la deformación:
                printf("Escribe la deformacion del neumatico que lleva (de 0 a 1): ");
                scanf("%f", &deformacion);
                //Pido la aceleración:
                printf("Escribe el tiempo que llevas en el stint: ");
                scanf("%f", &tiempofinal);
                //Calculo la constante:
                constante = (masa*(vDef[j-1]+2*vDef[j]/(j*j*j)))/(deformacion);
                //Muestro la fórmula
                printf("La formula es deformacion = %f+%f/t^3\n", constante*vDef[j-1], constante*2*vDef[j]);
            }
            else {//Si estoy en curva:
                //Pido la posición en el tiempo:
                printf("Escribe la posicion en t=%d: ", j);
                scanf("%f", &posicion[j]);
                //Relleno la matriz con el tiempo:
                m[0][j-1] = j-0.999;
                m[0][j] = 1;
                m[1][j-1] = j;
                m[1][j] = 1;
                //Calculo el término independiente:
                posiciondef[j-1] = posicion[j-1] + posicion[j-1]*(j-0.999);
                posiciondef[1] = posicion[1] + posicion[j-1]*j;
                //Calculo la solución:
                calcularInversa2x2(m, mAux, mAux2);
                vDef[j-1]=mAux2[j-1][j-1]*velocidaddef[j-1]+mAux2[j-1][j]*velocidaddef[j];
                vDef[j]=mAux2[j][j-1]*velocidaddef[j-1]+mAux2[j][j]*velocidaddef[j];
                //Calculo la aceleración: .
                printf("Aceleracion longiudinal:%f\n", 2*vDef[j-1]);
                //Pido el radio:
                printf("Escribe el radio: ");
                scanf("%f", &radio);
                //Muestro la aceleración lateral:
                printf("Aceleracion lateral:%f\n", 4*vDef[j-1]*vDef[j-1]/radio);
                //Pido la masa:
                printf("Escribe la masa del coche al final del stint: ");
                scanf("%f", &masa);
                //Pido la deformación:
                printf("Escribe la deformacion del neumatico que lleva (de 0 a 1): ");
                scanf("%f", &deformacion);
                //Pido el tiempo:
                printf("Escribe el tiempo que llevas en el stint: ");
                scanf("%f", &tiempofinal);
                //Pido la constante:
                constante = (masa*(2*vDef[j-1]+4*vDef[j-1]*vDef[j-1]/radio))/(deformacion);
                //Pido la deformación:
                printf("La formula es deformacion = %f\n", constante*vueltas*vDef[j-1]);
            }
        }
}
void calcularInversa2x2(float m[CARRERAS][LEN], float mAux[CARRERAS][
LEN], float mAux2[CARRERAS][LEN]){
        int i, j;
        mAux[0][0]=m[1][1];
        mAux[0][1]=-m[0][1];
        mAux[1][0]=-m[1][0];
        mAux[1][1]=m[0][0];
        for(i=0; i<CARRERAS; i++){
            for(j=0; j<LEN; j++){
             mAux2[i][1]=mAux[i][1]/calcularDeterminante2x2(m);
             }
        }
 }
 //Para calcular el determinante:
 float calcularDeterminante2x2(float m[CARRERAS][LEN]){
     float determinante;
     determinante=m[0][0]*m[1][1]-m[1][0]*m[0][1];
     return determinante;
 }
