import os
import sys

filename = sys.argv[1]

text = open(filename).readlines()

state = []
is_init = []
is_final = []
max_id = 0

for i in range(len(text)):
    line = text[i][:-1].split()
    if text[i].find("initial")>=0 or text[i].find("accepting")>=0:
        max_id = max(max_id, int(line[0]))
    else:
        max_id = max(max_id, max(int(line[0]), int(line[2])))

state = [{} for i in range(max_id+1)]
is_init = [0]*(max_id+1)
is_final = [0]*(max_id+1)

for i in range(len(text)):
    line = text[i][:-1].split()
    if text[i].find("initial")>=0:
        is_init[int(line[0])] = 1
    elif text[i].find("accepting")>=0:
        is_final[int(line[0])] = 1
    else:
        _from_ = int(line[0])
        _to_ = int(line[2])
        lower = 0
        higher = -1
        if line[4].find("|")>=0:
            lower = int(line[4].split("|")[0])
            higher = int(line[4].split("|")[1])
            #print(_from_, _to_, lower, higher)
            for ind in range(lower, higher+1):
                if (ind>255):
                    continue
                if state[_from_].__contains__(ind):
                    state[_from_][ind].add(_to_)
                else:
                    state[_from_][ind] = set([_to_])
        else:
            #print(_from_, _to_, "nop")
            if _from_ == _to_:
                continue
            if state[_from_].__contains__(-1):
                state[_from_][-1].add(_to_)
            else:
                state[_from_][-1] = set([_to_])


for i in range(len(state)):
    if state[i].__contains__(-1):
        while len(state[i][-1]):
            nop_to = state[i][-1].pop()
            if nop_to != i:
                if is_init[nop_to]:
                    is_init[i] = 1
                if is_final[nop_to]:
                    is_final[i] = 1
                for k in state[nop_to].keys():
                    if state[i].__contains__(k):
                        state[i][k] = state[i][k]|state[nop_to][k]
                    else:
                        state[i][k] = state[nop_to][k]

output_transitions = [{} for i in range(max_id+1)]


for i in range(len(state)):
    for k in state[i].keys():
        for j in state[i][k]:
            if output_transitions[i].__contains__(j):
                output_transitions[i][j].add(k)
            else:
                output_transitions[i][j]=set([k])

in_deg = [0]*(max_id+1)
new_id = [0]*(max_id+1)

for i in range(len(output_transitions)):
    for k in sorted(output_transitions[i].keys()):
        in_deg[k]+=1

totoal_id = 0
for i in range(len(output_transitions)):
    if in_deg[i]==0 and is_init[i]==0:
        continue
    new_id[i]=totoal_id
    totoal_id+=1


print ("# NFA")
print (totoal_id)

for i in range(len(output_transitions)):
    if in_deg[i]==0 and is_init[i]==0:
        continue
    if is_init[i]:
        print(str(new_id[i])+" : initial")
    if is_final[i]:
        print(str(new_id[i])+" : accepting 1")
    for k in sorted(output_transitions[i].keys()):
        last = -1
        latest = -2
        for j in sorted(output_transitions[i][k]):
            if j > 255:
                break
            if latest == j-1:
                latest = j
            else:
                if latest == last:
                    print("%d -> %d : %d"%(new_id[i],new_id[k],last))
                elif latest >= last:
                    print("%d -> %d : %d|%d"%(new_id[i],new_id[k],last,latest))
                last = j
                latest = j
        if latest == last:
            print("%d -> %d : %d"%(new_id[i],new_id[k],last))
        elif latest >= last:
            print("%d -> %d : %d|%d"%(new_id[i],new_id[k],last,latest))
