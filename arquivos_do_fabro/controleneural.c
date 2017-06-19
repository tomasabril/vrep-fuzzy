#include <math.h>

#include "neuro.h"

#include "interface.h"

INTERFACE controlador(ESTADO estado, int i)
{


  INTERFACE interface;

  neural_net NEURO_NET1;
  training_pair *TRNTEST;
  float in[6], *out;
 
  NEURO_NET1.load_net("hex1");

  /* carrega TRNTEST->in */
   
     in[0] = estado.dist1;
     in[1] = estado.dist2;
     in[2] = estado.dist3;
     in[3] = estado.dist4;
     in[4] = estado.dist5;
     in[5] = estado.dist6;
     for(int i=0;i<6;i++)
       printf("%f ", in[i]);
     printf("\n");

   TRNTEST = new training_pair;

   TRNTEST->put_in(in, 6);

   NEURO_NET1.remember(*TRNTEST);

   /* utiliza TRNTEST->out */
   out = TRNTEST->get_out();
 	 
  for(i=0;i<2;i++)
       printf("%f ", out[i]);
     printf("\n");

  interface.leftmotor= out[0];  interface.rightmotor= out[1];
  

  return interface;
   
}


