#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/param.h>
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

graph_t *graph_init_from_edges(edge_t *restrict es, size_t e) {
    unsigned v = 0;
    for (size_t i=0; i<e; ++i) {
        unsigned u = es[i].vi, w = es[i].vj;
        if (v<UINT_MAX)
            v = MAX(v, MAX(u, w));
        else {
            // fprintf(stderr, "Value for variable e is too large to be casted from size_t to unsigned.");
            // fprintf(stderr, "at %s, line %d.", __FILE__, __LINE__);
            // exit(EXIT_FAILURE);
            CUSTM_ERR_MSG("Value for variable e is too large to be casted from size_t to unsigned.");
        }
    }
    ++v;
    graph_t *g = graph_init(v);
    g->e = e; g->v = v;
    for (size_t i=0; i<e; ++i)
        graph_insert_edge(g, es[i]);
    return g;
}

void graph_insert_edge(graph_t *restrict g, edge_t e) {
    unsigned i = e.vi, j = e.vj;
    if (g->adj[i][j] == 0) ++g->e;
    g->adj[i][j] = 1;
    g->adj[j][i] = 1;
}

void graph_remove_edge(graph_t *restrict g, edge_t e) {
    unsigned i = e.vi, j = e.vj;
    if (g->adj[i][j] == 1) --g->e;
    g->adj[i][j] = 0;
    g->adj[j][i] = 0;
}

unsigned graph_edges(edge_t **restrict es, graph_t *restrict g) {
    unsigned v = g->v, e = g->e, e_cnt = 0;
    *es = calloc(e, sizeof(edge_t));
    MEM_ALLOC_ERR_CHCK(es);
    for (size_t i=0; i<v; ++i)
        for (size_t j=0; j<v; ++j)
            if (g->adj[i][j] == 1)
                (*es)[e_cnt++] = edge(i, j);
    return e_cnt;
}

void graph_show(graph_t *restrict g) {
    edge_t *es = NULL;
    unsigned e = graph_edges(&es, g);
    if (e > 0) {
        for (size_t i=0; i<e; ++i)
            printf("%u - %u\n", es[i].vi, es[i].vj);
    }
    free(es);
}

graph_t *graph_copy(graph_t *restrict g) {
    graph_t *g_cp = malloc(sizeof(graph_t));
    MEM_ALLOC_ERR_CHCK(g_cp);
    *g_cp = *g;
    return g_cp;
};

void graph_destroy(graph_t *restrict g) {
    unsigned v = g->v;
    for (size_t i=0; i<v; ++i)
        free(g->adj[i]);
    free(g);
}