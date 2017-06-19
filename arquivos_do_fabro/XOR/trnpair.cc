//
// trnpair.cpp
//
#include "neuro.h"

// Implements training_pair methods

training_pair::training_pair ()
{
  for(int i=0;i<NUMMAXNEURLAYER;i++)
    {
      in[i] = 0.0;
      out[i] = 0.0;
    }
}

training_pair::training_pair ( float in_part[NUMMAXDENTRITES],
			       float out_part[NUMMAXDENTRITES],
			       int num_of_pairs_in, int num_of_pairs_out )
{
  int i;
  num_pairs_in = num_of_pairs_in;
  for(i=0;i<num_pairs_in;i++)
    {
      in[i] = in_part[i];
    }
  num_pairs_out = num_of_pairs_out;
  for(i=0;i<num_pairs_out;i++)
    {
      out[i] = out_part[i];
    }
}

void training_pair::put_in ( float in_part[NUMMAXDENTRITES], int num_of_pairs )
{
  num_pairs_in = num_of_pairs;
  for(int i=0;i<num_pairs_in;i++)
    {
      in[i] = in_part[i];
    }
}

void training_pair::put_out ( float out_part[NUMMAXDENTRITES], int num_of_pairs )
{
  num_pairs_out = num_of_pairs;
  for(int i=0;i<num_pairs_out;i++)
    {
      out[i] = out_part[i];
    }
}

void training_pair::Show ()
{
  int i;
  /***************************************
  printf(" In Part \n");
  for(i=0;i<num_pairs_in;i++)
    printf(" In = %f \n", in[i]);
  printf(" Out Part \n");
  for(i=0;i<num_pairs_out;i++)
    printf(" Out = %f \n", out[i]);
  ****************************************/
  cout << " In Part \n";
  for(i=0;i<num_pairs_in;i++)
    cout << " In = " << in[i] << "\n";
  cout << " Out Part \n";
  for(i=0;i<num_pairs_out;i++)
    cout << " Out = " << out[i] << "\n";
}

/**************************************
   float& training_pair::get_in(void)
   {
   float g;
   return(g);
   }
   
   float &training_pair::get_out(void)
   {
   float f[3];
   return(f);
   }
***************************************/


float *training_pair::get_out(void)
{
  return(out);
}



training_pair::~training_pair ()
{
}

void training_pair::load_pair(FILE *filePair)
{
  char line[30];
  
  fgets(line, 30, filePair); line[strlen(line)-1] = '\0';
  num_pairs_in = atoi (line);
  for(int i=0; i< num_pairs_in; i++)
    {
      fgets(line, 30, filePair); line[strlen(line)-1] = '\0';
      in[i] = atof(line);
    }

  fgets(line, 30, filePair); line[strlen(line)-1] = '\0';
  num_pairs_out = atoi (line);
  for(int i=0; i< num_pairs_out; i++)
    {
      fgets(line, 30, filePair); line[strlen(line)-1] = '\0';
      out[i] = atof(line);
    }
}
  
