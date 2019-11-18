#include <stdio.h>

#define N 10000

typedef struct {
	int x;
	int y;
} Pos;


int main() {
	char c;
	Pos visited[N];
	visited[0].x = 0;
	int num = 1;
	Pos s_pos;
	s_pos.x = 0;
	s_pos.y = 0;
	Pos r_pos;
	r_pos.x = 0;
	r_pos.y = 0;
	int is_santa = 1;
	while ((c = getchar()) != EOF) {
		Pos *pos = is_santa ? &s_pos : &r_pos;
		switch (c) {
			case 'v':
				pos->y += 1;
				break;
			case '^':
				pos->y -= 1;
				break;
			case '<':
				pos->x -= 1;
				break;
			case '>':
				pos->x += 1;
				break;
		}
		int exists = 0;
		for (int i = 0; i < num; i++) {
			if (pos->x == visited[i].x && pos->y == visited[i].y) {
				exists = 1;
				break;
			}
		}
		if (!exists) {
			visited[num++] = *pos;
		}
		is_santa = !is_santa;
			
	}	
	printf("%d\n", num);
	return 0;
}
