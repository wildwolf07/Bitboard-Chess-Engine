#ifndef DEFS_H
#define DEFS_H

#include <cstdint>
#include <iostream>

typedef uint64_t U64;

#define C64(constant) constant##ULL
#define GET_BIT(bitboard, square) ((bitboard) & (1ULL << (square)))
#define SET_BIT(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define POP_BIT(bitboard, square) ((bitboard) &= ~(1ULL << (square)))

enum { a1, b1, c1, d1, e1, f1, g1, h1, a2, b2, c2, d2, e2, f2, g2, h2, a3, b3, c3, d3, e3, f3, g3, h3, a4, b4, c4, d4, e4, f4, g4, h4, a5, b5, c5, d5, e5, f5, g5, h5, a6, b6, c6, d6, e6, f6, g6, h6, a7, b7, c7, d7, e7, f7, g7, h7, a8, b8, c8, d8, e8, f8, g8, h8, no_sq };
enum { P, N, B, R, Q, K, p, n, b, r, q, k };
enum { WHITE, BLACK, BOTH };

static inline int count_bits(U64 bb) { return __builtin_popcountll(bb); }
static inline int get_ls1b_index(U64 bb) { return bb ? __builtin_ctzll(bb) : -1; }

extern U64 bitboards[12]; 
extern U64 occupancies[3];
extern int side;
extern U64 knight_attacks[64];
extern U64 king_attacks[64];

extern U64 bishop_masks[64];
extern U64 rook_masks[64];
extern U64 bishop_attacks[64][512];
extern U64 rook_attacks[64][4096];

struct Move { int source, target, piece, capture; };
struct MoveList { Move moves[256]; int count; };

void init_leapers_attacks();
void init_magic_numbers();

U64 get_rook_attacks(int square, U64 occupancy);
U64 get_bishop_attacks(int square, U64 occupancy);

void generate_moves(MoveList *move_list);
int make_move(Move move, int capture_flag);
void copy_board();
void take_back();
void perft_test(int depth);

U64 mask_bishop_attacks(int square);
U64 mask_rook_attacks(int square);
U64 bishop_attacks_on_the_fly(int square, U64 block);
U64 rook_attacks_on_the_fly(int square, U64 block);
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask);
U64 generate_magic_candidate();
U64 find_magic_number(int square, int relevant_bits, int bishop);

#endif