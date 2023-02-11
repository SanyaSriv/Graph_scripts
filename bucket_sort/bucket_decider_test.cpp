#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "bucket_sort_functions.h"

using namespace std;


int main(int argc, char** argv) {
    int lis[9] = {900, 890, 578, 90, 80, 50, 43, 2, 0};

    int r = bucket_decider(600, lis, 8);
    assert(r == 1);

    r = bucket_decider(900, lis, 8);
    assert(r == 0);

    r = bucket_decider(910, lis, 8);
    assert(r == 0);

    r = bucket_decider(890, lis, 8);
    assert(r == 1);

    r = bucket_decider(-8, lis, 8);
    assert(r == 7);

    r = bucket_decider(30, lis, 6);
    assert(r == 5);

    r = bucket_decider(95, lis, 8);
    assert(r == 2);

    int lis2[9] = {80, 70, 40, 0, 80, 50, 43, 2, 0};

    r = bucket_decider(80, lis2, 3);
    assert(r == 0);

    r = bucket_decider(90, lis2, 3);
    assert(r == 0);

    r = bucket_decider(45, lis2, 3);
    assert(r == 1);

    r = bucket_decider(-77, lis2, 3);
    assert(r == 2);

    r = bucket_decider(70, lis2, 3);
    assert(r == 1);

    r = bucket_decider(0, lis2, 3);
    assert(r == 2);

    int lis3[9] = {80, 70, 40, 20, 80, 50, 43, 2, 0};

    r = bucket_decider(20, lis3, 3);
    assert(r == 2);

     r = bucket_decider(0, lis3, 3);
    assert(r == 2);

    cout << "SUCCESS" << endl;
}

