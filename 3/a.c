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
	visited[0].y = 0;
	int num = 1;
	Pos pos;
	pos.x = 0;
	pos.y = 0;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case 'v':
				pos.y += 1;
				break;
			case '^':
				pos.y -= 1;
				break;
			case '<':
				pos.x -= 1;
				break;
			case '>':
				pos.x += 1;
				break;
		}
		int exists = 0;
		for (int i = 0; i < num; i++) {
			if (pos.x == visited[i].x && pos.y == visited[i].y) {
				exists = 1;
				break;
			}
		}
		if (!exists) {
			visited[num++] = pos;
		}
			
	}	
	printf("%d\n", num);
	return 0;
}
