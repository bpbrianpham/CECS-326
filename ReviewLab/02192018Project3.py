import random

n = 5
p = 0.7
x = 3

N = 1000

trial = [0]
trial = trial*n

j = 0

for k in range (N):
    for i in range(n):
        r = random.uniform(0,1)
        if r < p:
            trial[i] = 1
        else:
            trial[i] = 0

    print(trial)    
    s = sum(trial)

    if s == x:
        