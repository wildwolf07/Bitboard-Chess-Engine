#include "defs.h"

U64 knight_attacks[64];
U64 king_attacks[64];

const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;

U64 mask_knight_attacks(int square) {
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    SET_BIT(bitboard, square);

    if ((bitboard >> 17) & not_h_file) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_gh_file) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_ab_file) attacks |= (bitboard >> 6);
    if ((bitboard << 17) & not_a_file) attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file) attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_gh_file) attacks |= (bitboard << 6);

    return attacks;
}

U64 mask_king_attacks(int square) {
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    SET_BIT(bitboard, square);

    if (bitboard >> 8) attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);
    if (bitboard << 8) attacks |= (bitboard << 8);
    if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
    if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1);
    
    return attacks;
}

U64 mask_bishop_attacks(int square) {
    U64 attacks = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    
    for (r = tr + 1, f = tf + 1; r < 7 && f < 7; r++, f++) SET_BIT(attacks, r * 8 + f);
    for (r = tr + 1, f = tf - 1; r < 7 && f > 0; r++, f--) SET_BIT(attacks, r * 8 + f);
    for (r = tr - 1, f = tf + 1; r > 0 && f < 7; r--, f++) SET_BIT(attacks, r * 8 + f);
    for (r = tr - 1, f = tf - 1; r > 0 && f > 0; r--, f--) SET_BIT(attacks, r * 8 + f);
    
    return attacks;
}

U64 mask_rook_attacks(int square) {
    U64 attacks = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    
    for (r = tr + 1; r < 7; r++) SET_BIT(attacks, r * 8 + tf);
    for (r = tr - 1; r > 0; r--) SET_BIT(attacks, r * 8 + tf);
    for (f = tf + 1; f < 7; f++) SET_BIT(attacks, tr * 8 + f);
    for (f = tf - 1; f > 0; f--) SET_BIT(attacks, tr * 8 + f);
    
    return attacks;
}

U64 bishop_attacks_on_the_fly(int square, U64 block) {
    U64 attacks = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    
    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
        SET_BIT(attacks, r * 8 + f);
        if (GET_BIT(block, r * 8 + f)) break;
    }
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
        SET_BIT(attacks, r * 8 + f);
        if (GET_BIT(block, r * 8 + f)) break;
    }
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
        SET_BIT(attacks, r * 8 + f);
        if (GET_BIT(block, r * 8 + f)) break;
    }
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
        SET_BIT(attacks, r * 8 + f);
        if (GET_BIT(block, r * 8 + f)) break;
    }
    return attacks;
}

U64 rook_attacks_on_the_fly(int square, U64 block) {
    U64 attacks = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    
    for (r = tr + 1; r <= 7; r++) {
        SET_BIT(attacks, r * 8 + tf);
        if (GET_BIT(block, r * 8 + tf)) break;
    }
    for (r = tr - 1; r >= 0; r--) {
        SET_BIT(attacks, r * 8 + tf);
        if (GET_BIT(block, r * 8 + tf)) break;
    }
    for (f = tf + 1; f <= 7; f++) {
        SET_BIT(attacks, tr * 8 + f);
        if (GET_BIT(block, tr * 8 + f)) break;
    }
    for (f = tf - 1; f >= 0; f--) {
        SET_BIT(attacks, tr * 8 + f);
        if (GET_BIT(block, tr * 8 + f)) break;
    }
    return attacks;
}

U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask) {
    U64 occupancy = 0ULL;
    for (int count = 0; count < bits_in_mask; count++) {
        int square = get_ls1b_index(attack_mask);
        POP_BIT(attack_mask, square);
        if (index & (1 << count)) {
            SET_BIT(occupancy, square);
        }
    }
    return occupancy;
}

void init_leapers_attacks() {
    for (int square = 0; square < 64; square++) {
        knight_attacks[square] = mask_knight_attacks(square);
        king_attacks[square] = mask_king_attacks(square);
    }
}