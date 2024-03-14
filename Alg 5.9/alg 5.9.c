#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int element;
	int height;
	struct tree_t* left;// лево = ментше число
	struct tree_t* right;//право = больше число
}tree_t;

void print_tree(tree_t* tree) {
	if (tree == NULL) return;
	print_tree(tree->left);
	printf("%i ", tree->element);
	print_tree(tree->right);
}

void processing_even_number(int* massive, int size, tree_t* head) {
	for (int i = 0; i < size; i++) {
		if (massive[i] == 1) {
			print_tree(head->left);
			printf("%i ", head->element);
			head = head->right;
		}
		else head = head->left;
	}
	printf("\n");
}

void search(tree_t* tree, int k, int* size_massive, int** massive, tree_t* original) {
	tree_t* tmp_left = tree->left;
	tree_t* tmp_right = tree->right;
	if (tmp_left != NULL) {
		if (k > tmp_left->height + 1) {//+1 в условии т к плюс первый элемент это корень, который сейчас смотрю 
			*size_massive += 1;		
			(*massive) = realloc((*massive), (*size_massive) * sizeof(int));
			(*massive)[*size_massive - 1] = 1;//1 - сместился в правое поддерево, 0 - в левое
			search(tree->right, k - tmp_left->height - 1, size_massive, massive, original);
		}
		else if (k <= tmp_left->height) {
			*size_massive += 1;
			(*massive) = realloc((*massive), (*size_massive) * sizeof(int));
			(*massive)[*size_massive - 1] = 0;
			search(tree->left, k, size_massive, massive, original);
		}
		else {
			printf("%i is K smallest\n", tree->element);
			if (tree->element % 2 == 0) {
				*size_massive += 1;
				(*massive) = realloc((*massive), (*size_massive) * sizeof(int));
				(*massive)[*size_massive - 1] = 1;
				processing_even_number(*massive, *size_massive, original);
			}
			return;
		}
	}
	else if (tmp_right != NULL && k > 1) {//1 в учловии т к 1 это номер наименьшего элемента в этом поддереве, k - 1 т к в новом поддереве ищется k - 1 по размеру элемент
		*size_massive += 1;
		(*massive) = realloc((*massive), (*size_massive) * sizeof(int));
		(*massive)[*size_massive - 1] = 1;
		search(tree->right, k - 1, size_massive, massive, original);
	}
	else {
		printf("%i is K smallest\n", tree->element);
		if (tree->element % 2 == 0) {
			*size_massive += 1;
			(*massive) = realloc((*massive), (*size_massive) * sizeof(int));
			(*massive)[*size_massive - 1] = 1;
			processing_even_number(*massive, *size_massive, original);
		}
		return;
	}
}

void create_tree_from_massive(tree_t** tree, int* massive, int size) {
	tree_t** head = tree;
	for (int i = 0; i < size; i++) {
		while ((*tree) != NULL) {
			if (massive[i] >= (*tree)->element) {
				(*tree)->height += 1;
				tree = &((*tree)->right);
			}
			else {
				(*tree)->height += 1;
				tree = &((*tree)->left);
			}
		}
		(*tree) = malloc(sizeof(tree));
		(*tree)->element = massive[i];
		(*tree)->height = 1;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		tree = head;
	}
}

void main() {
	int size = 11;
	int massive[11] = { 13, 2, 26, 20, 37, 12, 25, 10, 11, 1, 38};// размера size
	tree_t* tree = NULL;
	create_tree_from_massive(&tree, massive, size);
	int tmp_size = 0;
	int* massive_tree = NULL;
	int k = 5;
	search(tree, k, &tmp_size, &massive_tree, tree);
}