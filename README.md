# Genetic (Evolutional) algorithm
This repository is an implementation of modified genetic algorithm, which we call Evolutional Algorithm. It is adapted to solve P||C<sub>max</sub> problem. Besides the implementation of the algorithm, this repo contains utlilities that help test it, such as benchmark generator or simple greedy algorithm

### How it works
The algorithm stores line-ups as dynamic arrays of vectors. Each vector in an array represents one processor, each vector stores total execution time on a given processor (first element), and times of each process within that processor. The statring line-up is random. The algorithm starts from that line-up and creates *n* generations, each consisting of a population of *m* line-ups (*n* and *m* are parameters, which can be adjusted to optimize time or quality of the solution). 

New line-ups in a generation are built in a following way based on the best line-up found in the process so far:

1. Processors with the longest and the shortest execution times are searched within the array
2. A random process from the longer processor is put into the shorter processor
3. The process is repeated *x* times ( *x* is a parameter, which can be adjusted)

Whilst creating the population, algorithm only memorizes the current line-up and the best line-up so far (which is determined by the P||C<sub>max</sub>). Once the population is done building, we have te best line-up from that population and if it is better than the base line-up, the new line-up is a base for the next generation.
