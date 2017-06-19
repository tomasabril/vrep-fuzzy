//
//  Neuron.cpp - Implementation of neuron class
//
#include "neuro.h"
#include "math.h"


// Implementation of neuron class methods

neuron::neuron()
{
  out = 0;
  error = 0;
}

void neuron::initialize ( int num_of_layer, int num_dentrites, int kind )
{
  int i;
  
  number_inputs = num_dentrites;
  layer         = num_of_layer;
  kind_of_layer = kind;
  
  for(i=0;i<num_dentrites;i++)
    Weight[i] = ( (float)(rand() % 500) - 250.0 ) / 250.0;  // 500 => arbitrary
//  printf("Peso = %f\n", Weight[1]);

  // Assigns to Weight a random number betwen -1 and +1
  
 for(i=0;i<num_dentrites;i++)
   last_change[i] = 0.0;

}

float neuron::propagation ( float outputs_previous_layer[NUMMAXDENTRITES] )
{
  double tmp = 0.0;
  
  for(int i=0;i<number_inputs;i++)
    tmp += outputs_previous_layer[i] * Weight[i];
  
  /***************************
     Function of propagation
  ****************************/

  if (tmp > 11.5129)
    out = 0.999999;
  else if (tmp < -11.5129)
    out = 0.000001;
  else
   out = (float)1.0/(1.0 + exp(-tmp));
  out = tanh(tmp); // Hiperbolic Tangent - Changed 13/08/2001
  return(out);
}
// Return the error on the output layer
float neuron::get_max_output_error(float target)
{
int DEBUG=0;
float err;

 err = target - out;
 if(err<0) err = -1*err;

if(DEBUG)
{
  printf("target = %f\t", target);
  printf("out = %f\t", out);
  printf("error = %f\n", err);
}
return(err);
}

// Weighted_error = sum of errors from next-layer times synaptic weights
// Except on last/output layer, where it is the target value for this neuron
float neuron::calculate_error ( float weighted_error_next_layer )
{
  // using formula: errors of output layer(d) = o(1-o)(o-t)
  // where: o = output layer vector, t = target (correct) activation
  // errors of intermed layer = o(1-o)weighted_value
  // here aren't errors on first layer = entry layer
  float target;
  switch(kind_of_layer)
    {
    case OUTPUT_LAYER:
      target = weighted_error_next_layer;
      // In this case, is passed training output
      error = (out * (1.0 - out)+0.5) * (target-out);   // in place of out-target;
      error = (1.0 - out*out) * (target -out);  // Added 13/08/2001-Tanh 
/*      cout << "Targ=" << target << "\tOut=" << out << "\t";
      cout << "Err=" << (target-out) << "\tErr'=" << error << "\n";
*/      break;
    default:
      error = out * (1.0 - out) * weighted_error_next_layer;
      error = (1.0 - out*out) *weighted_error_next_layer; // Added 13/08/2001-Tanh
      break;
    }
  return(error);
}


// This version of back_prop function just returns one weighted_error
// at a time: the neural_net object must add them to form the
// weighted error necessary to back_propagation of errors!
float neuron::back_propagation ( int index )
{
  float weighted_error;
  weighted_error = error * Weight[index];
  return(weighted_error);
}

void neuron::update_weights ( float learn_rate, float momentum,
			      float outputs_previous_layer[NUMMAXDENTRITES] )
{
  float tmp;
  for(int i=0;i < number_inputs;i++)
    {
      
      tmp = learn_rate*error*outputs_previous_layer[i] + momentum*last_change[i];
      last_change[i] = tmp;
      Weight[i] += tmp;
    }
}

neuron::~neuron ()
{
}

void neuron::print_weights ( int neuron )
{
  cout << "   Neuronio " << neuron << "\n";
  cout << "   Pesos :\n";
  for(int i=0;i<number_inputs;i++)
    cout << "\t" << i << "  " << Weight[i] << "\n";

  /********************************************
  printf("   Neuronio %d \n", neuron);
  printf("    Pesos :\n");
  for(int i=0;i<number_inputs;i++)
    printf("\t %d %f \n", i, Weight[i]);
  *********************************************/
}

void neuron::save_weights ( FILE *fileNeuron )
{
  fprintf (fileNeuron, "%d\n", number_inputs);
  for (int i=0;i<number_inputs;i++)
      fprintf (fileNeuron, "%f\n", Weight[i]);
}

void neuron::load_weights ( FILE *fileNeuron )
{
  char line[30];

  fgets (line, 30, fileNeuron); line[strlen(line)-1] = '\0';
  number_inputs = atoi (line);
  for (int i=0;i<number_inputs;i++)
    {
      fgets (line, 30, fileNeuron); line[strlen(line)-1] = '\0';
      Weight[i] = (float) atof (line);
    }
}
