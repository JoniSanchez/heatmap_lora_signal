.PHONY: help
.DEFAULT_GOAL := help

# Frist compile and deploy
build-deploy-application:  ## Frist compile and deploy
	docker-compose build
	docker-compose up 

# Build application
build-application:  ## Only build application
	docker-compose build

# Deploy application
deploy-application:  ## Only deploy application
	docker-compose up
	
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
	@echo -e "Arguments/env variables: \n \
				"