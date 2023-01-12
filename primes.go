// Author: Raciel Antela Pardo
// Date: 1-11-2023
// Note: This is the initial version I programmed before the assignment requirement was updated. I kept this since it
// actually resulted in the best runtime (500ms) on a Ryzen 5800x compared to my C++ solution (700ms). My guess is that
// the Go compiler is able to optimize this code better along with a more lightweight sync/threading library.

package main

import (
	"fmt"
	"log"
	"math"
	"os"
	"sync"
	"time"
)

const MAX_NUM = 100000000 // Max number to check for primes
const MAX_THREADS = 8     // Max threads to spawn

// Writes the following to a primes.txt file:
// <execution time>  <total number of primes found>  <sum of all primes found>
// <top ten maximum primes, listed in order from lowest to highest>
func writeToFile(primes []bool, durationMs int64) {
	f, err := os.Create("primes.txt")
	if err != nil {
		log.Fatal(err)
	}

	topPrimes := make([]int, 0, 10)
	primesSum := 0
	primesCount := 0

	for i := MAX_NUM; i >= 2; i-- {
		if primes[i] == true {
			if len(topPrimes) < 10 {
				topPrimes = append(topPrimes, i)
			}
			primesSum += i
			primesCount++
		}
	}

	f.WriteString(fmt.Sprintf("%dms %d %d\n", durationMs, primesCount, primesSum))
	for i := 9; i >= 0; i-- {
		f.WriteString(fmt.Sprintf("%d ", topPrimes[i]))
	}
	f.WriteString("\n")
	defer f.Close()
}

// Sets to false all composite numbers in the primes array
func markComposite(primes []bool, start int, end int, wg *sync.WaitGroup) {
	defer wg.Done()
	for i := start; i <= end; i++ {
		if primes[i] == true {
			for j := i * 2; j <= MAX_NUM; j += i {
				primes[j] = false
			}
		}
	}
}

func main() {
	primes := make([]bool, MAX_NUM+1)
	sqrtMaxNum := int(math.Sqrt(MAX_NUM))

	for i := 0; i < MAX_NUM+1; i++ {
		primes[i] = true
	}

	// Spawn 8 threads to mark composite numbers
	start := time.Now()
	var wg sync.WaitGroup
	wg.Add(MAX_THREADS)
	for i := 0; i < MAX_THREADS; i++ {
		start := 2 + i*sqrtMaxNum/MAX_THREADS
		end := start + sqrtMaxNum/MAX_THREADS
		go markComposite(primes, start, end, &wg)
	}
	wg.Wait()

	writeToFile(primes, time.Since(start).Milliseconds())

	fmt.Println("Finished")
}
