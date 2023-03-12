#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <iterator>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>
#include <string>
#include <string_view>
#include <map>
#include "bucket_sort_functions.h"

using namespace std;

// we can assume that it will use the Gorder file only 
// so the minimum node = 0 and not 1

int FLOAT_MIN = 0;
int FLOAT_MAX = 1;
// I think we can make the buckets global

// number_of_buckets should be the length of lis_range
// 256 34 20 1 0 - 4, 5
// number of buckets = 4
// [256, 34], [34, 20], [20, 1], [1, 0]
//  0           1        2         3

void make_graph(int bucket_number, int number_of_nodes, int number_of_edges, 
                int *dictionary_for_sorting, int bucket_range[], int dynamic_bucket_size, 
                vector<int> *dictionary_degree) {
//   fstream my_file;
//   string to_read;
//   int num;
//   std::cout << "skghdkg: " << dynamic_bucket_size << endl;
//   std::cout << "opening the b graph file" << endl;
//   my_file.open("b_graph_file.txt");
//   vector<int> *graph_bucket_list_nodes = new vector<int>[dynamic_bucket_size];
//   while(getline(my_file, to_read)) {
//     num = stoi(to_read);
//     int u = bucket_decider(dictionary_for_sorting[num], bucket_range, dynamic_bucket_size);
//     // std::cout << u << endl;
//     graph_bucket_list_nodes[u].push_back(num);
//   }
//   my_file.close();
//   std::cout << "Reached in 158" << endl;
//   string header_file = "header_" + to_string(bucket_number) + ".txt";
//   string index_file = "index_" + to_string(bucket_number) + ".txt";
//   string neighbour_file = "neighbour_" + to_string(bucket_number) + ".txt";
//   string sssp_file = "sssp_" + to_string(bucket_number) + ".txt";

//   ofstream outfile0 (header_file); // will contain number_of_nodes, and number_of_edges
//   ofstream outfile1 (index_file);
//   ofstream outfile2 (neighbour_file);
//   ofstream outfile3 (sssp_file);

//   unordered_map <int, int> dic_translate;
//   unordered_map <int, int> dic_translate_reverse;
//   // we are renumbering the nodes so node 0 is at the beginning
//   int k = 0;
//   for(int x = 0; x < dynamic_bucket_size; x++) {
//     outfile3 << k << endl; // start node - this will be the reordered value 
//     for (int j = 0; j < graph_bucket_list_nodes[x].size(); j++) {
//       // we need te first and alst node for the sssp cuh file here
//       dic_translate[graph_bucket_list_nodes[x][j]] = k;
//       dic_translate_reverse[k] = graph_bucket_list_nodes[x][j];
//       k += 1;
//     }
//     outfile3 << k << endl; //  end node - this will be the reordered value 
//     outfile3 << endl;
//   }
// // ending node id is exclusive
// // filling in the header.txt file
// outfile0 << number_of_nodes << endl;
// outfile0 << number_of_edges << endl;

// int neigh_start = 0;
// int count = 0;

// for (int i = 0; i < number_of_nodes; i++) {
//   outfile1 << neigh_start << endl;
//   for (int j = 0; j < dictionary_degree[dic_translate_reverse[i]].size(); j ++) {
//     neigh_start += 1;
//   }
// }
// outfile1 << neigh_start << endl;

// for (int i = 0; i < number_of_nodes; i++) {
//   for (int j = 0; j < dictionary_degree[dic_translate_reverse[i]].size(); j ++) {
//     outfile2 << dic_translate[dictionary_degree[dic_translate_reverse[i]][j]] << endl;
//   }
// }
//   outfile0.close();
//   outfile1.close();
//   outfile2.close();
//   outfile3.close();
}


map <string, vector <float> > benchmark_data_map;

int main(int argc, char** argv) {
  srand(time(nullptr));
  int number_of_edges, number_of_nodes;
  unordered_map <int, int> bucket_sizes_requested;

  std::cout << "The flag given was:" << argv[1] << endl;
  std::cout << "The unweighted graph entered is: " << argv[2] << endl;
  std::cout << "File to extract bucket data is: " << argv[3] << endl;
  std::cout << "Intermediate_representation: " << argv[4] << endl;
  std::cout << "Benchmark_data_file: " << argv[5] << endl;
  std::cout << "Number of nodes are: " << argv[6] << endl;
  std::cout << "Number of edges are: " << argv[7] << endl;

  // buckets we want should be from argv[8] to the rest of the number
  int number_of_bucket_sizes = 0;
  for (int i = 8; i < argc; i++) {
    bucket_sizes_requested[stoi(argv[i])] = 1;
    std::cout << "Bucket size needed: " << argv[i] << endl;
    number_of_bucket_sizes += 1;
  }

  // filling in number of nodes and edges
  number_of_nodes = stoi(argv[6]);
  number_of_edges = stoi(argv[7]);

  // doing the benchmark data filling
  fstream benchmark_file;
  benchmark_file.open(argv[5], ios::in);
  string line_read;
  getline(benchmark_file, line_read);
  int number_of_kernels;
  int number_of_segments;
  cout << "line read is: " << line_read <<  endl;
  number_of_kernels = stoi(line_read);
  getline(benchmark_file, line_read);
  number_of_segments = stoi(line_read);
  for(int i = 0; i < number_of_kernels; i++) {
    getline(benchmark_file, line_read);
    string kernel = line_read;
    vector<float> empty_vector;
    benchmark_data_map[line_read] = empty_vector;
    for(int j = 0; j < number_of_segments; j++) {
      getline(benchmark_file, line_read);
      benchmark_data_map[kernel].push_back(stof(line_read));
    }
  }

  // testing if we are printing out the map correctly: 
  for(auto it = benchmark_data_map.begin(); it != benchmark_data_map.end(); ++it) {
    cout << it->first << " : ";
    for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
      cout << *it2 << " ";
    }
    cout << endl << endl;
  }
  // benchmark data filled

  // Everything is getting stored correctly
  
  // what we could do is: from argv[8] and onwrds, consider everthing as the number of buckets we need.
  // as sson as we reach one of these values -> it should trigger bucket creation. 
  // so we might need to make a bucket creation function. It should  not be a part of main? 
  // when it does so, it should also create something for the sssp.cuh generator. 

  int to_do_flag = stoi(argv[1]);
  fstream my_file;
  my_file.open(argv[3], ios::in); // opening the bucket data file
  std::cout << "File opened: Success: " << argv[3] << endl;
  string to_read;
  getline(my_file, to_read); // read the number of buckets
  int number_of_buckets;
  std::cout << "number of buckets are: " << to_read << endl;
  number_of_buckets = stoi(to_read);

  // defining bucket arrays
  int bucket_range[number_of_buckets + 1];
  int bucket_range_copy[number_of_buckets + 1];
  float bucket_cost[number_of_buckets];
  string kernel_name[number_of_buckets];

  getline(my_file, to_read); // reading the empty line

  //storing the bucket ranges
  for(int i = 0; i < number_of_buckets + 1; i++) {
    getline(my_file, to_read);
    cout << "to_read is: " << to_read << endl;
    bucket_range[i] = stoi(to_read);
    bucket_range_copy[i] = stoi(to_read);
  }

  getline(my_file, to_read); // reading the empty line

  // now would be reading the cost of each bucket
  for(int i = 0; i < number_of_buckets; i++) {
    getline(my_file, to_read);
    bucket_cost[i] = stof(to_read); // refers to cost of bucket i to i + 1
  }

  getline(my_file, to_read); // reading the empty line

  // now would be reading the kernel of each bucket
  for(int i = 0; i < number_of_buckets; i++) {
    getline(my_file, to_read);
    kernel_name[i] = to_read; // refers to cost of bucket i to i + 1
    // cout << "kernel_name = " << kernel_name[i] << endl; // commenting out the debugging statement
  }

  my_file.close();
  // bucket data read and bucket data file closed
  std::cout << "Bucket variables initialised: Success" << endl;

  // reading the main graph file
  my_file.open(argv[2]);
  char *token;
  char *dup;

  std::cout << "Number of nodes = " << number_of_nodes << endl;
  std::cout << "Number of edges = " << number_of_edges << endl;
  std::cout <<"Number of nodes and edges initialised: Success" << endl;
  int insert = 0;
  int end = 0;
  bool insert_falg = false;

  int *encrpytion_array = new int[number_of_nodes];
  vector<int> *dictionary_degree = new vector<int>[number_of_nodes]; // array of vectors
  int *dictionary_for_sorting = new int[number_of_nodes] (); // initialize to all zeros IF THINGS DO NOT WORK **** -> MAKE THIS A DICTIONARY 
  std::cout << "Array set up done" << endl;

  // to store the order of the graph
  // ofstream outfile ("b_graph_file.txt");
  // unordered_map<int, bool> b_graph_set;
  // std::cout << "Graph variables initialised: Success" << endl;
  // int node_id;
  // int edge_id;
  // char* tok;
  // float u; // temporary variable for stroring the
  // string temp_string;
  // while (getline(my_file, to_read)) {
  //   dup = strdup(to_read.c_str());
  //   tok = strtok(dup, " ");
  //   edge_id = stoi(tok);  //edge_id = int(line[0]) - because Gorder nodes start from 0
  //   tok = strtok(NULL, " ");
  //   node_id = stoi(tok);  // node_id = int(line[1]) - because Gorder nodes start from 0

  //   if (b_graph_set.find(node_id) == b_graph_set.end()) {
  //     b_graph_set[node_id] = true;
  //     outfile << to_string(node_id) << endl; // writing to file of b_graph
  //   }

  //   dictionary_degree[node_id].push_back(edge_id);
  //   dictionary_for_sorting[node_id] += 1;
  // }

  // // accounting for the lonely nodes
  // for(int i = 0; i < number_of_nodes; i++) {
  //   if (b_graph_set.find(i) == b_graph_set.end()) {
  //     b_graph_set[i] = true;
  //     outfile << to_string(i) << endl;
  //   }
  // }
  // // all the nodes have been accounted
  // outfile.close();
  // my_file.close();

  // std::cout << "Graph read and variables populated: Success" << endl; // working till here - checked on Toucan
  // b_graph_set.clear();

  // should print out an initial schedule here before starting
  std::cout << "Printing out the initial schedule here -> " << endl;
  schedule_printer_cost(number_of_buckets, kernel_name, bucket_cost, bucket_range);
 
  vector<int> *graph_bucket_list_nodes = new vector<int>[number_of_buckets];
  int dynamic_bucket_size = number_of_buckets;
  int *bucket_size = new int[number_of_buckets]; // size of each bucket

  // now we need a method to split the graph
  // now we would have to open the b_graph file for reading
  my_file.open("b_graph_file.txt");
  int num;

  my_file.close();
  std::cout << "Reduction Process beginning: Success." << endl;
  std::cout <<"Current bucket size = " << dynamic_bucket_size << endl; // works till here - Success seen on Toucan
  if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
    // we need a graph with this bucket size
    std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
    make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
              dictionary_for_sorting, bucket_range, 
              dynamic_bucket_size, dictionary_degree);
    std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
    bucket_sizes_requested.erase(dynamic_bucket_size);
  }
// 200 180 140 50 70 80 0
  int ideal = 6;
  int ideal_for_name_merge = 1;
  // going to focus on merging by name only
  if (to_do_flag == 0) {
    while (dynamic_bucket_size > ideal_for_name_merge) {
      int change_made = 0;
      for(int i = 0; i < dynamic_bucket_size - 1; i++) {
        // std::cout << kernel_name[i] << " " << kernel_name[i + 1] << endl; -> debugging statement
        if (kernel_name[i] == kernel_name[i + 1]) {
          //merge_bucket(i, i + 1);
          // for now I am writing the algorithm here

          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          bucket_cost[i] = bucket_cost[i] + bucket_cost[i + 1];
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          change_made = 1;
          dynamic_bucket_size -=1;
        }
        if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
        }
      }
      std::cout << "Iteration completed" << endl;
      if (change_made == 0) {
        std::cout << "No change made: Stopping the merge by name process here." << endl;
        break;
      }
     schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
    }
    // merge by just the name
  } else if (to_do_flag == 2) {
    // merging by name first
    while (dynamic_bucket_size > ideal_for_name_merge) {
      int change_made = 0;
      for(int i = 0; i < dynamic_bucket_size - 1; i++) {
        // std::cout << kernel_name[i] << " " << kernel_name[i + 1] << endl; -> debugging statement
        if (kernel_name[i] == kernel_name[i + 1]) {
          //merge_bucket(i, i + 1);
          // for now I am writing the algorithm here
          // merging the name
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = bucket_cost[i] + bucket_cost[i + 1];
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          change_made = 1;
          dynamic_bucket_size -=1;
          schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
        }
        if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
        }
      }

      std::cout << "Iteration completed" << endl;

      if (change_made == 0) {
        break;
      }

      // if a change was made then we will print out the schedule
      std::cout << "Printing out the schedule -> " << endl;
      schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
    }

    // now start merging by the bucket cost and benchmark data
    // idea: cost after merge < cost of bucket 1 + cost of bucket 2 for either kernel1 or kernel2 

    // will be checking every pair
    int cost_merge_iteration_change = 1;
    while (cost_merge_iteration_change == 1) {
      if (dynamic_bucket_size == 1) {
        break;
      }
    for(int i = 0; i < dynamic_bucket_size - 1; i++) {
      cout << "Entering the merging here" << endl;
      // comparing (i) and (i + 1)
      float buck1_cost = bucket_cost[i];
      float buck2_cost = bucket_cost[i + 1];
      float combined_cost = buck1_cost + buck2_cost;
      cout << "The combined cost is: " << combined_cost <<  endl;
      int buck1_high = bucket_range[i];
      int buck1_low = bucket_range[i + 1];

      int buck2_high = bucket_range[i + 1];
      int buck2_low = bucket_range[i + 2];

      // only for debugging
      cout << "buck1_high = " << buck1_high <<  endl;
      cout << "buck1_low = " << buck1_low <<  endl;

      cout << "buck2_high = " << buck2_high << endl;
      cout << "buck2_low = " << buck2_low << endl;

      vector <int> buck1_array;
      vector <int> buck2_array;

      string kernel1 = kernel_name[i];
      string kernel2 = kernel_name[i + 1];

      // not sure about what is happening here

      for(int j = 0; j < number_of_buckets; j++ ) {
        if ((bucket_range_copy[j] <= buck1_high) && (bucket_range_copy[j + 1] >= buck1_low)) {
          buck1_array.push_back(j);
        }
        if ((bucket_range_copy[j] <= buck2_high) && (bucket_range_copy[j + 1] >= buck2_low)) {
          buck2_array.push_back(j);
        }
      }
      float buck1_with_kernel2_cost = 0;
      float buck2_with_kernel1_cost = 0;

      // j is the bucket value
      cout << "Entering the merging here 2" << endl;
      for(int j = 0; j < buck1_array.size(); j++) {
        cout << "value of j for bucket 1 is: " << buck1_array[j] << endl;
        buck1_with_kernel2_cost += benchmark_data_map[kernel2][buck1_array[j]];
      }

      for(int j = 0; j < buck2_array.size(); j++) {
        cout << "value of j for bucket 2 is: " << buck2_array[j] << endl;
        buck2_with_kernel1_cost += benchmark_data_map[kernel1][buck2_array[j]];
      }

      cout << "buck2 = " << buck2_with_kernel1_cost <<  endl;
      cout << "buck1 = " << buck1_with_kernel2_cost <<  endl;

      float kernel1_merge_cost = buck1_cost + buck2_with_kernel1_cost;
      float kernel2_merge_cost = buck2_cost + buck1_with_kernel2_cost;
      cout << "kernel1_merge_cost = " << kernel1_merge_cost <<  endl;
      cout << "kernel2_merge_cost = " << kernel2_merge_cost << endl;
      cout << "***************************************************************************************" << endl;
      cout << "Printing before merge: " << endl;
      schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
      cout << "Printing after merge " << endl;
      if ((kernel1_merge_cost < combined_cost) && (kernel2_merge_cost < combined_cost)) {
        if ((kernel1_merge_cost) <= (kernel2_merge_cost)) {
          // merging by kernel 1
          kernel_name[i] = kernel1;
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = kernel1_merge_cost;
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          dynamic_bucket_size -=1;
          cost_merge_iteration_change = 1;
        } else {
          kernel_name[i] = kernel2;
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = kernel2_merge_cost;
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          dynamic_bucket_size -=1;
          cost_merge_iteration_change = 1;
        }
      } else if (kernel1_merge_cost < combined_cost) {
        kernel_name[i] = kernel1;
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = kernel1_merge_cost;
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          dynamic_bucket_size -=1;
          cost_merge_iteration_change = 1;
      } else if (kernel2_merge_cost < combined_cost) {
        kernel_name[i] = kernel2;
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = kernel2_merge_cost;
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          dynamic_bucket_size -=1;
          cost_merge_iteration_change = 1;
      } else {
        cost_merge_iteration_change = 0;
      }
      std::cout << "Printing out the schedule after merge -> " << endl;
      schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
      cout << "***************************************************************************************" << endl;
      if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
      }

      // doing a name merge again.
      for(int i = 0; i < dynamic_bucket_size - 1; i++) {
        // std::cout << kernel_name[i] << " " << kernel_name[i + 1] << endl; -> debugging statement
        if (kernel_name[i] == kernel_name[i + 1]) {
          //merge_bucket(i, i + 1);
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = bucket_cost[i] + bucket_cost[i + 1];
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          dynamic_bucket_size -=1;
          schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
        }
        if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
        }
      }
    }
    }
    // force merge should begin in here
    // **************************************************************************************************************
    while (number_of_bucket_sizes > 0) {
      cout << "***************************************************************************************" << endl;
      cout << "Printing the schedule before force merge iteration begins: " << endl;
      schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
      if (dynamic_bucket_size == 1) {
        break;
      }
      // see which is the best candidate for merging
      int to_merge_bucket_1;
      int to_merge_bucket_2;
      float merging_cost = -1;
      string kernel_to_merge = "";

      for(int i = 0; i < dynamic_bucket_size - 1; i++) {
        float buck1_cost = bucket_cost[i];
        float buck2_cost = bucket_cost[i + 1];
        float combined_cost = buck1_cost + buck2_cost;

        cout << "combined cost = " << combined_cost << endl;

        int buck1_high = bucket_range[i];
        int buck1_low = bucket_range[i + 1];

        int buck2_high = bucket_range[i + 1];
        int buck2_low = bucket_range[i + 2];

        cout << "Bucket 1 range: " << buck1_high << " - " << buck1_low <<  endl;
        cout << "Bucket 2 range: " << buck2_high << " - " << buck2_low <<  endl;

        vector <int> buck1_array;
        vector <int> buck2_array;

        string kernel1 = kernel_name[i];
        string kernel2 = kernel_name[i + 1];

        // not sure about what is happening here

        for(int j = 0; j < number_of_buckets; j++ ) {
          cout << "Bucket range value: " << bucket_range_copy[j]<< " -> " << bucket_range_copy[j + 1] << endl;
          if ((bucket_range_copy[j] <= buck1_high) && (bucket_range_copy[j + 1] >= buck1_low)) {
            cout << "For buck1: " << j << endl;
            buck1_array.push_back(j);
          }
          if ((bucket_range_copy[j] <= buck2_high) && (bucket_range_copy[j + 1] >= buck2_low)) {
            buck2_array.push_back(j);
            cout << "For buck2 " << j << endl;
          }
        }

        float buck1_with_kernel2_cost = 0;
        float buck2_with_kernel1_cost = 0;


        for(int j = 0; j < buck1_array.size(); j++) {
          buck1_with_kernel2_cost += benchmark_data_map[kernel2][buck1_array[j]];
        }

        for(int j = 0; j < buck2_array.size(); j++) {
          buck2_with_kernel1_cost += benchmark_data_map[kernel1][buck2_array[j]];
        }

        float kernel1_merge_cost = buck1_cost + buck2_with_kernel1_cost;
        float kernel2_merge_cost = buck2_cost + buck1_with_kernel2_cost;

        cout << "Kernel1 merge cost = " << kernel1_merge_cost << endl;
        cout << "Kernel2 merge cost = " << kernel2_merge_cost << endl;
        cout << endl << endl;
        if (merging_cost == -1) {
          if (kernel1_merge_cost <= kernel2_merge_cost) {
            merging_cost = kernel1_merge_cost;
            to_merge_bucket_1 = i;
            to_merge_bucket_2 = i + 1;
            kernel_to_merge = kernel1;
          } else {
            merging_cost = kernel2_merge_cost;
            to_merge_bucket_1 = i;
            to_merge_bucket_2 = i + 1;
            kernel_to_merge = kernel2;
          }
        }
        if (kernel1_merge_cost <= kernel2_merge_cost) {
          if (kernel1_merge_cost < merging_cost) {
            merging_cost = kernel1_merge_cost;
            to_merge_bucket_1 = i;
            to_merge_bucket_2 = i + 1;
            kernel_to_merge = kernel1;
          }
        } else {
          if (kernel2_merge_cost < merging_cost) {
            merging_cost = kernel2_merge_cost;
            to_merge_bucket_1 = i;
            to_merge_bucket_2 = i + 1;
            kernel_to_merge = kernel2;
          }
        }
      }

      // after this we know which buckets to merge
      int i = to_merge_bucket_1;
      cout << "Final buckets chosen to be merged " << to_merge_bucket_1 << " - " << to_merge_bucket_2 <<  endl;
      // mergin down below
      kernel_name[i] = kernel_to_merge;
      for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
        }

      // merging the range
      for(int j = i+1; j < dynamic_bucket_size; j++) {
        bucket_range[j] = bucket_range[j + 1];
      }

      // merging the cost
      bucket_cost[i] = merging_cost;
      for(int j = i + 1; j < dynamic_bucket_size; j++) {
        bucket_cost[j] = bucket_cost[j + 1];
      }

      bucket_range[dynamic_bucket_size] = -1;
      kernel_name[dynamic_bucket_size - 1] = "-1";
      bucket_cost[dynamic_bucket_size - 1] = -1;
      dynamic_bucket_size -= 1;

      // printing the schedule once the force merge algorithm has finished
      cout << "Printing the schedule after force merge iteration: " << endl;
      schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
      cout << "***************************************************************************************" << endl;
      if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
      }

      // doing a name merge again.
      for(int i = 0; i < dynamic_bucket_size - 1; i++) {
        // std::cout << kernel_name[i] << " " << kernel_name[i + 1] << endl; -> debugging statement
        if (kernel_name[i] == kernel_name[i + 1]) {
          //merge_bucket(i, i + 1);
          for(int j = i+1; j < dynamic_bucket_size - 1; j++) {
            kernel_name[j] = kernel_name[j +  1];
          }
          // merging the range
          for(int j = i+1; j < dynamic_bucket_size; j++) {
            bucket_range[j] = bucket_range[j + 1];
          }
          // merging the cost
          bucket_cost[i] = bucket_cost[i] + bucket_cost[i + 1];
          for(int j = i + 1; j < dynamic_bucket_size; j++) {
            bucket_cost[j] = bucket_cost[j + 1];
          }

          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          bucket_cost[dynamic_bucket_size - 1] = -1;
          // now we need to merge the array of vector
          dynamic_bucket_size -=1;
          schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
        }
        if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
        }
      }

      cout << "Printing the schedule after force merge iteration: AFTER NAME MERGE: " << endl;
      schedule_printer_cost(dynamic_bucket_size, kernel_name, bucket_cost, bucket_range);
      cout << "***************************************************************************************" << endl;
    }
    // **************************************************************************************************************
    // force merge ends here
  } // if end in here
  if (bucket_sizes_requested.find(dynamic_bucket_size) != bucket_sizes_requested.end()) {
          // we need a graph with this bucket size
          std::cout << "Printing out a graph with the bucket size = " << dynamic_bucket_size << endl;
          make_graph(dynamic_bucket_size, number_of_nodes, number_of_edges, 
                    dictionary_for_sorting, bucket_range, 
                    dynamic_bucket_size, dictionary_degree);
          std::cout << "Printing the graph for bucket size = " << dynamic_bucket_size << " Completed" << endl;
          bucket_sizes_requested.erase(dynamic_bucket_size);
          number_of_bucket_sizes -= 1;
  }
  return 0;
}


