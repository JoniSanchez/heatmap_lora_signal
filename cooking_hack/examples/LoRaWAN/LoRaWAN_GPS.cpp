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

// Device parameters for Back-End registration
////////////////////////////////////////////////////////////
char DEVICE_EUI[]  = "0102030405060708";
char DEVICE_ADDR[] = "05060708";
char NWK_SESSION_KEY[] = "01020304050607080910111213141516";
char APP_SESSION_KEY[] = "000102030405060708090A0B0C0D0E0F";
////////////////////////////////////////////////////////////

// Define port to use in Back-End: from 1 to 223
uint8_t PORT = 3;

// Define data payload to send (maximum is up to data rate)
//char data[] = "0102030405060708090A0B0C0D0E0F";

// variable
uint8_t error;

void setup() 
{
  printf("LoRaWAN example - Send Unconfirmed packets (no ACK)\n");

  printf("------------------------------------\n");
  printf("Module configuration\n");
  printf("------------------------------------\n\n");


  //////////////////////////////////////////////
  // 1. Switch on
  //////////////////////////////////////////////

  error = LoRaWAN.ON(sock);

  // Check status
  if( error == 0 ) 
  {
    printf("1. Switch ON OK\n");     
  }
  else 
  {
    printf("1. Switch ON error = %d\n", error); 
  }


  //////////////////////////////////////////////
  // 2. Set Device EUI
  //////////////////////////////////////////////

  error = LoRaWAN.setDeviceEUI(DEVICE_EUI);

  // Check status
  if( error == 0 ) 
  {
    printf("2. Device EUI set OK\n");     
  }
  else 
  {
    printf("2. Device EUI set error = %d\n", error); 
  }


  //////////////////////////////////////////////
  // 3. Set Device Address
  //////////////////////////////////////////////

  error = LoRaWAN.setDeviceAddr(DEVICE_ADDR);

  // Check status
  if( error == 0 ) 
  {
    printf("3. Device address set OK\n");     
  }
  else 
  {
    printf("3. Device address set error = %d\n", error); 
  }


  //////////////////////////////////////////////
  // 4. Set Network Session Key
  //////////////////////////////////////////////
 
  error = LoRaWAN.setNwkSessionKey(NWK_SESSION_KEY);

  // Check status
  if( error == 0 ) 
  {
    printf("4. Network Session Key set OK\n");     
  }
  else 
  {
    printf("4. Network Session Key set error = %d\n",error); 
  }


  //////////////////////////////////////////////
  // 5. Set Application Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setAppSessionKey(APP_SESSION_KEY);

  // Check status
  if( error == 0 ) 
  {
    printf("5. Application Session Key set OK\n");     
  }
  else 
  {
    printf("5. Application Session Key set error = %d\n", error); 
  }


  //////////////////////////////////////////////
  // 6. Save configuration
  //////////////////////////////////////////////
  
  error = LoRaWAN.saveConfig();

  // Check status
  if( error == 0 ) 
  {
    printf("6. Save configuration OK\n");     
  }
  else 
  {
    printf("6. Save configuration error = %d\n", error);
  }


  printf("\n------------------------------------\n");
  printf("Module configured\n");
  printf("------------------------------------\n\n");
  
  LoRaWAN.getDeviceEUI();
  printf("Device EUI: %s\n", LoRaWAN._devEUI);
  
  LoRaWAN.getDeviceAddr();
  printf("Device Address: %s\n\n", LoRaWAN._devAddr);
}



void loop(char* data) 
{
  
  //////////////////////////////////////////////
  // 1. Switch on
  //////////////////////////////////////////////

  error = LoRaWAN.ON(sock);


  // Check status
  if( error == 0 ) 
  {
    printf("1. Switch ON OK\n");     
  }
  else 
  {
    printf("1. Switch ON error = %d\n", error);
  }
  
  
  //////////////////////////////////////////////
  // 2. Join network
  //////////////////////////////////////////////

  error = LoRaWAN.joinABP();

  // Check status
  if( error == 0 ) 
  {
    printf("2. Join network OK\n");     

    //////////////////////////////////////////////
    // 3. Send unconfirmed packet 
    //////////////////////////////////////////////
    error = LoRaWAN.sendUnconfirmed(PORT, data);
  
    // Error messages:
    /*
     * '6' : Module hasn't joined a network
     * '5' : Sending error
     * '4' : Error with data length	  
     * '2' : Module didn't response
     * '1' : Module communication error   
     */
    // Check status
    if( error == 0 ) 
    {
      printf("3. Send Unconfirmed packet OK\n");     
      if (LoRaWAN._dataReceived == true)
      { 
        printf("   There's data on port number %d.\r\n", LoRaWAN._port);
        printf("   Data: %s\n", LoRaWAN._data);
      }
    }
    else 
    {
      printf("3. Send Unconfirmed packet error = %d\n", error); 
    }
  }
  else 
  {
    printf("2. Join network error = %d\n",error);
  }

  
  //////////////////////////////////////////////
  // 4. Clean channels
  //////////////////////////////////////////////
  error = LoRaWAN.reset();

  // Reset channels
  if( error == 0 ) 
  {
    printf("4. Clean channels OK\n");     
  }
  else 
  {
    printf("4. Clean channels error = %d\n", error); 
  }


  //////////////////////////////////////////////
  // 5. Switch off
  //////////////////////////////////////////////
  error = LoRaWAN.OFF(sock);

  // Check status
  if( error == 0 ) 
  {
    printf("5. Switch OFF OK\n");     
  }
  else 
  {
    printf("5. Switch OFF error = %d\n",error); 
  }
  
  
  printf("\n");
  delay(5000);
}

void str2hex(char* strIndata, char* strOutdata){
    for (int i=0;i<strlen(strIndata); ++i) {
         sprintf (&strOutdata[i*2], "%02X", strIndata[i]);
    }
}

//////////////////////////////////////////////
// Main loop setup() and loop() declarations
//////////////////////////////////////////////

int main (){
	char data[] = "000000000000000000000000000000";
	int rc;
	struct timeval tv;
	struct gps_data_t gps_data;
	char aux[40] = "";
	char params[10] = "";
	
	
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
                    			printf("latitude: %f, longitude: %f, altitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.altitude, gps_data.fix.speed, gps_data.fix.time); //EDIT: Replaced tv.tv_sec with gps_data.fix.time
            			} else {
                			printf("no GPS data available\n");
            			}
        		}
    		}
		loop(data);
	}
	return (0);
}