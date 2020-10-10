// Linked List Node defintion for a name
struct NameNode{
    char name[MAX_NAME_LENGTH];
    struct NameNode *next;
};


struct NameNode *newNameNode(char *name){
    struct NameNode *newNode = (struct NameNode*) malloc(sizeof(struct NameNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}


struct NameNode *insertAtHead(struct NameNode *head, char *name){
    struct NameNode *newNode = newNameNode(name);
    newNode->next = head;
    head = newNode;
    return head;
}


void printNameLinkedList(struct NameNode *top){
    struct NameNode *curr = top;
    while(curr != NULL){
        printf("%s  ", curr->name);
        curr = curr->next;
    }
    printf("\n\n");
}
