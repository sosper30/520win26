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
└── hw1/                    (Your work)
│   └── main.cpp
└── hw2/                    (Your work)
    └── my_program.cpp

## 4. Setup (Do This Once)

Vocabulary:
- **image**: stateless set of files in a filesystem
- **container**: A running unix kernel using that filesystem

Follow these steps to build your environment for the first time.

1.  Open a terminal or command prompt.
2.  Navigate into this project directory (the one containing `docker-compose.yml`).
3.  Run the **`build`** command. This will download the base image and install all the tools. This will take several minutes.

    ```bash
    docker-compose build
    ```

## 5. How to Use the Container

Follow this workflow every time you want to work on your assignments.

### Step 1: Start the Container

In your terminal, run this command to start the container in the background:

```bash
docker-compose up -d
(Note: d stands for "detached")

Step 2: Get a Shell Inside the Container
Now that the container is running, "enter" it by running this command:

```
docker-compose exec eep520 /bin/bash
Your terminal prompt will change. You are now "inside" the Docker container and are in the /workspace directory (which is the same as your project directory). You can check by typing ls.

Step 3: Do Your Work
Inside the container, you can now compile and run your code just as you would on a standard Linux machine.

Compile with AddressSanitizer (ASan):

Bash

g++ -g -fsanitize=address hw1/main.cpp -o hw1/main
Run with Valgrind:

Bash

valgrind --leak-check=full hw1/main
Step 4: Exit the Container
When you are done, just type exit to leave the container.

Bash

exit
Your terminal will return to normal. The container will keep running in the background.

6. Stopping the Container
When you are completely finished working for the day, run this command to stop and remove the container. This does not delete your code, which is safe in your project folder.

Bash

docker-compose down
7. Useful Commands (Troubleshooting)
See running containers:

Bash

docker ps
(You should see eep520 in the list if it's running).

Force a "clean" build: If something seems broken, you can force Docker to rebuild everything from scratch. This will take a long time.

Bash

docker-compose build --no-cache
Stop and remove a container: If your container gets "stuck" or you just want to reset it, run docker-compose down and then docker-compose up -d to start a fresh one.