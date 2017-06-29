#include <math.h>

#include "neuro.h"

#include "interface.h"

INTERFACE controlador(ESTADO estado, int i)
{


  INTERFACE interface;

  neural_net NEURO_NET1;
  training_pair *TRNTEST;
  float in[18], *out;
 
  NEURO_NET1.load_net("hex1");

  /* carrega TRNTEST->in */
   
     in[0] = estado.movhorz1;
     in[1] = estado.movert1;
     int[2]= estado.dist1;
     in[3] = estado.movhorz2;
     in[4] = estado.movert2;
     int[5]= estado.dist2;
     in[6] = estado.movhorz3;
     in[7] = estado.movert3;
     int[8]= estado.dist3;
     in[9] = estado.movhorz4;
     in[10] = estado.movert4;
     int[11]= estado.dist4;
     in[12] = estado.movhorz5;
     in[13] = estado.movert5;
     int[14]= estado.dist5;
     in[15] = estado.movhorz6;
     in[16] = estado.movert6;
     int[17]= estado.dist6;
     for(int i=0;i<18;i++)
       printf("%f ", in[i]);
     printf("\n");

   TRNTEST = new training_pair;

   TRNTEST->put_in(in, 18);

   NEURO_NET1.remember(*TRNTEST);

   /* utiliza TRNTEST->out */
   out = TRNTEST->get_out();
 	 
  for(i=0;i<12;i++)
       printf("%f ", out[i]);
     printf("\n");

  interface.left1h= out[0];  interface.left1v= out[1];
  interface.left2h= out[2];  interface.left2v= out[3];
  interface.left3h= out[4];  interface.left3v= out[5];
  interface.right1h= out[6]; interface.right1v= out[7];
  interface.right2h= out[8]; interface.right2v= out[9];
  interface.right3h= out[10]; interface.right3v= out[11];

  return interface;
   
}

