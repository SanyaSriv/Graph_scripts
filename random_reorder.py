#
# random_reorder.py
#
# Author:   Sanya Srivastava
#
# This script is used for getting a random arrangement of the graph. 
#

# for using this file: random_reorder.py [name_of_file] [no. nodes] [no. edges] [lines_to_strip] [debug]


import random
import struct
import numpy as np
import sys

#inp = sys.argv[-1]
inp = sys.argv[1]
random.seed()
#ignore the first line
f = open(inp, "r")
# f.readline()
# param = f.readline().split()
number_of_nodes = int(sys.argv[2])
number_of_edges = int(sys.argv[3])

number_of_lines_to_strip = int(sys.argv[4])
for i in range(0, number_of_lines_to_strip):
    f.readline()

debug = int(sys.argv[5])

if (debug == 1):
    print("Name of file: ", inp)
    print("Number of nodes: ", number_of_nodes)
    print("Number of edges", number_of_edges)
    print("Number of lines stripped:", number_of_lines_to_strip)

index = 0
insert = 0
end = 0
insert_flag = False

line = f.readline().split()

# encryption_array = np.zeros(shape = (number_of_nodes, 2),dtype=np.int32)
dictionary_degree = {} # key: node_id, value: list of neighbours
prev_node = 0
on_node = 0
dictionary_for_sorting = {} # key: node_id, value: in_degree_count

while True:
    if line == []:
        break
    node_id = int(line[1]) - 1
    neighbour_id = int(line[0]) - 1

    # if prev_node != neighbour_id:
    #     while neighbour_id > on_node:
    #         if on_node not in dictionary_degree:
    #             dictionary_degree[on_node] = []
    #         on_node += 1
    #         if on_node == neighbour_id:
    #             break

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

if (debug == 1):
    print("Reading the graph is completed")
    print(dictionary_degree)
    print(dictionary_for_sorting)

for i in range(0, number_of_nodes):
    if i not in dictionary_degree:
        dictionary_degree[i] = []
    if i not in dictionary_for_sorting:
        dictionary_for_sorting[i] = 0

if (debug == 1):
    print("All lonely nodes added")
    print(dictionary_degree)
    print(dictionary_for_sorting)

# getting the random arrangement
random_arrangement = random.sample(range(0, number_of_nodes), number_of_nodes)

if (debug == 1):
    print("Random arrangement obtained")
    print(random_arrangement)

dic_encrypt = {} # random_number -> node_id
dic_encrypt_reverse = {} # node_id -> random_number

for i in range(0, number_of_nodes):
    dic_encrypt[random_arrangement[i]] = i
    dic_encrypt_reverse[i] = random_arrangement[i]

if (debug == 1):
    print("dic_encrypt and dic_encrypt reverse done.")
    print(dic_encrypt)
    print(dic_encrypt_reverse)

new_neighbour_array = np.zeros(shape = (number_of_edges, 2),dtype=np.int32)
new_index_array = np.zeros(shape = (number_of_nodes + 1, 1),dtype=np.int32)

count = 0
neigh_start = 0

for i in range(0, number_of_nodes):
    new_index_array[count] = neigh_start
    count += 1
    for j in dictionary_degree[dic_encrypt[i]]: # whichever node got relabeled as 0
        new_neighbour_array[neigh_start, 0] = dic_encrypt_reverse[j]
        new_neighbour_array[neigh_start, 1] = random.random()
        neigh_start += 1

new_index_array[count] = neigh_start

if (debug == 1):
    print("Index and neighbour array filled up")
    print(new_index_array)
    print(new_neighbour_array)
var = 0

f.close()

fname = inp.split(".")

with open("{}_Random_NP.wsg".format(fname[len(fname)- 1]), "wb") as f:
    f.write((len(new_index_array) - 1).to_bytes(4, byteorder = 'little'))
    f.write((len(new_neighbour_array)).to_bytes(8, byteorder = 'little'))
    for i in new_index_array:
        f.write(int(i[0]).to_bytes(8, byteorder = 'little'))
    for i in new_neighbour_array:
        f.write((int(i[0])).to_bytes(4, byteorder = 'little'))
        weight = random.random()
        # f.write(struct.pack('<f', i[1]))
        f.write(struct.pack('<f', weight))
