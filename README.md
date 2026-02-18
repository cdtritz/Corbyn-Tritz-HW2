Corbyn-Tritz-HW2
CS370 HW2 - fork(), exec(), wait()

Files:
- coordinator.c
  Spawns 4 child processes using fork(). After thatr it then uses execlp() to
  replace each child with the checker program. The parent has to then wait for each child
  to finish using waitpid() and finally prints the child's exit code.

- checker.c
  Accepts two positive integer arguments:
    arg1 = divisor
    arg2 = dividend
  Prints its PID, checks divisibility prints result and returns:
    1 if divisible (nonzero)
    0 if not divisible

- Makefile
  Supports:
    make all (or just make)
    make clean

Build:
  make

Run examples:
  ./coordinator 300 3 20 49 102
  ./coordinator 225 8 15 21 45
