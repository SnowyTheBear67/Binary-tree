// Lance Boza

#include <stdio.h>
#include <stdlib.h>

// binary tree node structure
struct Node {
	int data;
	struct Node * left;
	struct Node * right;
};

// helper function to create a new node with data as root
struct Node * createNode(int data){
	struct Node * temp;
	temp = malloc(sizeof(struct Node));
	temp -> data = data;
	temp -> left = NULL;
	temp -> right = NULL;

	return temp;
}

// function to add to leftIndex
void next(int * leftIndex){
	*leftIndex = *leftIndex + 1;
}

struct Node * makeTree(int low, int high, int preOrder[], int postOrder[], int size, int * leftIndex){
	int i;
	int count = low;

	// if the leftIndex (preOrder index) reaches the size of the array, then we have created nodes for every element
	// OR if the low is greater than the high (in the case of count and high being the same number in making a right subtree)
	if(low > high || *leftIndex >= size)
		return NULL;

	// creates new root using the leftIndex
	// leftIndex gives the NEXT element in the preOrder traversal
	// this element is the root of the left subtree of the root
	struct Node * root = createNode(preOrder[*leftIndex]);
	next(leftIndex);

	// counts and adds up the amount of numbers from low to high inclusive
	// to find the index of the left child of root (leftIndex) in postOrder
	for(i = low; i <= high; i++){
		if(postOrder[i] == preOrder[*leftIndex])
			break;
		count++;
	}

	// only recurses if the count (the index found in postOrder) not over the high bound
	if(count <= high){
	// recursing left first because we create the root node using leftIndex
	// breaks down the array recursively and goes from low to count to get
	// the indexes that belong in the left substree of the root
	root -> left = makeTree(low, count, preOrder, postOrder, size, leftIndex);
	// takes the right half of the array by getting count + 1 - high to
	// get the indexes that belong in the right subtree of the root
	root -> right = makeTree(count + 1, high, preOrder, postOrder, size, leftIndex);
	}

	return root;
}

// standard inOrder print function
void printInOrder (struct Node* temp){
    if (temp == NULL)
        return;
    printInOrder(temp -> left);
    printf("%d ", temp -> data);
    printInOrder(temp -> right);
}

int main(){
	int size, i;
	int leftIndex = 0;
	scanf("%d", &size);

	int preOrder[size];
	int postOrder[size];

	for(i = 0; i < size; i++)
		scanf("%d", &postOrder[i]);
	for(i = 0; i < size; i++)
		scanf("%d", &preOrder[i]);

	// approach is to create a full binary tree and then take the inOrder traversal to print
	struct Node * root = makeTree(0, size - 1, preOrder, postOrder, size, &leftIndex);
	printInOrder(root);
	printf("\n");
}
