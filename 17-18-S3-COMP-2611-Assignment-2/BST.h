// BST defintion for a name in a team
struct BSTNode{
    char name[MAX_NAME_LENGTH+1];
    struct BSTNode *left, *right;
};


// BST defintion for a team Node
struct BSTTeamNode{
    struct BSTNode *team;
    struct BSTTeamNode *left, *right;
};


// linked List defintion for a team Node
struct TeamNode{
    struct BSTNode *team;
    struct TeamNode *next;
};


// makes a new Team Node
struct TeamNode *newTeamNode(struct BSTNode *newTeam){
    struct TeamNode *newNode = (struct TeamNode*) malloc(sizeof(struct TeamNode));
    newNode->team = newTeam;
    newNode->next = NULL;
    return newNode;
}


// inserts the new team at the head of the LL of team BSTs
struct TeamNode *insertTeamAtHead(struct TeamNode *head, struct BSTNode *newTeam){
    struct TeamNode *newNode = newTeamNode(newTeam);
    newNode->next = head;
    head = newNode;
    return head;
}


// makes a new node
struct BSTNode *newNode(char name[]){
    struct BSTNode *newBSTNode = (struct BSTNode*) malloc(sizeof(struct BSTNode));

    strcpy(newBSTNode->name, name);
    newBSTNode->left = newBSTNode->right = NULL;

    //printf("%s added\n", name);

    return newBSTNode;
}


// inserts a name in inorder into a single team BST
struct BSTNode *insertInOrder(struct BSTNode *node, char *key){

    // case correction
    correctCase(key);

    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (strcmp(key, node->name)<0)      node->left  = insertInOrder(node->left, key);
    else if (strcmp(key, node->name)>0) node->right = insertInOrder(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}


// prints inorder traversal
void inorder(struct BSTNode *node){
    if(node == NULL) return;
    inorder(node->left);
    printf("%s ", node->name);
    inorder(node->right);
}


// C function to search a given key in a given BST
// returns the address of the root node where key was found
struct BSTNode* searchTeamForName(struct BSTNode* root, char *key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || strcmp(key, root->name) == 0)
       return root;

    // Key is greater than root's key
    if (strcmp(key, root->name) > 0)
       return searchTeamForName(root->right, key);

    // Key is smaller than root's key
    return searchTeamForName(root->left, key);
}


// prints out the LL of Team BST's to the screen
void printLLOfTeamBSTs(struct TeamNode *top){

    struct TeamNode *currTeam = top;
    // printf("\n\n%s\n\n", top->team->name);
    while(currTeam != NULL){
        inorder(currTeam->team);
        printf("\n\n");
        currTeam = currTeam->next;
    }

}



// this is the big boy function
// shits about to go down...
// function that accepts a linked list of names on a line and a linked list of BSTs of all the teams thus far
// searches if a name on a line already appears in the LL of current teams
// if found then add the ll of names on a line to the appropriate team
// if not found make a new team on the LL of teams and add the ll of names to that new team
// returns the LL of Teams
struct TeamNode *addToLinkedListOfTeams(struct TeamNode *topOfLinkedListOfTeams, struct NameNode *topOfListOfNamesOnALine){

    // search if a name in names on a line is already in a team BST

    // take note of the BST name was found in
    struct TeamNode *save = NULL;

    // boolean to break out of loops
    bool foundName = false;

    // going through the linked list of names on a line
    struct NameNode *currName = topOfListOfNamesOnALine;
    while(!foundName && currName != NULL){

        // now go through each team BST in the LL of Teams
        struct TeamNode *currTeam = topOfLinkedListOfTeams;     // variable to go through the linked list of team BSTs
        while(!foundName && currTeam != NULL){

            // search through the BST pointed to by currTeam

            // if found
            if(searchTeamForName(currTeam->team, currName->name) != NULL){
                save = currTeam;
                foundName = true;
            }

            currTeam = currTeam->next;
        }

        currName = currName->next;
    }


    // if name not found
    // make a new BST out of the LL of names on a line and add to the LL of Team BSTs
    if(!foundName){

        // new Team incomming
        struct BSTNode *newTeam = NULL;
        currName = topOfListOfNamesOnALine;
        while(currName != NULL){
            newTeam = insertInOrder(newTeam, currName->name);
            currName = currName->next;
        }

        // insert the newTeam into LL of Team BSTs
        topOfLinkedListOfTeams = insertTeamAtHead(topOfLinkedListOfTeams, newTeam);

        // return the top of ll of team BSTs
        return topOfLinkedListOfTeams;

    }

    // else name was found in a team
    // so add the names from the LL of names on a line to that team
    // omitting the duplicate name
    currName = topOfListOfNamesOnALine;
    while(currName != NULL){

        // insert inorder into the saved team BST
        insertInOrder(save->team, currName->name);

        currName = currName->next;
    }

    return topOfLinkedListOfTeams;

}


// makes a new BSTTeamNode
struct BSTTeamNode *newBSTTeamNode(struct BSTNode *rootOfATeamBST){

    struct BSTTeamNode *newNode = (struct BSTTeamNode *) malloc(sizeof(struct BSTTeamNode));
    newNode->team = rootOfATeamBST;
    newNode->left = newNode->right = NULL;
    return newNode;

}


// finds the first name in alphabetical order in a single team BSTs by going to the left most node
// returns the pointer to the name char array
struct BSTNode *findFirstName(struct BSTNode *root){

    struct BSTNode *curr = root;
    while(curr->left != NULL)
        curr = curr->left;
    return curr;

}


// inserts a team in inorder into a BST of team BSTs
struct BSTTeamNode *insertTeamInOrder(struct BSTTeamNode *node, struct BSTNode *key){

    /* If the tree is empty, return a new node */
    if (node == NULL) return newBSTTeamNode(key);

    /* Otherwise, recur down the tree */
    if (strcmp(findFirstName(key)->name, findFirstName(node->team)->name)<0)      node->left = insertTeamInOrder(node->left, key);
    else if (strcmp(findFirstName(key)->name, findFirstName(node->team)->name)>0) node->right = insertTeamInOrder(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}


// accepts the LL of teams
// and makes a BST of teams by looking at the left-most node of each team tree in the ll of Teams
struct BSTTeamNode *makeBSTOfTeams(struct TeamNode *topOfLinkedListOfTeams){

    // make the BST
    struct BSTTeamNode *allTeams = NULL;

    // go through the LL of team BSTs
    struct TeamNode *currTeam = topOfLinkedListOfTeams;
    while(currTeam != NULL){

        allTeams = insertTeamInOrder(allTeams, currTeam->team);

        currTeam = currTeam->next;
    }

    return allTeams;

}


// prints the BST of team BSTs
int printAllTeamsInAlphabeticalOrder(struct BSTTeamNode *top, int teamNumber){

    if(top == NULL) return teamNumber;

    teamNumber = printAllTeamsInAlphabeticalOrder(top->left, teamNumber);
    printf("Team %d\n", teamNumber);
    inorder(top->team);
    printf("\n\n");
    teamNumber++;
    teamNumber = printAllTeamsInAlphabeticalOrder(top->right, teamNumber);

}
