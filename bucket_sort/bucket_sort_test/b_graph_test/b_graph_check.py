import subprocess
import sys

cmd = "../../bucket_sort.cpp"
subprocess.call(["g++", "-o", "bucket_sort", cmd])
subprocess.call(["./bucket_sort", "0", "../raw_data/out.petster-friendships-hamster-uniq", "../bucket_reduction_by_name_tests/test_file5.txt" , "0"])
# b_graph file is created. Now going to assert if it is correct
print("*********** Going to assert is b_graph_file.txt is correct. ***********")
file1 = open("../raw_data/out.petster-friendships-hamster-uniq", 'r')
file2 = open("b_graph_file.txt", 'r')

file1.readline()
s = file1.readline()
data = s.split()
number_of_nodes = data[2]

s = file1.readline().split()
s2 = file2.readline().split()

nodes_read = {}

while True:
    if s == []:
        break
    if int(s[1]) - 1 not in nodes_read:
        if int(s[1]) - 1 != int(s2[0]):
            print("TEST FAIL: DIS-SIMILARITY has been found", s[1], int(s2[0]) + 1)
            sys.exit()
        s2 = file2.readline().split()
    nodes_read[int(s[1]) - 1] = True

    s = file1.readline().split()
    

# accounting for the lonely nodes
for i in range(0, int(number_of_nodes)):
    if i not in nodes_read:
        if i != int(s2[0]):
            print("TEST FAIL: missing lonely node", i, s2[0])
            sys.exit()
        s2 = file2.readline().split()
        nodes_read[i] = True

print("TEST SUCCESS")