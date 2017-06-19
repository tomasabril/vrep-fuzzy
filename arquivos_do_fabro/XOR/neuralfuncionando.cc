// Program Neuro.cpp - main program of the neuro project - Distributed Neural Nets

#include "neuro.h"


main()
{
  int ch;
  int i;
  int numneurlayers[NUMMAXNEURLAYER], numlayers, numberofinputs;
  int numberofdelayedoutputs, numberofdelayedinputs;
  double precision;
  vectorpair Pares;
  recurrent_neural_net NEURO_NET;

  precision = 0.01;

  Pares.load_vector_from_files("piv");

  cout << "(C)riar ou (T)estar :";
  ch = getchar();

  if ( (ch == 'C') || (ch == 'c') )
    {
      cout << "Entre com o numero de niveis :";
      scanf ("%d", &numlayers);
      cout << "Entre com o numero de entradas :";
      scanf ("%d", &numberofinputs);
      cout << "Entre com o numero de entradas atrasadas a serem consideradas :";
      scanf ("%d", &numberofdelayedinputs);
      cout << "Entre com o numero de saídas atrasadas a serem consideradas :";
      scanf ("%d", &numberofdelayedoutputs);
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
    NEURO_NET.load_net("piv");

  NEURO_NET.set_parameters(0.5,0.3,precision);

  double ok;
  if ( (ch == 'c') || (ch == 'C') )
    do
    {
    ok = NEURO_NET.train_sequence(Pares);
    }while(ok>0);
printf("Cheguei ate aqui!\n");
//  for (i=0;i<Pares.return_numpair();i++)
//    {
  if ( (ch == 't') || (ch == 'T') )
      NEURO_NET.remember(Pares);
//      Pares.show_pair(i);
//    }

//  if ( (ch == 'c') || (ch == 'C') )
//  NEURO_NET.print_net();
  NEURO_NET.save_net("piv");

  return(0);
}


