//
//  Neuronet.cpp - Implementation of neural_net class
//
#include "neuro.h"

// Implementation of neural_net class methods

neural_net::neural_net ()
{
  momentum = 1.0;
  learning_rate = 1.0;
  max_error = 0.001;
  count = 0;
}

void neural_net::create_net ( int numberoflayers,
			      int numberneuronslayer[NUMMAXNEURLAYER],
			      int numberofinputs )
{
  number_of_layers = numberoflayers;
  
  /******* Initialize number of neurons/layer *************/
  for(int i=0;i<number_of_layers;i++)
    {
      number_of_neurons_layer[i] = numberneuronslayer[i];

      cout << "Numero-Neuronios nivel " << i << " eh " << numberneuronslayer[i] << "\n";
    }
  
  /* Initialize each neuron of first layer */
  for(int k=0;k<number_of_neurons_layer[0];k++)
    net[0][k].initialize(0,numberofinputs,INPUT_LAYER);
  // Number of net inputs == number of inputs(from training_pair.in!)
  
  /* Initialize each neuron of other layers */
  for(int j=1;j<number_of_layers;j++)
    for(int l=0;l<number_of_neurons_layer[j];l++)
      net[j][l].initialize(j, number_of_neurons_layer[j-1],
			   j==(number_of_layers-1)?OUTPUT_LAYER:INTERMED_LAYER);
  
  /*****************************************************************************
     The Dentrite's number of each neuron is equal to the neuron's number of
     the predecessor layer , number_of_neurons_layer[j-1] 
     Last line sets kind_of_layer, Intermed or Output 
  ******************************************************************************/
}

void neural_net::set_parameters ( float moment, float learn_rate, float max_err )
{
  momentum = moment;
  learning_rate = learn_rate;
  max_error = max_err;
}

void neural_net::update_layer ( int number_of_layer )
{
  int i;
  if(number_of_layer == 0)
    {
      for(i=0; i < number_of_neurons_layer[number_of_layer]; i++)
	net[0][i].update_weights(learning_rate, momentum, tpair.in);
    }
  else
    {
      /************************
      for(i=0;i<number_of_neurons_layer[number_of_layer-1]; i++)
	neuron_outputs[i] = net[i][number_of_layer-1].return_output();
      *************************/
      for(i=0; i < number_of_neurons_layer[number_of_layer]; i++)
	net[number_of_layer][i].update_weights (learning_rate, momentum,
						&neuron_outputs[number_of_layer-1][0]);
    }
}

void neural_net::propagate_outputs ( int number_of_layer )
{
  int i;
  if(number_of_layer == 0)
    {
      for(i=0;i<number_of_neurons_layer[number_of_layer];i++)
	neuron_outputs[0][i]=net[0][i].propagation(tpair.in);
    }
  else
    {
      /*********************
      for(i=0;i<number_of_neurons_layer[number_of_layer-1]; i++)
      	neuron_outputs[i] = net[i][number_of_layer-1].return_output();
      **********************/
      for(i=0;i<number_of_neurons_layer[number_of_layer];i++)
	neuron_outputs[number_of_layer][i]=
	  net[number_of_layer][i].propagation(&neuron_outputs[number_of_layer-1][0]);
    }
}

float neural_net::propagate_errors(int number_of_layer)
{
  int i,k;
  float j;
  float err;
  float max_err =0.0;

  for(i=0;i<number_of_neurons_layer[number_of_layer];i++)
    {
      if(number_of_layer == number_of_layers-1)
      {
	  err=net[number_of_layer][i].calculate_error(tpair.out[i]);
	  sum_sq_err += err*err;
	}
      else
	{
	  j = 0.0;
	  for(k=0;k<number_of_neurons_layer[number_of_layer+1];k++)
	    j += net[number_of_layer+1][k].back_propagation(i);
	  err=net[number_of_layer][i].calculate_error(j);
          sum_sq_err += err*err;
	}
      if (err < 0.0)
	err *= -1.0;
      if (err > max_err)
	max_err = err;
    }

  return(max_err);
}

//Return 0 if train_pair OK, 1 Instead!
int neural_net::train_pair(training_pair& tp)
{
  int i,j;
  float max_err= 0.0;
  float temp;
  float err;


  //		 char *str;
  //		 int dec, sign, ndig = 5;

  tpair = tp;

  for(i=0;i<number_of_layers;i++)
    propagate_outputs(i);

  for(i=number_of_layers-1;i>=0;i--)// last change = ad >= n i>=0.
    {
      temp = propagate_errors(i);
      if(i==number_of_layers-1)
	{
	  /**********************
	  str = fcvt(err, ndig, &dec, &sign);
	  fputs(str, arqerros);
	  fputc('\n', arqerros);
	  ***********************/
          for(j=0;j<number_of_neurons_layer[i];j++)
          {
            err = net[i][j].get_max_output_error(tpair.out[j]);
	    if(err > max_err)	max_err = err;
          }
        }
//      /**************************
//      printf("Erro = %f\t", err);
//      if(err > max_err)
//      	max_err = err;
//      **************************/
   }

  if( max_err > max_error_epoch) 
  {
  max_error_epoch = max_err;
 // printf("Errepoch = %f\t", max_err);  
  }
  for(i=0;i<number_of_layers;i++)
    update_layer(i);

  count++;

  return((max_err>max_error)?1:0);
}

void neural_net::remember ( training_pair& tp )
{
  int i;
  tpair = tp;
  for(i=0;i<number_of_layers;i++)
    propagate_outputs(i);
  for(i=0;i<number_of_neurons_layer[number_of_layers-1];i++)
    tp.out[i]=net[number_of_layers-1][i].return_output();
  tp.num_pairs_out = number_of_neurons_layer[number_of_layers-1];
  /*********************************************************************
   returns each output value of last layer neurons(number_of_layers -1)
   and puts in out part of training_pair  
  **********************************************************************/
}

neural_net::~neural_net ()
{
}

void neural_net::print_net(int layer)
{
  for(int i=0;i<number_of_neurons_layer[layer];i++)
    {
      cout << " Nivel " << layer << " \n";
      net[layer][i].print_weights(i);
    }
}

void neural_net::save_net(char *extension)
{
  FILE *fileNeuron;
  char fileName[30];
  int i, j;

  strcpy(fileName, FILE_NEURAL);
  strcat(fileName, extension);
  if ( (fileNeuron = fopen ( fileName, "w" )) == NULL )
    {
      cout << "Error in file creation:" << fileName << "\n";
      exit(1);
    }

  fprintf ( fileNeuron, "%d\n", number_of_layers );
  for (i = 0; i < number_of_layers; i++)
    fprintf ( fileNeuron, "%d\n", number_of_neurons_layer[i] );

  for (i = 0; i < number_of_layers; i++)
    for(j = 0; j < number_of_neurons_layer[i]; j++)
      net[i][j].save_weights(fileNeuron);

  fclose (fileNeuron);
}

void neural_net::load_net(char *extension)
{
  FILE *fileNeuron;
  char fileName[30];
  char line[30];
  int i, j;

  strcpy(fileName, FILE_NEURAL);
  strcat(fileName, extension);
  if ( (fileNeuron = fopen ( fileName, "r" )) == NULL )
    {
      cout << "Error in file creation: " << fileName << "\n";
      exit(1);
    }

  fgets ( line, 30, fileNeuron); line[strlen(line)-1] = '\0';
  number_of_layers = atoi(line);

  for (i = 0; i < number_of_layers; i++)
    {
      fgets ( line, 30, fileNeuron);
      number_of_neurons_layer[i] = atoi (line); line[strlen(line)-1] = '\0';
    }

  for (i = 0; i < number_of_layers; i++)
    for(j = 0; j < number_of_neurons_layer[i]; j++)
      net[i][j].load_weights(fileNeuron);

  fclose (fileNeuron);
}

void neural_net::show_count()
{
  cout << "\n" << "The net was trained " << count << "\n";
}
