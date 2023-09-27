#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    unsigned vi;
    unsigned vj;
} edge_t;
edge_t edge(unsigned, unsigned);

typedef struct graph_t graph_t;
graph_t *graph_init(unsigned);
void graph_insert_e(graph_t *, edge_t);
void graph_remove_e(graph_t *, edge_t);
int graph_edges(edge_t *, graph_t *);
graph_t *graph_copy(graph_t *);
void graph_destroy(graph_t *);

#endif