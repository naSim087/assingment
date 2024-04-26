#include <iostream>
#include <queue>
using namespace std;


struct node{

int data;
node * left,*right,*equal;

};


node * create(int data){
  node* newNode= new node();
  newNode->data=data;
  newNode->left=NULL;
  newNode->equal=NULL;
  newNode->right=NULL;
  return newNode;

}

void insert(node** head, int data) {
    if (*head == NULL) {
        *head = create(data);
    } else if ((*head)->data > data) {
        insert(&(*head)->left, data);
    } else if ((*head)->data == data) {
        if ((*head)->equal == NULL) {
            insert(&(*head)->equal, data);
        } else {
            insert(&(*head)->equal, data); // You can decide what to do here; for now, inserting into equal again
        }
    } else {
        insert(&(*head)->right, data);
    }
}

int main(){

  node * head=NULL;
  insert(&head,10);
  insert(&head,20);
  insert(&head,30);
  insert(&head,10);
  insert(&head,40);
  insert(&head,50);


  queue<node*>q1;
  q1.push(head);
  while(q1.size()){
    node  *top=q1.front();
    q1.pop();
    cout<<top->data<<" ";
    if(top->left!=NULL)
    q1.push(top->left); 
    if(top->equal!=NULL)
    q1.push(top->equal);
     if(top->right!=NULL)
    q1.push(top->right);
  }


}




