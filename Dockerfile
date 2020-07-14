#----
FROM debian:stretch-slim as qemu
RUN apt update && apt install -y qemu-user-static

################################################################################
# ROOTFS
################################################################################
FROM arm32v7/debian:stretch-slim as rootfs
COPY --from=qemu /usr/bin/qemu-arm-static /usr/bin/
RUN apt update \
    && apt install -y vim \
	&& apt install -y gcc \
    && apt install -y libmosquitto-dev \
    && rm -rf /var/lib/apt/lists/*

###############################################################################
# Server
##############################################################################
ENV APP app
RUN mkdir /${APP}
COPY hellodocker /${APP}
WORKDIR /${APP}
RUN rm /usr/bin/qemu-arm-static

#CMD ["bash"]
CMD ["/app/hellodocker", "10.0.20.132", "1883", "update"]


