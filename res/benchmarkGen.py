import sys
import random

file = str(sys.argv[1])

# Cmax > nTasks
# nTask % nProc = 0

with open(file) as f:
    inst = [[int(el) for el in line[:-1].split()] for line in f.readlines()]
    
# odczyt z pliku kolejno po spacji liczba procesorow, liczba zadan, Cmax
# w kazdej linii dane dla kolejnej instancji

INSTANCES = len(inst)
for i in range(INSTANCES):

    nProc = inst[i][0]
    nTasks = inst[i][1]
    Cmax = inst[i][2]

    # pierwsza linijka w pliku to Cmax, druga - nProc, trzecia - nTasks
    f = open("instances/benchmark_{}".format(i+1),"w")
    f.write(str(Cmax)+'\n'); f.write(str(nProc)+'\n'); f.write(str(nTasks)+'\n')

    data = []
    for _ in range(nProc):
        space = Cmax
        segments = int(nTasks/nProc)-1
        for i in range(segments):
            cut = random.randint(1,space//5)
            data.append(cut)
            space -= cut
            if i == segments-1: data.append(space)

    for task in data:
        f.write("{}\n".format(str(task)))
    f.close()
