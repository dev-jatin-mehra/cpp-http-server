FROM ubuntu:22.04

# Install build tools and libcurl if you use it
RUN apt-get update && \
    apt-get install -y build-essential curl libcurl4-openssl-dev && \
    rm -rf /var/lib/apt/lists/*

# Copy code and build
WORKDIR /app
COPY . .
RUN make # or cmake .. && make, or whatever your build command is

# Expose the port your server uses
EXPOSE 9000

# Start the server
CMD ["./cpp-http-server"]