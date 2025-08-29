FROM ubuntu:22.04

# Install required packages
RUN apt-get update -qq && \
    apt-get install -y build-essential cmake curl libcurl4-openssl-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

COPY . /app
RUN mkdir -p /app/build
WORKDIR /app/build
RUN cmake .. && make

# Expose the port your server uses
EXPOSE 9000

# Run the compiled server binary (adjust if binary name is different)
CMD ["./cpp-http-server"]
