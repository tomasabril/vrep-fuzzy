// Project FLIE-Fuzzy Logic Inference Engine - João Alberto Fabro - out/1996

// File flie.cc

#include "Fermenta.h"
#include <stdlib.h> // Random!
#include <stdio.h> // Random!

#define DOS

// And last, we define one control system that will behave by that rules!

fuzzy_control fc,fc1, fc2; // Only global Variable!!!! Used in FlieGA();

recurrent_neural_net NEURO_NET1;
vectorpair Pares1;
recurrent_neural_net NEURO_NET2;
vectorpair Pares2;

training_pair *tp1;

trapezoid_category cat[21];
trapezoid_category cat1[21];// NeuroFlie
trapezoid_category DeltaErrorcat[2];// NeuroFlie

// And, for purpose of ease of use, we define linguistic variables to
//put the set into!

linguisticvariable Error, DeltaError, Control;
linguisticvariable Error1, NextStepError, Control1; // NeuroFlie
linguisticvariable DeltaError1;

#ifndef DOS
   void main(int argc, char *argv[])
#else
   void main1(int argc, char *argv[])
#endif

{
// In the main program, we have to instantiate the variables to contain

// all the fuzzy sets, and define them!

// We also have to define the rules of inference that will define the

// behavior of the control system! We also have to instantiate them!



// And last, we define one control system that will behave by that rules!
//fuzzy_control fc;

// And some variables that will contain the inputs and outputs(defuzzified) of
// the system under control!

float SumError, ControlOutput;

definelingvars5x5();

// Define the defuzzification method!

fc.set_defuzz(MAXIMUM);
fc1.set_defuzz(MAXIMUM);
fc2.set_defuzz(MAXIMUM);

// Define the fuzzy_control(by the fuzzy inputs (Error, DeltaError) and
// output (Control)

fc.definevars(Error, DeltaError, Control);
fc1.definevars(Error, DeltaError, Control);
fc2.definevars(Error, DeltaError, Control);

PDrulebase5x5(fc);
PDrulebase5x5(fc1);
PDrulebase5x5(fc2);



//*************** Begin loading of controllers *********************

// Define the neural network to be loaded!
NEURO_NET1.load_net("d51");  // NeuroFlie
Pares1.load_vector_from_files("d51"); // NeuroFlie

// Define the neural network to be loaded!
//NEURO_NET2.load_net("5al");  // NeuroFlie
//Pares2.load_vector_from_files("7al1"); // NeuroFlie


// Define the fuzzy_control(by the fuzzy inputs (Error1, NextStepError1) and

// output (Control1)
#ifdef PRED
fc1.definevars(NextStepError,DeltaError, Control1);
DeltaPPnewrulebase(fc1);

//fc2.definevars(NextStepError,DeltaError, Control1);
//DeltaPPnewrulebase(fc2);

#else
fc1.definevars(Error,DeltaError, Control);
PDrulebase5x5(fc1);
fc2.definevars(Error,DeltaError, Control);
PDrulebase5x5(fc2);
#endif

//***************End Loading Controllers*********************

//fc.set_defuzz(AVERAGEOFMAX);
//fc.set_defuzz(MAXIMUM);
//fc1.set_defuzz(AVERAGEOFMAX);
fc.set_defuzz(CENTEROFAREA);
fc1.set_defuzz(CENTEROFAREA);
fc2.set_defuzz(CENTEROFAREA);

fermentador(fc1,fc2, 0,4);// 1 Shows Setpoints, 2 Shows State Vector

int i;
float min=100000.0;
float indexmin=0;
char fcfilename[30];
float vel1, vel2;

if(argc>1)
 {
  sprintf(fcfilename, argv[1]);
//  NEURO_NET1.load_net(fcfilename);
  fc1.load(fcfilename);
  sprintf(fcfilename, argv[2]);
//  NEURO_NET2.load_net(fcfilename);
  fc2.load(fcfilename);
//  vel1 = (float)atof(argv[3]);
//  vel2 = (float)atof(argv[4]);

  min =  fermentador(fc1,fc2, 0,4);// 1 Shows Setpoints, 2 Shows State Vector
                                // 3 Shows Input and output of Fuzzy System!!
        printf("Controllers %s \t  Error %f\t ", argv[1], min);
        printf("\n");
 }

else
{
 cout << " Agora Testando 10 vezes com CENTEROFAREA " << "\n\n";
 fc1.set_defuzz(CENTEROFAREA);
 for(i=0;i<10;i++)
 {
   sprintf(fcfilename, "CAPDinc5%d", i);
   fliega3(fcfilename);
 //  NEURO_NET.save_net(fcfilename);
 }
}
fflush(stdout);

}

void definelingvars7x7()
{

// Define fuzzy sets for the linguistic variable Error

cat[0].setname("NB");
cat[0].setrange(-100,0);
cat[0].setval(-100,-100, -20,-10);
cat1[0].setname("NB");
cat1[0].setrange(-100,0);
cat1[0].setval(-100,-100, -20,-10);

cat[1].setname("NS");
cat[1].setrange(-20,0);
cat[1].setval(-20, -20, -10, 0);
cat1[1].setname("NS");
cat1[1].setrange(-20,0);
cat1[1].setval(-20, -20, -10, 0);

cat[2].setname("NVS");
cat[2].setrange(-50,0);
cat[2].setval(-10,-5, -5 ,0);
cat1[2].setname("NVS");
cat1[2].setrange(-50,0);
cat1[2].setval(-10,-5, -5 ,0);

cat[3].setname("QZ");
cat[3].setrange(-10,+10);
cat[3].setval(-5,0,0,5);
cat1[3].setname("QZ");
cat1[3].setrange(-10,+10);
cat1[3].setval(-5,0,0,5);

cat[4].setname("PVS");
cat[4].setrange(0,+50);
cat[4].setval(0,5,5,10);
cat1[4].setname("PVS");
cat1[4].setrange(0,50);
cat1[4].setval(0,5,5,10);

cat[5].setname("PS");
cat[5].setrange(0,+20);
cat[5].setval(0, 10,10,20);
cat1[5].setname("PS");
cat1[5].setrange(0,+20);
cat1[5].setval(0, 10,10,20);

cat[6].setname("PB");
cat[6].setrange(0,+100);
cat[6].setval(10, 20, 100, 100);
cat1[6].setname("PB");
cat1[6].setrange(0,+100);
cat1[6].setval(10, 20, 100, 100);



// Define the linguistic variable Error

Error.setname("Error");
Error.includecategory(&cat[0]);
Error.includecategory(&cat[1]);
Error.includecategory(&cat[2]);
Error.includecategory(&cat[3]);
Error.includecategory(&cat[4]);
Error.includecategory(&cat[5]);
Error.includecategory(&cat[6]);

// Define the linguistic variable Error1

Error1.setname("Error1");
Error1.includecategory(&cat1[0]);
Error1.includecategory(&cat1[1]);
Error1.includecategory(&cat1[2]);
Error1.includecategory(&cat1[3]);
Error1.includecategory(&cat1[4]);
Error1.includecategory(&cat1[5]);
Error1.includecategory(&cat1[6]);


// Define fuzzy sets for the linguistic variable DeltaError

cat[7].setname("NB");
cat[7].setrange(-20,0);
cat[7].setval(-20,-20,-10,-5);
cat1[7].setname("NB");
cat1[7].setrange(-20,0);
cat1[7].setval(-20,-20,-10,-5);

cat[8].setname("NS");
cat[8].setrange(-10,0);
cat[8].setval(-10, -5, -5,0);
cat1[8].setname("NS");
cat1[8].setrange(-10,0);
cat1[8].setval(-10, -5, -5,0);

cat[9].setname("NVS");
cat[9].setrange(-5,0);
cat[9].setval(-5,-1, -1, 0);
cat1[9].setname("NVS");
cat1[9].setrange(-100,0);
cat1[9].setval(-10,-10, -5, 0);

cat[10].setname("QZ");
cat[10].setrange(-5,+5);
cat[10].setval(-5,0,0,5);
cat1[10].setname("QZ");
cat1[10].setrange(-5,+5);
cat1[10].setval(-5,0,0,5);

cat[11].setname("PVS");
cat[11].setrange(0,+5);
cat[11].setval(0,1,1,5);
cat1[11].setname("PVS");
cat1[11].setrange(0,+100);
cat1[11].setval(0,5,10,10);

cat[12].setname("PS");
cat[12].setrange(0,+10);
cat[12].setval(0,5,5,10);
cat1[12].setname("PS");
cat1[12].setrange(0,+100);
cat1[12].setval(0,5,5,10);

cat[13].setname("PB");
cat[13].setrange(0,+20);
cat[13].setval(5,10,20,20);
cat1[13].setname("PB");
cat1[13].setrange(0,+20);
cat1[13].setval(5,10,20,20);


// Define Linguistic Variable DeltaError
DeltaError.setname("DeltaError");
DeltaError.includecategory(&cat[7]);
DeltaError.includecategory(&cat[8]);
DeltaError.includecategory(&cat[9]);
DeltaError.includecategory(&cat[10]);
DeltaError.includecategory(&cat[11]);
DeltaError.includecategory(&cat[12]);
DeltaError.includecategory(&cat[13]);

// Define Linguistic Variable NextStepError
NextStepError.setname("NextStepError");
NextStepError.includecategory(&cat1[7]);
NextStepError.includecategory(&cat1[8]);
NextStepError.includecategory(&cat1[9]);
NextStepError.includecategory(&cat1[10]);
NextStepError.includecategory(&cat1[11]);
NextStepError.includecategory(&cat1[12]);
NextStepError.includecategory(&cat1[13]);



// Define fuzzy sets for the linguistic variable  Control

cat[14].setname("NB");
cat[14].setrange(-100,0);
cat[14].setval(-100,-100,-80,-20);
cat1[14].setname("NB");
cat1[14].setrange(-100,0);
cat1[14].setval(-100,-100,-80,-20);

cat[15].setname("NS");
cat[15].setrange(-50,0);
cat[15].setval(-50,-50,-20,0);
cat1[15].setname("NS");
cat1[15].setrange(-50,0);
cat1[15].setval(-50,-50,-20,0);

cat[16].setname("NVS");
cat[16].setrange(-20,0);
cat[16].setval(-20,-10,-5,0);
cat1[16].setname("NVS");
cat1[16].setrange(-20,0);
cat1[16].setval(-20,-10,-5,0);

cat[17].setname("QZ");
cat[17].setrange(-10,+10);
cat[17].setval(-5,0,0,5);
cat1[17].setname("QZ");
cat1[17].setrange(-10,+10);
cat1[17].setval(-5,0,0,5);


cat[18].setname("PVS");
cat[18].setrange(0,+20);
cat[18].setval(0,5,10,20);
cat1[18].setname("PVS");
cat1[18].setrange(0,+20);
cat1[18].setval(0,5,10,20);


cat[19].setname("PS");
cat[19].setrange(0,+50);
cat[19].setval(0,20,50,50);
cat1[19].setname("PS");
cat1[19].setrange(0,+50);
cat1[19].setval(0,20,50,50);


cat[20].setname("PB");
cat[20].setrange(0,+100);
cat[20].setval(20,80,100,100);
cat1[20].setname("PB");
cat1[20].setrange(0,+100);
cat1[20].setval(20,80,100,100);



// Define the linguistic variable Control
Control.setname("Control");
Control.includecategory(&cat[14]);
Control.includecategory(&cat[15]);
Control.includecategory(&cat[16]);
Control.includecategory(&cat[17]);
Control.includecategory(&cat[18]);
Control.includecategory(&cat[19]);
Control.includecategory(&cat[20]);

// Define the linguistic variable Control1
Control1.setname("Control");
Control1.includecategory(&cat1[14]);
Control1.includecategory(&cat1[15]);
Control1.includecategory(&cat1[16]);
Control1.includecategory(&cat1[17]);
Control1.includecategory(&cat1[18]);
Control1.includecategory(&cat1[19]);
Control1.includecategory(&cat1[20]);
}

void definelingvars5x5()
{

// Define fuzzy sets for the linguistic variable Error

cat[0].setname("NB");
cat[0].setrange(-100,0);
cat[0].setval(-100,-100, -20,-10);
cat1[0].setname("NB");
cat1[0].setrange(-100,0);
cat1[0].setval(-100,-100, -20,-10);

cat[1].setname("NS");
cat[1].setrange(-20,0);
cat[1].setval(-20, -20, -10, 0);
cat1[1].setname("NS");
cat1[1].setrange(-20,0);
cat1[1].setval(-20, -20, -10, 0);

cat[2].setname("QZ");
cat[2].setrange(-10,+10);
cat[2].setval(-5,0,0,5);
cat1[2].setname("QZ");
cat1[2].setrange(-10,+10);
cat1[2].setval(-5,0,0,5);

cat[3].setname("PS");
cat[3].setrange(0,+20);
cat[3].setval(0, 10,10,20);
cat1[3].setname("PS");
cat1[3].setrange(0,+20);
cat1[3].setval(0, 10,10,20);

cat[4].setname("PB");
cat[4].setrange(0,+100);
cat[4].setval(10, 20, 100, 100);
cat1[4].setname("PB");
cat1[4].setrange(0,+100);
cat1[4].setval(10, 20, 100, 100);



// Define the linguistic variable Error

Error.setname("Error");
Error.includecategory(&cat[0]);
Error.includecategory(&cat[1]);
Error.includecategory(&cat[2]);
Error.includecategory(&cat[3]);
Error.includecategory(&cat[4]);

// Define the linguistic variable Error1

Error1.setname("Error1");
Error1.includecategory(&cat1[0]);
Error1.includecategory(&cat1[1]);
Error1.includecategory(&cat1[2]);
Error1.includecategory(&cat1[3]);
Error1.includecategory(&cat1[4]);


// Define fuzzy sets for the linguistic variable DeltaError

cat[7].setname("NB");
cat[7].setrange(-20,0);
cat[7].setval(-20,-20,-10,-5);
cat1[7].setname("NB");
cat1[7].setrange(-20,0);
cat1[7].setval(-20,-20,-10,-5);

cat[8].setname("NS");
cat[8].setrange(-10,0);
cat[8].setval(-10, -5, -5,0);
cat1[8].setname("NS");
cat1[8].setrange(-10,0);
cat1[8].setval(-10, -5, -5,0);

cat[9].setname("QZ");
cat[9].setrange(-5,+5);
cat[9].setval(-5,0,0,5);
cat1[9].setname("QZ");
cat1[9].setrange(-5,+5);
cat1[9].setval(-5,0,0,5);

cat[10].setname("PS");
cat[10].setrange(0,+10);
cat[10].setval(0,5,5,10);
cat1[10].setname("PS");
cat1[10].setrange(0,+100);
cat1[10].setval(0,5,5,10);

cat[11].setname("PB");
cat[11].setrange(0,+20);
cat[11].setval(5,10,20,20);
cat1[11].setname("PB");
cat1[11].setrange(0,+20);
cat1[11].setval(5,10,20,20);


// Define Linguistic Variable DeltaError
DeltaError.setname("DeltaError");
DeltaError.includecategory(&cat[7]);
DeltaError.includecategory(&cat[8]);
DeltaError.includecategory(&cat[9]);
DeltaError.includecategory(&cat[10]);
DeltaError.includecategory(&cat[11]);

// Define Linguistic Variable NextStepError
NextStepError.setname("NextStepError");
NextStepError.includecategory(&cat1[7]);
NextStepError.includecategory(&cat1[8]);
NextStepError.includecategory(&cat1[9]);
NextStepError.includecategory(&cat1[10]);
NextStepError.includecategory(&cat1[11]);


// Define fuzzy sets for the linguistic variable  Control

cat[14].setname("NB");
cat[14].setrange(-100,0);
cat[14].setval(-100,-100,-80,-20);
cat1[14].setname("NB");
cat1[14].setrange(-100,0);
cat1[14].setval(-100,-100,-80,-20);

cat[15].setname("NS");
cat[15].setrange(-50,0);
cat[15].setval(-50,-50,-20,0);
cat1[15].setname("NS");
cat1[15].setrange(-50,0);
cat1[15].setval(-50,-50,-20,0);

cat[16].setname("QZ");
cat[16].setrange(-10,+10);
cat[16].setval(-5,0,0,5);
cat1[16].setname("QZ");
cat1[16].setrange(-10,+10);
cat1[16].setval(-5,0,0,5);

cat[17].setname("PS");
cat[17].setrange(0,+50);
cat[17].setval(0,20,50,50);
cat1[17].setname("PS");
cat1[17].setrange(0,+50);
cat1[17].setval(0,20,50,50);

cat[18].setname("PB");
cat[18].setrange(0,+100);
cat[18].setval(20,80,100,100);
cat1[18].setname("PB");
cat1[18].setrange(0,+100);
cat1[18].setval(20,80,100,100);



// Define the linguistic variable Control
Control.setname("Control");
Control.includecategory(&cat[14]);
Control.includecategory(&cat[15]);
Control.includecategory(&cat[16]);
Control.includecategory(&cat[17]);
Control.includecategory(&cat[18]);

// Define the linguistic variable Control1
Control1.setname("Control");
Control1.includecategory(&cat1[14]);
Control1.includecategory(&cat1[15]);
Control1.includecategory(&cat1[16]);
Control1.includecategory(&cat1[17]);
Control1.includecategory(&cat1[18]);
}

void PDrulebase(fuzzy_control &fc)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If Error IS Negative Big and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NB","NB","PB");
// If Error IS Negative Big and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NB","NS","PB");
// If Error IS Negative Big and DeltaError IS Negative Very Small THEN Control IS Positive Big
fc.insert_rule("NB","NVS","PB");
// If Error IS Negative Big and DeltaError IS Quasi Zero THEN Control IS Positive Big
fc.insert_rule("NB","QZ","PB");
// If Error IS Negative Big and DeltaError IS Positive Very Small THEN Control IS Positive Small
fc.insert_rule("NB","PVS","PS");
// If Error IS Negative Big and DeltaError IS Positive Small THEN Control IS Positive Small
fc.insert_rule("NB","PS","PVS");
// If Error IS Negative Big and DeltaError IS Positive Big THEN Control IS Quasi Zero
fc.insert_rule("NB","PB","QZ");


// If Error IS Negative Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NS","NB","PB");
// If Error IS Negative Small and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NS","NS","PB");
// If Error IS Negative Small and DeltaError IS Negative Very Small THEN Control IS Positive Big
fc.insert_rule("NS","NVS","PB");
// If Error IS Negative Small and DeltaError IS Quasi Zero THEN Control IS Positive Small
fc.insert_rule("NS","QZ","PS");
// If Error IS Negative Small and DeltaError IS Positive Very Small THEN Control IS Positive Very Small
fc.insert_rule("NS","PVS","PVS");
// If Error IS Negative Small and DeltaError IS Positive Small THEN Control IS Quasi Zero
fc.insert_rule("NS","PS","QZ");
// If Error IS Negative Small and DeltaError IS Positive Big THEN Control IS Negative Very Small
fc.insert_rule("NS","PB","NVS");


// If Error IS Negative Very Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NVS","NB","PB");
// If Error IS Negative Very Small and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NVS","NS","PB");
// If Error IS Negative Very Small and DeltaError IS Negative Very Small THEN Control IS Positive Small
fc.insert_rule("NVS","NVS","PS");
// If Error IS Negative Very Small and DeltaError IS Quasi Zero THEN Control IS Positive Very Small
fc.insert_rule("NVS","QZ","PVS");
// If Error IS Negative Very Small and DeltaError IS Positive Very Small THEN Control IS Quasi Zero
fc.insert_rule("NVS","PVS","QZ");
// If Error IS Negative Very Small and DeltaError IS Positive Small THEN Control IS Negative Very Small
fc.insert_rule("NVS","PS","NVS");
// If Error IS Negative Very Small and DeltaError IS Positive Big THEN Control IS Negative Small
fc.insert_rule("NVS","PB","NS");


// If Error IS  Quasi Zero and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("QZ","NB","PB");
// If Error IS Quasi Zero and DeltaError IS Negative Small THEN Control IS Positive Small
fc.insert_rule("QZ","NS","PS");
// If Error IS Quasi Zero and DeltaError IS Negative Very Small THEN Control IS Positive Very Small
fc.insert_rule("QZ","NVS","PVS");
// If Error IS Quasi Zero and DeltaError IS Quasi Zero THEN Control IS Quasi Zero
fc.insert_rule("QZ","QZ","QZ");
// If Error IS Quasi Zero and DeltaError IS Positive Very Small THEN Control IS Negative Very Small
fc.insert_rule("QZ","PVS","NVS");
// If Error IS Quasi Zero and DeltaError IS Positive Small THEN Control IS Negative Small
fc.insert_rule("QZ","PS","NS");
// If Error IS Quasi Zero and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("QZ","PB","NB");


// If Error IS Positive Very Small and DeltaError IS Negative Big THEN Control IS Positive Small
fc.insert_rule("PVS","NB","PS");
// If Error IS Positive Very Small and DeltaError IS Negative Small THEN Control IS Positive Very Small
fc.insert_rule("PVS","NS","PVS");
// If Error IS Positive Very Small and DeltaError IS Negative Very Small THEN Control IS Quasi Zero
fc.insert_rule("PVS","NVS","QZ");
// If Error IS Positive Very Small and DeltaError IS Quasi Zero THEN Control IS Negative Very Small
fc.insert_rule("PVS","QZ","NVS");
// If Error IS Positive Very Small and DeltaError IS Positive Very Small THEN Control IS Negative Small
fc.insert_rule("PVS","PVS","NS");
// If Error IS Positive Very Small and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PVS","PS","NB");
// If Error IS Positive Very Small and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PVS","PB","NB");


// If Error IS Positive Small and DeltaError IS Negative Big THEN Control IS Positive Very Small
fc.insert_rule("PS","NB","PVS");
// If Error IS Positive Small and DeltaError IS Negative Small THEN Control IS Quasi Zero
fc.insert_rule("PS","NS","QZ");
// If Error IS Positive Small and DeltaError IS Negative Very Small THEN Control IS Negative Very Small
fc.insert_rule("PS","NVS","NVS");
// If Error IS Positive Small and DeltaError IS Quasi Zero THEN Control IS Negative Small
fc.insert_rule("PS","QZ","NS");
// If Error IS Positive Small and DeltaError IS Positive Very Small THEN Control IS Negative Big
fc.insert_rule("PS","PVS","NB");
// If Error IS Positive Small and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PS","PS","NB");
// If Error IS Positive Small and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PS","PB","NB");


// If Error IS  Positive Big and DeltaError IS Negative Big THEN Control IS Quasi Zero
fc.insert_rule("PB","NB","QZ");
// If Error IS Positive Big and DeltaError IS Negative Small THEN Control IS Negative Very Small
fc.insert_rule("PB","NS","NVS");
// If Error IS Positive Big and DeltaError IS Negative Very Small THEN Control IS Negative Small
fc.insert_rule("PB","NVS","NS");
// If Error IS Positive Big and DeltaError IS Quasi Zero THEN Control IS Negative Big
fc.insert_rule("PB","QZ","NB");
// If Error IS Positive Big and DeltaError IS Positive Very Small THEN Control IS Negative Big
fc.insert_rule("PB","PVS","NB");
// If Error IS Positive Big and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PB","PS","NB");
// If Error IS Positive Big and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PB","PB","NB");
}

void PDrulebase5x5(fuzzy_control &fc)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If Error IS Negative Big and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NB","NB","PB");
// If Error IS Negative Big and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NB","NS","PB");
// If Error IS Negative Big and DeltaError IS Quasi Zero THEN Control IS Positive Big
fc.insert_rule("NB","QZ","PB");
// If Error IS Negative Big and DeltaError IS Positive Small THEN Control IS Positive Small
fc.insert_rule("NB","PS","PS");
// If Error IS Negative Big and DeltaError IS Positive Big THEN Control IS Quasi Zero
fc.insert_rule("NB","PB","QZ");


// If Error IS Negative Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("NS","NB","PB");
// If Error IS Negative Small and DeltaError IS Negative Small THEN Control IS Positive Big
fc.insert_rule("NS","NS","PB");
// If Error IS Negative Small and DeltaError IS Quasi Zero THEN Control IS Positive Small
fc.insert_rule("NS","QZ","PS");
// If Error IS Negative Small and DeltaError IS Positive Small THEN Control IS Quasi Zero
fc.insert_rule("NS","PS","QZ");
// If Error IS Negative Small and DeltaError IS Positive Big THEN Control IS Negative Very Small
fc.insert_rule("NS","PB","NS");


// If Error IS  Quasi Zero and DeltaError IS Negative Big THEN Control IS Positive Big
fc.insert_rule("QZ","NB","PB");
// If Error IS Quasi Zero and DeltaError IS Negative Small THEN Control IS Positive Small
fc.insert_rule("QZ","NS","PS");
// If Error IS Quasi Zero and DeltaError IS Quasi Zero THEN Control IS Quasi Zero
fc.insert_rule("QZ","QZ","QZ");
// If Error IS Quasi Zero and DeltaError IS Positive Small THEN Control IS Negative Small
fc.insert_rule("QZ","PS","NS");
// If Error IS Quasi Zero and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("QZ","PB","NB");



// If Error IS Positive Small and DeltaError IS Negative Big THEN Control IS Positive Very Small
fc.insert_rule("PS","NB","PS");
// If Error IS Positive Small and DeltaError IS Negative Small THEN Control IS Quasi Zero
fc.insert_rule("PS","NS","QZ");
// If Error IS Positive Small and DeltaError IS Quasi Zero THEN Control IS Negative Small
fc.insert_rule("PS","QZ","NS");
// If Error IS Positive Small and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PS","PS","NB");
// If Error IS Positive Small and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PS","PB","NB");


// If Error IS  Positive Big and DeltaError IS Negative Big THEN Control IS Quasi Zero
fc.insert_rule("PB","NB","QZ");
// If Error IS Positive Big and DeltaError IS Negative Small THEN Control IS Negative Very Small
fc.insert_rule("PB","NS","NS");
// If Error IS Positive Big and DeltaError IS Quasi Zero THEN Control IS Negative Big
fc.insert_rule("PB","QZ","NB");
// If Error IS Positive Big and DeltaError IS Positive Small THEN Control IS Negative Big
fc.insert_rule("PB","PS","NB");
// If Error IS Positive Big and DeltaError IS Positive Big THEN Control IS Negative Big
fc.insert_rule("PB","PB","NB");
}

void PPrulebase(fuzzy_control &fc1)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If Error IS Negative Big and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NB","NB","PB");
// If Error IS Negative Big and NextStepError IS Negative Small THEN Control IS Positive Small
fc1.insert_rule("NB","NS","PS");
// If Error IS Negative Big and NextStepError IS Negative Very Small THEN Control IS Positive Very Small
fc1.insert_rule("NB","NVS","PVS");
// If Error IS Negative Big and NextStepError IS Quasi Zero THEN Control IS Neg Very Small
fc1.insert_rule("NB","QZ","NVS");
// If Error IS Negative Big and NextStepError IS Positive Very Small THEN Control IS Neg Small
fc1.insert_rule("NB","PVS","NS");
// If Error IS Negative Big and NextStepError IS Positive Small THEN Control IS Neg Big
fc1.insert_rule("NB","PS","NB");
// If Error IS Negative Big and NextStepError IS Positive Big THEN Control IS Neg Big
fc1.insert_rule("NB","PB","NB");



// If Error IS Negative Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NS","NB","PB");
// If Error IS Negative Small and NextStepError IS Negative Small THEN Control IS Positive Big
fc1.insert_rule("NS","NS","PB");
// If Error IS Negative Small and NextStepError IS Negative Very Small THEN Control IS Positive Small
fc1.insert_rule("NS","NVS","PS");
// If Error IS Negative Small and NextStepError IS Quasi Zero THEN Control IS Neg Very Small
fc1.insert_rule("NS","QZ","NVS");
// If Error IS Negative Small and NextStepError IS Positive Very Small THEN Control IS Neg Small
fc1.insert_rule("NS","PVS","NS");
// If Error IS Negative Small and NextStepError IS Positive Small THEN Control IS Neg Big
fc1.insert_rule("NS","PS","NB");
// If Error IS Negative Small and NextStepError IS Positive Big THEN Control IS Neg Big
fc1.insert_rule("NS","PB","NB");


// If Error IS Negative Very Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NVS","NB","PB");
// If Error IS Negative Very Small and NextStepError IS Negative Small THEN Control IS Positive Big
fc1.insert_rule("NVS","NS","PB");
// If Error IS Negative Very Small and NextStepError IS Negative Very Small THEN Control IS Positive Small
fc1.insert_rule("NVS","NVS","PS");
// If Error IS Negative Very Small and NextStepError IS Quasi Zero THEN Control IS Positive Very Small
fc1.insert_rule("NVS","QZ","PVS");
// If Error IS Negative Very Small and NextStepError IS Positive Very Small THEN Control IS Neg Small
fc1.insert_rule("NVS","PVS","NS");
// If Error IS Negative Very Small and NextStepError IS Positive Small THEN Control IS Negative Big
fc1.insert_rule("NVS","PS","NB");
// If Error IS Negative Very Small and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("NVS","PB","NB");


// If Error IS  Quasi Zero and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("QZ","NB","PB");
// If Error IS Quasi Zero and NextStepError IS Negative Small THEN Control IS Positive Small
fc1.insert_rule("QZ","NS","PS");
// If Error IS Quasi Zero and NextStepError IS Negative Very Small THEN Control IS Positive Very Small
fc1.insert_rule("QZ","NVS","PVS");
// If Error IS Quasi Zero and NextStepError IS Quasi Zero THEN Control IS Quasi Zero
fc1.insert_rule("QZ","QZ","QZ");
// If Error IS Quasi Zero and NextStepError IS Positive Very Small THEN Control IS Negative Very Small
fc1.insert_rule("QZ","PVS","NVS");
// If Error IS Quasi Zero and NextStepError IS Positive Small THEN Control IS Negative Small
fc1.insert_rule("QZ","PS","NS");
// If Error IS Quasi Zero and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("QZ","PB","NB");


// If Error IS Positive Very Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("PVS","NB","PB");
// If Error IS Positive Very Small and NextStepError IS Negative Small THEN Control IS Positive Big
fc1.insert_rule("PVS","NS","PB");
// If Error IS Positive Very Small and NextStepError IS Negative Very Small THEN Control IS Positive Small
fc1.insert_rule("PVS","NVS","PS");
// If Error IS Positive Very Small and NextStepError IS Quasi Zero THEN Control IS Negative Very Small
fc1.insert_rule("PVS","QZ","NVS");
// If Error IS Positive Very Small and NextStepError IS Positive Very Small THEN Control IS Negative Small
fc1.insert_rule("PVS","PVS","NS");
// If Error IS Positive Very Small and NextStepError IS Positive Small THEN Control IS Negative Big
fc1.insert_rule("PVS","PS","NB");
// If Error IS Positive Very Small and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("PVS","PB","NB");


// If Error IS Positive Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("PS","NB","PB");
// If Error IS Positive Small and NextStepError IS Negative Small THEN Control IS Pos Big
fc1.insert_rule("PS","NS","PB");
// If Error IS Positive Small and NextStepError IS Negative Very Small THEN Control IS Pos Small
fc1.insert_rule("PS","NVS","PS");
// If Error IS Positive Small and NextStepError IS Quasi Zero THEN Control IS Negative Very Small
fc1.insert_rule("PS","QZ","NVS");
// If Error IS Positive Small and NextStepError IS Positive Very Small THEN Control IS Negative Small
fc1.insert_rule("PS","PVS","NS");
// If Error IS Positive Small and NextStepError IS Positive Small THEN Control IS Negative Big
fc1.insert_rule("PS","PS","NB");
// If Error IS Positive Small and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("PS","PB","NB");


// If Error IS  Positive Big and NextStepError IS Negative Big THEN Control IS Pos Big
fc1.insert_rule("PB","NB","PB");
// If Error IS Positive Big and NextStepError IS Negative Small THEN Control IS Pos Small
fc1.insert_rule("PB","NS","PS");
// If Error IS Positive Big and NextStepError IS Negative Very Small THEN Control IS Pos Very Small
fc1.insert_rule("PB","NVS","PVS");
// If Error IS Positive Big and NextStepError IS Quasi Zero THEN Control IS Negative Very Small
fc1.insert_rule("PB","QZ","NVS");
// If Error IS Positive Big and NextStepError IS Positive Very Small THEN Control IS Negative Small
fc1.insert_rule("PB","PVS","NS");
// If Error IS Positive Big and NextStepError IS Positive Small THEN Control IS Negative Big
fc1.insert_rule("PB","PS","NB");
// If Error IS Positive Big and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("PB","PB","NB");
}

void PPrulebase5x5(fuzzy_control &fc1)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If Error IS Negative Big and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NB","NB","PB");
// If Error IS Negative Big and NextStepError IS Negative Small THEN Control IS Positive Small
fc1.insert_rule("NB","NS","PS");
// If Error IS Negative Big and NextStepError IS Quasi Zero THEN Control IS Neg Very Small
fc1.insert_rule("NB","QZ","NS");
// If Error IS Negative Big and NextStepError IS Positive Small THEN Control IS Neg Big
fc1.insert_rule("NB","PS","NB");
// If Error IS Negative Big and NextStepError IS Positive Big THEN Control IS Neg Big
fc1.insert_rule("NB","PB","NB");



// If Error IS Negative Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NS","NB","PB");
// If Error IS Negative Small and NextStepError IS Negative Small THEN Control IS Positive Big
fc1.insert_rule("NS","NS","PB");
// If Error IS Negative Small and NextStepError IS Quasi Zero THEN Control IS Neg Very Small
fc1.insert_rule("NS","QZ","NS");
// If Error IS Negative Small and NextStepError IS Positive Small THEN Control IS Neg Big
fc1.insert_rule("NS","PS","NB");
// If Error IS Negative Small and NextStepError IS Positive Big THEN Control IS Neg Big
fc1.insert_rule("NS","PB","NB");



// If Error IS  Quasi Zero and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("QZ","NB","PB");
// If Error IS Quasi Zero and NextStepError IS Negative Small THEN Control IS Positive Small
fc1.insert_rule("QZ","NS","PS");
// If Error IS Quasi Zero and NextStepError IS Quasi Zero THEN Control IS Quasi Zero
fc1.insert_rule("QZ","QZ","QZ");
// If Error IS Quasi Zero and NextStepError IS Positive Small THEN Control IS Negative Small
fc1.insert_rule("QZ","PS","NS");
// If Error IS Quasi Zero and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("QZ","PB","NB");



// If Error IS Positive Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("PS","NB","PB");
// If Error IS Positive Small and NextStepError IS Negative Small THEN Control IS Pos Big
fc1.insert_rule("PS","NS","PB");
// If Error IS Positive Small and NextStepError IS Quasi Zero THEN Control IS Negative Very Small
fc1.insert_rule("PS","QZ","NS");
// If Error IS Positive Small and NextStepError IS Positive Small THEN Control IS Negative Big
fc1.insert_rule("PS","PS","NB");
// If Error IS Positive Small and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("PS","PB","NB");


// If Error IS  Positive Big and NextStepError IS Negative Big THEN Control IS Pos Big
fc1.insert_rule("PB","NB","PB");
// If Error IS Positive Big and NextStepError IS Negative Small THEN Control IS Pos Small
fc1.insert_rule("PB","NS","PS");
// If Error IS Positive Big and NextStepError IS Quasi Zero THEN Control IS Negative Very Small
fc1.insert_rule("PB","QZ","NVS");
// If Error IS Positive Big and NextStepError IS Positive Small THEN Control IS Negative Big
fc1.insert_rule("PB","PS","NB");
// If Error IS Positive Big and NextStepError IS Positive Big THEN Control IS Negative Big
fc1.insert_rule("PB","PB","NB");
}


void PPnewrulebase(fuzzy_control &fc1)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If Error IS Negative Big and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NB","NB","PB");
fc1.insert_rule("NB","NS","NB");
fc1.insert_rule("NB","NVS","PS");
fc1.insert_rule("NB","QZ","NS");
fc1.insert_rule("NB","PVS","NB");
fc1.insert_rule("NB","PS","NB");
fc1.insert_rule("NB","PB","NB");

// If Error IS Negative Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NS","NB","PB");
fc1.insert_rule("NS","NS","PS");
fc1.insert_rule("NS","NVS","PVS");
fc1.insert_rule("NS","QZ","NVS");
fc1.insert_rule("NS","PVS","NS");
fc1.insert_rule("NS","PS","NB");
fc1.insert_rule("NS","PB","NB");


// If Error IS Negative Very Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NVS","NB","PB");
fc1.insert_rule("NVS","NS","PS");
fc1.insert_rule("NVS","NVS","PVS");
fc1.insert_rule("NVS","QZ","PVS");
fc1.insert_rule("NVS","PVS","NVS");
fc1.insert_rule("NVS","PS","NS");
fc1.insert_rule("NVS","PB","NB");


// If Error IS  Quasi Zero and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("QZ","NB","PB");
fc1.insert_rule("QZ","NS","PS");
fc1.insert_rule("QZ","NVS","PVS");
fc1.insert_rule("QZ","QZ","QZ");
fc1.insert_rule("QZ","PVS","NVS");
fc1.insert_rule("QZ","PS","NS");
fc1.insert_rule("QZ","PB","NB");


// If Error IS Positive Very Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("PVS","NB","PB");
fc1.insert_rule("PVS","NS","PS");
fc1.insert_rule("PVS","NVS","PVS");
fc1.insert_rule("PVS","QZ","NVS");
fc1.insert_rule("PVS","PVS","NVS");
fc1.insert_rule("PVS","PS","NS");
fc1.insert_rule("PVS","PB","NB");


// If Error IS Positive Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("PS","NB","PB");
fc1.insert_rule("PS","NS","PB");
fc1.insert_rule("PS","NVS","PS");
fc1.insert_rule("PS","QZ","PVS");
fc1.insert_rule("PS","PVS","NVS");
fc1.insert_rule("PS","PS","NS");
fc1.insert_rule("PS","PB","NB");


// If Error IS  Positive Big and NextStepError IS Negative Big THEN Control IS Pos Big
fc1.insert_rule("PB","NB","PB");
fc1.insert_rule("PB","NS","PB");
fc1.insert_rule("PB","NVS","PB");
fc1.insert_rule("PB","QZ","PS");
fc1.insert_rule("PB","PVS","NS");
fc1.insert_rule("PB","PS","PB");
fc1.insert_rule("PB","PB","NB");
}

void DeltaPPPDnewrulebase(fuzzy_control &fc2)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If DeltaError IS Small and Error IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Small","NB","NB","PB");
fc2.insert_rule("Small","NB","NS","PB");
fc2.insert_rule("Small","NB","NVS","PB");
fc2.insert_rule("Small","NB","QZ","PB");
fc2.insert_rule("Small","NB","PVS","PB");
fc2.insert_rule("Small","NB","PS","PB");
fc2.insert_rule("Small","NB","PB","PB");


// If DeltaError IS Small AND Error IS Negative Small and NextStepError IS ... THEN Control IS ...
fc2.insert_rule("Small","NS","NB","PB");
fc2.insert_rule("Small","NS","NS","PS");
fc2.insert_rule("Small","NS","NVS","PVS");
fc2.insert_rule("Small","NS","QZ","NVS");
fc2.insert_rule("Small","NS","PVS","NS");
fc2.insert_rule("Small","NS","PS","NB");
fc2.insert_rule("Small","NS","PB","NB");


// If Error IS Negative Very Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Small","NVS","NB","PB");
fc2.insert_rule("Small","NVS","NS","PS");
fc2.insert_rule("Small","NVS","NVS","PVS");
fc2.insert_rule("Small","NVS","QZ","NVS");
fc2.insert_rule("Small","NVS","PVS","NS");
fc2.insert_rule("Small","NVS","PS","NB");
fc2.insert_rule("Small","NVS","PB","NB");

// If Error IS  Quasi Zero and DeltaError IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Small","QZ","NB","PB");
fc2.insert_rule("Small","QZ","NS","PS");
fc2.insert_rule("Small","QZ","NVS","PVS");
fc2.insert_rule("Small","QZ","QZ","QZ");
fc2.insert_rule("Small","QZ","PVS","NVS");
fc2.insert_rule("Small","QZ","PS","NS");
fc2.insert_rule("Small","QZ","PB","NB");


// If Error IS Positive Very Small and DeltaError IS Negative Big THEN Control IS Positive Small
fc2.insert_rule("Small","PVS","NB","PB");
fc2.insert_rule("Small","PVS","NS","PB");
fc2.insert_rule("Small","PVS","NVS","PS");
fc2.insert_rule("Small","PVS","QZ","PVS");
fc2.insert_rule("Small","PVS","PVS","NVS");
fc2.insert_rule("Small","PVS","PS","NS");
fc2.insert_rule("Small","PVS","PB","NB");


// If Error IS Positive Small and DeltaError IS Negative Big THEN Control IS Positive Very Small
fc2.insert_rule("Small","PS","NB","PB");
fc2.insert_rule("Small","PS","NS","PB");
fc2.insert_rule("Small","PS","NVS","PS");
fc2.insert_rule("Small","PS","QZ","PVS");
fc2.insert_rule("Small","PS","PVS","NVS");
fc2.insert_rule("Small","PS","PS","NS");
fc2.insert_rule("Small","PS","PB","NB");


// If DeltaError IS Small and Error IS Positive Big THEN Control IS Negative Big
fc2.insert_rule("Small","PB","NB","NB");
fc2.insert_rule("Small","PB","NS","NB");
fc2.insert_rule("Small","PB","NVS","NB");
fc2.insert_rule("Small","PB","QZ","NB");
fc2.insert_rule("Small","PB","PVS","NB");
fc2.insert_rule("Small","PB","PS","NB");
fc2.insert_rule("Small","PB","PB","NB");




// If DeltaError IS Big and Error IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Big","NB","NB","PB");
fc2.insert_rule("Big","NB","NS","PB");
fc2.insert_rule("Big","NB","NVS","PB");
fc2.insert_rule("Big","NB","QZ","PB");
fc2.insert_rule("Big","NB","PVS","PB");
fc2.insert_rule("Big","NB","PS","PB");
fc2.insert_rule("Big","NB","PB","PB");

// If DeltaError IS Big AND Error IS Negative Small and NextStepError IS ... THEN Control IS ...
fc2.insert_rule("Big","NS","NB","PB");
fc2.insert_rule("Big","NS","NS","PB");
fc2.insert_rule("Big","NS","NVS","NS");
fc2.insert_rule("Big","NS","QZ","NS");
fc2.insert_rule("Big","NS","PVS","NB");
fc2.insert_rule("Big","NS","PS","NB");
fc2.insert_rule("Big","NS","PB","NB");


// If Error IS Negative Very Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Big","NVS","NB","PB");
fc2.insert_rule("Big","NVS","NS","PS");
fc2.insert_rule("Big","NVS","NVS","PS");
fc2.insert_rule("Big","NVS","QZ","NS");
fc2.insert_rule("Big","NVS","PVS","NS");
fc2.insert_rule("Big","NVS","PS","NB");
fc2.insert_rule("Big","NVS","PB","NB");


// If Error IS  Quasi Zero and NextStepError IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Big","QZ","NB","PB");
fc2.insert_rule("Big","QZ","NS","PS");
fc2.insert_rule("Big","QZ","NVS","PVS");
fc2.insert_rule("Big","QZ","QZ","PS");
fc2.insert_rule("Big","QZ","PVS","NS");
fc2.insert_rule("Big","QZ","PS","NS");
fc2.insert_rule("Big","QZ","PB","NB");


// If Error IS Positive Very Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Big","PVS","NB","PB");
fc2.insert_rule("Big","PVS","NS","PB");
fc2.insert_rule("Big","PVS","NVS","PB");
fc2.insert_rule("Big","PVS","QZ","PS");
fc2.insert_rule("Big","PVS","PVS","NS");
fc2.insert_rule("Big","PVS","PS","NS");
fc2.insert_rule("Big","PVS","PB","NB");


// If Error IS Positive Small and NextStepError IS Negative Big THEN Control IS Positive Big
fc2.insert_rule("Big","PS","NB","PB");
fc2.insert_rule("Big","PS","NS","PB");
fc2.insert_rule("Big","PS","NVS","PB");
fc2.insert_rule("Big","PS","QZ","PS");
fc2.insert_rule("Big","PS","PVS","PS");
fc2.insert_rule("Big","PS","PS","NB");
fc2.insert_rule("Big","PS","PB","NB");


// If DeltaError IS Big AND Error IS Positive Big THEN Control IS NEG Big
fc2.insert_rule("Big","PB","NB","NB");
fc2.insert_rule("Big","PB","NS","NB");
fc2.insert_rule("Big","PB","NVS","NB");
fc2.insert_rule("Big","PB","QZ","NB");
fc2.insert_rule("Big","PB","PVS","NB");
fc2.insert_rule("Big","PB","PS","NB");
fc2.insert_rule("Big","PB","PB","NB");
}

void DeltaPPnewrulebase(fuzzy_control &fc1)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If NextStepError IS Negative Big and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NB","NB","PB");
fc1.insert_rule("NB","NS","PB");
fc1.insert_rule("NB","NVS","PB");
fc1.insert_rule("NB","QZ","PB");
fc1.insert_rule("NB","PVS","PB");
fc1.insert_rule("NB","PS","PB");
fc1.insert_rule("NB","PB","PB");


// If NextStepError IS Negative Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NS","NB","PB");
fc1.insert_rule("NS","NS","PB");
fc1.insert_rule("NS","NVS","PB");
fc1.insert_rule("NS","QZ","PS");
fc1.insert_rule("NS","PVS","PVS");
fc1.insert_rule("NS","PS","QZ");
fc1.insert_rule("NS","PB","NVS");


// If NextStepError IS Negative Very Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NVS","NB","PB");
fc1.insert_rule("NVS","NS","PB");
fc1.insert_rule("NVS","NVS","PS");
fc1.insert_rule("NVS","QZ","PVS");
fc1.insert_rule("NVS","PVS","QZ");
fc1.insert_rule("NVS","PS","NVS");
fc1.insert_rule("NVS","PB","NS");


// If NextStepError IS  Quasi Zero and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("QZ","NB","PB");
fc1.insert_rule("QZ","NS","PS");
fc1.insert_rule("QZ","NVS","PVS");
fc1.insert_rule("QZ","QZ","QZ");
fc1.insert_rule("QZ","PVS","NVS");
fc1.insert_rule("QZ","PS","NS");
fc1.insert_rule("QZ","PB","NB");


// If NextStepError IS Positive Very Small and DeltaError IS Negative Big THEN Control IS Positive Small
fc1.insert_rule("PVS","NB","PS");
fc1.insert_rule("PVS","NS","PVS");
fc1.insert_rule("PVS","NVS","QZ");
fc1.insert_rule("PVS","QZ","NVS");
fc1.insert_rule("PVS","PVS","NS");
fc1.insert_rule("PVS","PS","NB");
fc1.insert_rule("PVS","PB","NB");


// If NextStepError IS Positive Small and DeltaError IS Negative Big THEN Control IS Positive Very Small
fc1.insert_rule("PS","NB","PVS");
fc1.insert_rule("PS","NS","QZ");
fc1.insert_rule("PS","NVS","NVS");
fc1.insert_rule("PS","QZ","NS");
fc1.insert_rule("PS","PVS","NB");
fc1.insert_rule("PS","PS","NB");
fc1.insert_rule("PS","PB","NB");


// If NextStepError IS  Positive Big and DeltaError IS Negative Big THEN Control IS Quasi Zero
fc1.insert_rule("PB","NB","NB");
fc1.insert_rule("PB","NS","NB");
fc1.insert_rule("PB","NVS","NB");
fc1.insert_rule("PB","QZ","NB");
fc1.insert_rule("PB","PVS","NB");
fc1.insert_rule("PB","PS","NB");
fc1.insert_rule("PB","PB","NB");

}

void DeltaPPnewrulebase2(fuzzy_control &fc1)
{
// Include each fuzzy rule in the fuzzy_control!(linguisticly!)

// If NextStepError IS Negative Big and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NB","NB","PB");
fc1.insert_rule("NB","NS","PB");
fc1.insert_rule("NB","NVS","PB");
fc1.insert_rule("NB","QZ","PB");
fc1.insert_rule("NB","PVS","PB");
fc1.insert_rule("NB","PS","PB");
fc1.insert_rule("NB","PB","PB");


// If NextStepError IS Negative Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NS","NB", "NB");
fc1.insert_rule("NS","NS", "NB");
fc1.insert_rule("NS","NVS","NB");
fc1.insert_rule("NS","QZ", "NS");
fc1.insert_rule("NS","PVS","NVS");
fc1.insert_rule("NS","PS", "PVS");
fc1.insert_rule("NS","PB", "PS");


// If NextStepError IS Negative Very Small and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("NVS","NB","PB");
fc1.insert_rule("NVS","NS","PB");
fc1.insert_rule("NVS","NVS","PS");
fc1.insert_rule("NVS","QZ","PVS");
fc1.insert_rule("NVS","PVS","QZ");
fc1.insert_rule("NVS","PS","NVS");
fc1.insert_rule("NVS","PB","NS");


// If NextStepError IS  Quasi Zero and DeltaError IS Negative Big THEN Control IS Positive Big
fc1.insert_rule("QZ","NB","PB");
fc1.insert_rule("QZ","NS","PS");
fc1.insert_rule("QZ","NVS","PVS");
fc1.insert_rule("QZ","QZ","QZ");
fc1.insert_rule("QZ","PVS","NVS");
fc1.insert_rule("QZ","PS","NS");
fc1.insert_rule("QZ","PB","NB");


// If NextStepError IS Positive Very Small and DeltaError IS Negative Big THEN Control IS Positive Small
fc1.insert_rule("PVS","NB","PS");
fc1.insert_rule("PVS","NS","PVS");
fc1.insert_rule("PVS","NVS","QZ");
fc1.insert_rule("PVS","QZ","NVS");
fc1.insert_rule("PVS","PVS","NS");
fc1.insert_rule("PVS","PS","NB");
fc1.insert_rule("PVS","PB","NB");


// If NextStepError IS Positive Small and DeltaError IS Negative Big THEN Control IS Positive Very Small
fc1.insert_rule("PS","NB","NS");
fc1.insert_rule("PS","NS","NVS");
fc1.insert_rule("PS","NVS","PVS");
fc1.insert_rule("PS","QZ","PS");
fc1.insert_rule("PS","PVS","PB");
fc1.insert_rule("PS","PS","PB");
fc1.insert_rule("PS","PB","PB");


// If NextStepError IS  Positive Big and DeltaError IS Negative Big THEN Control IS Quasi Zero
fc1.insert_rule("PB","NB","NB");
fc1.insert_rule("PB","NS","NB");
fc1.insert_rule("PB","NVS","NB");
fc1.insert_rule("PB","QZ","NB");
fc1.insert_rule("PB","PVS","NB");
fc1.insert_rule("PB","PS","NB");
fc1.insert_rule("PB","PB","NB");

}

