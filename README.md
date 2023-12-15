# 42Cursus-Philosophers

This project is an integral part of the 42Lisboa curriculum and aims to create a program written in C that simulates and solves the dining philosophers problem.

The primary goal of this project is to learn about concurrent multithreading and explore associated challenges, such as race conditions and deadlocks. Additionally, the project aims to understand and implement solutions for these challenges through the use of mutexes or semaphores.

## Table of Content
1. [The Dining Philosophers Problem](#the-dining-philosophers-problem)
2. [Specific Problems and Solutions](#specific-problems-and-solutions)
   1. [Race Condition](#race-condition)
   2. [Deadlocks](#deadlocks)
   3. [Conclusion](#conclusion)
3. [Installation / Usage](#installation--usage)
4. [License](#license)
5. [Contact](#contact)

## The Dining Philosophers Problem

The Dining Philosophers Problem is a classic challenge designed to explore multithreading and its associated challenges.

On a round table, there are five bowls of spaghetti, and between each bowl, there is a fork (five forks on the table). In front of each bowl sits a philosopher, starving and eager to eat.
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

This creates a problem known as a race condition. Race condition occurs when multiple threads attempt to process a resource simultaneously, leading to issues. For example, consider an integer with an initial value of 10 that we want two threads to increment. The expected result should be 12, as each thread increments the original value by 1. However, if the threads try to increment the value at the same time, both may read the original value 10 before either increments it. Consequently, they both increment from the value 10, resulting in a final value of 11, which is incorrect.

To solve this problem, a technique called mutexes (locking mechanism) is employed. This essentially locks a section of memory when some thread are using it and releases that memory to allow another thread to use it. The result is that only one thread at a time can use a resource.

**Deadlocks:**

So, while using mutexes to solve race conditions, we introduce another problem known as deadlocks. 

For simplicity, consider a scenario with two philosophers, two bowls of spaghetti, and two forks. In the initial program state, if each philosopher attempts to grab a right fork, neither can eat because there is only one fork, and neither can release a fork because they haven't eaten yet. Consequently, the two philosophers will starve until death, resulting in a deadlock. A deadlock occurs when a thread is waiting for a resource that is being used by another thread, and the thread holding the resource cannot release it because it requires a resource held by the first thread.

In this case, the solution is simple. If at the start of the program, we introduce a delay for the second philosopher to wait, the first philosopher has enough time to grab both forks and eat. After eating, the first philosopher will sleep, allowing the second philosopher the opportunity to grab the forks and eat. The second philosopher will, in turn, sleep after eating. This solution introduces a synchronization between the two philosophers, preventing the occurrence of deadlocks.

If we categorize the philosophers into even and odd, we can start by allowing the odd philosophers to begin and introduce a delay for the even philosophers at the start of the program. After this initial delay, all the philosophers will synchronize, ensuring a smooth and coordinated execution.

**Conclusion:**

In conclusion, if we successfully solve race conditions and deadlocks, the only way for philosophers to face mortality is by not providing sufficient time for sleep and setting a short "time to die." As these are variable parameters that you can customize, you have the flexibility to test with any quantity of philosophers (exercise caution with the number of threads you create) and adjust the times as needed. Below is an example:

```shell
./philo n_of_philosophers time_to_die time_to_eat time_to_sleep n_of_times_each_philosopher_must_eat(optional)
```

![example](https://github.com/dspereira/42Cursus-Philosophers/blob/main/images/example.png)

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
