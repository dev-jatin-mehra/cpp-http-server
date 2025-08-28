# Minimal C++ HTTP Server

A simple HTTP server built using only C++ 

## Features

- Listens for HTTP connections on a configurable port
- Handles basic HTTP GET requests (returns "Hello, World!" for `/`)
- Minimal, clean, and easy to understand
- Good starting point to learn how HTTP works at a low level

## Folder Structure

```
cpp-http-server/
├── src/
│   ├── main.cpp
│   ├── http_server.cpp
│   └── http_server.h
├── include/
│   └── http_server.h
├── CMakeLists.txt
└── README.md
```

## Run

1. **Clone the repo** (or copy these files into your Codespace).
2. **Build:**
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. **Run:**
   ```sh
   ./cpp-http-server
   ```
4. **Test:**  
   Open your browser to [http://localhost:8080](http://localhost:8080) and you should see "Hello, World!".

---