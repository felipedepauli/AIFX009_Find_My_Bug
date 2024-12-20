FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/Sao_Paulo

WORKDIR /app
COPY app/* .

CMD ["./client", "video", "/app/resources/videos/Vehicles_Traffic.mp4"]
