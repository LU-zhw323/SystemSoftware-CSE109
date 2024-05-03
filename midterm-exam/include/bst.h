

typedef struct Node{
  void* item;
  struct Node** nodes;
  struct Node* left;
  struct Node* right;
}Node;//I use left and right to replace Node array, which would be more readable

typedef struct BST{
  Node* tree_root;
  int depth;
  int item_size;
}BST;

void initBinaryTree(BST* bst, int item_size);
int insertItem(BST* bst, void* item);
void* findItem(BST* bst, void* query);
void* removeItem(BST* bst, void* query);
void freeNodes(BST* bst);
void free_tree(Node* node);
void rebalanceTree(BST* bst);
Node* rebalance(void** BSTlist, int start, int end);
int Inorder(Node* node, void** BSTlist, int count);
void printTree(BST* bst);
void Preorder(Node* node);
int CountNode(Node* node);
int compareInt(void* target, void* current);
int compareChar(void* target, void* current);
int compareString(void* target, void* current);

