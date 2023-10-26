#ifndef BigInteger_h
#define BigInteger_h
typedef struct node
{
    int data;
    struct node *next;
}node;
typedef struct BigInteger
{
node *head;
int len;
node *last;
}bigint;
node *newNode(int);
bigint  initialize(char[]);
bigint initializeEmpty();
void print(node *);
bigint  add(bigint ,bigint);
bigint  sub(bigint ,bigint);
int length(bigint);
node *lastnode(node*);
bigint mul(bigint,bigint);
int cmp(bigint,bigint);
bigint  div1(bigint ,bigint);
bigint mod(bigint,bigint);
void removeextra(bigint*);
void display(struct BigInteger);
#endif