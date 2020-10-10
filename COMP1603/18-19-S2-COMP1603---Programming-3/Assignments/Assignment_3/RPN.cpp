// MUST COMPILE ON WINDOWS, NOT LINUX OR MAC

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// define a Node in a linked list for converting in to post
struct Node {
  char data;
  Node * next;
};


// for postfix evaluation
struct NodeFloat{
    float data;
    NodeFloat *next;
};


// defining the stack
struct Stack {
  Node * top;
};


struct StackFloat{
    NodeFloat *top;
};


// all stack operations
Node * createNode (char n) {
  Node * newNode = (Node *) malloc (sizeof (Node));
  newNode->data = n;
  newNode->next = NULL;
  return newNode;
}


NodeFloat * createNodeFloat (float n) {
  NodeFloat * newNode = (NodeFloat *) malloc (sizeof (NodeFloat));
  newNode->data = n;
  newNode->next = NULL;
  return newNode;
}


// insert at head of linked list
Node * insertAtHead (Node * top, char n) {
  Node * newNode = createNode (n);
  newNode->next = top; // this works even if the list is empty (i.e., top = NULL)
  top = newNode;
  return top;          // return pointer to new head of list
}


NodeFloat * insertAtHeadFloat (NodeFloat * top, float n) {
  NodeFloat * newNode = createNodeFloat (n);
  newNode->next = top; // this works even if the list is empty (i.e., top = NULL)
  top = newNode;
  return top;          // return pointer to new head of list
}



// insert at tail of linked list
Node *insertAtTail(Node *top, char n){
    Node *newNode = createNode(n);
    if(top == NULL){
        top = newNode;
        return top;
    }
    Node *curr = top;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newNode;
    return top;
}


NodeFloat *insertAtTailFloat(NodeFloat *top, float n){
    NodeFloat *newNode = createNodeFloat(n);
    if(top == NULL){
        top = newNode;
        return top;
    }
    NodeFloat *curr = top;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newNode;
    return top;
}


// delete at head of linked list
Node * deleteAtHead (Node * top) {
  Node * curr = top;
  if (top == NULL)
      return NULL;
  else {
      curr = top;
      top = top->next;
      free (curr);
      return top;
  }
}


NodeFloat * deleteAtHeadFloat (NodeFloat * top) {
  NodeFloat * curr = top;
  if (top == NULL)
      return NULL;
  else {
      curr = top;
      top = top->next;
      free (curr);
      return top;
  }
}


// initialises a stack
Stack * initStack() {
    Stack * s = (Stack *) malloc (sizeof (Stack));
    s->top = NULL;
    return s;
}


StackFloat * initStackFloat() {
    StackFloat * s = (StackFloat *) malloc (sizeof (StackFloat));
    s->top = NULL;
    return s;
}



// checks if a stack is empty
bool isEmpty(Stack * s) {
    return (s->top == NULL);
}


bool isEmptyFloat(StackFloat * s) {
    return (s->top == NULL);
}


// pushes a new element on top of stack
void push(Stack * s, char n) {
    s->top = insertAtHead(s->top,n);
}


void pushFloat(StackFloat * s, float n) {
    s->top = insertAtHeadFloat(s->top,n);
}


// pops an element from on top the stack
char pop(Stack * s) {
    char n;
    Node *top;

    if (isEmpty(s)) {
        cout << "Stack is empty." << endl;
        return '!';
    }

    top = s->top;
    n = top->data;
    s->top = deleteAtHead(s->top);

    return n;
}



float popFloat(StackFloat * s) {
    float n;
    NodeFloat *top;

    if (isEmptyFloat(s)) {
        cout << "Stack is empty." << endl;
        return -99999999;
    }

    top = s->top;
    n = top->data;
    s->top = deleteAtHeadFloat(s->top);

    return n;
}



// returns the item at the top of the stack
char peek(Stack * s) {
    char  n;
    Node *top;
    top = s->top;
    n = top->data;
    return n;
}



float peekFloat(StackFloat * s) {
    float n;
    NodeFloat *top;
    top = s->top;
    n = top->data;
    return n;
}
// end of stack operations



// print the contents of linked list to report.txt
void printList (Node * top, ofstream &fout) {
   Node * curr;
   if (top == NULL) {
      fout << "List empty." <<endl;
      return;
   }
   curr = top;
   while (curr != NULL) {
      fout << curr -> data;
      curr = curr->next;
   }
   fout << "\n";
}



// checks for mismatched parenthesis
bool isMatched(Node *top, ofstream &fout){
    Stack *s = initStack();
    Node *curr = top;
    while(curr != NULL){
        if(curr->data == '(')
            push(s, curr->data);
        else{
            if(curr->data == ')' && pop(s) == '!'){
                fout << "\tError: more right than left parentheses!\n\n";
                return false;
            }
        }
        curr = curr->next;
    }
    if(!isEmpty(s)){
        fout << "\tError: more left than right parentheses!\n\n";
        return false;
    }
    return true;
}



// checks if a token is an operator
bool isOperator(char ch){
    return ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '(';
}



// gets the priority of an operator
int priority(char ch){
    if(ch == '^') return 3;
    if(ch == '*' || ch == '/') return 2;
    if(ch == '+' || ch == '-') return 1;
    else return 0;
}



// converts an infix expression to a postfix expression
Node *infixToPostfix(Node *inFixTop){
    Stack *s = initStack();
    Node *curr = inFixTop;
    Node *postfixTop = NULL;

    while(curr != NULL){
        // if left parenthesis
        if(curr->data == '('){
            push(s, curr->data);
        }

        // if right parenthesis
        else if(curr->data == ')'){
            while(peek(s) != '(' ){
                postfixTop = insertAtTail(postfixTop, pop(s));
            }
            pop(s);
        }

        // if operator
        else if(isOperator(curr->data)){
            if(isEmpty(s) || priority(curr->data) > priority(peek(s))){
                push(s, curr->data);
            }
            else{
                while(!isEmpty(s) && priority(curr->data) <= priority(peek(s))){
                    if(peek(s) == '(')
                        pop(s);
                    else
                        postfixTop = insertAtTail(postfixTop, pop(s));
                }
                push(s, curr->data);
            }
        }

        // if operand
        else{
            postfixTop = insertAtTail(postfixTop, curr->data);
        }

        // get next token
        curr = curr->next;
    }

    // popping the remainder of the stack
    while(!isEmpty(s)){
        if(peek(s) == '(')
            pop(s);
        else
            postfixTop = insertAtTail(postfixTop, pop(s));
    }

    return postfixTop;
}



// converts a digit character to a float
float toFloat(char ch){
    float num = ch - '0';
    return num;
}



// computes the result of the 2 topmost operands on the stack
float result(float operand1, float operand2, char symbol){
    float answer;
    if(symbol == '^'){
        answer = 1.0;
        for(int i = 1; i <= operand1; i++){
            answer *= operand2;
        }
    }

    else if(symbol == '*')
        answer = operand2 * operand1;

    else if(symbol == '/'){
        if(operand1 == 0){
            cout << "\nDivision by zero detected. Result is undefined!\n\n";
            return -999;
        }
        answer = operand2 / operand1;
    }


    else if(symbol == '+')
        answer = operand2 + operand1;

    else
        answer = operand2 - operand1;

    return answer;
}



// evaluates postfix expression
float evaluatePostfix(Node *top){
    StackFloat *s = initStackFloat();
    Node *curr = top;
    float operand1, operand2, answer;

    while(curr != NULL){
        if(!isOperator(curr->data)){
            pushFloat(s, toFloat(curr->data));
        }
        else{
            operand1 = popFloat(s);
            operand2 = popFloat(s);
            answer = result(operand1, operand2, curr->data);
            if(answer == -999)
                return answer;
            pushFloat(s, answer);
        }

        curr = curr->next;
    }

    return popFloat(s);
}


int main(){
    ifstream fin("input.txt");
    if(!fin){
        cout << "Could not open input file!\n\n\n";
        return -1;
    }

    ofstream fout("output.txt");
    if(!fout){
        cout << "Could not open output file!\n\n\n";
        return -1;
    }

    Node *inFixTop;
    Node *postFixTop;
    char ch;
    fin >> noskipws;
    int count = 0;

    fin >> ch;
    while(ch != '$'){
        count++;

        inFixTop = NULL;
        postFixTop = NULL;

        while(ch != '\n'){
            while(ch == ' ' || ch == '\t'){
                fin >> ch;
            }
            inFixTop = insertAtTail(inFixTop, ch);
            fin >> ch;
        }

        fout << count << ".\tINFIX\t\t: ";
        printList(inFixTop, fout);

        if(isMatched(inFixTop, fout)){
            postFixTop = infixToPostfix(inFixTop);

            fout << "\tPOSTFIX\t\t: ";
            printList(postFixTop, fout);

            float eval = evaluatePostfix(postFixTop);
            if(eval == -999)
                fout << "\tEVALUATION\t: Division by zero detected. Result is undefined!\n\n";
            else
                fout << "\tEVALUATION\t: " << eval << endl << endl;
        }
        fin >> ch;
    }

    fin.close();
    fout.close();
	return 0;
}
