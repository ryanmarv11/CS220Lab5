#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "ref.h"

#define BIT(n) 			(1UL << (n))
#define SET_BIT(x, n)	((x) |= BIT((n)))
#define RESET_BIT(x, n) ((x) &= ~BIT(n))
#define IS_SET(x, n) 	((x) & BIT((n)))

PlayerState player[2];
PlayerColor current_player;
Pos ep_square;
void display_board();
char get_piece_char(Pos pos);
Piece get_piece_at_pos(PlayerColor c, Pos pos);


int main(int argc, char *argv[])
{
	ParseBoardOut *ret;
	Move *moves, *t; 
	if(argc != 2) return  -1;

	ret = ref_parse_board(argv[1]); 
	if(ret == NULL) {
		printf("Ret is null.\n"); 
		return -1; 
	}
	ref_display_board(ret); 

	moves = ref_legal_moves(argv[1], ret->current_player);
	while(moves) {
		ref_print_move(moves); 
		printf("\n"); 
		t = moves->next_move; 
		free(moves); 
		moves = t; 
	}
	free(ret); 

	if(ref_is_checkmate(argv[1], WHITE)) {
		printf("White is under checkmate\n"); 
	}
	if(ref_is_checkmate(argv[1], BLACK)) {
		printf("Black is under checkmate\n"); 
	}


	return 0; 
}

void display_board(){
	unsigned int i,j;
	printf("\n -------------------------\n");
	for(i = 0; i < 8; i++){
		printf("%d |", 8 - i);
		for(j = 0; j < 8; j++){
			printf(" %c |", get_piece_char(i*8 + j));
		}
		printf("\n -------------------------\n");
	}
	printf("\t a  b  c  d  e  f  g  h\n");
	printf("\n");
	printf("Current move %s\n", current_player == WHITE ? "White" : "Black");
}

char get_piece_char(Pos pos){
	if(IS_SET(player[WHITE].r, pos)) return 'R';
	if(IS_SET(player[WHITE].q, pos)) return 'Q';
	if(IS_SET(player[WHITE].p, pos)) return 'P';
	if(IS_SET(player[WHITE].k, pos)) return 'K';
	if(IS_SET(player[WHITE].b, pos)) return 'B';
	if(IS_SET(player[WHITE].n, pos)) return 'N';

	if(IS_SET(player[BLACK].r, pos)) return 'R';
	if(IS_SET(player[BLACK].q, pos)) return 'Q';
	if(IS_SET(player[BLACK].p, pos)) return 'P';
	if(IS_SET(player[BLACK].k, pos)) return 'K';
	if(IS_SET(player[BLACK].b, pos)) return 'B';
	if(IS_SET(player[BLACK].n, pos)) return 'N';

	return ' ';
}

Piece get_piece_at_pos(PlayerColor c, Pos pos){
	if(IS_SET(player[c].k, pos)) return KING;
	if(IS_SET(player[c].q, pos)) return QUEEN;
	if(IS_SET(player[c].p, pos)) return PAWN;
	if(IS_SET(player[c].r, pos)) return ROOK;
	if(IS_SET(player[c].b, pos)) return BISHOP;
	if(IS_SET(player[c].n, pos)) return NIGHT;

	return UNKNOWN;
}