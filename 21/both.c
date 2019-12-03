#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct {
    int hp;
    int dp;
    int ap;
} Player;

typedef struct {
    char *name;
    int cost;
    int dp;
    int ap;
} Item;

#define NUM_WEAPONS 5
Item weapons[] = {
    (Item){"Dagger",        8,     4,       0},
    (Item){"Shortsword",   10,     5,       0},
    (Item){"Warhammer",    25,     6,       0},
    (Item){"Longsword",    40,     7,       0},
    (Item){"Greataxe",     74,     8,       0}
};
#define NUM_ARMOR 5
Item armor[] = {
    (Item){"Leather",      13,     0,       1},
    (Item){"Chainmail",    31,     0,       2},
    (Item){"Splintmail",   53,     0,       3},
    (Item){"Bandedmail",   75,     0,       4},
    (Item){"Platemail",   102,     0,       5}
};
#define NUM_RINGS 6
Item rings[] = {
    (Item){"Damage_1",    25,     1,       0},
    (Item){"Damage_2",    50,     2,       0},
    (Item){"Damage_3",   100,     3,       0},
    (Item){"Defense_1",   20,     0,       1},
    (Item){"Defense_2",   40,     0,       2},
    (Item){"Defense_3",   80,     0,       3}
};

typedef struct {
    Item *weapon;
    Item *armor;
    Item *ring1;
    Item *ring2;
    int cost;
    int dp;
    int ap;
} Comb;

Item Empty = {
    "Empty", 0, 0, 0
};

Comb combs[NUM_WEAPONS*NUM_ARMOR*NUM_RINGS*NUM_RINGS];
size_t num_combs = 0;

int compCombs(const void *a, const void *b) {
    return ((Comb *)a)->cost - ((Comb *)b)->cost;
}

void initCombs() {
    for (int i = 0; i < NUM_WEAPONS; i++) {
        for (int j = 0; j < NUM_ARMOR + 1; j++) {
            for (int k = 0; k < NUM_RINGS + 1; k++) {
                for (int l = 0; l < NUM_RINGS + 1; l++) {
                    if (k == l && k < NUM_RINGS) continue;
                    if (l > k) continue;
                    Comb c;
                    c.weapon = &weapons[i];
                    c.armor = j == NUM_ARMOR ? &Empty : &armor[j];
                    c.ring1 = k == NUM_RINGS ? &Empty : &rings[k];
                    c.ring2 = l == NUM_RINGS ? &Empty : &rings[l];
                    c.cost = c.weapon->cost + c.armor->cost + c.ring1->cost + c.ring2->cost;
                    c.dp = c.weapon->dp + c.armor->dp + c.ring1->dp + c.ring2->dp;
                    c.ap = c.weapon->ap + c.armor->ap + c.ring1->ap + c.ring2->ap;
                    
                    combs[num_combs++] = c;
                }
            }
        }
    }
    qsort(combs, num_combs, sizeof(Comb), compCombs);
}

void attack(Player *p1, Player *p2) {
    p2->hp -= MAX(1, p1->dp - p2->ap);
}

bool play(Player p, Player b) {
    while (true) {
        attack(&p, &b);
        if (b.hp <= 0) {
            return true;
        } 
        attack(&b, &p);
        if (p.hp <= 0) {
            return false;
        }
    }
}

int main() {
    Player b = (Player) {100, 8, 2};
    initCombs();
    for (int i = 0; i < num_combs; i++) {
        Comb c = combs[i];
        Player p = (Player) {100, c.dp, c.ap};
        if (play(p, b)) {
            printf("%d\n", c.cost);
            break;
        }
    }
    for (int i = num_combs - 1; i >= 0; i--) {
        Comb c = combs[i];
        Player p = (Player) {100, c.dp, c.ap};
        if (!play(p, b)) {
            printf("%d\n", c.cost);
            break;
        }
    }
    return 0;
}