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

int bucket_decider(int degree, int *lis_range, int number_of_buckets) {
   for(int i = 0; i < number_of_buckets; i++) {
     if ((degree <= lis_range[i]) && (degree > lis_range[i + 1])) {
       return i;
     } else if (degree == 0) {
       //return number_of_buckets - 1; // will put this in the last bucket
       return number_of_buckets - 1; // will put this in the last bucket
     }
   }
   if (degree >= lis_range[0]){
    return 0;
   }
   if (degree < lis_range[number_of_buckets - 1]) {
    return number_of_buckets - 1;
   }
   return 0;
}

void schedule_printer(int number_of_buckets, string kernel_name[], int bucket_range[]) {
  // TODO (SanyaSriv): Fill in this code.
   for(int indi = 0; indi < 6; indi ++) {
    std::cout << "----------";
  }
  std::cout << endl;
  int mid_size = 30;
  string header_string = "Bucket name + range";
  std::cout << "Bucket name + range";
  int temp_space = mid_size - header_string.size();
  for(int indi = 0; indi < temp_space; indi ++) {
    cout << " ";
  }
  cout << "|";
  std::cout << "     Kernel Name" << endl;
  // std::cout << "Bucket name + range" << "      |     Kernel Name" << endl;
  
  for(int i = 0; i < number_of_buckets; i++) {
    for(int indi = 0; indi < 6; indi ++) {
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
}

void schedule_printer_cost(int dynamic_bucket_size, string kernel_name[], float bucket_cost[], int bucket_range[]) {
  for (int indi = 0; indi < 9; indi++) {
    std::cout << "----------";
  }
  std::cout << endl;
  int mid_size = 30;
  string header_string = "Bucket name + range";
  std::cout << "Bucket name + range";
  int temp_space = mid_size - header_string.size();
  for (int indi = 0; indi < temp_space; indi++) {
    cout << " ";
  }
  cout << "|";
  std::cout << "     Kernel Name";
  header_string = "Kernel Name";
  temp_space = mid_size - header_string.size();
  for (int indi = 0; indi < temp_space; indi++) {
    cout << " ";
  }
  std::cout << "|      Bucket Cost" << endl;

  for (int i = 0; i < dynamic_bucket_size; i++) {
    for (int indi = 0; indi < 9; indi++) {
      std::cout << "----------";
    }
    std::cout << endl;
    string bucket = "Bucket" + to_string(i);
    int temp_space_var = mid_size - bucket.length();
    std::cout << bucket;
    for (int indi = 0; indi < temp_space_var; indi++) {
      cout << " ";
    }
    cout << "|     ";

    cout << kernel_name[i];
    temp_space_var = mid_size - kernel_name[i].size();
    for (int indi = 0; indi < temp_space_var; indi++) {
      cout << " ";
    }
    cout << "|     ";

    // putting the kernel cost in here
    cout << bucket_cost[i] << endl;

    bucket = to_string(bucket_range[i]) + " - " + to_string(bucket_range[i + 1]);
    temp_space_var = mid_size - bucket.length();
    std::cout << bucket;
    for (int indi = 0; indi < temp_space_var; indi++)
    {
      cout << " ";
    }
    cout << "|     ";

    temp_space_var = mid_size - kernel_name[i].size();
    for (int indi = 0; indi < mid_size; indi++) {
      cout << " ";
    }
    cout << "|     " << endl;
  }
  cout << endl;
}