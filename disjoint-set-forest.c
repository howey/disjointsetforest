#include <stdio.h>

#define MAX_SET_SIZE 10 

typedef struct {
	int parent[MAX_SET_SIZE];
	int rank[MAX_SET_SIZE];
} Forest;

//Adds the set {i} to the collection of sets in the forest f
void makeSet(Forest * f, int i) {
	f->parent[i] = i;
}

//Gets the representative of the element i in the forest f. If two elements return the same value in findSet, they are in the same set
int findSet(Forest * f, int i) {
	if(f->parent[i] != i)
		f->parent[i] = findSet(f, f->parent[i]); //path compression, speed up future findSets 
	return f->parent[i];
}

//Merges the sets containing the elements i and j
void makeUnion(Forest * f, int i, int j) {
	int x = findSet(f, i);
	int y = findSet(f, j);
	if(x == y)
		return; //i and j are already in the same set
	if(f->rank[x] > f->rank[y]) //union by rank, make the root of the tree of lower height point to the root of the tree with higher height 
		f->parent[y] = x;
	else {
		f->parent[x] = y;
		if(f->rank[x] == f->rank[y])
			++f->rank[y];
	}
}

void printSet(Forest * f) {
	int i = 0;
	for(i = 0; i < MAX_SET_SIZE; i++) {
		printf("%d ", f->parent[i]);
	}
	printf("\n");
	for(i = 0; i < MAX_SET_SIZE; i++) {
		printf("%d ", f->rank[i]);
	}
	printf("\n");

}

int main() {
	Forest someSet = {{0}, {0}};
	Forest * f = &someSet;
	makeSet(f, 1);
	makeSet(f, 2);
	makeSet(f, 3);
	printf("are 1 and 3 in the same set? %s\n", findSet(f, 1) == findSet(f, 3) ? "yes" : "no");
	printf("makeUnion(f, 1, 3)\n");
	makeUnion(f, 1, 3);
	printf("are 1 and 3 in the same set? %s\n", findSet(f, 1) == findSet(f, 3) ? "yes" : "no");
	printSet(f);
	return 0;
}
