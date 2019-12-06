#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct {
    int id;
    char *name;
    int cost;
    bool instant;
    int time;
    int dp;
    int hp; 
    int ap;
    int mp;
} Spell;

typedef struct {
    Spell *spell;
    int time;
    bool active;
} ActiveSpell;

enum SpellId {
    MAGIC_MISSILE = 0,
    DRAIN,
    SHEILD,
    POISON,
    RECHARGE
};

#define NUM_SPELLS 5
Spell spells[] = {
    (Spell){0, "Magic Missile",    53,     true,  0, 4, 0, 0, 0    },
    (Spell){1, "Drain",            73,     true,  0, 2, 2, 0, 0    },
    (Spell){2, "Sheild",           113,    false, 6, 0, 0, 7, 0    },
    (Spell){3, "Poison",           173,    false, 6, 3, 0, 0, 0    },
    (Spell){4, "Recharge",         229,    false, 5, 0, 0, 0, 101  }
};


typedef struct {
    int hp;
    int ap;
    int mp;
} Player;

typedef struct {
    int hp;
    int dp;
} Boss;


void useEffect(ActiveSpell *active_spells, size_t num_active_spells, Player *p, Boss *b) {
    for (int i = 0; i < num_active_spells; i++) {
        ActiveSpell as = active_spells[i];
        if (as.active) {
            if (as.spell->id == SHEILD) {
                p->ap = as.spell->ap;
            }
            b->hp -= as.spell->dp;
            p->mp += as.spell->mp;
            active_spells[i].time--;
            if (active_spells[i].time == 0) {
                active_spells[i].active = false;
                if (as.spell->id == SHEILD) {
                    p->ap = 0;
                }
            }
        }
    }
}

long random_at_most(long max) {
    unsigned long
        num_bins = (unsigned long) max + 1,
        num_rand = (unsigned long) RAND_MAX + 1,
        bin_size = num_rand / num_bins,
        defect   = num_rand % num_bins;

    long x;
    do {
        x = random();
    }
    while (num_rand - defect <= (unsigned long)x);

    return x/bin_size;
}

Spell *getSpell(ActiveSpell *active_spells, size_t *num_active_spells, Player *p) {
    Spell *spell;
    bool is_active;
    long idx;
    do {
        idx = random_at_most(NUM_SPELLS - 1);
        spell = &spells[idx];
        is_active = false;
        for (int i = 0; i < *num_active_spells; i++) {
            if (spell->id == active_spells[i].spell->id && active_spells[i].active) {
                is_active = true;
                break;
            }
        } 
    } while (is_active);
    ActiveSpell as;
    as.spell = spell;
    if (!spell->instant) {
        as.active = true;
        as.time = spell->time;
        active_spells[(*num_active_spells)++] = as; 
    }
    return spell;

}


int min_mana_used = 9999999;

void player_won(int mana_used) {
    if (mana_used < min_mana_used) {
        min_mana_used = mana_used;
        printf("%d\n", mana_used);
    }
}

bool play(Player p, Boss b) {
    ActiveSpell *active_spells = malloc(256*sizeof(ActiveSpell));
    size_t num_active_spells = 0;
    int mana_used = 0;
    while (true) {
        p.hp--;
        if (p.hp <= 0) {
            free(active_spells);
            return false;
        }
        useEffect(active_spells, num_active_spells, &p, &b);
        Spell *spell = getSpell(active_spells, &num_active_spells, &p);
        p.mp -= spell->cost;
        mana_used += spell->cost;
        if (p.mp < 0) {
            free(active_spells);
            return false;
        }
        if (spell->instant) {
            b.hp -= spell->dp;
            p.hp += spell->hp;
        }
        if (b.hp <= 0) {
            player_won(mana_used);
            free(active_spells);
            return true;
        } 
        useEffect(active_spells, num_active_spells, &p, &b);
        if (b.hp <= 0) {
            player_won(mana_used);
            free(active_spells);
            return true;
        } 
        p.hp -= MAX(1, b.dp - p.ap);
        if (p.hp <= 0) {
            free(active_spells);
            return false;
        }
    }
}

int main() {
    srand(time(NULL));
    while (true) {
        Player p = (Player) {50, 0, 500};
        Boss b = (Boss) {71, 10};
        play(p, b);
    }

    return 0;
}

