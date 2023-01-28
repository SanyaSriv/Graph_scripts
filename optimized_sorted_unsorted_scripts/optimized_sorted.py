
# method to use this file: 
# python3 optimized_sorted.py [raw_data_file.txt] [no. nodes] [no. edges] [lines to strip from beginning]
import random
import struct
import numpy as np
import sys

inp = sys.argv[1]
random.seed()
#ignore the first line
f = open(inp, "r")
number_of_nodes = sys.argv[2]
number_of_edges = sys.argv[3]
number_of_lines_to_remove = sys.argv[4]

for i in range(0, number_of_lines_to_remove):
    f.readline()

index = 0
insert = 0
end = 0
insert_flag = False

encryption_array = np.zeros(shape = (number_of_nodes, 2),dtype=np.int32)
dictionary_degree = {}
prev_node = 0
on_node = 0
dictionary_for_sorting = {}

line = f.readline().split()

while True:
    if line == []:
        break
    
    node_id = int(line[1]) - 1
    neighbour_id = int(line[0]) - 1

    if prev_node != neighbour_id:
        while neighbour_id > on_node:
            if on_node not in dictionary_degree:
                dictionary_degree[on_node] = []
            on_node += 1
            if on_node == neighbour_id:
                break

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

encryption_array = encryption_array[encryption_array[:,1].argsort()[::-1]]
# sorted the above by 2nd column

dic_encrypt = {}
for i in range(0, len(encryption_array)):
    dic_encrypt[encryption_array[i][0]] = i

# instead of the code below, we will have to optimize it
# new_neighbour_array = np.zeros(shape = (number_of_edges, 2),dtype=np.int32)
# new_index_array = np.zeros(shape = (number_of_nodes + 1, 1),dtype=np.int32)

# count = 0
# neigh_start = 0
# for i in range(0, len(encryption_array)):
#     # new_index_array.append(len(new_neighbour_array))
#     new_index_array[count] = neigh_start
#     count += 1
#     for j in dictionary_degree[encryption_array[i, 0]]:
#         new_neighbour_array[neigh_start, 0] = dic_encrypt[j]
#         new_neighbour_array[neigh_start, 0] = random.random()
#         neigh_start += 1

# new_index_array[count] = neigh_start

# var = 0

# f.close()

# fname = inp.split(".")

# with open("{}NP.wsg".format(fname[len(fname)- 1]), "wb") as f:
#     f.write((len(new_index_array) - 1).to_bytes(4, byteorder = 'little'))
#     f.write((len(new_neighbour_array)).to_bytes(8, byteorder = 'little'))
#     for i in new_index_array:
#         f.write(int(i[0]).to_bytes(8, byteorder = 'little'))
#     for i in new_neighbour_array:
#         f.write((int(i[0])).to_bytes(4, byteorder = 'little'))
#         f.write(struct.pack('<f', i[1]))

# optimized version here
f.close()

fname = inp.split(".")

with open("{}NP.wsg".format(fname[len(fname)- 1]), "wb") as f:

    f.write((len(encryption_array)).to_bytes(4, byteorder = 'little'))
    f.write((len(number_of_edges)).to_bytes(8, byteorder = 'little'))

    neigh_start = 0
    count = 0

    for i in range(0, len(encryption_array)):
        f.write((neigh_start).to_bytes(8, byteorder = 'little'))
        for j in dictionary_degree[encryption_array[i, 0]]:
            neigh_start += 1
    f.write((neigh_start).to_bytes(8, byteorder = 'little'))

    for i in range(0, len(encryption_array)):
        for j in dictionary_degree[encryption_array[i, 0]]:
            f.write((dic_encrypt[j]).to_bytes(4, byteorder = 'little'))
            random_number = random.random()
            f.write(struct.pack('<f', random_number))

            
