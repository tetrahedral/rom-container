FROM alpine:3.18 as builder
RUN apk add --no-cache build-base curl
WORKDIR /rom
COPY ./src src
COPY ./Makefile Makefile
RUN make

FROM alpine:3.18 as runner
WORKDIR /rom
COPY --from=builder /rom/rom rom
# MOUNT ./area area
# MOUNT ./gods gods
# MOUNT ./player player
# MOUNT ./scripts scripts
ENTRYPOINT [ "rom" ]
