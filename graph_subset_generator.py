import sys

def main(argv):
    input_graph = argv[1]
    size_of_graph = argv[2]
    size_of_subset = argv[4]

    print("Input graph is: ", input_graph)
    print("Size of input graph is: ", size_of_graph)
    print("size of subset: ", size_of_each_subset)

    f = open(input_graph, "r")
    f.readline()
    line = f.readline()

    # not sure, we might have to change the order
    number_of_edges = line[2]
    number_of_nodes = line[1]
    list_of_edges = [i for i in range(0, number_of_edges)]
    number_of_edges_for_size = (number_of_edges / size_of_graph) * size_of_subset
    final_edge_list = random.sample(list_of_edges, int(number_of_edges_for_size))

    counter = 0
    f2 = open("graph_subset_{}_{}" % (input_graph, size_of_subset), "w")
    line = f.readline.split()
    while True:
        if line == []:
            break
        if counter in list_of_edges:
            # add it to the output graph
            f2.write("%s %s", line[0], line[1])
        line = f.readline.split()
        counter += 1

f.close()
f2.close()
if __name__ == "__main__":
    main()
