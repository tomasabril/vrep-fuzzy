
// Program Neuro.cpp - main program of the neuro project - Distributed Neural Nets

#include "neuro.h"


main(int argc, char *argv[])
{
  int ch;
  int i;
  int numneurlayers[NUMMAXNEURLAYER], numlayers;
  int numberofinputs,numberofoutputs;
  int numberofdelayedoutputs,numberofdelayedinputs;
  double momentum=0.0;
  double learning_rate=0.1;
  double precision;
  vectorpair Pares;
  recurrent_neural_net NEURO_NET;
  double ok;
  long count;
  char extension[15];

  char line[30];
  FILE *fileConf;
  char fileName[30];
  int DEBUG=1;

  if(DEBUG) printf("Argc= %d\n", argc);
  if( (argc>1)&&(argc<=3) )
  {
   strcpy (fileName, FILE_CONFIG);
   strcat (fileName, argv[1]); //strcat (fileName, extension);
   printf("Configuration file: %s\n", fileName);
   if ( (fileConf = fopen ( fileName, "r" )) == NULL )
    {
      cout << "Error in configuration file reading!\n";
      exit(1);
    }

   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
   numberofinputs = atoi (line);
   if(DEBUG) printf(" Number of Inputs : %d\n", numberofinputs);
   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
   numberofoutputs = atoi (line);
   if (DEBUG) printf(" Number of Outputs : %d\n", numberofoutputs);
   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
//   numberofdelayedinputs = atoi (line);
//   if (DEBUG)
//    printf(" Number of Delayed Inputs : %d\n", numberofdelayedinputs);
//   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
//   numberofdelayedoutputs = atoi (line);
//   if (DEBUG)
//    printf(" Number of Delayed Outputs : %d\n", numberofdelayedoutputs);
//   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
   numlayers = atoi (line);
   if (DEBUG)
    printf(" Number of Layers of the Net: %d\n", numlayers);
   for(int j=0;j<numlayers;j++)
   { fgets ( line, 30, fileConf);
     line[strlen(line)-1] = '\0';
     numneurlayers[j] = atoi (line);
   if (DEBUG)
    printf(" Number of Neurons on Layer %d : %d\n", j, numneurlayers[j]);
   }
   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
   momentum = atof (line);
   if (DEBUG)
    printf(" Momentum: %f\n", momentum);
   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
   learning_rate = atof (line);
   if (DEBUG)
    printf(" Learning Rate: %f\n", learning_rate);
   fgets ( line, 30, fileConf); line[strlen(line)-1] = '\0';
   precision = atof (line);
   if (DEBUG)
    printf(" Precision: %f\n", precision);

   fclose(fileConf);
   NEURO_NET.create_net(numlayers, numneurlayers, numberofinputs,
                           numberofdelayedinputs, numberofdelayedoutputs);
   NEURO_NET.set_parameters(momentum,learning_rate,precision);

   if(argc==3)//In this case, the second parameter is the test config file!
   {
       NEURO_NET.load_net(argv[1]);
       Pares.load_vector(argv[2]);
       NEURO_NET.remember(Pares);
   }
   else
   {
    Pares.load_vector(argv[1]);

    printf("Begin of training\n");
    count=0;
    do
     {
     ok = NEURO_NET.train_sequence(Pares);
     cout << "Epoch " << count << "\t Error: " << ok;
     count++;
/*   if(count%1000 == 0)
   {       learning_rate +=0.01;
	   NEURO_NET.set_parameters(momentum,learning_rate,precision);
   }*/
     }while(ok>0);
    printf("End of training: %d epochs\n", count);
   NEURO_NET.save_net(argv[1]);
  }
 }
// else
/* {
  precision = 0.01;
  strcpy(extension,"xor");
    Pares.load_vector(extension);

  cout << "(C)riar ou (T)estar :";
  ch = getchar();

  if ( (ch == 'C') || (ch == 'c') )
    {
      cout << "Entre com o numero de niveis :";
      scanf ("%d", &numlayers);
      cout << "Entre com o numero de entradas :";
      scanf ("%d", &numberofinputs);
//      cout << "Entre com o numero de entradas atrasadas a serem consideradas :";
//      scanf ("%d", &numberofdelayedinputs);
//      cout << "Entre com o numero de sa�das atrasadas a serem consideradas :";
//      scanf ("%d", &numberofdelayedoutputs);
      for (i = 0; i < numlayers; i++)
	{
	  cout << "Numero de neuronios no nivel " << i << " :";
	  scanf ("%d", &numneurlayers[i]);
	}
      cout << "Entre com a precisao :";
      scanf ("%lf", &precision);
      NEURO_NET.create_net(numlayers, numneurlayers, numberofinputs,
                           numberofdelayedinputs, numberofdelayedoutputs);
    }
  else
    NEURO_NET.load_net(extension);

  NEURO_NET.set_parameters(momentum,learning_rate,precision);
  count=0;
  if ( (ch == 'c') || (ch == 'C') )
    do
    {
    ok = NEURO_NET.train_sequence(Pares);
    cout << "Epoch " << count << "\t Error: " << ok <<"\n";
    count++;
 //   getchar();
    }while(ok>0);
   printf("Cheguei ate aqui!\n");
   if ( (ch == 't') || (ch == 'T') )
      NEURO_NET.remember(Pares);
  NEURO_NET.save_net(extension);
}// end of else!
*/
  return(0);
}
