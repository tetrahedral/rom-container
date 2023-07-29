FROM alpine:3.18 as builder
RUN apk add --no-cache build-base curl

COPY ./src /rom/src
COPY ./Makefile /rom/Makefile
WORKDIR /rom
RUN make

FROM alpine:3.18 as runner

RUN mkdir -p /rom/src && \
    mkdir -p /rom/area && \
    mkdir -p /rom/log && \
    mkdir -p /rom/player

COPY --from=builder /rom/src/rom /rom/src/rom
COPY ./area /rom/area
COPY ./scripts /rom/scripts

WORKDIR /rom/area
VOLUME /rom
ARG PORT=9000
ENTRYPOINT [ "startup", "${PORT}" ]
