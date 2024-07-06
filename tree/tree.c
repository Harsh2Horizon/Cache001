#include "tree.h"


Tree root = {
	.n = {
	.tag = (TagRoot | TagNode),
	.north = (Node *) &root,
	.west = 0,
	.east = 0,
	.path = "/"
	}
};


void zero(int8* str , int16 size){
	int8 *p;
	int16 n;

	for(n=0 ,p=str ; n < size ; p++,n++){
		*p = 0;
	}
}


Node* create_node(Node* parent , int8* path ){
	Node* n;
	int16 size;

	assert(parent);
	size = sizeof(struct s_node);

	n = (Node *)malloc(size);
	zero((int8 *)n , (int)size);

	parent->west = n ;
	n->tag = TagNode;
	n->north = parent;
	strncpy((char *)n->path , (char*) path, 255);

	return n;
}


Leaf* find_last_linear(Node* parent){
	assert(parent);
	Leaf* l;

	
	if(!parent->east)
		return NULL;
	
	for(l=parent->east ; l->east ; l = l->east );

	return l;
}

Leaf* create_leaf(Node* parent,  int8* key ,int8* value ,  int16 count ){
	Leaf *l,*new ;
	//Node* n;

	int16 size ;


	assert(parent);
	l = find_last(parent);

	size = sizeof(struct s_leaf);
	new = (Leaf*) malloc(size);
	assert(new);

	if(!l)
		parent->east = new;
	else
		l->east = new;

	zero((int8*) new ,size);

	new->tag = TagLeaf;
	new->west = (!l) ? (Tree*) parent : (Tree*) l ;
	strncpy((char*) new->key , (char*) key , 127) ;

	new->value = (int8*) malloc(count);
	zero(new->value,count);

	strncpy((char*)new->value , (char*)value , count);
	new->size = count ;

	return new;
}


int main(){

	Node* n = create_node((Node*) &root, (int8* )"/Users");
	assert(n);
	Node* n2 = create_node(n , (int8* )"/Users/login");
	assert(n2);

	Leaf *l1 , *l2 ;
	int8 *key , *value;
	int16 size;


	key = (int8*)"Harsh";
	value = (int8*) "pqc123211" ;
	size = (int16) strlen((char*) value);
	l1 = create_leaf(n2,key,value,size);
	assert(l1);

	printf("%s\n" , l1->value);


	key = (int8*)"aj";
	value = (int8*)"sadasdad";
	size = (int16) strlen((char*) value);
	l2 = create_leaf(n2,key,value,size);

	assert(l2);

	printf("%s\n" , l2->value);

 

	printf("%p %p\n" , n,n2);
	free(n2);
	free(n);

	return 0;


}