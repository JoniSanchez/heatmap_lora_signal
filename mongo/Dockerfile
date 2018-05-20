FROM mongo:3.6

ENV MONGODB_USER=lora
ENV MONGODB_DATABASE=lora
ENV MONGODB_PASS=lora

COPY /initialMongo.sh /initialMongo.sh
    
CMD ["/initialMongo.sh"] 