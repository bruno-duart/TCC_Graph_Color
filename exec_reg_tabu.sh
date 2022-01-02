#!/bin/bash

gcc mainREGTabu.c forward_list.c metaheuristics.c grafos.c -lm -o mainREGTabu

#for file in instances/REG/*; do
#    echo "num_colors,num_conflicts,num_spilling,num_iter,time,converge,equilibrio,t_iter" > "REG/Tabu/$(basename -s .txt "$file").csv"
#    echo "num_colors,num_conflicts,num_spilling,num_iter,time,converge,equilibrio,temp" > "REG/SA/$(basename -s .txt "$file").csv"
#done

# instance, equilibrio, t_iter, output, num_registers
for counter in {1..10}; do
    for num_registers in 8 12; do
        for file in instances/REG/*; do
            for t_iter in 10 25 50 100; do
                for equi in 100; do
                    ./mainREGTabu $file $equi $t_iter "REG/Tabu/$(basename -s .txt "$file").csv" $num_registers ;
                    echo "./mainREG $file $equi $t_iter $(basename -s .txt "$file").csv $num_registers";
                done
            done
        done
    done
done