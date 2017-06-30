#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

float fuzzyFy(float dist){
float fuzzy;
				if(dist < 150){
					fuzzy = 1;
				}else if(dist>= 150&& dist < 350){
					float distaux = dist;
					distaux  = distaux  -150;
					distaux = 1-(distaux/200);
					fuzzy = distaux;
				}else if(dist >= 350){
					fuzzy = 0;
				}
				return fuzzy;

}
float virarPouco(float fuzzy){
if(fuzzy < 1 && fuzzy > 0)
	return -6*fuzzy;
else return 0;
}
float virarMuito(float fuzzy){
if (fuzzy == 1)
	return -6;
	else return 0;
}
float virarNada(float fuzzy){
                return 0;
}
int main(){
    float valueMotorE = 3;
    float valueMotorD = 3;
    float distances[5];
    float sensorso[6];

    sensorso[5] = 0;

    ofstream output;
    output.open("output.txt");

    int treinos;

    float maxEsquerda	= 0;
    float maxFrente		= 0;
    float maxDireita	= 0;

    float valueFuzzyE;
    float valueFuzzyD;

    srand(time(NULL));


    printf("digite o numero de treinos");
    scanf("%d", &treinos);
    output << treinos << "\n";

    for(int i = 0; i< treinos; i++){
        output << 6 << "\n";
//colocando randoms nos sensores vetor distances
        for(int j = 0; j<5; j++){
            distances[j] = rand()%350;
            sensorso[j] = distances[j]/350;
            output << sensorso[j] << "\n";
        }
            output << "0"<< "\n";
            if(distances[0] < distances[1])
				maxEsquerda = distances[0];
			else
				maxEsquerda = distances[1];

            if(distances[3] < distances[4])
				maxDireita = distances[3];
			else
				maxDireita = distances[4];
         output << 2 << "\n";

// aqui os valores ja estao setados
    valueFuzzyD = fuzzyFy(maxDireita);
    valueFuzzyE = fuzzyFy(maxEsquerda);

            if(valueMotorD < -5.0)
				valueMotorD = -5;
			if(valueMotorE < -5.0)
				valueMotorE = -5;

			if(valueMotorD > 5.0)
				valueMotorD = 5;
			if(valueMotorE > 5.0)
				valueMotorE = 5;

            valueMotorE = (3 +(virarPouco(fuzzyFy(maxDireita))+virarMuito(fuzzyFy(maxDireita))+virarNada(fuzzyFy(maxDireita))));
            if(fuzzyFy(maxDireita) <0.5)
                valueMotorD = (3 +(virarPouco(fuzzyFy(maxEsquerda))+virarMuito(fuzzyFy(maxEsquerda))+virarNada(fuzzyFy(maxEsquerda))));
            else
                valueMotorD = 3;

               output << valueMotorE/3 << "\n";
                output << valueMotorD/3 << "\n";

    }


return 0;}
