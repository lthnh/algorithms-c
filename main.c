#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    unsigned v, e;
    printf("Number of vertices: ");
    scanf("%u", &v);
    printf("Number of edges: ");
    scanf("%u", &e);
    graph_t *g = graph_init(v);
    for (size_t i=0; i<(size_t)e; ++i) {
        unsigned u, w;
        scanf("%u %u", &u, &w);
        graph_insert_edge(g, edge(u, w));
    }
    graph_show(g);
    graph_destroy(g);
    return EXIT_SUCCESS;
}