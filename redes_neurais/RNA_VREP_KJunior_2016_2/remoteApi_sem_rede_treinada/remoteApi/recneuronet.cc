#include "neuro.h"



recurrent_neural_net::recurrent_neural_net()

{

for(int i=0;i<NUMMAXNEURLAYER;i++) // Initializing!!!

 {

   delayedinputs[i] = 0.0;

   delayedoutputs[i]= 0.0;

 }

}



recurrent_neural_net::~recurrent_neural_net()

{

}



void recurrent_neural_net::create_net ( int numberoflayers,

			      int numberneuronslayer[NUMMAXNEURLAYER],

			      int numberofinputs,

               int numberofdelayedinputs,

               int numberofdelayedoutputs )

{

number_of_delayed_inputs = numberofdelayedinputs;

number_of_delayed_outputs = numberofdelayedoutputs;



MLP.create_net( numberoflayers, numberneuronslayer,

                numberofinputs*(number_of_delayed_inputs+number_of_delayed_outputs+1));

// number of inputs becomes equal to number of inputs multiplied by number of delayed

//outputs that must be remembered by the recurrent part of the network(the recurrent connections!)

}





int recurrent_neural_net::train_sequence ( vectorpair& vp )   // train the net for 1 trainig pair!

  // In this case, the training pairs MUST be presented in the exact order they appear in

  // the pattern file! Just one sequence so far... but on each "epoch" begins at a different place

{

int ok;

int count = 0;

int i, j, k;

int numin, numout;

float vectin[NUMMAXNEURLAYER];

float vectout[NUMMAXNEURLAYER];

training_pair *tp;

training_pair newpair;

int DEBUG=0;
int DEBUG2=0;

int begin;
int num_pairs;
int luck=0;
num_pairs = vp.return_numpair();
begin = number_of_delayed_inputs;
if(begin<number_of_delayed_outputs) begin = number_of_delayed_outputs; // Choose the maximum between delayedinputs and delayedoutputs!
//luck = rint((float)(rand() % num_pairs))-begin; 
if (luck<0) luck = 0;
//printf("Luck = %d", luck);
for(i=luck;i<luck+number_of_delayed_inputs;i++)
  { tp = vp.return_pair(i);
    k = tp->get_num_of_pairs_in();
    for(j=0;j<k;j++)
    {
     delayedinputs[i*k+j] = tp->in[j];
    }
   }

for(i=luck;i<luck+number_of_delayed_outputs;i++)
  { tp = vp.return_pair(i);
    k = tp->get_num_of_pairs_out();
    for(j=0;j<k;j++)
    {
     delayedoutputs[i*k+j] = tp->out[j];
    }
   }
  
ok = 0;
MLP.begin_epoch();
for(i=luck+begin;i<vp.return_numpair();i++)//One epoch! One passing through all the sequence of patterns!

 {

   tp = vp.return_pair(i);

   numin = tp->get_num_of_pairs_in();

   for(j=0;j<numin;j++)

    vectin[j] = tp->in[j];



   count = numin;

   for(j=0;j<number_of_delayed_inputs;j++)

    for(k=0;k<numin;k++)

    { if(DEBUG)

      printf("Atualizando padrão de entrada: entrada %d vale agora %f\n", count, delayedinputs[j*numin+k]);

      vectin[count++] = delayedinputs[j*numin+k];

    }

   numout = tp->get_num_of_pairs_out();

   for(j=0;j<numout;j++)

    vectout[j] = tp->out[j];



   for(j=0;j<number_of_delayed_outputs;j++)

    for(k=0;k<numout;k++)

    {if(DEBUG)

       printf("Atualizando padrão de entrada: entrada %d vale agora %f\n", count, delayedoutputs[j*numin+k]);

       vectin[count++] = delayedoutputs[j*numout+k];

    }
       vectin[count++] = 1.0; //BIAS Term, introduced 11/08/2001!

   newpair.put_in(vectin, numin+numin*number_of_delayed_inputs +numout*number_of_delayed_outputs+1);//+1 introduced 11/08/2001, room for bias term!

   newpair.put_out(vectout, numout);



   if(DEBUG>1)

     newpair.Show();

   if(DEBUG>1) getchar();

   ok+=MLP.train_pair(newpair);
  // printf("%d\t", ok);

   if(DEBUG>2)

   {

    printf(" Valor de number_of_delayed_inputs = %d \n", number_of_delayed_inputs);

    printf(" Valor de number_of_delayed_outputs = %d \n", number_of_delayed_outputs);

    printf(" Valor de numin = %d \n", numin);

    printf(" Valor de numout = %d \n", numout);

   }



   // Storing the delayed patterns!!!

   for(j=(number_of_delayed_inputs+1)*numin;j>=0;j--)

      {delayedinputs[j+numin]=delayedinputs[j];

      //if(DEBUG) printf("1%d\t",j);
      }

   for(j=0;j<numin;j++)

      {delayedinputs[j]=tp->in[j];
       //if(DEBUG) printf("2%d\t",j);
      }

//   printf("\n");

   for(j=(number_of_delayed_outputs+1)*numout;j>=0;j--)

      {delayedoutputs[j+numout]=delayedoutputs[j];
      //if(DEBUG) printf("3%d\t",j);
      }

   for(j=0;j<numout;j++)

      {delayedoutputs[j]=tp->out[j];//Teacher Forcing!!! Use the training output pattern !!!

       //if(DEBUG) printf("4%d\t",j);
      } 

   if(DEBUG) printf("\n");

   if(DEBUG2)

   {

   printf("Vetor de Entradas Atrasadas:\n");

   for(j=0;j<numin*(number_of_delayed_inputs+1);j++)

       printf("%f\n", delayedinputs[j]);

   printf("Vetor de Saídas Atrasadas:\n");

   for(j=0;j<numout*(number_of_delayed_outputs+1);j++)

       printf("%f\n", delayedoutputs[j]);

   newpair.Show();
   getchar();

   }

 }
  printf("\n");
 printf("Max Error of Epoch=%f ", MLP.end_epoch());
 printf("SumSqerr=%f\t" , MLP.get_sum_sq_err());
 fflush(stdout);
 return(ok);

}



void recurrent_neural_net::remember ( vectorpair& vp )   // remember output pattern... also sequential!!!

{

int count = 0;

int i, j, k;

int numin, numout;

float delayedinputs[NUMMAXNEURLAYER];

float delayedoutputs[NUMMAXNEURLAYER];

float vectin[NUMMAXNEURLAYER];

float vectout[NUMMAXNEURLAYER];

training_pair *tp;

training_pair newpair;

int DEBUG=0;

int DEBUG1=1;
int DEBUG3=0;
for(i=0;i<NUMMAXNEURLAYER;i++) // Initializing!!!

 {

   delayedinputs[i] = 0.0;

   delayedoutputs[i]= 0.0;

 }

 

for(i=0;i<vp.return_numpair();i++)//One epoch! One passing through all the sequence of patterns!

 {

   tp = vp.return_pair(i); 

   numin = tp->get_num_of_pairs_in();

   for(j=0;j<numin;j++)

    vectin[j] = tp->in[j];



   count = numin;

   for(j=0;j<number_of_delayed_inputs;j++)

    for(k=0;k<numin;k++)

    { if(DEBUG)

      printf("Atualizando padrão de entrada: entrada %d vale agora %f\n", count, delayedinputs[j*numin+k]);

       vectin[count++] = delayedinputs[j*numin+k];

    }

   numout = tp->get_num_of_pairs_out();

   for(j=0;j<numout;j++)

    vectout[j] = tp->out[j];



   for(j=0;j<number_of_delayed_outputs;j++)

    for(k=0;k<numout;k++)

    {if(DEBUG)

       printf("Atualizando padrão de entrada: entrada %d vale agora %f\n", count, delayedoutputs[j*numin+k]);

       vectin[count++] = delayedoutputs[j*numout+k];

    }

   vectin[count++] = 1.0; //BIAS Term, introduced 11/08/2001!

   newpair.put_in(vectin, numin+numin*number_of_delayed_inputs +numout*number_of_delayed_outputs+1);
//+1, room for bias term!
   newpair.put_out(vectout, numout);



   if(DEBUG1)

     newpair.Show();

   MLP.remember(newpair);

   if(DEBUG1) 
     newpair.Show(); 
   if(DEBUG1) 
     getchar(); 

   // Storing the delayed patterns!!!

   for(j=number_of_delayed_inputs*numin;j>=0;j--)

       delayedinputs[j+numin]=delayedinputs[j];

   for(j=0;j<numin;j++)

       delayedinputs[j]=tp->in[j];



   for(j=number_of_delayed_outputs*numout;j>=0;j--)

       delayedoutputs[j+numout]=delayedoutputs[j];

   for(j=0;j<numout;j++)

     {
      delayedoutputs[j]=newpair.out[j];//NOT using teacher forcing to remember!
      if(DEBUG3) printf("%f\t",newpair.out[j]);
         //cout << newpair.out[j] << "\t";
     }
     if(DEBUG3) cout << "\n";
  if(DEBUG)
        
    {

     printf("Vetor de Entradas Atrasadas:\n"); 
     for(j=0;j<numin*number_of_delayed_inputs;j++)
        
        printf("%f\n",delayedinputs[j]);
    
     printf("Vetor de Saídas Atrasadas:\n");

     for(j=0;j<numout*number_of_delayed_outputs;j++)

       printf("%f\n", delayedoutputs[j]);

     getchar();

   }

 }

}



void recurrent_neural_net::print_net()

{

  printf(" Recurrent Neural Net:\n");

  printf(" Number of Delayed Inputs: %d\n",number_of_delayed_inputs); 

  printf(" Number of Delayed Outputs: %d\n",number_of_delayed_outputs);

  for(int i=0;i<MLP.get_num_layers();i++)

    MLP.print_net(i);

    

}









void recurrent_neural_net::save_net (char *extension)

{

  FILE *fileNeuron;

  char fileName[30];



  strcpy(fileName, FILE_RECNEURAL);

  strcat(fileName, extension);

  if ( (fileNeuron = fopen ( fileName, "w" )) == NULL )

    {

      cout << "Error in file creation:" << fileName << "\n";

      exit(1);

    }





  fprintf ( fileNeuron, "%d\n", number_of_delayed_inputs );

  fprintf ( fileNeuron, "%d\n", number_of_delayed_outputs);

  fclose (fileNeuron);

  

  MLP.save_net(extension);



}



void recurrent_neural_net::load_net (char *extension)

{

  FILE *fileNeuron;

  char fileName[30];

  char line[30];



  strcpy(fileName, FILE_RECNEURAL);

  strcat(fileName, extension);

  if ( (fileNeuron = fopen ( fileName, "r" )) == NULL )

    {

      cout << "Error in file creation: " << fileName << "\n";

      exit(1);

    }



  fgets ( line, 30, fileNeuron); line[strlen(line)-1] = '\0';

  number_of_delayed_inputs = atoi(line);

  fgets ( line, 30, fileNeuron); line[strlen(line)-1] = '\0';

  number_of_delayed_outputs = atoi(line);



  fclose (fileNeuron);

  

  MLP.load_net(extension);



}



