struct BSTNode{
    char name[MAX_CHAR_PER_WORD];
    struct BSTNode *left, *right;
};


// makes a new BSTNode
struct BSTNode *newBSTNode(char name[]){
    struct BSTNode *newNode = (struct BSTNode *) malloc(sizeof(struct BSTNode));
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}


// inserts a new node inorder
struct BSTNode *insertBSTNodeInOrder(struct BSTNode *node, char name[]){

    // if tree is empty
    if(node == NULL) return newBSTNode(name);

    // if name < node
    if(strcmp(name, node->name) < 0) node->left = insertBSTNodeInOrder(node->left, name);

    // else name > node
    else if(strcmp(name, node->name) > 0) node->right = insertBSTNodeInOrder(node->right, name);

    // else return the unchanged node
    return node;

}


// prints inorder traveral of the BST
void printInOrderBSTTraversal(struct BSTNode *root){
    if(root == NULL) return;
    printInOrderBSTTraversal(root->left);
    printf("%s   ", root->name);
    printInOrderBSTTraversal(root->right);
}


// reads from the file and makes the BST
struct BSTNode *makeBSTOfNodeNames(FILE **fin){

    // makes the root
    struct BSTNode *root = NULL;

    // gets words from the FILE
    char name[MAX_CHAR_PER_WORD+1];
    fscanf(*fin, "%s", name);
    capitalize(name);
    while(strcmp(name, FILE_SENTINEL) != 0){
        root = insertBSTNodeInOrder(root, name);    // inserts name in the BST
        fscanf(*fin, "%s", name);
        capitalize(name);
    }

    // testing with an inorder traversal
    // printInOrderBSTTraversal(root);

    return root;

}


// counts nodes in a BST
int getNumBSTNodes(struct BSTNode *root){
    if(root == NULL) return 0;
    return 1 + getNumBSTNodes(root->left) + getNumBSTNodes(root->right);
}
