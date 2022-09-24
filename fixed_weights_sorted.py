#
# fixed_weights_sorted.py
#
# Author:   Sanya Srivastava
#
# This script completely sorts the graph and assigns a weight between 0 - 1
# to every edge before sorting.
#

import random
import struct
import numpy as np
inp = input("Enter the unweighted graph file: ")
random.seed()
#ignore the first line
f = open(inp, "r")
f.readline()
param = f.readline().split()
number_of_nodes = int(param[2])
number_of_edges = int(param[1])

index = 0
insert = 0
end = 0
insert_flag = False
line = f.readline().split()

encryption_array = np.zeros(shape = (number_of_nodes, 2),dtype=np.int32)
dictionary_degree = {}
prev_node = 0
on_node = 0
dictionary_for_sorting = {}
dic_weights = {} # for assigning a weight to every edge

while True:
    if line == []:
        break
    s = str(int(line[0]) - 1) + "_" + str(int(line[1]) - 1)
    dic_weights[s] = random.random()

    if prev_node != int(line[0]) - 1:
        while int(line[0]) - 1 > on_node:
            if on_node not in dictionary_degree:
                dictionary_degree[on_node] = []
            on_node += 1
            if on_node == int(line[0]) - 1:
                break

    if int(line[1]) - 1 in dictionary_degree:
        dictionary_degree[int(line[1]) - 1].append(int(line[0]) - 1)
    else:
        dictionary_degree[int(line[1]) - 1] = [int(line[0]) - 1]

    if int(line[1]) -1 in dictionary_for_sorting:
        dictionary_for_sorting[int(line[1]) - 1] += 1
    else:
        dictionary_for_sorting[int(line[1]) - 1] = 1

    prev_node = int(line[0]) - 1
    line = f.readline().split()

for i in range(0, number_of_nodes):
    if i not in dictionary_degree:
        dictionary_degree[i] = []
    if i not in dictionary_for_sorting:
        dictionary_for_sorting[i] = 0

count = 0
for i in dictionary_for_sorting:
    encryption_array[count, 0] = i
    encryption_array[count, 1] = dictionary_for_sorting[i]
    count += 1

# encryption_array = sorted(encryption_array,key=lambda encryption_array:encryption_array[1], reverse=True)

encryption_array = encryption_array[encryption_array[:,1].argsort()[::-1]]
# sorted the above by 2nd column

dic_encrypt = {}
for i in range(0, len(encryption_array)):
    dic_encrypt[encryption_array[i][0]] = i

new_neighbour_array = np.zeros(shape = (number_of_edges, 2),dtype=np.int32)
new_index_array = np.zeros(shape = (number_of_nodes + 1, 1),dtype=np.int32)

count = 0
neigh_start = 0
for i in range(0, len(encryption_array)):
    # new_index_array.append(len(new_neighbour_array))
    new_index_array[count] = neigh_start
    count += 1
    for j in dictionary_degree[encryption_array[i, 0]]:
        new_neighbour_array[neigh_start, 0] = dic_encrypt[j]
        s = str(j) + "_" + str(encryption_array[i][0])
        new_neighbour_array[neigh_start, 0] = dic_weights[s]
        neigh_start += 1

new_index_array[count] = neigh_start

var = 0

f.close()

fname = inp.split(".")

with open("{}NP.wsg".format(fname[len(fname)- 1]), "wb") as f:
    f.write((len(new_index_array) - 1).to_bytes(4, byteorder = 'little'))
    f.write((len(new_neighbour_array)).to_bytes(8, byteorder = 'little'))
    for i in new_index_array:
        f.write(int(i[0]).to_bytes(8, byteorder = 'little'))
    for i in new_neighbour_array:
        f.write((int(i[0])).to_bytes(4, byteorder = 'little'))
        f.write(struct.pack('<f', i[1]))
