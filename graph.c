#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include "mlib.h"
#include "graph.h"

struct graph_t {
    unsigned v;
    unsigned e;
    int **adj;
};

static int **matrix_init(size_t r, size_t c, int val) {
    int **m = calloc(r, sizeof(int *));
    MEM_ALLOC_ERR_CHCK(m);
    for (size_t i=0; i<r; ++i) {
        m[i] = calloc(c, sizeof(int));
        memset(m[i], val, c);
    }
    return m;
}

edge_t edge(unsigned i, unsigned j) {
    edge_t e;
    e.vi = i;
    e.vj = j;
    return e;
}

graph_t *graph_init(unsigned v) {
    graph_t *g = malloc(sizeof(graph_t));
    MEM_ALLOC_ERR_CHCK(g);
    g->v = v; g->e = 0;
    g->adj = matrix_init(v, v, 0);
    return g;
}

graph_t *graph_init_from_edges(edge_t *es, size_t e) {
    unsigned v = (unsigned)ceil(0.5 + sqrt(1.0 - 4.0*(-2.0*e))/2.0);
    graph_t *g = graph_init(v);
    g->e = e; g->v = v;
    for (size_t i=0; i<e; ++i)
        graph_insert_edge(g, es[i]);
    return g;
}

void graph_insert_edge(graph_t *restrict g, edge_t e) {
    int i = e.vi, j = e.vj;
    if (g->adj[i][j] == 0) ++g->e;
    g->adj[i][j] = 1;
    g->adj[j][i] = 1;
}

void graph_remove_edge(graph_t *restrict g, edge_t e) {
    int i = e.vi, j = e.vj;
    if (g->adj[i][j] == 1) --g->e;
    g->adj[i][j] = 0;
    g->adj[j][i] = 0;
}

int graph_edges(edge_t *restrict es, graph_t *restrict g) {
    size_t v = g->v, e = g->e, e_cnt = 0;
    if (es == NULL) {
        es = calloc(e, sizeof(edge_t));
        MEM_ALLOC_ERR_CHCK(es);
    }
    else {
        fprintf(stderr, "Pointer to edges array has not been initalized to NULL.");
        return EXIT_FAILURE;
    }
    for (size_t i=0; i<v; ++i)
        for (size_t j=0; j<v; ++j)
            if (g->adj[i][j] == 1)
                es[e_cnt++] = edge(i, j);
    return e_cnt;
}

void graph_show(graph_t *restrict g) {
    size_t v = g->v;
    for (size_t i=0; i<v; ++i) {
        printf("%zu ", i);
        for (size_t j=0; j<v; ++j)
            if (g->adj[i][j])
                printf("%zu ", j);
        printf("\n");
    }
}

graph_t *graph_copy(graph_t *restrict g) {
    graph_t *g_cp = malloc(sizeof(graph_t));
    MEM_ALLOC_ERR_CHCK(g_cp);
    *g_cp = *g;
    return g_cp;
};

void graph_destroy(graph_t *restrict g) {
    int v = g->v;
    for (size_t i=0; i<v; ++i)
        free(g->adj[i]);
    free(g);
}