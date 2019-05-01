// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// code for SIR on networks by Petter Holme (2018)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "sir.h"

extern NODE *n;
extern GLOBALS g;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// reads the network, assumes an edge list with vertex label 0,N-1
// if your network has nodes with degree zero, make sure that none of them is
// the node with largest index
int GetRandom(int min, int max) {
    float my_rand = min + rand()*(1.0)/(1.0+RAND_MAX);

    if(my_rand < g.coverage){
        printf("returning 1 because %f\n", my_rand);
        return 1;
    }

    else{
        printf("returning 0 because %f\n", my_rand);
        return 0;
    }
    //return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void read_data (FILE *fp) {
	unsigned int i, me, you;

    g.n = 0;

	// scan the system size
	while (2 == fscanf(fp, "%u %u\n", &me, &you)) {
		if (g.n < me) g.n = me;
		if (g.n < you) g.n = you;
	}

	g.n++;

	n = calloc(g.n, sizeof(NODE));

	rewind(fp);

	int count = 0;

	for(i = 0; i < g.n; i++){
	    n[i].immunity = GetRandom(0, 1);
	    count += n[i].immunity;
	}

	//float result = count/g.n;
    printf("count = %d\n", count);

	// scan the degrees
	while (2 == fscanf(fp, "%u %u\n", &me, &you)) {
		n[me].deg++;
		n[you].deg++;
	}

	// allocate adjacency lists
	for (i = 0; i < g.n; i++) {
		n[i].nb = malloc(n[i].deg * sizeof(unsigned int));
		n[i].deg = 0;
	}

	rewind(fp);

	// fill adjacency lists
	while (2 == fscanf(fp, "%u %u\n", &me, &you)) {
		n[me].nb[n[me].deg++] = you;
		n[you].nb[n[you].deg++] = me;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
