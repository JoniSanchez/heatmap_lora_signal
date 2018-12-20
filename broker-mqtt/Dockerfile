FROM alpine:3.6

EXPOSE 1883
EXPOSE 9883

#VOLUME ["/var/lib/mosquitto", "/etc/mosquitto", "/etc/mosquitto.d"]
VOLUME ["/mosquitto/config", "/mosquitto/data", "/mosquitto/log"]

RUN addgroup -S mosquitto && \
    adduser -S -H -h /var/empty -s /sbin/nologin -D -G mosquitto mosquitto

ENV PATH=/usr/local/bin:/usr/local/sbin:$PATH
ENV MOSQUITTO_VERSION=v1.4.14
ENV MONGOC_VERSION=9982861dac67bae659ce8a3370b18c3a44f764fc
ENV AUTHPLUG_VERSION=b74a79a6767b56c773e21e9c4cf12b392c29e8e2

COPY run.sh /
COPY libressl.patch /
RUN buildDeps='git build-base libressl-dev libwebsockets-dev c-ares-dev util-linux-dev curl-dev libxslt docbook-xsl automake autoconf libtool'; \
    chmod +x /run.sh && \
    mkdir -p /mosquitto/data && \
    touch /mosquitto/data/.keep && \
    apk update && \
    apk add $buildDeps libwebsockets libuuid c-ares libressl curl ca-certificates && \
    git clone https://github.com/mongodb/mongo-c-driver.git && \
    cd mongo-c-driver && \
    git checkout ${MONGOC_VERSION} && \
    sh autogen.sh --with-libbson=bundled && \
    make && \
    make install && \
    cd / && \
    git clone https://github.com/eclipse/mosquitto.git mosquitto_src && \
    cd mosquitto_src && \
    git checkout ${MOSQUITTO_VERSION} -b ${MOSQUITTO_VERSION} && \
    sed -i -e "s|(INSTALL) -s|(INSTALL)|g" -e 's|--strip-program=${CROSS_COMPILE}${STRIP}||' */Makefile */*/Makefile && \
    sed -i "s@/usr/share/xml/docbook/stylesheet/docbook-xsl/manpages/docbook.xsl@/usr/share/xml/docbook/xsl-stylesheets-1.79.1/manpages/docbook.xsl@" man/manpage.xsl && \
    ## musl c lib do not support libanl
    sed -i 's/ -lanl//' config.mk && \
    patch -p1 < /libressl.patch && \
    # wo WITH_MEMORY_TRACKING=no, mosquitto segfault after receiving first message
    # libressl does not suppor PSK
    make WITH_MEMORY_TRACKING=no WITH_SRV=yes WITH_WEBSOCKETS=yes WITH_TLS_PSK=no && \
    make install && \
    git clone git://github.com/jpmens/mosquitto-auth-plug.git && \
    cd mosquitto-auth-plug && \
    git checkout ${AUTHPLUG_VERSION} && \
    cp config.mk.in config.mk && \
    sed -i "s/BACKEND_MONGO ?= no/BACKEND_MONGO ?= yes/" config.mk && \
    sed -i "s/BACKEND_FILES ?= no/BACKEND_FILES ?= yes/" config.mk && \
    sed -i "s/BACKEND_MYSQL ?= yes/BACKEND_MYSQL ?= no/" config.mk && \
    sed -i "s/MOSQUITTO_SRC =/MOSQUITTO_SRC = ..\//" config.mk && \
    sed -i "s/EVP_MD_CTX_new/EVP_MD_CTX_create/g" cache.c && \
    sed -i "s/EVP_MD_CTX_free/EVP_MD_CTX_destroy/g" cache.c && \
    make && \
    cp auth-plug.so /usr/local/lib/ && \
    cp np /usr/local/bin/ && chmod +x /usr/local/bin/np && \
    cd / && rm -rf mosquitto_src && rm /libressl.patch && rm -rf mongo-c-driver && \
    apk del $buildDeps && rm -rf /var/cache/apk/*

ADD mosquitto.conf /etc/mosquitto/mosquitto.conf
ENTRYPOINT ["/run.sh"]
CMD ["mosquitto"]
