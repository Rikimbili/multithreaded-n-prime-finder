# Multi-Threaded N Prime Finder using Sieve of Eratosthenes in C++ and Golang

###### Made by Raciel Antela Pardo for COP4520

## Problem Description

Your non-technical manager assigns you the task to find all primes between 1 and
10^8. The assumption is that your company is going to use a parallel machine that
supports eight concurrent threads. Thus, in your design you should plan to spawn 8
threads that will perform the necessary computation. Your boss does not have a strong
technical background but she is a reasonable person. Therefore, she expects to see that
the work is distributed such that the computational execution time is approximately
equivalent among the threads. Finally, you need to provide a brief summary of your
approach and an informal statement reasoning about the correctness and efficiency of
your design. Provide a summary of the experimental evaluation of your approach.
Remember, that your company cannot afford a supercomputer and rents a machine by
the minute, so the longer your program takes, the more it costs. Feel free to use any
programming language of your choice that supports multi-threading as long as you
provide a ReadMe file with instructions for your manager explaining how to compile and
run your program from the command prompt.

## Approach

For the solution, the algorithm Sieve of Eratosthenes was implemented to avoid brute force and efficiently find all
primes for the given n value of 10^8. The algorithm is as follows:

1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
2. Initially, let p equal 2, the smallest prime number.
3. Enumerate the multiples of p by counting in increments of p from 2p to n, and mark them as composite in the list (
   these will be 2p, 3p, 4p, ...; the p itself should not be marked).
4. Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise,
   let p now equal this new number (which is the next prime), and repeat from step 3 until p reaches the square root of
   n (the largest possible prime factor of any number in the list).
5. All the numbers remaining not marked in the list are prime.

## Proof of Correctness

C++ has built-in support for multi-threading via the standard library. To ensure that all threads were running
concurrently,
a for loop pushed each thread into a vector of threads. After that, each thread was joined in a separate for loop.

## Experimental Evaluation and Results

**Note:** Any timing result shown was measured on a Ryzen 5800X Zen 3 CPU with 8 cores / 16 threads and 32GB of System
RAM. 8 threads were used when running the program and n = 10^8.

The algorithm used ensures that no unnecessary iteration takes place. The Sieve of Eratosthenes implementation has
time complexity of O(n log log n) for any arbitrary input. However, since this problem specifies that the upper bound is
10^8, the runtime is constant.

As explained in the last section, the algorithm only iterates through the numbers that are not composite up to the
square root of n which ensures a very efficient operation compared with brute force.

Initially, the numbers' vector was instantiated with the boolean type, but it caused unsafe thread
accesses and the output was different with each run of the program. On top of that, the runtime averaged **1781ms**
which is worse than the best runtime ultimately achieved. To fix this, the vector was changed to the integer type. After
this small change. the runtime was brought down to an average of **1254ms**.

To ensure that all threads were doing close to equivalent work, the smaller numbers were distributed to 2/3 of all the
threads or 5 out of 8 threads in this case. Smaller numbers result in larger operations as those have more multiples
that need to be checked when marking composite numbers. The final runtime after this change was **712ms**.

## How to run

1. `cd` to this project folder
2. Run `g++ -std=c++20 -pthread primes.cpp && ./a.out` in the terminal
3. The full output will be in the `primes.txt` file