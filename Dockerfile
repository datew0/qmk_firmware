FROM debian:latest

VOLUME /qmk_firmware
WORKDIR /qmk_firmware

RUN apt update && apt install make gcc-arm-none-eabi -y

CMD ["make annepro2/c18:datew0"]
