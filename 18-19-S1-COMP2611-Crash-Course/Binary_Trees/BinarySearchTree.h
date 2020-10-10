// Think about this like a linked list
BTNode * min(BTNode * root) {
	BTNode* current = root;

	if(current == NULL)					// empty
		return current;

	while (current->left != NULL) {		// go all the way to the left
		current = current->left;
	}

	return current;
}


// Think about this like a linked list
BTNode * max(BTNode * root) {
	BTNode* current = root;

	if(current == NULL)					// empty
		return current;

	while (current->right != NULL) {	// go all the way to the right
		current = current->right;
	}

	return current;
}


BTNode * ceiling(BTNode * root, string key) {
	return NULL;
}


bool isBST(BTNode *root){
	if(root == NULL)												// if the tree is empty
		return true;
	if(root->left != NULL && max(root->left)->data > root->data)	// max value of left subtree must be less than root value, if not then not a BST
		return false;
	if(root->right != NULL && min(root->right)->data < root->data)	// min value of right subtree must be more than root value, if not then not a BST
		return false;
	if(!isBST(root->left) || !isBST(root->right))					// recur down the tree
		return false;
	return true;													// is BST
}


// returns NULL, LEAF POINTERS, and SUBTREE POINTERS
BTNode * search(BTNode * root, string key) {

	if(root == NULL || root->data == key)		// (BASE CASES) CASE 1: the tree at root is empty, CASE 2: the root node contains key
		return root;

	if(key < root->data) 						// CASE 3: the key may be in the left subtree
		return search(root->left, key);

	else 										// CASE 4: the key may be in the right subtree
		return search(root->right, key);

}


// returns NULL, LEAF POINTERS, and SUBTREE POINTERS
BTNode * deleteNode(BTNode * root, string key) {

	if(root == NULL)												// CASE 0: Node doesn't exist in tree
		return root;

																	// search for node
	if(key < root->data){											// CASE: key might be in the left subtree
		BTNode *leftChildSubtree = deleteNode(root->left, key); 			// recur down the left subtree and catch whatever it returns (either the newNode or a subtree at root)
		root->left = leftChildSubtree;										// set the left subtree at root
		if(leftChildSubtree != NULL)
			leftChildSubtree->parent = root;								// set parent of leftChildSubtree
	}
	else if(key > root->data){										// CASE: key might be in the right subtree
		BTNode *rightChildSubtree = deleteNode(root->right, key); 			// recur down the right subtree and catch whatever it returns (either the newNode or a subtree at root)
		root->right = rightChildSubtree;									// set the right subtree at root
		if(rightChildSubtree != NULL)
			rightChildSubtree->parent = root;								// set parent of rightChildSubtree
	}
	else{															// we have found the node
																	// CASE 1 and 2: node is leaf or has 1 child
		if (root->left == NULL){											// we have a right leaf
            BTNode *rightLeaf = root->right;
            delete root;
            return rightLeaf;
        }
        else if (root->right == NULL){										// we have a left leaf
            BTNode *leftLeaf = root->left;
            delete root;
            return leftLeaf;
        }

		else{														// CASE 3: Node has 2 children
			BTNode* inOrderSuccessor = min(root->right); 				// get the inOrderSuccessor (min value in the right subtree)
			root->data = inOrderSuccessor->data;							// put inOrderSuccessor value in the
			root->right = deleteNode(root->right, inOrderSuccessor->data);	// delete inOrderSuccessor
		}

	}

	return root;

}


BTNode * floor(BTNode * root, string key) {
	return NULL;
}


BTNode * inOrderPredecessor (BTNode * node) {
	return NULL;
}


BTNode * inOrderSuccessor (BTNode * node) {
	return NULL;
}


struct BTNode * inOrderSuccessor_G4G(struct BTNode *root, struct node *n)
{
  // step 1 of the above algorithm
  if( n->right != NULL )					// if we have a right subtree
    return min(n->right);						// the inOrderSuccessor is the smallest element in that right subtree

  // step 2 of the above algorithm
  struct BTNode *p = n->parent;
  while(p != NULL && n == p->right)			// while n has a parent AND n is a right child of that parent
  {
     n = p;
     p = p->parent;								// keep going up the tree
  }
  return p;									// stop when the node n is a left child of parent
}


// returns NULL, LEAF POINTERS, and SUBTREE POINTERS
BTNode * insert(BTNode * root, string key) {
	if(root == NULL) 												// CASE 1: we have reached an empty tree
		return createBTNode(key); 											// so insert here as a leaf

	if(key < root->data){											// CASE 2: key should be in the left subtree
		BTNode *leftChildSubtree = insert(root->left, key); 				// recur down the left subtree and catch whatever it returns (either the newNode or a subtree at root)
		root->left = leftChildSubtree;										// set the left subtree at root
		leftChildSubtree->parent = root;									// set parent of leftChildSubtree
	}
	if(key > root->data){											// CASE 3: key should be in the right subtree
		BTNode *rightChildSubtree = insert(root->right, key); 				// recur down the right subtree and catch whatever it returns (either the newNode or a subtree at root)
		root->right = rightChildSubtree;									// set the right subtree at root
		rightChildSubtree->parent = root;									// set parent of rightChildSubtree
	}

	return root;													// return the subtree at root
}


int range(BTNode * root, string low, string high) {
	return 0;
}


int rank(BTNode * root, string key) {
	return 0;
}
