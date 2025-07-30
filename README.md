# 🧠 Philosophers

This project is part of the 42 curriculum and introduces fundamental concepts of **concurrent programming** using **threads** and **mutexes** in C.

## 📚 Project Overview

The program simulates a group of philosophers sitting around a table. Each philosopher alternates between **thinking**, **eating**, and **sleeping**. To eat, a philosopher must pick up two forks – one on the left and one on the right. Forks are shared between neighbors, so proper synchronization is required to avoid deadlocks and starvation.

The simulation ends either when a philosopher dies of starvation or, optionally, when all philosophers have eaten a certain number of times.

## ✅ Mandatory Part (`philo/`)

- Implemented in **C** using **POSIX threads (`pthread`)** and **mutexes**
- Each philosopher is represented by a **separate thread**
- Each fork is protected by a **mutex**
- No global variables are allowed
- Simulation logs must follow a strict format:

``` bash
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- Log messages must not overlap or interleave
- The program must avoid **race conditions**, **segfaults**, and **memory leaks**

### 🧪 Example Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Arguments:

number_of_philosophers: Number of philosophers (and forks)

time_to_die: Max time (ms) a philosopher can go without eating

time_to_eat: Time (ms) a philosopher takes to eat

time_to_sleep: Time (ms) a philosopher sleeps after eating

number_of_times_each_philosopher_must_eat (optional): If specified, the simulation ends when each philosopher has eaten at least this many times

## 🛠️ Makefile Rules
- make / make all – compile the program

- make clean – remove object files

- make fclean – remove object files and binary

- make re – recompile everything from scratch

## 🔒 Constraints
- Must follow the 42 Norm coding standard

Only allowed functions:

- memset, printf, malloc, free, write, usleep, gettimeofday

- pthread_create, pthread_detach, pthread_join

- pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

“Philosophy begins in wonder.”
— Socrates