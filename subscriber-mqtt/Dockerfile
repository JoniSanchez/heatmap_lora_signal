FROM node:carbon

ADD ./ /

RUN npm install

EXPOSE 8083

RUN npm install

CMD ["node", "/server.js"]