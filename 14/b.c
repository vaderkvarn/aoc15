#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *name;
    int speed;
    int fly_time;
    int rest_time;
    int *secs;
    int score;
} Reindeer;

Reindeer reindeers[64];
size_t num_reindeers = 0;

int main() {
    int duration = 2503;
    char name[16];
    int speed, fly_time, rest_time;
    while(scanf("%s can fly %d km/s for %d seconds, but then must rest for %d seconds.\n", name, &speed, &fly_time, &rest_time) != EOF) {
        Reindeer r;
        r.name = malloc(16*sizeof(char));
        strcpy(r.name, name);
        r.speed = speed;
        r.fly_time = fly_time;
        r.rest_time = rest_time;
        r.secs = malloc(duration*sizeof(int));
        r.score = 0;
        reindeers[num_reindeers++] = r;
    }
    for (int i = 0; i < num_reindeers; i++) {
        Reindeer r = reindeers[i];
        int dist = 0;
        bool flying = true;
        int cur_duration = 0;
        for (int j = 0; j < duration; j++) {
            cur_duration++;
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
            r.secs[j] = dist;
        }
    }

    for (int i = 0; i < duration; i++) {
        int sec_max = 0;
        for (int j = 0; j < num_reindeers; j++) {
            if (reindeers[j].secs[i] > sec_max) {
                sec_max = reindeers[j].secs[i];
            }
        }
        for (int j = 0; j < num_reindeers; j++) {
            if (reindeers[j].secs[i] == sec_max) {
                reindeers[j].score++;
            }
        }

    }
    int max_score = 0;

    for (int j = 0; j < num_reindeers; j++) {
        if (reindeers[j].score > max_score) {
            max_score = reindeers[j].score;
        }
    }
    printf("%d\n", max_score);
    return 0;
}