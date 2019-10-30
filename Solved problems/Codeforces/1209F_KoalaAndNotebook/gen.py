import random

N = 20
M = 30

nodes = list(range(1,N+1))
random.shuffle(nodes)
edges = []
edge_set = set()
for i in range(1, N):
    u = nodes[random.randint(0, i-1)]
    v = nodes[i]
    if random.random() <= 0.5:
        u,v = v,u
    edges.append((u,v))
    edge_set.add((u,v))
    edge_set.add((v,u))

while len(edges) < M:
    u, v = random.sample(nodes, 2)
    e1 = (u,v)
    e2 = (v,u)
    if e1 in edge_set: continue
    edges.append(e1)
    edge_set.add(e1)
    edge_set.add(e2)

random.shuffle(edges)
print(N, M)
for e in edges: print(e[0], e[1])