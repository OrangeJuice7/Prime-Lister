# Prime Lister
A small and fast(?) prime number generator, written in C++.

## How It Works
To test if a number `n` is prime, this algorithm checks if `n` is divisible by any *prime* that is at most `sqrt(n)`. As a further optimization, all even `n` are skipped.

By the [prime number theorem](https://en.wikipedia.org/wiki/Prime_number_theorem), the number of primes before any number `n` approaches `n / log(n)`. Thus, testing if `n` is prime takes O(`sqrt(n) / log(sqrt(n))`) = O(`sqrt(n) / log(n)`) time.

This is in comparison to a more naive algorithm that checks if `n` is divisble by every number before `sqrt(n)`, which would take O(`sqrt(n)`) time for each `n`.
