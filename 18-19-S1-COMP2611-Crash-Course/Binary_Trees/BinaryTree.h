BTNode * createBTNode (string data) {
	BTNode * newNode;

	newNode = new BTNode;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;

}


void visitNode (BTNode * btNode) {
	cout << btNode->data << " ";
}


int height (BTNode * root) {
	if(root == NULL)											// tree is empty
		return 0;
	return 1 + max(height(root->left), height(root->right));	// recur down the tree, finding the height of left and right and take the bigger
}


void inOrderIterative(BTNode * root) {

}


void inOrderRecursive(BTNode *root){
	if(root == NULL) return;
	inOrderRecursive(root->left);
	visitNode(root);
	inOrderRecursive(root->right);
}


bool isEmptyTree (BTNode * root) {
	return true;
}


bool isEqual (BTNode * root1, BTNode * root2) {
	return false;
}


void levelOrder (BTNode * root) {
}


int moment(BTNode * root) {
	return 0;
}


// same as height
int numLevels(BTNode * root) {
	return 0;
}


void preOrderIterative (BTNode * root) {
}


void postOrderIterative (BTNode * root) {
}


int weight(BTNode * root) {
	return 0;
}


int width(BTNode * root) {
	return 0;
}
