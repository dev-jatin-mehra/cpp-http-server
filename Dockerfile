FROM ubuntu:22.04

RUN apt-get update -qq && \
    apt-get install -y build-essential cmake curl libcurl4-openssl-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*
    
COPY cpp-http-server /app/cpp-http-server

WORKDIR /app/cpp-http-server/build

RUN cmake .. && make

EXPOSE 9000

CMD ["./cpp-http-server"]
