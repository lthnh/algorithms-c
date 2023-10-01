#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    unsigned e;
    // printf("Number of vertices: ");
    // scanf("%u", &v);
    printf("Number of edges: ");
    scanf("%u", &e);
    edge_t *es = calloc(e, sizeof(edge_t));
    for (size_t i=0; i<e; ++i) {
        unsigned u, w;
        scanf("%u %u", &u, &w);
        es[i] = edge(u, w);
    }
    graph_t *g = graph_init_from_edges(es, e);
    graph_show(g);
    graph_destroy(g);
    return EXIT_SUCCESS;
}