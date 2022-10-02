# importing networkx
import networkx as nx
# importing matplotlib.pyplot
import matplotlib.pyplot as plt
 
g = nx.Graph()

f = open("out.china_users", "r")
f.readline()
f.readline()
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
    g.add_edge(line[0], line[1])
nx.draw(g)
plt.savefig("filename.png")

