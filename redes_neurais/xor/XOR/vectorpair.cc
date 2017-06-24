//

//  Vectorpair.cpp - Implementation of vectorpair class

//

#include "neuro.h"

#include "math.h"





// Implementation of vectorpair class methods



vectorpair::vectorpair()

{

  pairs = 0;

}



void vectorpair::load_vector (char *extension)

{

  FILE *filePair;

  char fileName[30];

  char line[30];



  strcpy (fileName, FILE_TRAIN);

  strcat (fileName, extension);

  if ( (filePair = fopen ( fileName, "r" )) == NULL )

    {

      cout << "Error in file reading!\n";

      exit(1);

    }



  fgets ( line, 30, filePair); line[strlen(line)-1] = '\0';

  pairs = atoi (line); 

  for(int i=0;i<pairs;i++)

    {

      trainingPair[i] = new training_pair;

      trainingPair[i]->load_pair(filePair);

    }

  

  fclose (filePair);

}



void vectorpair::load_vector_from_files (char *extension)

{
  char line[30];
  FILE *filePair, *fileInputs[NUMMAXFILES], *fileOutputs[NUMMAXFILES];
  char fileName[30], fileNameInputs[NUMMAXFILES][30], fileNameOutputs[NUMMAXFILES][30];
  int numinputs;
  int numoutputs;
  float in[NUMMAXDENTRITES], out[NUMMAXDENTRITES];
  int DEBUG=0;


  strcpy (fileName, FILE_TRAIN);
  strcat (fileName, extension);

  if ( (filePair = fopen ( fileName, "r" )) == NULL )
    {
      cout << "Error in file reading!\n";
      exit(1);
    }

  fgets ( line, 30, filePair); line[strlen(line)-1] = '\0';
  pairs = atoi (line); 

  fgets ( line, 30, filePair); line[strlen(line)-1] = '\0';
  numinputs = atoi (line); 

  for(int i=0;i<numinputs;i++)
  {
    fgets(fileNameInputs[i], 30, filePair); 
    fileNameInputs[i][strlen(fileNameInputs[i])-1] = '\0';
    if ( (fileInputs[i] = fopen ( fileNameInputs[i], "r" )) == NULL )
    {
      cout << "Error in input pattern reading!\n";
      exit(1);
    }
  } 

  fgets ( line, 30, filePair); 
  line[strlen(line)-1] = '\0';
  numoutputs = atoi (line); 

  for(int i=0;i<numoutputs;i++)
  {
  fgets ( fileNameOutputs[i], 30, filePair); 
  fileNameOutputs[i][strlen(fileNameOutputs[i])-1] = '\0';
  if ( (fileOutputs[i] = fopen ( fileNameOutputs[i], "r" )) == NULL )
    {
      cout << "Error in output pattern reading!\n";
      exit(1);
    }
  }

  for(int h=0;h<pairs;h++)

  {
    for(int i=0; i<numinputs; i++)
     {
      fgets(line, 30, fileInputs[i]); line[strlen(line)-1] = '\0';
      in[i] = atof(line);
     }

    for(int i=0; i< numoutputs; i++)
     {
      fgets(line, 30, fileOutputs[i]); line[strlen(line)-1] = '\0';
      out[i] = atof(line);
     }


    trainingPair[h] = new training_pair;
    trainingPair[h]->put_in(in, numinputs);
    trainingPair[h]->put_out(out, numoutputs);
      

if(DEBUG)
   { trainingPair[h]->Show();
     getchar();
   }
  }
  
  fclose (filePair);
  for(int i=0; i<numinputs; i++)
   fclose (fileInputs[i]);
  for(int i=0; i< numoutputs; i++)
   fclose (fileOutputs[i]);
}





training_pair* vectorpair::return_pair ( int pair )

{

  return trainingPair[pair];

}



void vectorpair::show_pair(int pair)

{

  trainingPair[pair]->Show();

}



int vectorpair::return_numpair ()

{

  return pairs;

}



vectorpair::~vectorpair()

{

  for(int i=0;i<pairs;i++)

    delete trainingPair[i];

}

