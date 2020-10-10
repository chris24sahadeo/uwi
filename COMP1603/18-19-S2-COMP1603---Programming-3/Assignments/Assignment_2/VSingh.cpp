//Name : Vishma Singh
//ID : 816003377
//My program is working 100%!

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define MAX_DIGITS 50


struct Node{
    int data;
    Node *next;
};


struct Stack{
    Node *top;
};

void printList(Node *top){
    cout << "top -> ";
    Node *curr = top;
    while(curr!=NULL) {
        cout<<curr->data<<" -> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}

Stack *initStack(){
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->top = NULL;
	return s;
}

void push(Stack *s, int data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = s->top;
	s->top = newNode;
}

bool isEmpty(Stack *s){
    if(s->top == NULL)
        return true;
    else
        return false;
}

int pop(Stack *s){
	if(isEmpty(s))  //Checking to see if stack is empty
		return -1;


	Node *curr = s->top;
	s->top = curr->next;
	int n = curr->data;
	free(curr);
	return n;
}

int peek(Stack *s){
	if(isEmpty(s))
		return -1;
		
	return s->top->data;
}


int charToInt(char ch){
    int value;
    value = ch - 48;

    return value;
}

char intToChar(int n){
	char c;
	c = n + 48;

	return c;
}

// function accepts a single character array (max size 50 digits)
// and returns a stack with 1 digit per node with the least significant digit at the top of stack
Stack *cStringToStack(char num[]){
	Stack *s = initStack();
	int i = 0;

	while(num[i] != '\0'){
		int integer = charToInt(num[i]);
		push(s , integer);
		i++;
	}
	return s;
}


// function accepts 2 stacks
// and returns a new stack which holds the sum of the two stacks, 1 digit per node, with the least significant digit at the top of stack
Stack *addStacks(Stack *stackNum1, Stack *stackNum2){
	Stack *sumStack = initStack();
	int sum = 0;
	int carry = 0;

	while(!isEmpty(stackNum1) && !isEmpty(stackNum2)){
		int digit1 = pop(stackNum1);
		int digit2 = pop(stackNum2);

		sum = (digit1 + digit2 + carry) % 10;
		carry = (digit1 + digit2 + carry) /10;

		push(sumStack , sum);
	}

	if(isEmpty(stackNum1)){
		while(!isEmpty(stackNum2)){
			int digit3 = pop(stackNum2);
			sum = (digit3 + carry) % 10;
			carry = (digit3 + carry) / 10;
			push(sumStack, sum);
		}
	}
	
	else {
		while(!isEmpty(stackNum1)){
			int digit3 = pop(stackNum1);
			sum = (digit3 + carry) % 10;
			carry = (digit3 + carry) / 10;
			push(sumStack, sum);
		}
	}

	if(carry == 1){
		push(sumStack, carry);
	}

	return sumStack;
}


int main(){
	
	ifstream fin("input.txt");
	if(!fin){
		cout<<"Error. Input file cannot be opeend."<<endl;
		exit(-1);
	}
	
	ofstream fout("output.txt");
	if(!fout){
		cout<<"Error. Output file cannot be opened."<<endl;
		exit(-1);
	}
	
	char cStringNum1[MAX_DIGITS+1];
	char cStringNum2[MAX_DIGITS+1];
	
	fin>>cStringNum1;
	while(strcmp(cStringNum1, "-1")!=0) {
		fin>>cStringNum2;

		cout << setw(MAX_DIGITS+2) << cStringNum1 << endl;
		cout << setw(MAX_DIGITS+2) << cStringNum2 << endl;
		
		fout << setw(MAX_DIGITS+2) << cStringNum1 << endl;
		fout << setw(MAX_DIGITS+2) << cStringNum2 << endl;

		Stack *stackNum1 = cStringToStack(cStringNum1);
		Stack *stackNum2 = cStringToStack(cStringNum2);
		Stack *sumStack = addStacks(stackNum1, stackNum2);

		for(int i = 0; i < MAX_DIGITS+2; i++){
			cout << "=";
			fout<<"=";
		}
		cout << endl;
		fout<<endl;
		

		char result[MAX_DIGITS+2];
		int i = 0;
		while(!isEmpty(sumStack)){
			int digit = pop(sumStack);
			result[i] = intToChar(digit);
			i++;
		}
		result[i] = '\0';
		cout << setw(MAX_DIGITS+2) << result << endl;
		fout << setw(MAX_DIGITS+2) << result << endl;

		for(int i = 0; i < MAX_DIGITS+2; i++){
			cout << "=";
			fout<<"=";
		}
		cout << "\n\n\n"; 
		fout << "\n\n\n";

		fin>>cStringNum1;
	}
	
	fin.close();
	fout.close();
	
	return 0;
}
