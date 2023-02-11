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

using namespace std;

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int bucket_decider(int degree, int *lis_range, int number_of_buckets);
void schedule_printer(int number_of_buckets, string kernel_name[], int bucket_range[]);
void schedule_printer_cost(int dynamic_bucket_size, string kernel_name[], float bucket_cost[], int bucket_range[]);

#endif