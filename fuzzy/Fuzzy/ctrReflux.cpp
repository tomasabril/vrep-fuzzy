// Project FLIE-Fuzzy Logic Inference Engine - João Alberto Fabro - out/1996

// File flie.cc

#include <vcl.h>
#include <stdlib.h> // Random!
#include <stdio.h> // Random!
#define DOS
#include "flie.h"

/*Deve-se definir um sistema de controle que irá conter as regras.*/
fuzzy_control fcREFLUX;

/*No programa principal é necessário instanciar as variáveis para conter
todos os conjuntos fuzzy e também defini-los.*/

trapezoid_category catREFLUX[21];



/*Deve-se definir as variáveis linguísticas que irão conter os conjuntos fuzzy*/

linguisticvariable ErrorREFLUX, DeltaErrorREFLUX, ControlREFLUX;



/*Deve-se definir as regras de inferência que irão reger o comportamento do
sistema de controle.É necessário instanciá-los.*/

rule infruleREFLUX[49];


fuzzy_control* Reflux()
{
        int i;



/*deve-se definir variáveis que irão conter as entradas e saídas(defuzificadas)
do sistema submetidas ao controle.*/

float SumError, ControlOutput;


/* Defini-se os conjuntos fuzzy para a variável linguística Error*/

catREFLUX[0].setname("NB");
catREFLUX[0].setrange(-200,0);
catREFLUX[0].setval(-200,-200, -30,-10);

catREFLUX[1].setname("NS");
catREFLUX[1].setrange(-100,0);
catREFLUX[1].setval(-20,-10,-0);

catREFLUX[2].setname("NVS");
catREFLUX[2].setrange(-100,0);
catREFLUX[2].setval(-10,-5,-0);

catREFLUX[3].setname("QZ");
catREFLUX[3].setrange(-100,+100);// JAF 13/12/2001, changed range from -100~+100 to -10~+10
catREFLUX[3].setval(-5,0,5);

catREFLUX[4].setname("PVS");
catREFLUX[4].setrange(0,+100);
catREFLUX[4].setval(0,5,10);

catREFLUX[5].setname("PS");
catREFLUX[5].setrange(0,+100);
catREFLUX[5].setval(0,10,20);

catREFLUX[6].setname("PB");
catREFLUX[6].setrange(0,+200);
catREFLUX[6].setval(10, 30, 200, 200);


/*Defini-se a Variável linguística Error*/

ErrorREFLUX.setname("ErrorREFLUX");

ErrorREFLUX.includecategory(&catREFLUX[0]);

ErrorREFLUX.includecategory(&catREFLUX[1]);

ErrorREFLUX.includecategory(&catREFLUX[2]);

ErrorREFLUX.includecategory(&catREFLUX[3]);

ErrorREFLUX.includecategory(&catREFLUX[4]);

ErrorREFLUX.includecategory(&catREFLUX[5]);

ErrorREFLUX.includecategory(&catREFLUX[6]);


/*Defini-se os conjuntos fuzzy para a variável linguística DeltaError*/

catREFLUX[7].setname("NB");
catREFLUX[7].setrange(-20,0);
catREFLUX[7].setval(-20,-20,-2);

catREFLUX[8].setname("NS");
catREFLUX[8].setrange(-10,0);
catREFLUX[8].setval(-5,-2,0);

catREFLUX[9].setname("NVS");
catREFLUX[9].setrange(-10,0);
catREFLUX[9].setval(-1,-0.5,0);

catREFLUX[10].setname("QZ");
catREFLUX[10].setrange(-10,+10);;// JAF 13/12/2001, changed range from -10~+10 to -1~+1; Returned 17/12!
catREFLUX[10].setval(-0.5,0,0.5);

catREFLUX[11].setname("PVS");
catREFLUX[11].setrange(0,+10);
catREFLUX[11].setval(0,0.5,1);

catREFLUX[12].setname("PS");
catREFLUX[12].setrange(0,+10);
catREFLUX[12].setval(0,2,5);

catREFLUX[13].setname("PB");
catREFLUX[13].setrange(0,+20);
catREFLUX[13].setval(2,20,20);




/*Defini-se a variável linguística DeltaError*/

DeltaErrorREFLUX.setname("DeltaErrorREFLUX");

DeltaErrorREFLUX.includecategory(&catREFLUX[7]);

DeltaErrorREFLUX.includecategory(&catREFLUX[8]);

DeltaErrorREFLUX.includecategory(&catREFLUX[9]);

DeltaErrorREFLUX.includecategory(&catREFLUX[10]);

DeltaErrorREFLUX.includecategory(&catREFLUX[11]);

DeltaErrorREFLUX.includecategory(&catREFLUX[12]);

DeltaErrorREFLUX.includecategory(&catREFLUX[13]);




/*Defini-se os conjuntos fuzzy para a variável linguística Control*/

catREFLUX[14].setname("NB");
catREFLUX[14].setrange(-100,0);
catREFLUX[14].setval(-100,-100,-90,-20);

catREFLUX[15].setname("NS");
catREFLUX[15].setrange(-100,0);
catREFLUX[15].setval(-50,-20,0);

catREFLUX[16].setname("NVS");
catREFLUX[16].setrange(-100,0);
catREFLUX[16].setval(-20,-10,0);

catREFLUX[17].setname("QZ");
catREFLUX[17].setrange(-10,+10);;// JAF 13/12/2001, changed range from -100~+100 to -10~+10; Returned 17/12!
catREFLUX[17].setval(-10,0,10);

catREFLUX[18].setname("PVS");
catREFLUX[18].setrange(0,+100);
catREFLUX[18].setval(0,10,20);

catREFLUX[19].setname("PS");
catREFLUX[19].setrange(0,+100);
catREFLUX[19].setval(0,20,50);

catREFLUX[20].setname("PB");
catREFLUX[20].setrange(0,+100);
catREFLUX[20].setval(20,90,100,100);


/*Defini-se a variável linguística Control*/

ControlREFLUX.setname("ControlREFLUX");

ControlREFLUX.includecategory(&catREFLUX[14]);

ControlREFLUX.includecategory(&catREFLUX[15]);

ControlREFLUX.includecategory(&catREFLUX[16]);

ControlREFLUX.includecategory(&catREFLUX[17]);

ControlREFLUX.includecategory(&catREFLUX[18]);

ControlREFLUX.includecategory(&catREFLUX[19]);

ControlREFLUX.includecategory(&catREFLUX[20]);




/*Defini-se o método defuzzificação*/

fcREFLUX.set_defuzz(MAXIMUM);


/* Defini-se o fuzzy_control pelas entradas fuzzy( ErrorREFLUX, DeltaErrorREFLUX)
e saídas (ControlREFLUX) )*/

fcREFLUX.definevars(ErrorREFLUX, DeltaErrorREFLUX, ControlREFLUX);



/*Deve-se incluir cada regra fuzzy no fuzzy_control*/

// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NB","NB","PB");

// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NB","NS","PB");


// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NB","NVS","PB");


// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NB","QZ","PB");

// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Positive Small
fcREFLUX.insert_rule("NB","PVS","PS");

// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Positive Small
fcREFLUX.insert_rule("NB","PS","PVS");

// If ErrorREFLUX IS Negative Big and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("NB","PB","QZ");



// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NS","NB","PB");

// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NS","NS","PB");

// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NS","NVS","PB");

// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Positive Small
fcREFLUX.insert_rule("NS","QZ","PS");

// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Positive Very Small
fcREFLUX.insert_rule("NS","PVS","PVS");

// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("NS","PS","QZ");

// If ErrorREFLUX IS Negative Small and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Negative Very Small
fcREFLUX.insert_rule("NS","PB","NVS");



// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NVS","NB","PB");

// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("NVS","NS","PB");

// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Positive Small
fcREFLUX.insert_rule("NVS","NVS","PS");

// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Positive Very Small
fcREFLUX.insert_rule("NVS","QZ","PVS");

// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("NVS","PVS","QZ");

// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Negative Very Small
fcREFLUX.insert_rule("NVS","PS","NVS");

// If ErrorREFLUX IS Negative Very Small and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Negative Small
fcREFLUX.insert_rule("NVS","PB","NS");




// If ErrorREFLUX IS  Quasi Zero and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Positive Big
fcREFLUX.insert_rule("QZ","NB","PB");

// If ErrorREFLUX IS Quasi Zero and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Positive Small
fcREFLUX.insert_rule("QZ","NS","PS");

// If ErrorREFLUX IS Quasi Zero and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Positive Very Small
fcREFLUX.insert_rule("QZ","NVS","PVS");

// If ErrorREFLUX IS Quasi Zero and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("QZ","QZ","QZ");

// If ErrorREFLUX IS Quasi Zero and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Negative Very Small
fcREFLUX.insert_rule("QZ","PVS","NVS");

// If ErrorREFLUX IS Quasi Zero and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Negative Small
fcREFLUX.insert_rule("QZ","PS","NS");

// If ErrorREFLUX IS Quasi Zero and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("QZ","PB","NB");



// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Positive Small
fcREFLUX.insert_rule("PVS","NB","PS");

// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Positive Very Small
fcREFLUX.insert_rule("PVS","NS","PVS");

// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("PVS","NVS","QZ");

// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Negative Very Small
fcREFLUX.insert_rule("PVS","QZ","NVS");

// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Negative Small
fcREFLUX.insert_rule("PVS","PVS","NS");

// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PVS","PS","NB");

// If ErrorREFLUX IS Positive Very Small and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PVS","PB","NB");



// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Positive Very Small
fcREFLUX.insert_rule("PS","NB","PVS");

// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("PS","NS","QZ");

// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Negative Very Small
fcREFLUX.insert_rule("PS","NVS","NVS");

// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Negative Small
fcREFLUX.insert_rule("PS","QZ","NS");

// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PS","PVS","NB");

// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PS","PS","NB");

// If ErrorREFLUX IS Positive Small and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PS","PB","NB");



// If ErrorREFLUX IS  Positive Big and DeltaErrorREFLUX IS Negative Big THEN ControlREFLUX IS Quasi Zero
fcREFLUX.insert_rule("PB","NB","QZ");

// If ErrorREFLUX IS Positive Big and DeltaErrorREFLUX IS Negative Small THEN ControlREFLUX IS Negative Very Small
fcREFLUX.insert_rule("PB","NS","NVS");

// If ErrorREFLUX IS Positive Big and DeltaErrorREFLUX IS Negative Very Small THEN ControlREFLUX IS Negative Small
fcREFLUX.insert_rule("PB","NVS","NS");

// If ErrorREFLUX IS Positive Big and DeltaErrorREFLUX IS Quasi Zero THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PB","QZ","NB");

// If ErrorREFLUX IS Positive Big and DeltaErrorREFLUX IS Positive Very Small THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PB","PVS","NB");

// If ErrorREFLUX IS Positive Big and DeltaErrorREFLUX IS Positive Small THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PB","PS","NB");

// If ErrorREFLUX IS Positive Big and DeltaErrorREFLUX IS Positive Big THEN ControlREFLUX IS Negative Big
fcREFLUX.insert_rule("PB","PB","NB");


// Defini-se a leitura dos sensores do seu sistema
//float ErrorInput = -100.0;
//float DeltaErrorInput = 0.0;

float min;
char fcREFLUXfilename[20];



fcREFLUX.set_defuzz(CENTEROFAREA);

// Teste para os controles

//min =  navio(fcREFLUX,1);
//  printf("Minimum ErrorREFLUX = %f\n", min);
  fcREFLUX.save_m("controlebottom", 0);

return &fcREFLUX;

}

