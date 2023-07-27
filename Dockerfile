FROM alpine:3.18 as builder

RUN apk add --no-cache build-base

WORKDIR /rom

COPY ./area area
COPY ./gods gods
COPY ./player player
COPY ./src src

WORKDIR /rom/src

RUN make -f Makefile.linux
