#!/bin/bash

set -o errexit

echo "Going to start with Twitter 2 (Twitter WWWW): SORTED"
python3 optimized_sorted.py twitter/out.twitter2 41652230 1468365182 1 0
echo "Twitter WWWW finished: SORTED"

sleep 5

echo "Going to start with Twitter 2 (Twitter WWWW): UNSORTED"
python3 optimized_unsorted.py twitter/out.twitter2 41652230 1468365182 1 0
echo "Twitter WWWW finished: UNSORTED"

sleep 5

echo "Going to start with Twitter 2 (Twitter WWWW): RANDOM"
python3 random_reorder.py twitter/out.twitter2 41652230 1468365182 1 0
echo "Twitter WWWW finished: RANDOM"

sleep 5

echo "Going to start with Friendster Original: SORTED"
python3 optimized_sorted.py out.friendster_graph 124836179 1806067135 4 0
echo "Friendster Original Finished: SORTED"

sleep 5

echo "Going to start with Friendster Original: UNSORTED"
python3 optimized_unsorted.py out.friendster_graph 124836179 1806067135 4 0
echo "Friendster Original Finished: UNSORTED"

sleep 5

echo "Going to start with Friendster Original: RANDOM"
python3 random_reorder.py out.friendster_graph 124836179 1806067135 4 0
echo "Friendster Original Finished: RANDOM"

sleep 5

echo "Going to start with Friendster new:UNSORTED"
python3 optimized_unsorted.py friendster/out.friendster_bigger 68349466 2586147869 2 0
echo "Friendster new finished:UNSORTED"

sleep 5

echo "Going to start with Friendster new:RANDOM"
python3 random_reorder.py friendster/out.friendster_bigger 68349466 2586147869 2 0
echo "Friendster new finished:RANDOM"

sleep 5

echo "Going to start with Friendster new:SORTED"
python3 optimized_sorted.py friendster/out.friendster_bigger 68349466 2586147869 2 0
echo "Friendster new finished:SORTED"
