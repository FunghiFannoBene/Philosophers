#!/bin/bash

for i in {1..100}
do
    count=$(./philo 3 410 200 200 10 | grep " 2 is thinking" | wc -l)
    if [ "$count" -eq 10 ]; then
        echo "Iteration $i: Count is 10"
    else
        echo "Iteration $i: Count is NOT 10"
    fi
done