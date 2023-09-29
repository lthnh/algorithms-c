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
graph_t *graph_init_from_edges(edge_t *restrict, size_t);
void graph_insert_edge(graph_t *restrict, edge_t);
void graph_remove_edge(graph_t *restrict, edge_t);
unsigned graph_edges(edge_t *restrict, graph_t *restrict);
void graph_show(graph_t *restrict);
graph_t *graph_copy(graph_t *restrict);
void graph_destroy(graph_t *restrict);

#endif