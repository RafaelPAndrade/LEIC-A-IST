# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct node *link;

typedef char* Item;

struct node {
	Item item;
	link next;
};


Item newItem(char*);
link newNode(Item);
int itemCompare(Item, Item);
void showItem(Item);
void deleteItem(Item);


Item newItem(char* s){
	Item res = (Item) malloc( sizeof(char) * (strlen(s)+1) ) ;
	strcpy(res, s);
	return res;
}

link newNode(Item i){

	link res = (link) malloc( sizeof(struct node) );
	res->item= i;
	res->next= NULL;
	return res;
}

int itemCompare(Item i1, Item i2){
	return strcmp(i1, i2);
}

void showItem(Item i){

	printf("%s\n", i);
}

void deleteItem(Item i){

	free(i);
}



int main(){

	link a = newNode(newItem("Ola!"));
	Item b=newItem("Adeus...");
	showItem(a->item);
	printf("%d\n", itemCompare(a->item, b));
	deleteItem(b);
	deleteItem(a->item);
	free(a);
	return 0;
}
