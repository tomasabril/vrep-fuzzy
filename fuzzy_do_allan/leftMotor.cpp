// Project FLIE-Fuzzy Logic Inference Engine - Jo�o Alberto Fabro - out/1996

// File flie.cc

#include <stdlib.h> // Random!
#include <stdio.h> // Random!
//#define DOS
#include "leftMotor.h"

/*Deve-se definir um sistema de controle que ir� conter as regras.*/
fuzzy_control fuzzycontrolE;

/*No programa principal � necess�rio instanciar as vari�veis para conter
todos os conjuntos fuzzy e tamb�m defini-los.*/

trapezoid_category cat2[16];



/*Deve-se definir as vari�veis lingu�sticas que ir�o conter os conjuntos fuzzy*/

linguisticvariable sens_front2, sens_right2, sens_left2, lingLeftMotor;



/*Deve-se definir as regras de infer�ncia que ir�o reger o comportamento do
sistema de controle.� necess�rio instanci�-los.*/

rule infruleE[99];

leftMotor::leftMotor(){
	mainE();
}

leftMotor::~leftMotor(){

}

void leftMotor::mainE()
{
        int i;



/*deve-se definir vari�veis que ir�o conter as entradas e sa�das(defuzificadas)
do sistema submetidas ao controle.*/

float SumError, ControlOutput;



	cat2[0].setname("M");
	cat2[0].setrange(0, 1000);
	cat2[0].setval(0, 0, 500, 1000);

	cat2[1].setname("P");
	cat2[1].setrange(500, 1400);
	cat2[1].setval(500, 1000, 1200, 1400);

	cat2[2].setname("MP");
	cat2[2].setrange(1400, 2000);
	cat2[2].setval(1400, 1500, 2000, 2000);



	/*Define-se a Vari�vel lingu�stica Error*/

	sens_right2.setname("Sensores da direita");

	sens_right2.includecategory(&cat2[0]);

	sens_right2.includecategory(&cat2[1]);

	sens_right2.includecategory(&cat2[2]);



	cat2[3].setname("M");
	cat2[3].setrange(0, 1000);
	cat2[3].setval(0, 0, 500, 1000);

	cat2[5].setname("P");
	cat2[5].setrange(500, 1400);
	cat2[5].setval(500, 1000, 1200, 1400);

	cat2[6].setname("MP");
	cat2[6].setrange(1400, 2000);
	cat2[6].setval(1400, 1500, 2000, 2000);
	



	/*Define-se a Vari�vel lingu�stica Error*/

	sens_left2.setname("Sensores da esquerda");

	sens_left2.includecategory(&cat2[3]);

	sens_left2.includecategory(&cat2[4]);

	sens_left2.includecategory(&cat2[5]);



	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/



	cat2[6].setname("M");
	cat2[6].setrange(0, 1000);
	cat2[6].setval(0, 0, 500, 1000);

	cat2[7].setname("P");
	cat2[7].setrange(500, 1400);
	cat2[7].setval(500, 1000, 1200, 1400);

	cat2[8].setname("MP");
	cat2[8].setrange(1200, 2000);
	cat2[8].setval(1400, 1500, 2000, 2000);


	/*Defini-se a Vari�vel lingu�stica Error*/

	sens_front2.setname("Sensores da frente");

	sens_front2.includecategory(&cat2[6]);

	sens_front2.includecategory(&cat2[7]);

	sens_front2.includecategory(&cat2[8]);



	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat2[9].setname("RT");
	cat2[9].setrange(-10, -7);
	cat2[9].setval(-10, -10, -8, -7);

	cat2[10].setname("MT");
	cat2[10].setrange(-8,-2);
	cat2[10].setval(-8, -7, -3, -2);

	cat2[11].setname("DT");
	cat2[11].setrange(-3, 1);
	cat2[11].setval(-3, -2, -1, 1);

	cat2[12].setname("DF");
	cat2[12].setrange(-1, 3);
	cat2[12].setval(-1, 1, 2, 3);

	cat2[13].setname("MF");
	cat2[13].setrange(2, 8);
	cat2[13].setval(2, 3, 7, 8);

	cat2[14].setname("RF");
	cat2[14].setrange(7, 10);
	cat2[14].setval(7, 8, 10, 10);


	/*Defini-se a vari�vel lingu�stica Control*/

	lingLeftMotor.setname("Controle");



	lingLeftMotor.includecategory(&cat2[9]);

	lingLeftMotor.includecategory(&cat2[10]);

	lingLeftMotor.includecategory(&cat2[11]);
	
	lingLeftMotor.includecategory(&cat2[12]);
    lingLeftMotor.includecategory(&cat2[13]);

	lingLeftMotor.includecategory(&cat2[14]);


	/*Defini-se o m�todo defuzzifica��o*/

	fuzzycontrolE.set_defuzz(CENTEROFAREA);


	/* Defini-se o fuzzy_control pelas entradas fuzzy( Error, DeltaError)
	 e sa�das (Control) )*/

	fuzzycontrolE.definevars(sens_left2, sens_front2, sens_right2, lingLeftMotor);

	//Regras para Muito Perto com o sensor da esquerda
	//girar K-Junior para a direita

	fuzzycontrolE.insert_rule("M","M","M","RF");
	fuzzycontrolE.insert_rule("M","M","P","DF");
	fuzzycontrolE.insert_rule("M","M","MP","DT");

	fuzzycontrolE.insert_rule("M","P","M","DT");
	fuzzycontrolE.insert_rule("M","P","P","DT");
	fuzzycontrolE.insert_rule("M","P","MP","MT");

	fuzzycontrolE.insert_rule("M","MP","M","MT");
	fuzzycontrolE.insert_rule("M","MP","P","MT");
	fuzzycontrolE.insert_rule("M","MP","MP","DT");


	//Regras para M�dio com sensor esquerda
	//girar K-Junior para a direita
	fuzzycontrolE.insert_rule("P","M","M","RF");
	fuzzycontrolE.insert_rule("P","M","P","MT");
	fuzzycontrolE.insert_rule("P","M","MP","DT");


	fuzzycontrolE.insert_rule("P","P","M","RF");
	fuzzycontrolE.insert_rule("P","P","P","MT");
	fuzzycontrolE.insert_rule("P","P","MP","DT");

	fuzzycontrolE.insert_rule("P","MP","M","RF");
	fuzzycontrolE.insert_rule("P","MP","P","RT");
	fuzzycontrolE.insert_rule("P","MP","MP","RT");
	
	//Regras para Muito Perto com o sensor da direita
	//girar K-Junior para a esquerda
	
	fuzzycontrolE.insert_rule("MP","M","M","MF");
	fuzzycontrolE.insert_rule("MP","M","P","MF");
	fuzzycontrolE.insert_rule("MP","M","MP","DT");
	
	fuzzycontrolE.insert_rule("MP","P","M","DF");
	fuzzycontrolE.insert_rule("MP","P","P","DF");
	fuzzycontrolE.insert_rule("MP","P","MP","DT");
		
	fuzzycontrolE.insert_rule("MP","MP","M","DF");
	fuzzycontrolE.insert_rule("MP","MP","P","DF");
	fuzzycontrolE.insert_rule("MP","MP","MP","DT");

// Defini-se a leitura dos sensores do seu sistema
float ErrorInput = -100.0;
float DeltaErrorInput = 0.0;

float min;
char fcfilename[20];



	fuzzycontrolE.set_defuzz(CENTEROFAREA);

// Teste para os controles

//min =  navio(fc,1);
//  printf("Minimum Error = %f\n", min);
  fuzzycontrolE.save_m("controlebottom", 0);
}

float leftMotor::makeInference(float input1, float input2, float input3){
	return fuzzycontrolE.make_inference(input1, input2, input3);
}
