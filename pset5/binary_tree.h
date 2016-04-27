#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct tree_node
{
  int data;
  struct tree_node* left;
  struct tree_node* right;
} tree_node;

tree_node* allocate_tree_node(int data);
tree_node* add_tree_node(tree_node* root, int data);

#endif