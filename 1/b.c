#include <stdio.h>
int main() {
	char c;
	int floor = 0;
	int pos = 0;
	while ((c = getchar()) != EOF) {
		pos++;
		switch (c) {
			case '(':
				floor++;
				break;
			case ')':
				floor--;
				break;
		}
		if (floor == -1) {
			printf("%d\n", pos);
			break;	
		}
	}	
	return 0;
}
