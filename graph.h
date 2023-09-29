#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

typedef struct {
    unsigned vi;
    unsigned vj;
} edge_t;
edge_t edge(unsigned, unsigned);

typedef struct graph_t graph_t;
graph_t *graph_init(unsigned);
graph_t *graph_init_from_edges(edge_t *, size_t);
void graph_insert_edge(graph_t *, edge_t);
void graph_remove_edge(graph_t *, edge_t);
unsigned graph_edges(edge_t *, graph_t *);
void graph_show(graph_t *);
graph_t *graph_copy(graph_t *);
void graph_destroy(graph_t *);

#endif