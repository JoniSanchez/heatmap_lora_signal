FROM node:carbon

USER root

ADD ./ /

RUN mkdir -p /home/node/.ssh
	
ADD id_rsa_raspi /home/node/.ssh/id_rsa
ADD id_rsa_raspi /root/.ssh/id_rsa

RUN npm install

EXPOSE 8082

RUN \
	export ANSIBLE_HOST_KEY_CHECKING=False && \
	apt-get update && \
	apt-get install -y ansible && \
	cp /ansible/playbook/ansible.cfg /etc/ansible/ansible.cfg && \
	chown node:node /home/node/.ssh/id_rsa && \
	chown node:node /home/node/.ssh && \
	chmod 600 /home/node/.ssh/id_rsa && \
	chmod 600 /root/.ssh/id_rsa

CMD [ "node", "/server.js" ]