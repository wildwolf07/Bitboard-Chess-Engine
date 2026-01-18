#include "defs.h"
#include <iostream>
#include <cstring>

U64 bishop_masks[64];
U64 rook_masks[64];
U64 bishop_attacks[64][512];
U64 rook_attacks[64][4096];
U64 get_rook_attacks(int square, U64 occupancy) {
    return rook_attacks_on_the_fly(square, occupancy);
}

U64 get_bishop_attacks(int square, U64 occupancy) {
    return bishop_attacks_on_the_fly(square, occupancy);
}

unsigned int random_state = 1804289383;

unsigned int get_random_U32_number() {
    unsigned int number = random_state;
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;
    random_state = number;
    return number;
}

U64 get_random_U64_number() {
    U64 n1 = (U64)(get_random_U32_number()) & 0xFFFF;
    U64 n2 = (U64)(get_random_U32_number()) & 0xFFFF;
    U64 n3 = (U64)(get_random_U32_number()) & 0xFFFF;
    U64 n4 = (U64)(get_random_U32_number()) & 0xFFFF;
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

U64 generate_magic_candidate() {
    return get_random_U64_number() & get_random_U64_number() & get_random_U64_number();
}

U64 find_magic_number(int square, int relevant_bits, int bishop) {
    U64 occupancies[4096];
    U64 attacks[4096];
    U64 used_attacks[4096];
    
    U64 attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);
    int occupancy_indices = 1 << relevant_bits;
    
    for (int index = 0; index < occupancy_indices; index++) {
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);
        if (bishop) 
            attacks[index] = bishop_attacks_on_the_fly(square, occupancies[index]);
        else
            attacks[index] = rook_attacks_on_the_fly(square, occupancies[index]);
    }
    
    for (int k = 0; k < 100000000; k++) {
        U64 magic_candidate = generate_magic_candidate();
        if (count_bits((attack_mask * magic_candidate) & 0xFF00000000000000ULL) < 6) continue;
        
        std::memset(used_attacks, 0ULL, sizeof(used_attacks));
        int fail = 0;
        
        for (int index = 0; index < occupancy_indices; index++) {
            int magic_index = (int)((occupancies[index] * magic_candidate) >> (64 - relevant_bits));
            
            if (used_attacks[magic_index] == 0ULL) {
                used_attacks[magic_index] = attacks[index];
            }
            else if (used_attacks[magic_index] != attacks[index]) {
                fail = 1; 
                break;
            }
        }
        if (!fail) return magic_candidate;
    }
    std::cout << "Magic search failed!" << std::endl;
    return 0ULL;
}

void init_magic_numbers() {
    std::cout << "Initializing Magics...\n";
}