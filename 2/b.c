#include <stdio.h>

int min3(int a, int b, int c) {
	if (a < b && a < c) return a;
	if (b < c) return b;
	return c;
}

int main() {
	int l, w, h;
	int tot = 0;
	while (scanf("%dx%dx%d\n", &l, &w, &h) != EOF) {
		//printf("%dx%dx%d\n", l, w, h);
		tot += 2*min3(l+w, l+h, w+h);
		tot += l*w*h;
	}
	printf("%d\n", tot);
	return 0;
}

