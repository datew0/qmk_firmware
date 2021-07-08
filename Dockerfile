FROM debian:latest

VOLUME /qmk_firmware
WORKDIR /qmk_firmware

#COPY util/qmk_install.sh /etc/

RUN apt update && apt install make gcc-arm-none-eabi -y

CMD ["make annepro2/c18:datew0"]
