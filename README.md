# Multi-Threaded N Prime Finder using Sieve of Eratosthenes in Golang
Raciel Antela Pardo - COP4520

## Problem Description
Your non-technical manager assigns you the task to find all primes between 1 and 
10^8.  The assumption is that your company is going to use a parallel machine that 
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
For the solution, the algorithm Sieve of Eratosthenes was implemented to avoid brute force and efficiently find all primes for the given n value of 10^8. The algorithm is as follows: 
1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
2. Initially, let p equal 2, the smallest prime number.
3. Enumerate the multiples of p by counting in increments of p from 2p to n, and mark them as composite in the list (these will be 2p, 3p, 4p, ...; the p itself should not be marked).
4. Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3 until p reaches the square root of n (the largest possible prime factor of any number in the list).
5. All the numbers remaining not marked in the list are prime.

## Evaluation
The algorithm used ensures that no unnecessary iteration takes place and the time complexity remains O(n log log n). 

The average time recorded for n=10^8 on a Ryzen 5800X (8 cores 16 threads CPU) was: 550ms

## How to run
1. Install Go here -> https://go.dev/doc/install
2. Run `go run primes.go` in the terminal

**Note:** If you are on windows and get the error `The term 'go' is not recognized...`, close the terminal window and reopen it so that it loads the updated env variables.
```