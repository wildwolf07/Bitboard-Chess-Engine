#include "defs.h"
#include <cstring>

struct GameState {
    U64 bitboards[12];
    U64 occupancies[3];
    int side;
};

GameState state_stack[64]; 
int ply = 0; 

void copy_board() {
    std::memcpy(state_stack[ply].bitboards, bitboards, 96); 
    std::memcpy(state_stack[ply].occupancies, occupancies, 24); 
    state_stack[ply].side = side;
    ply++;
}

void take_back() {
    ply--;
    std::memcpy(bitboards, state_stack[ply].bitboards, 96);
    std::memcpy(occupancies, state_stack[ply].occupancies, 24);
    side = state_stack[ply].side;
}

int make_move(Move move, int capture_flag) {
    copy_board();

    POP_BIT(bitboards[move.piece], move.source);
    
    SET_BIT(bitboards[move.piece], move.target);
    if (move.capture) {
        int start_piece, end_piece;
        if (side == WHITE) { start_piece = p; end_piece = k; }
        else               { start_piece = P; end_piece = K; }
                for (int bb_piece = start_piece; bb_piece <= end_piece; bb_piece++) {
            if (GET_BIT(bitboards[bb_piece], move.target)) {
                POP_BIT(bitboards[bb_piece], move.target);
                break;
            }
        }
    }

    std::memset(occupancies, 0ULL, 24);
    for (int bb_piece = P; bb_piece <= K; bb_piece++) occupancies[WHITE] |= bitboards[bb_piece];
    for (int bb_piece = p; bb_piece <= k; bb_piece++) occupancies[BLACK] |= bitboards[bb_piece];
    occupancies[BOTH] = occupancies[WHITE] | occupancies[BLACK];

    side ^= 1;
    
    return 1; 
}