import re
import sys

meta_data = {}

NUMBER_OF_SEGMENTS = 24
MATCH_KERNEL = "  kernel:"
MATCH_MILLIS = "        millis:"

benchmark_file = open(sys.argv[-1], 'r');

output_file_name = "benchmark_data.txt"

output_file = open(output_file_name, "w")

while True:
    line = benchmark_file.readline()
    # reached the end of file
    if len(line) == 0:
        break
    if re.match(MATCH_KERNEL, line) != None:
        # we matched with a kernel name
        name_of_kernel = " ".join(line.split()[1::])
        meta_data[name_of_kernel] = []
        # print(name_of_kernel)
        number_of_millis = 0
        while number_of_millis < NUMBER_OF_SEGMENTS:
            line = benchmark_file.readline()
            if re.match(MATCH_MILLIS, line) != None:
                number_of_millis += 1
                millis = line.split()[-1]
                meta_data[name_of_kernel].append(millis)
                # print(millis)
print(meta_data)
output_file.write(str(len(meta_data)) + "\n")
output_file.write(str(NUMBER_OF_SEGMENTS) + "\n")

for i in meta_data:
    output_file.write(i + "\n")
    for j in meta_data[i]:
        output_file.write(str(j) + "\n")

output_file.close()
benchmark_file.close()


        



