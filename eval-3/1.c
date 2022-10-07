#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a
typedef struct node Node;

struct node {
  int value;
  struct node *left;
  struct node *right;
};

// b
typedef struct tree Tree;

struct tree {
  int size;
  Node *root;
};

// c
void binary_tree_add_node(Tree *tree, int value) {
  // null pointer check?
  if (!tree->root) {
    tree->root = malloc(sizeof(Node));
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->value = value;
    tree->size++;
    return;
  }

  Node *node = tree->root;
  int side = value < node->value; // 1 for left, 0 for right
  while (side ? node->left : node->right) {
    if (side) {
      node = node->left;
    } else {
      node = node->right;
    }

    side = value < node->value;
  }

  Node *new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  if (!node) {
    tree->root = new_node;
  } else if (side) {
    node->left = new_node;
  } else {
    node->right = new_node;
  }

  tree->size++;
}

// d
Tree *binary_tree_from_array(int values[], int size) {
  Tree *tree = malloc(sizeof(Tree));
  tree->size = 0;
  tree->root = NULL;

  for (int i = 0; i < size; i++) {
    binary_tree_add_node(tree, values[i]);
  }
  return tree;
}

// e
int binary_tree_remove_node(Tree *tree, int value) {
  if (!tree) {
    return 0;
  }

  Node *node = tree->root;
  int side = value < node->value;
  while ((side ? node->left : node->right)->value != value) {
    if (side) {
      node = node->left;
    } else {
      node = node->right;
    }

    side = value < node->value;

    if ((side && !node->left) || (!side && !node->right)) {
      return 0;
    }
  }

  Node *matching_node = side ? node->left : node->right;

  if (!matching_node->left && !matching_node->right) {
    // the matching node has no children
    if (side) {
      node->left = NULL;
    } else {
      node->right = NULL;
    }
  } else if (!matching_node->left) {
    // the matching node has one child on the right
    if (side) {
      node->left = matching_node->right;
    } else {
      node->right = matching_node->right;
    }
  } else {
    // the matching node has one child on the left, or a child on
    // the left and right.
    if (side) {
      node->left = matching_node->left;
    } else {
      node->right = matching_node->left;
    }

    if (matching_node->right) {
      // then, matching_node->right needs to be added to the tree,
      // we will just add it the same way we would add a new node.
      // but based on node->right for a slight performance improvement
      // from starting at the root.
      side = 0;
      while (side ? node->left : node->right) {
        if (side) {
          node = node->left;
        } else { // no duplicates, so safe to assume value != node->value
          node = node->right;
        }

        side = value < node->value;
      }

      if (side) {
        node->left = matching_node->right;
      } else {
        node->right = matching_node->right;
      }
    }
  }

  free(matching_node);
  tree->size--;
  return 1;
}

// f
void binary_tree_free_node(Node *node) {
  if (!node) {
    return;
  }

  binary_tree_free_node(node->left);
  binary_tree_free_node(node->right);
  free(node);
}

void binary_tree_free(Tree *tree) {
  binary_tree_free_node(tree->root);
  free(tree);
}

// testing
void binary_tree_print_node(Node *node, int indent) {
  for (int i = 0; i < indent; i++) {
    printf(" |");
  }

  if (!node) {
    printf("\n");
    return;
  }

  printf("%d\n", node->value);

  indent++;
  if ((node->left && node->right) || node->right) {
    binary_tree_print_node(node->left, indent);
    binary_tree_print_node(node->right, indent);
  } else if (node->left) {
    binary_tree_print_node(node->left, indent);
  }
}

void binary_tree_print(Tree *tree) {
  printf("size: %d\n", tree->size);
  binary_tree_print_node(tree->root, 0);
}

int main() {
  int array[] = {51, 31, 88, 9,  92, 95, 44, 23, 32, 60, 55,
                 96, 78, 14, 73, 37, 33, 22, 71, 97, 36};
  Tree *tree = binary_tree_from_array(array, 21);

  printf("base tree\n");
  binary_tree_print(tree);

  binary_tree_add_node(tree, 50);
  printf("\n+50\n");
  binary_tree_print(tree);

  binary_tree_add_node(tree, 70);
  printf("\n+70\n");
  binary_tree_print(tree);

  binary_tree_remove_node(tree, 37);
  printf("\n-37\n");
  binary_tree_print(tree);

  binary_tree_remove_node(tree, 36);
  printf("\n-36\n");
  binary_tree_print(tree);

  binary_tree_remove_node(tree, 31);
  printf("\n-31\n");
  binary_tree_print(tree);

  binary_tree_free(tree);
}
