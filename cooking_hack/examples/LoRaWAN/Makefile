.PHONY: help
.DEFAULT_GOAL := help

##Variables
SPREADING_FACTOR?=sf7
FRECUENCY?=868000000
BANDWIDTH?=125
CODING_RATE?=4/5

# All complete configure and send
configure-send-lora:  ## All complete
	sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock
	./cook.sh LoRaWAN_P2P_01_configure_module.cpp 
	sudo ./LoRaWAN_P2P_01_configure_module.cpp_exe ${SPREADING_FACTOR} ${FRECUENCY} ${BANDWIDTH} ${CODING_RATE}
	./cook.sh LoRaWAN_GPS.cpp
	sudo ./LoRaWAN_GPS.cpp_exe 

# Frist compile to Lora
deploy-configure-lora:  ## Frist compile to Lora
	./cook.sh LoRaWAN_P2P_01_configure_module.cpp 
	sudo ./LoRaWAN_P2P_01_configure_module.cpp_exe ${SPREADING_FACTOR} ${FRECUENCY} ${BANDWIDTH} ${CODING_RATE}

# Send Packages Lora with GPS
send-packages-lora-gps:  ## Send Packages Lora with GPS
	sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock
	./cook.sh LoRaWAN_GPS.cpp
	sudo ./LoRaWAN_GPS.cpp_exe 

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
	@echo -e "Arguments/env variables: \n \
				"