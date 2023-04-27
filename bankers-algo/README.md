# Bankers Algorithm

This project provides a solution for the bankers algorithm and answers the question
"Is the system in a safe state? If Yes, then what is the safe sequence?"

# Getting Started

### Prerequisites
* clang - install using `sudo apt install clang`
* make - the following command will install `make` as well as `gcc`, `g++`, etc.

    ```sudo apt install build-essentials```

### Installation
Clone the repository using [git](https://git-scm.com/downloads)
```
git clone https://github.com/tristanbesser/bankers-algo.git
```
Or download the zip from [github](https://github.com/tristanbesser/producer-consumer)

# Usage
### Input File
The program is set to consider a system with 5 processes (numbered 0 to 4) and 3 resource types.
The default input file is set to 
```
3 3 2

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```
The first group of numbers represents the number of available resources of each type. The second line represents the number of resources of each type currently allocated to each process. The third group of numbers represents he maximum demand of each process in a system.

### Compiling and Running
There are 2 ways to run the project
1. Using the provided Makefile

    Compile the program
    ```
    make algo
    ```
    Run the programs
    ```
    make run
    ```

    Remove executable files when done
    ```bash
    make clean
    ```
2. Manually inputing the commands in the terminal
    
    Compile the programs
    ```bash
    clang++ main.cpp -o algo.o
    ```
    Run the program
    ```
    ./algo.o
    ```

    Remove executable files when done
    ```
    rm *.o
    ```

### Sample Output
```
user@example:~/Projects/bankers-algo/src$ make algo
clang++ main.cpp -o algo.o
user@example:~/Projects/bankers-algo/src$ make run
./algo.o
Available:
3 3 2 

Allocated:
0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 

Max:
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 

The system is in a safe state!
The safe sequence is: P1 ~ P3 ~ P4 ~ P0 ~ P2
```