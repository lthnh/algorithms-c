#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    unsigned n;
    printf("Number of edges: ");
    scanf("%u", &n);
    graph_t *g = graph_init(n);
    for (size_t i=0; i<(size_t)n; ++i) {
        unsigned u, w;
        scanf("%u %u", &u, &w);
        graph_insert_e(g, edge(u, w));
    }
    return EXIT_SUCCESS;
}