.PHONY: help
.DEFAULT_GOAL := help

##Variables
SPREADING_FACTOR?=sf12
FRECUENCY?=868100000
BANDWIDTH?=125
CODING_RATE?=4/5

# Frist compile to Lora
deploy-configure-lora:  ## Frist compile to Lora
	./cook.sh LoRaWAN_P2P_01_configure_module.cpp 
	sudo ./LoRaWAN_P2P_01_configure_module.cpp_exe

# Send Packages Lora with GPS
send-packages-lora-gps:  ## Send Packages Lora with GPS
	./cook.sh LoRaWAN_GPS.cpp
	sudo ./LoRaWAN_GPS.cpp_exe ${SPREADING_FACTOR} ${FRECUENCY} ${BANDWIDTH} ${CODING_RATE}

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
	@echo -e "Arguments/env variables: \n \
				"