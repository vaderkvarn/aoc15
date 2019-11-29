#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *name;
    int speed;
    int fly_time;
    int rest_time;
} Reindeer;

Reindeer reindeers[64];
size_t num_reindeers = 0;

int main() {
    char name[16];
    int speed, fly_time, rest_time;
    while(scanf("%s can fly %d km/s for %d seconds, but then must rest for %d seconds.\n", name, &speed, &fly_time, &rest_time) != EOF) {
        Reindeer r;
        r.name = malloc(16*sizeof(char));
        strcpy(r.name, name);
        r.speed = speed;
        r.fly_time = fly_time;
        r.rest_time = rest_time;
        reindeers[num_reindeers++] = r;
    }
    int duration = 2503;
    int max_dist = 0;
    for (int i = 0; i < num_reindeers; i++) {
        Reindeer r = reindeers[i];
        int dist = 0;
        bool flying = true;
        int cur_duration = 1;
        for (int j = 0; j < duration; j++, cur_duration++) {
            if (flying) {
                dist += r.speed;
                if (cur_duration == r.fly_time) {
                    flying = false;
                    cur_duration = 0;
                }
            } else {
                if (cur_duration == r.rest_time) {
                    flying = true;
                    cur_duration = 0;
                }
            }
        }
        if (dist > max_dist) {
            max_dist = dist;
        }
    }
    printf("%d\n", max_dist);
    return 0;
}