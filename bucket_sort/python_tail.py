import pdb
import random
import struct

inp = "out.orkut"
fname = inp.split(".")
weights = open("weights_array.txt", "r")
index   = open("index_array.txt", "r")
neighbours = open("neighbour_array.txt", "r")
param0 = index.readline().split()
param1 = neighbours.readline().split()
param2 = weights.readline().split()
index_array = []
neighbour_array = []
y = 0
p = 0
while True:
    if param0 == []: # we ahve reached at the end of the file
        break
    index_array.append(int(param0[0]))
    param0 = index.readline().split()
    p += 1

while True:
    if param1 == []:
        break
    neighbour_array.append([int(param1[0]), float(param2[0])])
    param1 = neighbours.readline().split()
    param2 = weights.readline().split()
    y += 1
print("these maney lines read = ", y, p)

with open("{}_Bucket_1b.wsg".format(fname[len(fname)- 1]), "wb") as f:
    f.write((len(index_array) - 1).to_bytes(4, byteorder = 'little'))
    f.write((len(neighbour_array)).to_bytes(8, byteorder = 'little'))
    for i in index_array:
        f.write((i).to_bytes(8, byteorder = 'little'))
    for i in neighbour_array:
        f.write((i[0]).to_bytes(4, byteorder = 'little'))
        f.write(struct.pack('<f', i[1]))
weights.close()
index.close()
neighbours.close()
