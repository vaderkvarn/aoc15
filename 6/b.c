#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

#define TURN_ON 0
#define TURN_OFF 1
#define TOGGLE 2

int get_action(char* str) {
    if (strcmp(str, "on") == 0) return TURN_ON;
    if (strcmp(str, "off") == 0) return TURN_OFF;
    if (strcmp(str, "toggle") == 0) return TOGGLE;
    return -1;
}

int check(int** map) {
    int num = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num += map[i][j];
        }
    }
    return num;
}

int main() {
    int **map = calloc(N, sizeof(int*));
    for (size_t i = 0; i < N; i++) {
        map[i] = calloc(N, sizeof(int));
    }
    
    char action[32];
    int x1, y1, x2, y2;
	while (scanf("%s %d,%d through %d,%d\n", action, &x1, &y1, &x2, &y2) != EOF) {
        for (size_t i = x1; i <= x2; i++) {
            for (size_t j = y1; j <= y2; j++) {
                switch (get_action(action)) {
                    case TURN_ON: 
                        map[i][j] += 1;
                        break;
                    case TURN_OFF:
                        map[i][j] = map[i][j] == 0 ? 0 : map[i][j] - 1;
                        break;
                    case TOGGLE:
                        map[i][j] += 2;
                        break;
                    default: exit(1);
                }

            }
        }

	}
    printf("%d\n", check(map));
    return 0;
}

