#include <cstdint>
#include <climits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <list>

#define PRIMES_FILENAME "primes.txt"
#define PRIME_TYPE uint64_t
#define PRIME_LIMIT ULLONG_MAX // > 18e18

// SIGINT catcher
// Credit: https://stackoverflow.com/questions/13010531/leaving-an-infinite-while-loop-in-c
//#include <unistd.h>
#include <csignal>
volatile sig_atomic_t stop;
void inthand(int signum) {
    stop = 1;
}

std::list<PRIME_TYPE> primes;
std::fstream primesFile;

void addPrime(PRIME_TYPE prime) {
    if (primes.size() % 100000 == 0) std::cout << primes.size() << "th prime: " << prime << "\n";
    primesFile << prime << "\n";
    primes.push_back(prime);
}

int main() {
    std::cout << "Started!\n";
    PRIME_TYPE n = 0;

    // Open primes file for reading
    std::cout << "Opening " << PRIMES_FILENAME << "...\n";
    primesFile.open(PRIMES_FILENAME, std::ios::in | std::ios::out | std::ios::app);

    // Read in the current list of primes
    if (primesFile.is_open()) {
        while (true) {
            primesFile >> n;
            if (primesFile.eof()) break;
            primes.push_back(n);
        }
    } else {
        primesFile.open(PRIMES_FILENAME, std::ios::out);
        addPrime(2);
        addPrime(3);
        n = 3;
    }
    std::cout << "Primes loaded.\n";
    primesFile.close();

    // Open primes file for writing
    primesFile.open(PRIMES_FILENAME, std::ios::out | std::ios::app);

    // Loop to generate more primes, until ctrl-C (SIGINT) is given
    std::cout << "Searching for primes... (do ctrl-C to stop)\n";
    signal(SIGINT, inthand);
    while (!stop && n < PRIME_LIMIT) {
        n += 2;
        bool n_is_prime = true;

        for (PRIME_TYPE prime : primes) {
            if (prime > sqrt(n)) break;

            if (n % prime == 0) { // n is divisible by prime
                n_is_prime = false;
                break;
            }
        }

        if (n_is_prime)
            addPrime(n);
    }

    std::cout << "n = " << n << "\n";
    std::cout << "Last prime found: " << primes.back() << "\n";
    primesFile.close();
    return 0;
}
