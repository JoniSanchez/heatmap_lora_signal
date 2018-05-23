/*LIB TO LORA*/
#include "arduPiLoRaWAN.h"
#include "arduPiUtils.h"
/*LIB TO GPS*/
#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// socket to use
//////////////////////////////////////////////
uint8_t sock = SOCKET0;
//////////////////////////////////////////////

// define radio settings
//////////////////////////////////////////////
uint8_t power = 15;
uint32_t frequency = 868100000;
char spreading_factor[] = "sf12";
char coding_rate[] = "4/5";
uint16_t bandwidth = 125;
char crc_mode[] = "on";
//////////////////////////////////////////////

// define functions
uint8_t radioModuleSetup(void);

// define data to send
char data[] = "989898987877";

// variable
uint8_t error;

void setup() 
{
  printf("Radio P2P example - Sending packets\n\n");

  // module setup
  error = radioModuleSetup();
  
  // Check status
  if (error == 0)
  {
    printf("Module configured OK\n");     
  }
  else 
  {
    printf("Module configured ERROR\n");     
  }  

}


void loop() 
{
  // Send packet
  error = LoRaWAN.sendRadio(data);
  
  // Check status
  if (error == 0)
  {
    printf("--> Packet sent OK\n");
  }
  else 
  {
    printf("Error waiting for packets. error = %d\n", error);  
  }
  
  delay(5000);
}


/***********************************************************************************
*
* radioModuleSetup()
*
*   This function includes all functions related to the module setup and configuration
*   The user must keep in mind that each time the module powers on, all settings are set
*   to default values. So it is better to develop a specific function including all steps
*   for setup and call it everytime the module powers on.
*
*
***********************************************************************************/
uint8_t radioModuleSetup()
{ 
  uint8_t status = 0;
  uint8_t e = 0;
  
  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////

  e = LoRaWAN.ON(sock);

  // Check status
  if (e == 0)
  {
    printf("1. Switch ON OK\n");     
  }
  else 
  {
    printf("1. Switch ON error = %d\n",e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 2. Enable P2P mode
  //////////////////////////////////////////////

  e = LoRaWAN.macPause();

  // Check status
  if (e == 0)
  {
    printf("2. P2P mode enabled OK\n");
  }
  else 
  {
    printf("2. Enable P2P mode error = %d\n", e);
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 3. Set/Get Radio Power
  //////////////////////////////////////////////

  // Set power
  e = LoRaWAN.setRadioPower(power);

  // Check status
  if (e == 0)
  {
    printf("3.1. Set Radio Power OK\n");
  }
  else 
  {
    printf("3.1. Set Radio Power error = %d\n", e);
    status = 1;
  }

  // Get power
  e = LoRaWAN.getRadioPower();

  // Check status
  if (e == 0) 
  {
    printf("3.2. Get Radio Power OK. "); 
    printf("Power: %d\n",LoRaWAN._radioPower);
  }
  else 
  {
    printf("3.2. Get Radio Power error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 4. Set/Get Radio Frequency
  //////////////////////////////////////////////

  // Set frequency
  e = LoRaWAN.setRadioFreq(frequency);

  // Check status
  if (e == 0)
  {
    printf("4.1. Set Radio Frequency OK\n");
  }
  else 
  {
    printf("4.1. Set Radio Frequency error = %d\n", error);
    status = 1;
  }

  // Get frequency
  e = LoRaWAN.getRadioFreq();

  // Check status
  if (e == 0) 
  {
    printf("4.2. Get Radio Frequency OK. "); 
    printf("Frequency: %d\n", LoRaWAN._radioFreq);
  }
  else 
  {
    printf("4.2. Get Radio Frequency error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 5. Set/Get Radio Spreading Factor (SF)
  //////////////////////////////////////////////

  // Set SF
  e = LoRaWAN.setRadioSF(spreading_factor);

  // Check status
  if (e == 0)
  {
    printf("5.1. Set Radio SF OK\n");
  }
  else 
  {
    printf("5.1. Set Radio SF error = %e\n", e);
    status = 1;
  }

  // Get SF
  e = LoRaWAN.getRadioSF();

  // Check status
  if (e == 0) 
  {
    printf("5.2. Get Radio SF OK. "); 
    printf("Spreading Factor: %s\n", LoRaWAN._radioSF);
  }
  else 
  {
    printf("5.2. Get Radio SF error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 6. Set/Get Radio Coding Rate (CR)
  //////////////////////////////////////////////

  // Set CR
  e = LoRaWAN.setRadioCR(coding_rate);

  // Check status
  if (e == 0)
  {
    printf("6.1. Set Radio CR OK\n");
  }
  else 
  {
    printf("6.1. Set Radio CR error = %d\n", e);
    status = 1;
  }

  // Get CR
  e = LoRaWAN.getRadioCR();

  // Check status
  if (e == 0) 
  {
    printf("6.2. Get Radio CR OK. "); 
    printf("Coding Rate: %s\n",LoRaWAN._radioCR);
  }
  else 
  {
    printf("6.2. Get Radio CR error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 7. Set/Get Radio Bandwidth (BW)
  //////////////////////////////////////////////

  // Set BW
  e = LoRaWAN.setRadioBW(bandwidth);

  // Check status
  if (e == 0)
  {
    printf("7.1. Set Radio BW OK\n");
  }
  else 
  {
    printf("7.1. Set Radio BW error = %d\n", e);
  }

  // Get BW
  e = LoRaWAN.getRadioBW();

  // Check status
  if (e == 0) 
  {
    printf("7.2. Get Radio BW OK. "); 
    printf("Bandwidth: %u\n", LoRaWAN._radioBW);
  }
  else 
  {
    printf("7.2. Get Radio BW error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 8. Set/Get Radio CRC mode
  //////////////////////////////////////////////

  // Set CRC
  e = LoRaWAN.setRadioCRC(crc_mode);

  // Check status
  if (e == 0)
  {
    printf("8.1. Set Radio CRC mode OK\n");
  }
  else 
  {
    printf("8.1. Set Radio CRC mode error = %d\n", e);
    status = 1;
  }

  // Get CRC
  e = LoRaWAN.getRadioCRC();

  // Check status
  if (e == 0) 
  {
    printf("8.2. Get Radio CRC mode OK. "); 
    printf("CRC status: %u\n",LoRaWAN._crcStatus);
  }
  else 
  {
    printf("8.2. Get Radio CRC mode error = %e\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");


  return status;
}

void str2hex(char* strIndata, char* strOutdata){
    for (int i=0;i<strlen(strIndata); ++i) {
         sprintf (&strOutdata[i*2], "%02X", strIndata[i]);
    }
}

//////////////////////////////////////////////
// Main loop setup() and loop() declarations
//////////////////////////////////////////////

int main(int argc, char *argv[]){
	int rc;
	struct timeval tv;
	struct gps_data_t gps_data;
	char aux[40] = "";
	char params[10] = "";
	
	if (argc != 5){										  
		printf("Error en la entrada de argumentos.\n");
		exit(1);
	}
	
    frequency = atoi(argv[2]);
    strncpy(spreading_factor, argv[1], 10);
    strncpy(coding_rate, argv[4], 10);
    bandwidth = atoi(argv[3]);
	
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
    		printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
    		return EXIT_FAILURE;
	}
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

	setup();
	while(1){
		// Catch data
		if (gps_waiting (&gps_data, 2000000)) {
        		/* read data */
        		if ((rc = gps_read(&gps_data)) == -1) {
            			printf("error occured reading gps data. code: %d, reason: %s\n", rc, gps_errstr(rc));
        		} else {
            			/* Display data from the GPS receiver. */
            			if ((gps_data.status == STATUS_FIX) &&
               	 			(gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                			!isnan(gps_data.fix.latitude) &&
                			!isnan(gps_data.fix.longitude)) {
                			    sprintf(params, "%f", gps_data.fix.latitude);
                                strncat(params, ";", 20);
                                strncpy(aux, params, 20);
                                sprintf(params, "%f", gps_data.fix.longitude);
                                strncat(params, ";", 20);
                                strncat(aux, params, 20); 
                                sprintf(params, "%f", gps_data.fix.altitude);
                                strncat(params, ";", 20);
                                strncat(aux, params, 20);
                				str2hex(aux, data);
								printf("\n%s\n", data); 
                   		 		//gettimeofday(&tv, NULL); EDIT: tv.tv_sec isn't actually the timestamp!
                    			printf("latitude: %f, longitude: %f, altitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.altitude, gps_data.fix.speed, gps_data.fix.time); //EDIT: Replaced tv.tv_sec with gps_data.fix.time
            			} else {
                			printf("no GPS data available\n");
            			}
        		}
    		}
		loop();
	}
	return (0);
}

