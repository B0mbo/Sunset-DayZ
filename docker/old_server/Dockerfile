FROM debian:stable

RUN dpkg --add-architecture i386 \
 && apt-get update \
 && apt-get install -fyqq bash psutils inetutils-ping dnsutils mc apt-file libc6:i386 libncurses5:i386 libstdc++6:i386 cmake vim \
 && apt-get install -fyqq build-essential gcc-multilib g++-multilib make libcurl4-gnutls-dev:i386 libmariadb-dev:i386 curl pigz
#libmariadb-dev-compat multiarch-support

ENV SAMP_DATA="server_data"
ENV SAMP_ARCH="samp037svr_R3.tar.gz"
ENV SAMP_OLD="http://files.sa-mp.app/$SAMP_ARCH"

RUN mkdir /server
ADD $SAMP_OLD /server
RUN tar -I pigz -xf /server/$SAMP_ARCH -C /server && \
    mkdir -p /server/samp03/plugins && \
    sed -e '/^rcon_password\ /c rcon_password\ MyCoolPassW0rd' -e \
            '/^lanmode\ /c lanmode\ 1' -e \
            '/^filterscripts/c filterscripts baseTexture' -e \
            '/^maxnpc\ /c maxnpc\ 20' -e \
            '/^stream_distance\ /c stream_distance\ 1000.0' -e \
            '/^stream_rate\ /c stream_rate\ 800' -e \
            '/^port\ /c port\ 7780' -e \
            's/^announce\ 0$/announce\ 1/' -e \
            '/^hostname\ /c hostname\ DayZ\ Sunset\ Survival\ v0.6.3' -e \
            's/^weburl\ www\.sa\-mp\.com$/weburl\ vk\.com\/botinform/' -e \
            '/^maxplayers/c maxplayers\ 150' -i /server/samp03/server.cfg
ADD ./$SAMP_DATA.tar.gz /server

RUN cp /server/$SAMP_DATA/DayZ_037/samp-npc /server/samp03/samp-npc && \
    cp /server/$SAMP_DATA/DayZ_037/samp03svr /server/samp03/samp03svr && \
    cp /server/$SAMP_DATA/DayZ_037/server_log.txt /server/samp03/server_log.txt && \
    cp /server/$SAMP_DATA/DayZ_037/scriptfiles/SAfull* /server/samp03/scriptfiles && \
    cp /server/$SAMP_DATA/DayZ_037/plugins/*.so /server/samp03/plugins && \
    cp /server/$SAMP_DATA/DayZ_037/filterscripts/animations.amx /server/$SAMP_DATA/DayZ_037/filterscripts/small_base.amx /server/$SAMP_DATA/DayZ_037/filterscripts/baseTexture.amx /server/samp03/filterscripts && \
    cp /server/$SAMP_DATA/DayZ_037/gamemodes/DayZ+.amx /server/samp03/gamemodes && \
    sed -r 's/^gamemode0\ grandlarc\ 1$/gamemode0\ DayZ+\ 1/' -i /server/samp03/server.cfg && \
    echo 'gamemodetext DayZ Sunset v0.6.3' >> /server/samp03/server.cfg && \
    echo 'language Translator' >> /server/samp03/server.cfg && \
    echo 'plugins crashdetect.so mysql_static.so things.so MapAndreas.so translator.so FCNPC.so streamer.so' >> /server/samp03/server.cfg && \
    cat /server/samp03/server.cfg && \
    rm -rf /etc/localtime && \
    ln -s /usr/share/zoneinfo/Europe/Moscow /etc/localtime


EXPOSE 7780

WORKDIR /server/samp03
ENTRYPOINT ./samp03svr
