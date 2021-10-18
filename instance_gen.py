import os
import random
import subprocess

LO = 0.2
HI = 0.5
MIN_TASK = 50
MAX_TASK = 10000
MIN_TIME = 20
MAX_TIME = 500
N_INSTANCES = 10
INST_DIR = 'instances'


def mkdir(dir):
    try:
        os.mkdir(dir)
    except:
        pass

mkdir(INST_DIR)

for i in range(1, N_INSTANCES+1):
    fract = random.uniform(LO, HI)
    task_n = random.randint(MIN_TASK, MAX_TASK)
    proc_n = int(fract * task_n)

    f = open('{}/instance_{}'.format(INST_DIR, i), 'w')
    f.write('{}\n{}\n'.format(proc_n, task_n))

    for i in range(task_n):
        proc_n = random.randint(MIN_TASK, MAX_TASK)
        f.write('{}\n'.format(proc_n))
f.close()
