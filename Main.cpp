#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RBTree.h"

int main(){

	RBTree *rbtree = new RBTree();
	rbtree->insert(10);
	rbtree->insert(5);
	rbtree->insert(12);
	rbtree->insert(7);
	rbtree->insert(11);
	rbtree->print(rbtree->getRoot());
	rbtree->remove(12);

	printf("Apos a removao p/ testar Transplante:\n");

	rbtree->print(rbtree->getRoot());
	 
	delete  rbtree;

	return 0;
}
