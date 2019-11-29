#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

typedef struct {
    char *name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
} Ingredient;

Ingredient ingredents[8];
size_t num_ingredients = 0;

int getTot(int *amounts) {
    int tot = 0;
    for (int i = 0; i < num_ingredients; i++) {
        tot += amounts[i];
    }
    return tot;
}

int *combs[200000];
size_t num_combs = 0;
void getCombinations(int *amounts, int i) {
    int tot = getTot(amounts);
    if (tot == 100) {
        combs[num_combs++] = amounts;        
        return;
    }
    for (int j = 0; j <= 100; j++) {
        int t = getTot(amounts);
        t += j;
        t -= amounts[i];
        if (t > 100) {
            return;
        }
        int *a = calloc(num_ingredients, sizeof(int));
        for (int k = 0; k < num_ingredients; k++) {
            a[k] = amounts[k];
        }
        a[i] = j;
        if (i < num_ingredients)
            getCombinations(a, i + 1);
        else {
            free(a);
        }

    }
    free(amounts);
}

uint64_t calcValue(int *comb) {
    int capacity = 0, durability = 0, flavor = 0, texture = 0;
    for (int i = 0; i < num_ingredients; i++) {
        capacity += comb[i]*ingredents[i].capacity;
        durability += comb[i]*ingredents[i].durability;
        flavor += comb[i]*ingredents[i].flavor;
        texture += comb[i]*ingredents[i].texture;
    }
    if (capacity < 0 || durability < 0 || flavor < 0 || texture < 0) return 0;
    return capacity*durability*flavor*texture;
}

int main() {
    char name[32];
    int capacity, durability, flavor, texture, calories; 
    while (scanf("%s capacity %d, durability %d, flavor %d, texture %d, calories %d",
    name, &capacity, &durability, &flavor, &texture, &calories) != EOF) {
        Ingredient i;
        i.name = malloc(32*sizeof(char));
        strcpy(i.name, name);
        i.capacity = capacity;
        i.durability = durability;
        i.flavor = flavor;
        i.texture = texture;
        i.calories = calories;
        ingredents[num_ingredients++] = i;
    }
    int *amounts = calloc(num_ingredients, sizeof(int)); 
    getCombinations(amounts, 0);
    uint64_t max_value = 0;

    for (int i = 0; i < num_combs; i++) {
        uint64_t value = calcValue(combs[i]);
        if (value > max_value ) {
            max_value = value;
        }
    }
    printf("%ld\n", max_value);
    return 0;
}