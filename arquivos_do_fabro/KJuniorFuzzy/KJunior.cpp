#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
#include "rightMotor.h"
#include "leftMotor.h"

extern "C" {
	#include "extApi.h"
}

int main(int argc, const char * argv[]) {

        std::string s;
	int countdown = 0;
	int portNb, leftMotorHandle, rightMotorHandle;
	int sensors [6] = {0, 0, 0, 0, 0, 0};
	float distances [6] = {0, 0, 0, 0, 0, 0};
//        float alternativedistances [6] = {0, 0, 0, 0, 0, 0};

	bool ginga = true;
    float valueMotorE = 0;
    float valueMotorD = 0;
	//check if there are correct quantity of parameters
	if (argc>=10)
	{
		portNb=atoi(argv[1]);
		leftMotorHandle=atoi(argv[2]);
		rightMotorHandle=atoi(argv[3]);
		//sensorHandle=atoi(argv[4], argv[4], argv[4]);
		for(int i = 0; i < 6; i++){
			sensors[i] = atoi(argv[i+4]);
			printf("Getting sensor %d\n", sensors[i]);
		}
	}
	else
	{
		printf("Indicate following arguments: 'portNumber leftMotorHandle rightMotorHandle sensors'!\n");
		extApi_sleepMs(5000);
		return 0;
	}
/*

simxReadProximitySensor
regular API equivalent: simReadProximitySensor
ROS service equivalent: simRosReadProximitySensor
Description 	Reads the state of a proximity sensor. This function doesn't perform detection, it merely reads the result from a previous call to simHandleProximitySensor (simHandleProximitySensor is called in the default main script). See also simxGetObjectGroupData.
C synopsis 	simxInt simxReadProximitySensor(simxInt clientID,simxInt sensorHandle,simxUChar* detectionState,simxFloat* detectedPoint,simxInt* detectedObjectHandle,simxFloat* detectedSurfaceNormalVector,simxInt operationMode)
C parameters
clientID: the client ID. refer to simxStart.
sensorHandle: handle of the proximity sensor
detectionState: pointer to a value receiving the detection state (0=no detection). Can be NULL.
detectedPoint: pointer to 3 values receiving the detected point coordinates (relative to the sensor reference frame). Can be NULL.
detectedObjectHandle: pointer to a value receiving the handle of the detected object. Can be NULL.
detectedSurfaceNormalVector: pointer to 3 values receiving the normal vector (normalized) of the detected surface. Relative to the sensor reference frame. Can be NULL
operationMode: a remote API function operation mode. Recommended operation modes for this function are simx_opmode_streaming (the first call) and simx_opmode_buffer (the following calls)
C return value
a remote API function return code
 */
	simxInt clientID=simxStart((simxChar*)"127.0.0.1",portNb,true,true,2000,5);

	//Creating and opening console

	//Printing something on the console
	simxInt returnNumber;

	leftMotor* motorE = new leftMotor();
        rightMotor* motorD = new rightMotor();

	if (clientID!=-1)
	{
		//int driveBackStartTime=-99000;
		float motorSpeeds[2];
		unsigned char readValue = 0;
		float readDistance[3] = {0, 0, 0};

                for(int i=0; i<6; i++){
                    returnNumber = simxReadProximitySensor(clientID,sensors[i],&readValue,&(readDistance[0]),NULL,NULL,simx_opmode_streaming);
                }
		while (simxGetConnectionId(clientID)!=-1)
		{

			/*
			 Reding values from sensors
			 */

                        for(int i=0; i<6; i++){

				returnNumber = simxReadProximitySensor(clientID,sensors[i],&readValue,&(readDistance[0]),NULL,NULL,simx_opmode_buffer);

                                if(readValue != 0)
                                    {//calculating distance sqrt(x^2+y^2+z^2)
                                    distances[i] = sqrt(pow(readDistance[0], 2.0) + pow(readDistance[1], 2.0) + pow(readDistance[2], 2.0))*3200;


                                if(distances[i]>350)
                                        distances[i] = 350;
				//getting complement of it (1000-x)
                               //distances[i] = 350 - distances[i];
                                }
                                else
                                {
                                    distances[i]= 350;
                                }

			}

			/*

			 Printing calculated distances

			 */



                       /* for(int i=0; i<6; i++){
				//converting from int to String
                                s = std::to_string(distances[i]);
				//converting from string to char*
                                char const *pchar = s.c_str();  //use char const* as target type
                                //returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,pchar,simx_opmode_blocking);
                                returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,s.c_str(),simx_opmode_blocking);
				//break line
				returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n",simx_opmode_blocking);
			}*/

                        //getting the maximum (worst) value
			float maxEsquerda	= 0;
			float maxFrente		= 0;
			float maxDireita	= 0;
			//frente
			maxFrente = distances[2];
			//esquerda
                        if(distances[0] < distances[1])
				maxEsquerda = distances[0];
			else
				maxEsquerda = distances[1];
			//direita
                        if(distances[3] < distances[4])
				maxDireita = distances[3];
			else
				maxDireita = distances[4];


			/*
			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n ==Valores Max==\n",simx_opmode_blocking);

                        s = std::to_string(maxEsquerda);
			//converting from string to char*
                        char const *pcharMaxEsq = s.c_str();  //use char const* as target type
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,pcharMaxEsq,simx_opmode_blocking);
			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n",simx_opmode_blocking);
                        s = std::to_string(maxFrente);
			//converting from string to char*
                        char const *pcharMaxFre = s.c_str();  //use char const* as target type
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,pcharMaxFre,simx_opmode_blocking);
			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n",simx_opmode_blocking);
                        s = std::to_string(maxDireita);
			//converting from string to char*
                        char const *pcharMaxDir = s.c_str();  //use char const* as target type
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,pcharMaxDir,simx_opmode_blocking);

			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n",simx_opmode_blocking);
			*/
                        /*

			 Applying Fuzzy rules

			 */
			;// = motorD->makeInference(maxEsquerda, maxFrente, maxDireita);//maxEsquerda, maxFrente, maxDireita);
			//valueMotorE = valueMotorE;//*0.31415;
			//valueMotorD = valueMotorD;//*0.31415;
/*
			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n ==Valor antes motores==\n",simx_opmode_blocking);

                        s = std::to_string(valueMotorE);
			//converting from string to char*
			char const *pcharE = s.c_str();  //use char const* as target type
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,pcharE,simx_opmode_blocking);

			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n",simx_opmode_blocking);

			s = std::to_string(valueMotorD);
			//converting from string to char*
			char const *pcharD = s.c_str();  //use char const* as target type
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,pcharD,simx_opmode_blocking);

			//break line
			returnNumber = simxAuxiliaryConsolePrint(clientID,consoleHandle,"\n",simx_opmode_blocking);

			/*
			 Writing motor speeds back to simulator*/


			// maxDireita maxEsquerda maxFrente*/
			float valueFuzzyE;
			float valueFuzzyD;
			if(abs(valueMotorD)<0.1 && abs(valueMotorD)<0.1 && countdown == 0){
				countdown = 100;
				ginga = !ginga;
			}


				if(maxDireita < 30){
					valueFuzzyD = 1;
				}else if(maxDireita >= 30 && maxDireita < 250){
					float maxDaux = maxDireita;
					maxDaux = maxDaux -30;
					maxDaux = 1-(maxDaux/220);
					valueFuzzyD = maxDaux;
				}else if(maxDireita >= 220){
					valueFuzzyD = 0;
				}
				if(maxEsquerda < 30){
					valueFuzzyE = 1;
				}else if(maxEsquerda >= 30 && maxEsquerda < 200){
					float maxEaux = maxEsquerda ;
					maxEaux = maxEaux -30;
					maxEaux = 1-(maxEaux/170);
					valueFuzzyE = maxEaux;
				}else if(maxEsquerda  >= 200){
					valueFuzzyE = 0;
				}

			if(countdown == 0){
				valueMotorE = 1.5- 3*valueFuzzyD;
				valueMotorD = 1.5- 3*valueFuzzyE;
			}else if(ginga == true){
				valueMotorE =	-2.5;
				valueMotorD = 	+2.5;
				countdown--;


			}else {
				valueMotorE =  +2.5;
				valueMotorD = 	-2.5;
				countdown--;

			}
        printf("\n maxd= %f maxe = %f maxf = %f velme = %f velmd = %f\n", maxDireita, maxEsquerda, maxFrente, valueMotorE, valueMotorD);





			if(valueMotorD < -5.0)
				valueMotorD = -5;
			if(valueMotorE < -5.0)
				valueMotorE = -5;

			if(valueMotorD > 5.0)
				valueMotorD = 5;
			if(valueMotorE > 5.0)
				valueMotorE = 5;





			simxSetJointTargetVelocity(clientID,leftMotorHandle,valueMotorE, simx_opmode_streaming);
			simxSetJointTargetVelocity(clientID,rightMotorHandle,valueMotorD, simx_opmode_streaming);


			//writing values in the

			simxInt simxSetJointTargetVelocity(simxInt clientID,simxInt jointHandle,simxFloat targetVelocity,simxInt operationMode);

			if (simxReadProximitySensor(clientID,sensors[0],NULL,NULL,NULL,NULL,simx_opmode_streaming)==simx_return_ok)
			{ // We succeeded at reading the proximity sensor
				int simulationTime=simxGetLastCmdTime(clientID);
			}
			extApi_sleepMs(5);
		}
		simxFinish(clientID);
	}



    return 0;
}


