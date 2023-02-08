
# method to use this file: 
# python3 optimized_sorted.py [raw_data_file.txt] [no. nodes] [no. edges] [lines to strip from beginning] [debug]
import random
import struct
import numpy as np
import sys

inp = sys.argv[1]
random.seed()
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

    if node_id in dictionary_degree:
        dictionary_degree[node_id].append(neighbour_id)
    else:
        dictionary_degree[node_id] = [neighbour_id]

    if node_id in dictionary_for_sorting:
        dictionary_for_sorting[node_id] += 1
    else:
        dictionary_for_sorting[node_id] = 1

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

if (debug == 1):
    print("Encryption array before: ")
    print(encryption_array)

encryption_array = encryption_array[encryption_array[:,1].argsort()[::-1]]
# sorted the above by 2nd column

if (debug == 1):
    print("Encryption array after:")
    print(encryption_array)

dic_encrypt = {}
for i in range(0, len(encryption_array)):
    dic_encrypt[encryption_array[i][0]] = i


# optimized version here
f.close()

fname = inp.split(".")
with open("{}_Sorted_NP.wsg".format(fname[len(fname)- 1]), "wb") as f:
    f.write((len(encryption_array)).to_bytes(4, byteorder = 'little'))
    print(len(encryption_array))
    f.write((number_of_edges).to_bytes(8, byteorder = 'little'))
    print(number_of_edges)
    
    neigh_start = 0
    count = 0
    # print("Index array starting now: ")
    for i in range(0, len(encryption_array)):
        f.write((neigh_start).to_bytes(8, byteorder = 'little'))
        # print(neigh_start)
        for j in dictionary_degree[encryption_array[i, 0]]:
            neigh_start += 1
    f.write((neigh_start).to_bytes(8, byteorder = 'little'))
    # print(neigh_start)
    # print("Neighbours array now")
    for i in range(0, len(encryption_array)):
        for j in dictionary_degree[encryption_array[i, 0]]:
            f.write((int(dic_encrypt[j])).to_bytes(4, byteorder = 'little'))
            # print(int(dic_encrypt[j]))
            random_number = random.random()
            f.write(struct.pack('<f', random_number))

            
