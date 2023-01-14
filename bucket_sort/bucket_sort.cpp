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
using namespace std;

// global variables declared here
// bucket delete -> modify -> could buckets be stored on disk?
// codes -
// 1 -> O E O
// 2 -> E O O
// 3 -> O O E
int FLOAT_MIN = 0;
int FLOAT_MAX = 1;
// I think we can make the buckets global

void merge_bucket(int first, int second, int new_position, int &dynamic_bucket_size, float *bucket_cost, int *bucket_range, int *bucket_size_array) {
  vector <int> bu_range; // range
  int left, right;
  float final_cost = 0;
  int final_size = 0;
  int to_div;
  left = first;
  right = second + 1;
  for (int i = first; i <= second; i ++ ) {
    final_cost += bucket_cost[i];
    final_size += bucket_size_array[i];
    dynamic_bucket_size -= 1;
    to_div += 1;
  }
  dynamic_bucket_size += 1;
  final_cost += final_cost / to_div;
  // now we just need to replace
  for (int i = 0; i < dynamic_bucket_size + 1; i++) {
    if (i <= left || i >= right) {
      bu_range.push_back(bucket_range[i]);
    }
  }
  for (int i = 0; i < dynamic_bucket_size + 1; i ++) {
    bucket_range[i] = bu_range[i];
  }
  // bucket range has been handled
  // now going to handle cost array and bucket size array
  bucket_cost[new_position] = final_cost;
  bucket_size_array[new_position] = final_size;
  for (int i = new_position + 1; i < dynamic_bucket_size -1; i++) {
    bucket_cost[i] = bucket_cost[i + 1];
    bucket_size_array[i] = bucket_size_array[i + 1];
  }
}

void deleting_empty_bucket(int bucket_to_del, vector<string> &kernel_name, float* cost, int number_of_buckets, vector<int> *bucket_array, int *range) { // INCOMPLETE
  if (bucket_to_del == 0) { // if we need to delete the first bucket, then
    int marker = range[0];
    for(int i = 1; i < number_of_buckets; i++) {
      cost[i-1] = cost[i];
      kernel_name[i - 1] = kernel_name[i];
      bucket_array[i - 1] = bucket_array[i];
    }
    for(int i = 1; i < number_of_buckets + 1; i++) {
      range[i - 1] = range[i];
    }
    cost[number_of_buckets - 1] = -1; // saying that value is no longer valid
    kernel_name[number_of_buckets - 1].clear();
    bucket_array[number_of_buckets - 1].clear();
    range[0] = marker;
    range[number_of_buckets] = -1;
  } else if (bucket_to_del == number_of_buckets - 1) { // end bucket to be deleted
    // deleting the last element in the number of buckets and stuff
    int marker = range[number_of_buckets];
    cost[number_of_buckets - 1] = -1;
    kernel_name[number_of_buckets - 1].clear();
    bucket_array[number_of_buckets - 1].clear();
    range[number_of_buckets - 1] = marker;
    range[number_of_buckets] = -1;
  } else { // it comes in between
    // delete the value from the kernel name corresponding to the bucket
    // delete the value from the cost bucket
    // shift the ranges


  }
}
// number_of_buckets should be the length of lis_range
// 256 34 20 1 0 - 4, 5
// number of buckets = 4
// [256, 34], [34, 20], [20, 1], [1, 0]
//  0           1        2         3
int bucket_decider(int degree, int *lis_range, int number_of_buckets) {
   for(int i = 1; i < number_of_buckets; i++) {
     if ((degree <= lis_range[i - 1]) && (degree > lis_range[i])) {
       return i;
     } else if (degree == 0) {
       //return number_of_buckets - 1; // will put this in the last bucket
       return number_of_buckets; // will put this in the last bucket
     }
   }
   return 1;
}

int main(int argc, char** argv) {
  srand(time(nullptr));
  std::cout << "The flag given was:" << argv[1] << endl;
  std::cout << "The unweighted graph entered is: " << argv[2] << endl;
  std::cout << "File to extract bucket data is: " << argv[3] << endl;
  std::cout << "Intermediate_representation: " << argv[4] << endl;
  int intermediate_representation = 0; // we are processing the entire graph at once
  if ((int)(size_t)argv[4] == 1) {
    intermediate_representation = 1;
  }

  int to_do_flag = stoi(argv[1]);
  fstream my_file;
  my_file.open(argv[3], ios::in); // opening the bucket data file
  std::cout << "File opened: Success" << endl;
  string to_read;
  getline(my_file, to_read); // read the number of buckets
  int number_of_buckets;
  std::cout << "number of buckets are: " << to_read << endl;
  number_of_buckets = stoi(to_read);

  // defining bucket arrays
  int bucket_range[number_of_buckets + 1];
  float bucket_cost[number_of_buckets];
  string kernel_name[number_of_buckets];

  getline(my_file, to_read); // reading the empty line

  //storing the bucket ranges
  for(int i = 0; i < number_of_buckets + 1; i++) {
    getline(my_file, to_read);
    bucket_range[i] = stoi(to_read);
  }

  getline(my_file, to_read); // reading the empty line

  // now would be reading the cost of each bucket
  for(int i = 0; i < number_of_buckets; i++) {
    getline(my_file, to_read);
    bucket_cost[i] = stoi(to_read); // refers to cost of bucket i to i + 1
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
  getline(my_file, to_read);
  getline(my_file, to_read);
  // now we would have to split to_read to get everything
  std::cout << "tokenizing to read number of edges and nodes: " << to_read << endl;
  int number_of_edges, number_of_nodes;
  char *token;
  char *dup = strdup(to_read.c_str());
  token = strtok(dup, " ");
  token = strtok(NULL, " ");
  number_of_edges = stoi(token);
  token = strtok(NULL, " ");
  number_of_nodes = stoi(token);

  std::cout << "Number of nodes = " << number_of_nodes << endl;
  std::cout << "Number of edges = " << number_of_edges << endl;
  std::cout <<"Number of nodes and edges initialised: Success" << endl;
  int insert = 0;
  int end = 0;
  bool insert_falg = false;
  ssize_t getline_lable;

  // getline_lable = getline(my_file, to_read);
  // now we need encryption array

  int *encrpytion_array = new int[number_of_nodes];
  vector<int> *dictionary_degree = new vector<int>[number_of_nodes];
  int *dictionary_for_sorting = new int[number_of_nodes] (); // initialize to all zeros
  std::cout << "Array set up done" << endl;

  int prev_node = 0;
  int on_node = 0;

  // int *weight_dictionary{new float[number_of_nodes]};
  unordered_map<string, float> weight_dictionary;
  //int *b_graph{new int[number_of_nodes]}; // could be stored as a file
  std::cout << "map set up" << endl;

  // to store the order of the graph
  ofstream outfile ("b_graph_file.txt");
  unordered_map<int, bool> b_graph_set;
  std::cout << "Graph variables initialised: Success" << endl;
  int node_id;
  int edge_id;
  char* tok;
  float u; // temporary variable for stroring the
  string temp_string;
  while (getline(my_file, to_read)) {
    dup = strdup(to_read.c_str());
    tok = strtok(dup, " ");
    edge_id = stoi(tok) - 1;  //edge_id = int(line[0]) - 1
    tok = strtok(NULL, " ");
    node_id = stoi(tok) - 1;  // node_id = int(line[1]) - 1
    temp_string = to_string(node_id) + "-" + to_string(edge_id) + "-";
    if (weight_dictionary.find(temp_string) == weight_dictionary.end()) {
      u = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
      weight_dictionary[temp_string] = u;
    }

    // might remove this if statement
    if (prev_node != edge_id) {
      while (edge_id > on_node) {
        if (dictionary_degree[on_node].size() == 0) {
        }
        on_node += 1;
        if (on_node == edge_id) {
          break;
        }
      }
    }

    if (b_graph_set.find(node_id) == b_graph_set.end()) {
      b_graph_set[node_id] = true;
      outfile << to_string(node_id) << endl; // writing to file of b_graph
    }

    dictionary_degree[node_id].push_back(edge_id);
    dictionary_for_sorting[node_id] += 1;
    prev_node = edge_id;
  }

  // accounting for the lonely nodes
  for(int i = 0; i < number_of_nodes; i++) {
    if (b_graph_set.find(i) == b_graph_set.end()) {
      b_graph_set[i] = true;
      outfile << to_string(i) << endl;
    }
  }
  // all the nodes have been accounted
  outfile.close();
  my_file.close();

  std::cout << "Graph read and variables populated: Success" << endl; // working till here - checked on Toucan
  b_graph_set.clear();

  std::cout << "Bucketing process starting: Success" << endl;

  // should print out an initial schedule here before starting
  std::cout << "Printing out the initial schedule here -> " << endl;
  // technically, we should be calling a function here but for now, I am writing the code in the main
  for(int indi = 0; indi < 5; indi ++) {
    std::cout << "----------";
  }
  std::cout << endl;
  int mid_size = 25;
  std::cout << "Bucket name + range" << "      |     Kernel Name" << endl;
  
  for(int i = 0; i < number_of_buckets; i++) {
    for(int indi = 0; indi < 5; indi ++) {
      std::cout << "----------";
    }
    std::cout << endl;
    string bucket = "Bucket" + to_string(i);
    int temp_space_var = mid_size - bucket.length();
    std::cout << bucket;
    for(int indi = 0; indi < temp_space_var; indi ++) {
      cout << " ";
    }
    cout << "|     ";
    cout << kernel_name[i] << endl;
    bucket = to_string(bucket_range[i]) + " - " + to_string(bucket_range[i + 1]);
    temp_space_var = mid_size - bucket.length();
    std::cout << bucket;
    for(int indi = 0; indi < temp_space_var; indi ++) {
      cout << " ";
    }
    cout << "|     " <<  endl;
  }
  cout << endl;

  // code for printing out the buckets ends here

  vector<int> *graph_bucket_list_nodes = new vector<int>[number_of_buckets];
  int dynamic_bucket_size = number_of_buckets;
  int *bucket_size = new int[number_of_buckets]; // size of each bucket

  // now we need a method to split the graph
  // now we would have to open the b_graph file for reading
  my_file.open("b_graph_file.txt");
  int num;
  // while(getline(my_file, to_read)) {
  //   num = stoi(to_read);
  //   if (num == 2826033) { // this is just for debugging purpose
  //     std::cout << "deg = " << dictionary_for_sorting[num] << endl;
  //     std:cout << "result = " << bucket_decider(dictionary_for_sorting[num], bucket_range, number_of_buckets + 1) - 1;
  //   } // int degree, int *lis_range, int number_of_buckets
  //   graph_bucket_list_nodes[bucket_decider(dictionary_for_sorting[num], bucket_range, number_of_buckets + 1) - 1].push_back(num);
  //   //int degree, int lis_range[], int number_of_buckets
  // }
  my_file.close();
  std::cout << "Buckets created + populated: Success." << endl;
  std::cout << "Reduction Process beginning: Success." << endl;
  std::cout <<"Current bucket size = " << dynamic_bucket_size << endl; // works till here - Success seen on Toucan
  // std::cout << "Number of nodes in buckets = " << endl;
  // for(int i = 0; i < number_of_buckets; i++) {
  //   bucket_size[i] = graph_bucket_list_nodes[i].size();
  //   std::cout << to_string(i) << "  " << to_string(bucket_size[i]) << endl;
  // }

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
          bucket_range[dynamic_bucket_size] = -1;
          kernel_name[dynamic_bucket_size - 1] = "-1";
          // now we need to merge the array of vector
          change_made = 1;
          dynamic_bucket_size -=1;
        }
      }

      std::cout << "Iteration completed" << endl;

      if (change_made == 0) {
        break;
      }

      // if a change was made then we will print out the schedule
      std::cout << "Printing out the schedule -> " << endl;
      // technically, we should be calling a function here but for now, I am writing the code in the main
      for(int indi = 0; indi < 5; indi ++) {
        std::cout << "----------";
      }
      std::cout << endl;
      int mid_size = 25;
      std::cout << "Bucket name + range" << "      |     Kernel Name" << endl;
      
      for(int i = 0; i < dynamic_bucket_size; i++) {
        for(int indi = 0; indi < 5; indi ++) {
          std::cout << "----------";
        }
        std::cout << endl;
        string bucket = "Bucket" + to_string(i);
        int temp_space_var = mid_size - bucket.length();
        std::cout << bucket;
        for(int indi = 0; indi < temp_space_var; indi ++) {
          cout << " ";
        }
        cout << "|     ";
        cout << kernel_name[i] << endl;
        bucket = to_string(bucket_range[i]) + " - " + to_string(bucket_range[i + 1]);
        temp_space_var = mid_size - bucket.length();
        std::cout << bucket;
        for(int indi = 0; indi < temp_space_var; indi ++) {
          cout << " ";
        }
        cout << "|     " <<  endl;
      }
      cout << endl;
      // printing ends here
    }
    // merge by just the name
  } else if (to_do_flag == 2) {
    // TODO (SanyaSriv): merge by both time and name

  } else if (to_do_flag == 1) {
    // merge by time only
    vector <int> flagged_buckets;
    while (dynamic_bucket_size > ideal) {
      // initializing our variables for now
      int smallest = -1;
      int to_comp = number_of_nodes; // size of the smallest bucket
      std::cout << dynamic_bucket_size << endl;
      // now we will compute the smallest bucket
      for (int i = 0; i < dynamic_bucket_size; i++) {
        int s = bucket_size[i];
        if ((s < to_comp) && (find(flagged_buckets.begin(), flagged_buckets.end(), i) == flagged_buckets.end())) {
          smallest = i;
          to_comp = s;
        }
      }

      if (smallest == -1) {
          // algorithm should terminate because no smallest bucket was found
          break;
      }

      // at this point - comp = smallest bucket, and smallest = index of that bucket
      // if the size of the smallest bucket == 0, then we should delete it
      if (bucket_size[smallest] == 0) {
        // do not care if it is the last bucket because there would not be anything in it anyway
        // delete bucket index == smallest
        int i = smallest;
        for(int j = i; j < dynamic_bucket_size - 1; j++) {
          kernel_name[j] = kernel_name[j +  1];
          bucket_cost[j] = bucket_cost[j + 1];
          bucket_size[j] = bucket_size[j + 1];
        }
        for(int j = i; j < dynamic_bucket_size; j++) {
          bucket_range[j] = bucket_range[j + 1];
        }

        // assigning -1 to the deleted things
        bucket_range[dynamic_bucket_size] = -1;
        kernel_name[dynamic_bucket_size - 1] = "-1";
        bucket_cost[dynamic_bucket_size - 1] = -1.0;
        bucket_size[dynamic_bucket_size - 1] = -1;
        // now we need to merge the array of vector
        dynamic_bucket_size -=1;
        continue; // to another iteration
      }

      // if the smallest bucket has size > 0, then we need to merge

      float cost_smallest_buck = bucket_cost[smallest];
      float cost_after_buck = -1.0; // initializing - cost of bucket previous to the smallest one
      float cost_prev_buck = -1.0; // initializing - cost of bucket next to the smallest one

      if (smallest != dynamic_bucket_size - 1) { // if the smallest bucket is not the last bucket
        cost_after_buck = bucket_cost[smallest + 1];
      }
      if (smallest != 0) { // if the smallest bucket is not the next bucket
        cost_prev_buck = bucket_cost[smallest - 1];
      }

      if ((cost_prev_buck != -1.0) && (cost_after_buck != -1.0)) { // if we are merging the middle bucket
        if ((cost_prev_buck == cost_after_buck) && (cost_prev_buck == cost_smallest_buck)) { // merge all 3 together
          merge_bucket(smallest - 1, smallest + 1, smallest - 1, dynamic_bucket_size, bucket_cost, bucket_range, bucket_size);
        } else if ((cost_prev_buck <= cost_smallest_buck) && (cost_smallest_buck < cost_after_buck)) { // merge prev with smallest
          merge_bucket(smallest - 1, smallest, smallest - 1, dynamic_bucket_size, bucket_cost, bucket_range, bucket_size);
        } else if ((cost_prev_buck > cost_smallest_buck) && (cost_smallest_buck >= cost_after_buck)) { // merge after with smallest
          merge_bucket(smallest, smallest + 1, smallest, dynamic_bucket_size, bucket_cost, bucket_range, bucket_size);
        } else {
          // int first, int second, int new_position, int *dynamic_bucket_size, int *bucket_cost, int *bucket_range, int *bucket_size_array
          // nothing got merged
          // flag the bucket so we do not get it again as the smallest bucket
          std::cout << "did nothing" << endl;
          flagged_buckets.push_back(smallest);
        }
      } else if ((cost_prev_buck != -1.0) && (cost_after_buck == -1.0)) { // end bucket to be merged
        if (cost_prev_buck <= cost_smallest_buck) {
          merge_bucket(smallest - 1, smallest, smallest - 1, dynamic_bucket_size, bucket_cost, bucket_range, bucket_size);
        } else {
          // nothing got merged
          // flag the bucket so we do not get it again as the smallest bucket
          std::cout << "did nothing" << endl;
          flagged_buckets.push_back(smallest);

        }
      } else if ((cost_prev_buck == -1.0) && (cost_after_buck != -1.0)) { // first bucket is to be merged
        if (cost_after_buck <= cost_smallest_buck) {
          merge_bucket(smallest, smallest + 1, smallest, dynamic_bucket_size, bucket_cost, bucket_range, bucket_size);
        } else {
          // nothing got merged
          // flag the bucket so we do not get it again as the smallest bucket
          std::cout << "did nothing" << endl;
          flagged_buckets.push_back(smallest);
        }
      }
    }
  }

  std::cout << "Bucket reduciton process is completed. Number of buckets now = " << dynamic_bucket_size << endl;
  // std::cout << "Bucket ranges now - " << endl;
  // for(int i = 0; i < dynamic_bucket_size + 1; i++) {
  //   std::cout << to_string(bucket_range[i]) << endl;
  // }

  // now we need to empty graph_bucket_list_nodes
  // for(int i = 0; i < number_of_buckets; i ++) {
  //   graph_bucket_list_nodes[i].clear();
  // }
  // now we need to populate the graph_bucket_list_nodes
  std::cout << "opening the b graph file" << endl;
  my_file.open("b_graph_file.txt");
  while(getline(my_file, to_read)) {
    num = stoi(to_read);
    // int degree, int *lis_range, int number_of_buckets
    graph_bucket_list_nodes[bucket_decider(dictionary_for_sorting[num], bucket_range, dynamic_bucket_size + 1) - 1].push_back(num);
    //int degree, int lis_range[], int number_of_buckets
  }
  my_file.close();

  // have to check if it is working till here
  // commenting out the python tail code for now - will check it later
  // TODO (SanyaSriv): Check if this works 
  /*
  // now we will create 2 files -
  ofstream outfile1 ("index_array.txt");
  ofstream outfile2 ("neighbour_array.txt");
  ofstream outfile3 ("weights_array.txt");
  unordered_map <int, int> dic_translate;
  int k = 0;
  for(int x = 0; x < dynamic_bucket_size; x++) {
    for (int j = 0; j < graph_bucket_list_nodes[x].size(); j++) {
      dic_translate[graph_bucket_list_nodes[x][j]] = k;
      k += 1;
    }
  }

  // for the intermediate_representation, we are just outputting the different nodes
  // in the buckets
  // TODO (SanyaSriv): Add another file that has all the neighbours of these nodes
  if (intermediate_representation == 1) {
    ofstream outfile_i ("intermediate_representation.txt");
    for (int i = 0; i < dynamic_bucket_size; i++) {
      outfile_i << endl << to_string(i) << endl << endl;
      for (int j = 0; j < graph_bucket_list_nodes[i].size(); j++) {
        outfile_i << to_string(graph_bucket_list_nodes[i][j]) <<  endl;
      }
    }
    outfile_i.close();
    return 0;
  }

  string st;
  int neighbour_array_size = 0;
  for (int i = 0; i < dynamic_bucket_size; i++) {
    for (int j = 0; j < graph_bucket_list_nodes[i].size(); j++) {
      outfile1 << to_string(neighbour_array_size) << endl;
      for (auto&k : dictionary_degree[graph_bucket_list_nodes[i][j]]) { // k are the neighbours of j
        // TODO (SanyaSriv): The line below should be to_string(graph_bucket_list_nodes[i][j])
        st = to_string(j) + "-" + to_string(k) + "-";
        float to_insert = weight_dictionary[st];
        outfile2 << to_string(dic_translate[k]) << endl;
        outfile3 << to_string(to_insert) << endl;
        neighbour_array_size += 1;
      }
    }
  }
  outfile1 << to_string(neighbour_array_size) << endl;

  outfile1.close();
  outfile2.close();
  outfile3.close();
  */
  return 0;
}
