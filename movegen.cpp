#include "defs.h"
#include <iostream>

void add_move(MoveList *move_list, int source, int target, int piece, int capture) {
    Move move;
    move.source = source;
    move.target = target;
    move.piece = piece;
    move.capture = capture;
    move_list->moves[move_list->count] = move;
    move_list->count++;
}

void generate_moves(MoveList *move_list) {
    move_list->count = 0;
    
    int source_square, target_square;
    U64 bitboard, attacks;
    
    U64 occupancy[3];
    occupancy[WHITE] = bitboards[P] | bitboards[N] | bitboards[B] | bitboards[R] | bitboards[Q] | bitboards[K];
    occupancy[BLACK] = bitboards[p] | bitboards[n] | bitboards[b] | bitboards[r] | bitboards[q] | bitboards[k];
    occupancy[BOTH] = occupancy[WHITE] | occupancy[BLACK];

    if (side == WHITE) {
        bitboard = bitboards[N];
        while (bitboard) {
            source_square = get_ls1b_index(bitboard);
            attacks = knight_attacks[source_square] & ~occupancy[WHITE];
            while (attacks) {
                target_square = get_ls1b_index(attacks);
                int capture = GET_BIT(occupancy[BLACK], target_square) ? 1 : 0;
                add_move(move_list, source_square, target_square, N, capture);
                POP_BIT(attacks, target_square);
            }
            POP_BIT(bitboard, source_square);
        }
        
        bitboard = bitboards[K];
        while (bitboard) {
            source_square = get_ls1b_index(bitboard);
            attacks = king_attacks[source_square] & ~occupancy[WHITE];
            while (attacks) {
                target_square = get_ls1b_index(attacks);
                int capture = GET_BIT(occupancy[BLACK], target_square) ? 1 : 0;
                add_move(move_list, source_square, target_square, K, capture);
                POP_BIT(attacks, target_square);
            }
            POP_BIT(bitboard, source_square);
        }
        
        bitboard = bitboards[R];
        while (bitboard) {
            source_square = get_ls1b_index(bitboard);
            attacks = get_rook_attacks(source_square, occupancy[BOTH]) & ~occupancy[WHITE];
            while (attacks) {
                target_square = get_ls1b_index(attacks);
                int capture = GET_BIT(occupancy[BLACK], target_square) ? 1 : 0;
                add_move(move_list, source_square, target_square, R, capture);
                POP_BIT(attacks, target_square);
            }
            POP_BIT(bitboard, source_square);
        }
    }
    else {
        bitboard = bitboards[n];
        while (bitboard) {
            source_square = get_ls1b_index(bitboard);
            attacks = knight_attacks[source_square] & ~occupancy[BLACK];
            while (attacks) {
                target_square = get_ls1b_index(attacks);
                int capture = GET_BIT(occupancy[WHITE], target_square) ? 1 : 0;
                add_move(move_list, source_square, target_square, n, capture);
                POP_BIT(attacks, target_square);
            }
            POP_BIT(bitboard, source_square);
        }

        bitboard = bitboards[k];
        while (bitboard) {
            source_square = get_ls1b_index(bitboard);
            attacks = king_attacks[source_square] & ~occupancy[BLACK];
            while (attacks) {
                target_square = get_ls1b_index(attacks);
                int capture = GET_BIT(occupancy[WHITE], target_square) ? 1 : 0;
                add_move(move_list, source_square, target_square, k, capture);
                POP_BIT(attacks, target_square);
            }
            POP_BIT(bitboard, source_square);
        }

        bitboard = bitboards[r];
        while (bitboard) {
            source_square = get_ls1b_index(bitboard);
            attacks = get_rook_attacks(source_square, occupancy[BOTH]) & ~occupancy[BLACK];
            while (attacks) {
                target_square = get_ls1b_index(attacks);
                int capture = GET_BIT(occupancy[WHITE], target_square) ? 1 : 0;
                add_move(move_list, source_square, target_square, r, capture);
                POP_BIT(attacks, target_square);
            }
            POP_BIT(bitboard, source_square);
        }
    }
}