FROM debian:11
WORKDIR /code

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y gcc make tcpdump wget git curl man cmake g++
