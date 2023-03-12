import random
import struct
inp = input("Enter the unweighted graph file: ")

#ignore the first line
f = open(inp, "r")
f.readline()
param = f.readline().split()
number_of_nodes = int(param[2])

index = 0
insert = 0
end = 0
insert_flag = False
line = f.readline().split()

encryption_array = []
dictionary_degree = {}
prev_node = 0
on_node = 0
dictionary_for_sorting = {}

while True:
    # print(line)
    if line == []:
        break
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

    #sorting by in degree
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

for i in dictionary_for_sorting:
    encryption_array.append([i, dictionary_for_sorting[i]])
encryption_array = sorted(encryption_array,key=lambda encryption_array:encryption_array[1], reverse=True)

dic_encrypt = {}
for i in range(0, len(encryption_array)):
    dic_encrypt[encryption_array[i][0]] = i

for i in range(0, number_of_nodes):
    if i not in dic_encrypt:
        dic_encrypt[i] = len(dic_encrypt)

new_neighbour_array = []
new_index_array = []

for i in range(0, len(encryption_array)):
    new_index_array.append(len(new_neighbour_array))
    for j in dictionary_degree[encryption_array[i][0]]:
        new_neighbour_array.append([dic_encrypt[j], random.random()])
        new_neighbour_array.append([dic_encrypt[j], 0.0])
new_index_array.append(len(new_neighbour_array))

var = 0

f.close()

fname = inp.split(".")
hu = open("fg", "w")
with open("{}.wsg".format(fname[len(fname)- 1]), "wb") as f:
    f.write((len(new_index_array) - 1).to_bytes(4, byteorder = 'little'))
    hu.write(str(len(new_index_array) - 1))
    hu.write("\n")
    f.write((len(new_neighbour_array)).to_bytes(8, byteorder = 'little'))
    hu.write(str(len(new_neighbour_array)))
    hu.write("\n")
    for i in new_index_array:
        f.write((i).to_bytes(8, byteorder = 'little'))
        hu.write(str(i))
        hu.write("\n")
    for i in new_neighbour_array:
        f.write((i[0]).to_bytes(4, byteorder = 'little'))
        hu.write(str(i[0]))
        hu.write("\n")
        hu.write("0.0")
        hu.write("\n")
        # f.write(struct.pack('<f', i[1]))
