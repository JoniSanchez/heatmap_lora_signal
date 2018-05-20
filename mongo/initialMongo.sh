#!/bin/bash 
set -m
 
mongod --bind_ip_all --smallfiles &

USER=${MONGODB_USER:-"lora"} 
DATABASE=${MONGODB_DATABASE:-"lora"} 
PASS=${MONGODB_PASS:-"lora"} 
_word=$( [ ${MONGODB_PASS} ] && echo "preset" || echo "random" ) 
sleep 3
echo "=> Creating an ${USER} user with a ${_word} password in MongoDB" 
/usr/bin/mongo $DATABASE --eval  "db.createUser({ user: '$USER', pwd: '$PASS', roles:['dbOwner']});"
/usr/bin/mongo admin --eval  "db.createUser({ user: '$USER', pwd: '$PASS', roles:['root']});"
mongo admin -u $USER -p $PASS << EOF 
use test; 
db.createUser({ user: '$USER' , pwd: '$PASS', roles: ['dbOwner']}); 
EOF
echo "=> Done!" 

echo "=> Creating an ${USER} user with a ${_word} password in MongoDB" 

mongod --shutdown

echo "========================================================================" 
echo "You can now connect to this MongoDB server using:" 
echo "" 
echo "    mongo $DATABASE -u $USER -p $PASS --host <host> --port <port>" 
echo "" 
echo "Please remember to change the above password as soon as possible!" 
echo "========================================================================"

mongod --bind_ip_all --smallfiles --auth