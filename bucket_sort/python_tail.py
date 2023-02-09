import pdb
import random
import struct
import sys

header_file = sys.argv[2]
index_file = sys.argv[3]
neighbour_file = sys.argv[4]
output_file_name = sys.argv[5]

f = open(output_file_name, "wb")
f_header = open(header_file, "r")
f_index = open(index_file, "r")
f_neighbour = open(neighbour_file, "r")

number_of_nodes = int(f_header.readline().split()[0])
number_of_edges = int(f_header.readline().split()[0])

f.write((number_of_nodes).to_bytes(4, byteorder='little'))
f.write((number_of_edges).to_bytes(8, byteorder = 'little'))

while True:
    line = f_index.readline().split()
    if line == []:
        break
    to_write = int(line[0])
    f.write((to_write).to_bytes(8, byteorder = 'little'))

while True:
    line = f_neighbour.readline().split()
    if line == []:
        break
    to_write = int(line[0])
    f.write((to_write).to_bytes(4, byteorder = 'little'))
    random_number = random.random()
    f.write(struct.pack('<f', random_number))

f.close()
f_header.close()
f_index.close()
f_neighbour.close()