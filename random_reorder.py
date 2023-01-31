#
# random_reorder.py
#
# Author:   Sanya Srivastava
#
# This script is used for getting a random arrangement of the graph. 
#

import random
import struct
import numpy as np
import sys

#inp = sys.argv[-1]
inp = "out.petster-friendships-hamster-uniq"
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
dictionary_degree = {} # key: node_id, value: list of neighbours
prev_node = 0
on_node = 0
dictionary_for_sorting = {} # key: node_id, value: in_degree_count
dic_weights = {} # for assigning a weight to every edge

while True:
    if line == []:
        break
    # generating a weight for the edge 
    node_id = int(line[1]) - 1
    neighbour_id = int(line[0]) - 1

    s = str(neighbour_id) + "_" + str(node_id)
    dic_weights[s] = random.random()

    if prev_node != neighbour_id:
        while neighbour_id > on_node:
            if on_node not in dictionary_degree:
                dictionary_degree[on_node] = []
            on_node += 1
            if on_node == neighbour_id:
                break

    # adding the neighbour for the node
    if node_id in dictionary_degree:
        dictionary_degree[node_id].append(neighbour_id)
    else:
        dictionary_degree[node_id] = [neighbour_id]

    if node_id in dictionary_for_sorting:
        dictionary_for_sorting[node_id] += 1
    else:
        dictionary_for_sorting[node_id] = 1

    prev_node = neighbour_id
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

# getting the random arrangement
random_arrangement = random.sample(range(0, number_of_nodes), number_of_nodes)

encryption_array = encryption_array[encryption_array[:,1].argsort()[::-1]]
# sorted the above by 2nd column

dic_encrypt = {}
for i in range(0, len(encryption_array)):
    dic_encrypt[encryption_array[i][0]] = random_arrangement[i]

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
        new_neighbour_array[neigh_start, 1] = dic_weights[s]
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
