//

// Program Neuro.h - Definitions for the Neuro Project Distributed Neural Nets

//

#include <time.h>     // randomize() function
#include <math.h>     // rint() function

//#include <stdio.h>     // printf() function

#include <stdio.h>      // open & close files

#include <stdlib.h>    // rand() function

#include <string.h>    // strcpy, strcat

#include <iostream.h>



/***************************

void printf(char *pt);

void printf(char *pt,int t);

void printf(char *pt, int t1, int t2);

***************************/



#define NUMMAXDENTRITES   500

#define NUMMAXNEURLAYER   500

#define NUMMAXLAYERS       2

#define MAXDELAY	   15



#define INPUT_LAYER        0

#define INTERMED_LAYER     1

#define OUTPUT_LAYER       2



#define NUMMAXPAIRS       2500
#define NUMMAXFILES       50



#define FILE_CONFIG        "config."

#define FILE_NEURAL        "neuralnet."

#define FILE_RECNEURAL     "recneuro."

#define FILE_TRAIN         "training."



class neuron {

private:

  float Weight[NUMMAXDENTRITES];

  int   number_inputs;

  float out;

  float error;

  float last_change[NUMMAXDENTRITES];

  int   kind_of_layer;                // INPUT, OUTPUT, INTERMED

  int   layer;                        // Number of Layer: 0 = input

public:

  neuron                 ();

  void initialize        ( int num_of_layer, int num_dentrites, int kind );

  void update_weights    ( float learn_rate, float momentum,

			   float outputs_previous_layer[NUMMAXDENTRITES] );

  float propagation      ( float outputs_previous_layer[NUMMAXDENTRITES] );

  float back_propagation ( int index );               // Just for preliminary testing

  float calculate_error  ( float weighted_error_next_level );

  float get_max_output_error( float target );

  float return_output    ( void ) { return(out);};

  ~neuron                ();

  void print_weights     ( int neuron );

  void save_weights      ( FILE *fileNeuron );

  void load_weights      ( FILE *fileNeuron );

};





class training_pair {

friend class neural_net;

friend class recurrent_neural_net;

  int   num_pairs_in;

  int   num_pairs_out;

  float in[NUMMAXDENTRITES];

  float out[NUMMAXDENTRITES];

public:

  training_pair  ();

  training_pair  ( float in_part[NUMMAXDENTRITES],

		  float out_part[NUMMAXDENTRITES],

		  int num_of_pairs_in, int num_of_pairs_out );

  void put_in    ( float in_part[NUMMAXDENTRITES], int num_of_pairs_in );

  void put_out   ( float out_pair[NUMMAXDENTRITES], int num_of_pairs_out );

  void Show      ( void );

  //    float& get_in  ( void );

  //    float& get_out ( void );

  int  get_num_of_pairs_in(){return(num_pairs_in);};

  int  get_num_of_pairs_out(){return(num_pairs_out);};

//  float *training_pair::get_in(void);

  float *training_pair::get_out(void);

  ~training_pair ();

  void load_pair ( FILE *filePair );

};



class vectorpair {

private:

  int           pairs;

  training_pair *trainingPair[NUMMAXPAIRS];



public:

                 vectorpair  ();

  void           load_vector (char *extension);

  void           load_vector_from_files (char *extension);

  void           show_pair   (int pair);

  training_pair *return_pair ( int pair);

  int            return_numpair ();

                ~vectorpair  ();

};





class neural_net {

protected:

  // FILE       *arqerros;

  long          count;                     // counter: how many times trained the net!

  float         momentum;

  float         learning_rate;

  float         max_error;

  float         max_error_epoch;
  
  float		sum_sq_err;  

  int           number_of_layers;

  int           number_of_neurons_layer[NUMMAXNEURLAYER];

  neuron        net[NUMMAXLAYERS][NUMMAXNEURLAYER];

  training_pair tpair;                          // pair in training!

  // float      neuron_outputs[NUMMAXNEURLAYER];// Used to compose previous layer output

  float         neuron_outputs[NUMMAXLAYERS][NUMMAXNEURLAYER];

  // float      neuron_errors[NUMMAXLAYERS][NUMMAXNEURLAYER];

  // (future) enhacement : medium coarse/ more efficient = use of

  // "layer" in place of "neuron" as minimum piece of code...

public:

  neural_net             ();

  void create_net        ( int numberoflayers,

		           int numberneuronslayer[NUMMAXLAYERS],

		           int numberofinputs );

  int  get_count         () { return((int)count);};

  int  get_num_layers    () { return( number_of_layers);};

  void set_parameters    ( float momentum, float learn_rate, float max_err );

  void update_layer      ( int number_of_layer ); //

  void propagate_outputs ( int number_of_layer ); // just propagate outputs

  float propagate_errors ( int number_of_layer ); // adjust weights of net

  int train_pair         ( training_pair& tp );   // train the net for 1 trainig pair!

  void remember          ( training_pair& tp );   // remember output pattern, returning

  // in out term of training_pair tp

  // float train_net     (training_set& ts);      // ??????????

  //great weakness: you'll need all training pair on primary mem. to train...

  ~neural_net            ();

  void print_net         ( int layer );

  void save_net          (char *extension);

  void load_net          (char *extension);

  void show_count        ();

  void begin_epoch	 (){ max_error_epoch = 0.0;sum_sq_err = 0.0;};

  float end_epoch	 (){ return(max_error_epoch);};

  float get_sum_sq_err   (){return(sum_sq_err);};
};



class recurrent_neural_net{// :public neural_net {

protected:

  neural_net MLP;

  int number_of_delayed_inputs;

  int number_of_delayed_outputs;

  float delayedinputs[NUMMAXNEURLAYER];

  float delayedoutputs[NUMMAXNEURLAYER];



//  float delayed_inputs[MAXDELAY][NUMMAXNEURLAYER];

//  float delayed_outputs[MAXDELAY][NUMMAXNEURLAYER];

  

public:

  void create_net        ( int numberoflayers,

		           int numberneuronslayer[NUMMAXLAYERS],

		           int numberofinputs,

                           int numberofdelayedinputs,

                           int numberofdelayedoutputs );



  recurrent_neural_net             ();

  void set_parameters    (float momentum,float learn_rate,float max_err)

     {MLP.set_parameters(momentum,learn_rate,max_err );};



//  void update_layer      ( int number_of_layer ); //

//  void propagate_outputs ( int number_of_layer ); // just propagate outputs

//  float propagate_errors ( int number_of_layer ); // adjust weights of net

  int train_sequence       ( vectorpair& vp );   // train the net for 1 trainig pair!

  // In this case, the training pairs MUST be presented in the exact order they appear in 

  // the pattern file! Just one sequence so far... but on each "epoch" begins at a different place

  void remember          ( vectorpair& vp );   // remember output pattern... also sequential!!!

  void print_net         ();

  void save_net          (char *extension);

  void load_net          (char *extension);



  ~recurrent_neural_net  ();



};

