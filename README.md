# Genetic (Evolutional) algorithm for process scheduling
This repository is an implementation of modified genetic algorithm, which we call Evolutional Algorithm. It is adapted to solve P||C<sub>max</sub> problem. Besides the implementation of the algorithm, this repo contains utlilities that help test it, such as benchmark generator or simple greedy algorithm

### How it works
The algorithm stores line-ups as dynamic arrays of vectors. Each vector in an array represents one processor which contains a total execution time on the processor (first element of every vector) and duration of each process within that processor. The statring line-up is random. The algorithm starts from that data and creates *n* generations, each consisting of a population of *m* line-ups (*n* and *m* are parameters, which can be adjusted to optimize time or quality of the solution). 

New line-ups in a generation are built in a following way based on the best line-up found in the process so far:

1. Processors with the longest and the shortest execution times are searched within the array
2. A random process from the longer processor is put into the shorter processor
3. This process is repeated *x* times (*x* is a parameter, which can be adjusted)

While creating the population, algorithm only memorizes the current line-up and the best line-up so far (which is determined by the P||C<sub>max</sub>). Once the population is done building, we have te best line-up from that population and if it is better than the base line-up, the new line-up is a base for the next generation.

## Pseudocode
1. For size of population:

    1.1. For number of processes:

        1.1.1 Assign process to random processor
    
        1.1.2 Add to execution time of this processor duration of current process

2. For number of generations:

    2.1. For size of population:

        2.1.1. Best new line up is base line-up

        2.1.2. For *x* times (*x* is a parameter, which can be adjusted):
    
            2.1.1.1. Find max and min execution time for every processor

            2.1.1.2. From processor with max execution time and transfer random process to min processor

        2.1.3. If new line-up is better than best new line-up:

            2.1.2.1. Best new line-up is now new line-up

    2.2. If best line-up from new population is better than base line-up:
        
        2.2.1. Base line-up is best new line-up from new population

## Authors
- Grzegorz Płaczek (148071)
- Kamil Kałużny (148121)
- Olga Gerlich (148088)
