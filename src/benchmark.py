import random

# umieszczenie przeciec symbolizujacych koniec okreslonego zadania w losowo wybranych availableCuts miejscach
# dla jednego procesora
def partition(availableCuts, spaceLeft):
    res = []
    while(availableCuts > 0):
        n = random.randint(1,spaceLeft-availableCuts)
        res.append(n)
        spaceLeft-=n
        availableCuts-=1
    res.append(spaceLeft)
    return res

# partition dla wszystkich procesorów
def partitionAll(nProc, nTasks, Cmax):
    data = []
    for i in range(nProc):
        if i == nProc-1: cut = nTasks-1
        else:
            if nTasks-1-(nProc-i-1) <= 0 : cut = 0
            else: 
                cut = random.randint(0,(nTasks-1-(nProc-i-1))//nProc)
        data.append(partition(cut, Cmax))
        nTasks-=(cut+1)
    return data

# Cmax > nTasks
nProc, nTasks, Cmax = map(int, input().split())

# pierwsza linijka w pliku to Cmax, druga - nProc, trzecia - nTasks
f = open("benchmark.txt","w")
f.write(str(Cmax)+"\n"); f.write(str(nProc)+"\n"); f.write(str(nTasks)+"\n")
for proc in partitionAll(nProc, nTasks, Cmax):
    for el in proc:
        f.write(str(el)+"\n")
f.close()