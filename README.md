# 42Cursus-Philosophers

This project is an integral part of the 42Lisboa curriculum and aims to create a program written in C that simulates and solves the dining philosophers problem.

The primary goal of this project is to learn about concurrent multithreading and explore associated challenges, such as race conditions and deadlocks. Additionally, the project aims to understand and implement solutions for these challenges through the use of mutexes or semaphores.

## The Dining Philosophers Problem

The Dining Philosophers Problem is a classic challenge designed to explore multithreading and its associated challenges.

So, on a round table, there are five bowls of spaghetti and between each bowl, there is a fork (five forks on the table). In front of each bowl sits a philosopher, starving and eager to eat.
Each philosopher needs to eat, sleep and think in that order and they must start eating before starving until death.

1. Eat:
   - For the philosopher to eat, he needs two forks. However, since each philosopher has only one fork, he needs to hold the fork of his neighbor on the table. First, he tries to grab a right fork and then the left. After successfully catch any forks, he just release after being able to eat and finish.
  
2. Sleep:
   - After eating, the philosopher places the forks back on the table and starts sleeping.

3. Think:
   - After waking up, the philosopher begins to think. While doing so, he will attempt to grab the forks again to eat, repeating the cycle.

## Specific Problems and Solutions

Each philosopher takes a predetermined time to eat, to sleep and to die, the especific times will be passed by parameter. If a philosopher cannot grab the forks and eat before the 'time to die' timeout, the philosopher will die and the simulation stops. Of course, the goal is to continue the simulation for as long as possible.

**Race Condition:**

Every philosopher is a thread and every fork is a resource that the thread has to process. In this case, every thread will share resources with another thread (every philosopher will share a fork with the neighbor on the table).

This creates a problem known as a race condition. Race conditions occur when multiple threads attempt to process a resource simultaneously, leading to issues. For example, consider an integer with an initial value of 10 that we want two threads to increment. The expected result should be 12, as each thread increments the original value by 1. However, if the threads try to increment the value at the same time, both may read the original value (10) before either increments it. Consequently, they both increment from the value 10, resulting in a final value of 11, which is incorrect.

To solve this problem, a technique called mutexes (locking mechanism) is employed. This essentially locks a section of memory when some threads are using it and releases that memory to allow another thread to use it. The result is that only one thread at a time can use a resource.


## Installation / Usage

This project is designed to work on Linux and macOS.

Clone repo:
```shell
git clone https://github.com/dspereira/42Cursus-Philosophers.git philo
```

Build:
```shell
make
```
or
```shell
make re
```

Usage example:
```shell
./philo 4 310 200 100
```

## License

This project is licensed under the [MIT License](https://github.com/dspereira/42Cursus-Philosophers/blob/main/LICENSE).

## Contact

If you have any questions or comments about this project, please feel free to contact me at diogo.s.pereira@outlook.pt.
