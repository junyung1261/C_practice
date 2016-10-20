#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX 9999
#define NODES 7

int cost[NODES][NODES] = {
	{ 0,    7,     MAX,   MAX,   3,     10,    MAX },
	{ 7,    0,       4,   10,    2,     6,     MAX },
	{ MAX,  4,       0,   2,     MAX,   MAX,   MAX },
	{ MAX,  10,      2,   0,     11,    9,     4 },
	{ 3,    2,     MAX,   11,    0,     MAX,   5 },
	{ 10,   6,     MAX,   9,     MAX,   0,     MAX },
	{ MAX,  MAX,   MAX,   4,     5,     MAX,   0 }
};


int distance[NODES];		/* 시작노드로부터의 최단경로 거리 */
int path[NODES];			/* 경유 노드  */
int visit[NODES];			/* 방문한 노드 표시 */

void dijkstra_run(int start) {
	int i, j, k;
	int min, min_index;
	for (i = 0; i < NODES; i++) {
		distance[i] = cost[start][i];
		path[i] = start;
		visit[i] = FALSE;
	}
	distance[start] = 0;
	visit[start] = TRUE;

	for (i = 0; i < NODES; i++) {
		min = MAX;
		for (j = 0; j < NODES; j++) {
			if (distance[j] < min && !visit[j]) {
				min = distance[j];
				min_index = j;
			}
		}
		visit[min_index] = TRUE;

		for (k = 0; k < NODES; k++) {
			if (distance[k] > distance[min_index] + cost[min_index][k]) {
				distance[k] = distance[min_index] + cost[min_index][k];
				path[k] = min_index;
			}
		}
	}

}


void print_path(int start, int end)
{
	if (path[end] != start)
		print_path(start, path[end]);
	printf("\t<%d->%d> \n ", path[end], end);

}

void main() {

	dijkstra_run(2);

	print_path(2, 6);

}