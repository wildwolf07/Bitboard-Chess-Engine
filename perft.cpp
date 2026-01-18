#include "defs.h"
#include <iostream>
#include <chrono>

long nodes = 0;

void perft_driver(int depth) {
    if (depth == 0) {
        nodes++;
        return;
    }
    
    MoveList move_list;
    generate_moves(&move_list);
    
    for (int i = 0; i < move_list.count; i++) {

        if (!make_move(move_list.moves[i], move_list.moves[i].capture)) {
            continue; 
        }
        
        perft_driver(depth - 1);
        take_back();
    }
}

void perft_test(int depth) {
    std::cout << "\n   Performance Test (Perft) Depth: " << depth << "\n";
    
    nodes = 0;
    auto start = std::chrono::high_resolution_clock::now();
    
    MoveList move_list;
    generate_moves(&move_list);
    
    for (int i = 0; i < move_list.count; i++) {
        make_move(move_list.moves[i], move_list.moves[i].capture);
        long old_nodes = nodes;
        
        perft_driver(depth - 1);
        
        take_back();
        long current_nodes = nodes - old_nodes;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "\n   Nodes: " << nodes;
    std::cout << "\n   Time:  " << duration.count() << " ms";
    if(duration.count() > 0)
        std::cout << "\n   NPS:   " << (nodes * 1000) / duration.count() << " (Nodes/Sec)";
    std::cout << "\n\n";
}