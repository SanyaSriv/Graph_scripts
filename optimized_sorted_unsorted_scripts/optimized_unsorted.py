#
# fixed_weights_unsorted.py
#
# Author:   Sanya Srivastava
#
# This script does not sort the graph and assigns a weight between 0 - 1
# to every edge before sorting.
#

import random
import struct
import numpy as np
import sys

inp = sys.argv[1]

random.seed(10)
#ignore the first line
f = open(inp, "r")
number_of_nodes = int(sys.argv[2])
number_of_edges = int(sys.argv[3])
number_of_lines_to_remove = int(sys.argv[4])
debug = int(sys.argv[5])

for i in range(0, number_of_lines_to_remove):
    f.readline()

index = 0
insert = 0
end = 0
insert_flag = False

neighbour_dic = {}
order_of_nodes = []
while True:
    line = f.readline().split()
    if not line:
        break
    
    node_id = int(line[1]) - 1
    neighbour_id = int(line[0]) - 1

    if node_id in neighbour_dic:
        neighbour_dic[node_id].append(neighbour_id)
    elif node_id not in neighbour_dic:
        neighbour_dic[node_id] = [neighbour_id]
        order_of_nodes.append(node_id)

for i in range(0, number_of_nodes):
    if i not in neighbour_dic:
        neighbour_dic[i] = []
        order_of_nodes.append(i)

index_start = 0
neigh_start = 0

index_array = np.zeros(shape = (number_of_nodes + 1, 1),dtype=np.int32)
neighbour_array = np.zeros(shape = (number_of_edges, 2),dtype=np.float32)

for i in range(0, number_of_nodes):
    index_array[index_start] = neigh_start
    index_start += 1
    for j in neighbour_dic[order_of_nodes[i]]:
        neighbour_array[neigh_start, 0] = j
        neighbour_array[neigh_start, 1] = random.random()
        neigh_start += 1
index_array[index_start] = neigh_start

f.close()

fname = inp.split(".")
# print("going to write the graph")
with open("{}_UnsortedNP.wsg".format(fname[len(fname)- 1]), "wb") as f:
    f.write((number_of_nodes).to_bytes(4, byteorder = 'little'))
    f.write((len(neighbour_array)).to_bytes(8, byteorder = 'little'))
    for i in index_array:
        f.write(int(i[0]).to_bytes(8, byteorder = 'little'))
    for i in neighbour_array:
        f.write((int(i[0])).to_bytes(4, byteorder = 'little'))
        f.write(struct.pack('<f', i[1]))
