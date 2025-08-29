FROM ubuntu:22.04

RUN apt-get update -qq && \
    apt-get install -y build-essential cmake curl libcurl4-openssl-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app/build

RUN cmake .. && make

# Expose the port your server listens on
EXPOSE 9000

# Start the server
CMD ["./cpp-http-server"]
