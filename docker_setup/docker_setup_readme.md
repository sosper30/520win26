# EEP 520: C++ Development Environment

## 1. Overview

This course provides a self-contained C++ development environment using Docker. It includes all the necessary tools for this course, such as:
* `g++` / `gcc`
* `make` / `cmake`
* `gdb` (The GNU Debugger)
* `valgrind` (for memory leak detection)
* AddressSanitizer (ASan)
* GoogleTest (for unit testing)

You will edit code on your main computer (the "host") and compile/run it *inside* the container.

## 2. Prerequisites

You must install **Docker** on your system.
Mac
---
- Go to https://www.docker.com/

Download `Docker.dmg` and double click on it. Once the Docker icon shows up in your status bar, you can open a terminal and start using docker.

Windows 10 Professional or Enterprise
---
- Go to https://www.docker.com/
- Download and run installer
- Note: Go to UWARE/Microsoft ad upgrade from Win 10 to "Win 10 for education"

Windows 10 Home and possibly Windows 8
---
- Go to https://docs.docker.com/toolbox/toolbox_install_windows/
- Download and run installer
- Run Docker Quickstart

Unix
---
```
sudo apt install docker.io
sudo systemctl start docker
```

## 3. Folder Structure

All files in this project directory (the one containing your `Dockerfile` and `docker-compose.yml`) are automatically shared with the Docker container.

You can create your homework folders, `main.cpp` files, and `Makefiles` right here, and they will be inside the container for you to compile.

A good structure would be:

eep520-docker-project/
│
├── docker-compose.yml    (From course)
├── Dockerfile            (From course)
│
├── hw1/                  (Your work)
│   └── main.cpp
│
└── hw2/                  (Your work)
    └── my_program.cpp


## 4. Setup 

Vocabulary:
- **image**: stateless set of files in a filesystem
- **container**: A running unix kernel using that filesystem

Step 1: Build and Start the Container

Open a terminal and navigate to this project directory. Run the following command:

```
docker-compose up -d --build
```

This command will:

Build your Docker image (the first time, this will take several minutes).

Create and start your eep520 container in the background (-d).

You can run this same command every time. It will intelligently start, re-create, or build the container as needed.

Step 2: Get a Shell Inside the Container

Now that the container is running, "enter" it by running this command:

```
docker exec -it eep520 /bin/bash
```

Your terminal prompt will change. You are now "inside" the Docker container and are in the /workspace directory (which is the same as your project directory). You can check by typing ls. 

Step 3: Do Your Work
Inside the container, you can now compile and run your code just as you would on a standard Linux machine.

Step 4: Exit the Container
When you are done, just type exit to leave the container.

```
exit
```
Your terminal will return to normal. The container will keep running in the background.

## 5. Stopping the Container
When you are completely finished working for the day, run this command to stop and remove the container. 

```
docker-compose down
```