#include <stdint.h>
#include <stdio.h>
#include "chess.h"

uint8_t notation_to_idx(char file, char rank){
	if(file < 'a' || file > 'h' || rank < '1' || rank > '8')
		return INVALID_INDEX;	
	uint8_t id = (8 - (rank - '0')) * 8 + file - 'a';
	printf("Index: %i\n", id);
	return id;

}

char get_piece_at(uint8_t i){
	if(IS_SET(king_pos, i))
		return 'K';
	return ' ';
}

void display_board(){
	printf("\n  ---------------------------------\n");
	int i, j;
	for(i = 0; i < 8; i++){
		printf("%d |", 8 - i);
		for(j = 0; j < 8; j++){
			printf(" %c |", get_piece_at(i*8+j));
		}
		printf("\n  ---------------------------------\n");
	}
	printf("    a   b   c   d   e   f   g   h");
	printf("\n");
}

Move get_move(){
	char s[128];
	unsigned int error;
	Move m = {INVALID_INDEX, INVALID_INDEX};

	error = 0;
	do{
		if(error == 1){
			printf("Try again.\n");
		}
		
		error = 0;
		
		printf("Enter move: ");
		fgets(s, 127, stdin);
		
		s[5] = '\0';
		
		m.from = notation_to_idx(s[0], s[1]);
		if(m.from == INVALID_INDEX){
			printf("Invalid from.\n");
			error = 1;
			continue;
		}
		
		if(s[2] != '-'){
			printf("A '-' exptected after from square.\n");
			error = 1;
			continue;
		}
		m.to = notation_to_idx(s[3], s[4]);
		if(m.to == INVALID_INDEX){
			printf("Invalid to./n");
			error = 1;
			continue;
		}
	}while (error == 1);
	
	return m;
}
