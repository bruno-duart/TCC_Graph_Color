#!/bin/bash

gcc mainREGSA.c forward_list.c metaheuristics.c grafos.c -lm -o mainREGSA

for counter in {1..5}; do
    for num_registers in 8 12; do
        for file in instances/REG/*; do
            for t_iter in 10 25 50 100; do
                for equi in 100 250 500; do
                    for conv in 100 250 500; do
                        ./mainREGSA $file $equi $conv $t_iter "REG/SA/$(basename -s .txt "$file").csv" $num_registers ;
                        echo "./mainREG $file $equi $conv $t_iter $(basename -s .txt "$file").csv $num_registers";
                    done
                done
            done
        done
    done
done