from itertools import permutations

edge_dict = {}
cities = set([])
f = open('input')
for line in f:
    parts = line.split(' ')
    edge_dict[(parts[0], parts[2])] = int(parts[4])
    edge_dict[(parts[2], parts[0])] = int(parts[4])
    cities.add(parts[0])
    cities.add(parts[2])

def calc_cities(cs):
    tot = 0
    for i in range(1, len(cs)):
        tot += edge_dict[(cs[i-1], cs[i])]
    return tot

min_dist = 0
for p in permutations(cities):
    dist = calc_cities(p)
    if dist > min_dist:
        min_dist = dist
print(min_dist)