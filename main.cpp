#include <iostream>
#include <cstring>
#include "defs.h"

U64 bitboards[12]; 
U64 occupancies[3];
int side = WHITE;

void reset_board() {
    for (int i = 0; i < 12; i++) bitboards[i] = 0ULL;
    for (int i = 0; i < 3; i++) occupancies[i] = 0ULL;
    side = WHITE;
}

int main() {
    std::cout << "--- HFT Chess Engine v1.0 (Final) ---" << std::endl;
    
    init_leapers_attacks();
    init_magic_numbers();
    
    reset_board();
    SET_BIT(bitboards[R], d4);
    SET_BIT(bitboards[N], g1);
    SET_BIT(bitboards[K], e1);
    SET_BIT(bitboards[p], d7);
    SET_BIT(bitboards[k], e8);
    
    occupancies[WHITE] = bitboards[R] | bitboards[N] | bitboards[K];
    occupancies[BLACK] = bitboards[p] | bitboards[k];
    occupancies[BOTH] = occupancies[WHITE] | occupancies[BLACK];
    
    perft_test(4);
    std::cout << "Starting stress test (Depth 6)..." << std::endl;
    perft_test(6);
    
    return 0;
}