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
inp = input("Enter the unweighted graph file: ")

random.seed(10)
#ignore the first line
f = open(inp, "r")
f.readline()
param = f.readline().split()
number_of_edges = int(param[2])
number_of_nodes = int(param[1])
index_array = np.zeros(shape = (number_of_nodes + 1, 1),dtype=np.int32)
neighbour_array = np.zeros(shape = (number_of_edges, 2),dtype=np.float32)

index = 0
insert = 0
end = 0
insert_flag = False

neighbour_dic = {}

weight_dic = {}
# print("initialized")
while True:
    line = f.readline().split()
    if not line:
        break

    s = str(int(line[1]) - 1) + "_" + str(int(line[0]) - 1)
    weight_dic[s] = random.random()

    if int(line[1]) - 1 in neighbour_dic:
        neighbour_dic[int(line[1]) - 1].append(int(line[0]) - 1)
    elif int(line[1]) - 1 not in neighbour_dic:
        neighbour_dic[int(line[1]) - 1] = [int(line[0]) - 1]

for i in range(0, number_of_nodes):
    if i not in neighbour_dic:
        neighbour_dic[i] = []
# print("read the graph")
index_start = 0
neigh_start = 0

for i in range(0, number_of_nodes):
    index_array[index_start] = neigh_start
    index_start += 1
    for j in neighbour_dic[i]:
        neighbour_array[neigh_start, 0] = j
        s = str(i) + "_" + str(j)
        neighbour_array[neigh_start, 1] = weight_dic[s]
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
