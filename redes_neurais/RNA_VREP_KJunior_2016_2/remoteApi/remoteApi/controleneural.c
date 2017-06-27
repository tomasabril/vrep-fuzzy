#include <math.h>

#include "neuro.h"

float interface[2] = {0, 0};

float* controlador(float* estado)
{

  int i;

  neural_net NEURO_NET1;
  training_pair *TRNTEST;
  float *in, *out;
  NEURO_NET1.load_net("junin");

  /* carrega TRNTEST->in */
     in = estado;
     /*in[0] = estado.dist1;
     in[1] = estado.dist2;
     in[2] = estado.dist3;
     in[3] = estado.dist4;
     in[4] = estado.dist5;
     in[5] = estado.dist6;*/
     for(int i=0;i<6;i++)
       printf("%f ", in[i]);
     printf("\n");

   TRNTEST = new training_pair;

   TRNTEST->put_in(in, 6);

   NEURO_NET1.remember(*TRNTEST);

   /* utiliza TRNTEST->out */
   out = TRNTEST->get_out();


  printf("Cheguei0");
  for(i=0;i<2;i++)
       printf("%f ", out[i]);
         printf("Cheguei1");
     printf("\n");
     printf("Cheguei2");

  interface[0]= out[0];  interface[1]= out[1];


  return interface;

}

// Make sure to have the server side running in V-REP!
// Start the server from a child script with following command:
// simExtRemoteApiStart(portNumber) -- starts a remote API server service on the specified port

extern "C" {
    #include "extApi.h"
}

int main(int argc,char* argv[])
{
    
    int portNb=0;
    int leftMotorHandle;
    int rightMotorHandle;
    int sensor[6] = {0, 0, 0, 0, 0, 0};
    float distanceSensors[6] = {0, 0, 0, 0, 0, 0};

    if (argc>=5)
    {
        portNb=atoi(argv[1]);
        leftMotorHandle=atoi(argv[2]);
        rightMotorHandle=atoi(argv[3]);
        for(int i = 0; i < 6; i++){
            sensor[i] = atoi(argv[i+4]);
        }
    }
    else
    {
        printf("Indicate following arguments: 'portNumber leftMotorHandle rightMotorHandle sensorHandle'!\n");
        extApi_sleepMs(5000);
        return 0;
    }

    simxInt clientID=simxStart((simxChar*)"127.0.0.1",portNb,true,true,2000,5);

    if (clientID!=-1)
    {
        int driveBackStartTime=-99000;
        float *motorSpeeds;

        while (simxGetConnectionId(clientID)!=-1)
        {
            simxUChar sensorTrigger = 0;

            for(int i = 0; i < 6; i++){
                float distanceAxis[3];

                simxReadProximitySensor(clientID,sensor[i],NULL,&(distanceAxis[0]),NULL,NULL,simx_opmode_buffer);



                float distance = pow(distanceAxis[0],2) + pow(distanceAxis[1],2) + pow(distanceAxis[2],2);
                distance = sqrt(distance);
                if(distance <= 0.001 && i != 5)
                    distance = 0;


                distanceSensors[i] = distance;
            }

            if(distanceSensors[5] == distanceSensors[0])
              distanceSensors[5] = 0;

            motorSpeeds = controlador(distanceSensors);
            printf(" %f, %f", motorSpeeds[0], motorSpeeds[1]);
            float velMotorD = motorSpeeds[0]*6;
            float velMotorE = motorSpeeds[1]*6;

            simxSetJointTargetVelocity(clientID,leftMotorHandle,velMotorE,simx_opmode_oneshot);
            simxSetJointTargetVelocity(clientID,rightMotorHandle,velMotorD,simx_opmode_oneshot);


            extApi_sleepMs(5);
        }
        simxFinish(clientID);
    }
    return(0);
}
