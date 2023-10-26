#include<stdio.h>
#include "BigInteger.h"
#include<string.h>
#include<stdlib.h>
struct node* newNode(int val)
{
    node *temp=(node *)malloc(sizeof(node));
    temp->data=val;
    temp->next=NULL;
    return temp;
}
struct BigInteger initializeEmpty()
{
    bigint n;
    n.head=NULL;
    return n;
}
struct BigInteger initialize(char st[])
{
    bigint n;
    n.head=NULL;
    node *itr=NULL;
    int l=strlen(st);
    for(int i=l-1;i>=0;i--)
    {
        char ch=st[i];
       
        if(n.head==NULL)
       { 
        n.head=newNode(ch-48);
        itr=n.head;
       }
        else if(st[i-1]=='-')
        {
            itr->next=newNode((ch-48)*-1);
            itr=itr->next;
            i=i-1;
        }
        else if(st[i]>=48&&st[i]<=57)
        {
            itr->next=newNode(ch-48);
            itr=itr->next;
        }
        
    }
    removeextra(&n);
    return n;
}
void display(struct BigInteger n)
{
    print(n.head);
}
void print(node *head)
{
    if(head==NULL)
    {
        printf("\n");
        return;
    }
    print(head->next);
    printf("%d",head->data);
}
int length(bigint bg)
{
    node*itr=bg.head;
    int l=0;
    while(itr!=NULL)
    {
        l=l+1;
        itr=itr->next;
    }
    return l;
}
node * lastnode(node *head)
{
    if(!head)
    return head;
    while(head->next!=NULL)
        head=head->next;
    return head;
}
bigint add(bigint n1,bigint n2)
{
   
    bigint n3;
    n3.head=NULL;
     node *last1=lastnode(n1.head);
        node *last2=lastnode(n2.head);
        int s=0;
        if(last1->data<0&&last2->data<0)
        {
            s=1;
            last1->data=last1->data*-1;
            last2->data=last2->data*-1;
        }
        else if(last1->data<0 )
        {
            last1->data=last1->data*-1;
            n3=sub(n1,n2);
            last1->data=last1->data*-1;
           
             if(n3.head)
             {
            if((n3.head)->next)
             removeextra(&n3);
            }
             node *l3=lastnode(n3.head);
            l3->data=l3->data*-1;
            return n3;
        }
        else if(last2->data<0)
        {
            last2->data=last2->data*-1;
            n3=sub(n1,n2);
            last2->data=last2->data*-1;
             if(n3.head)
             {
            if(n3.head->next)
            removeextra(&n3);
            }
            return n3;
        }
    
    node *n1itr=n1.head;
    node *n2itr=n2.head;
    node *itr=NULL;
    int carry=0;
    while((n1itr!=NULL)  &&  ( n2itr!=NULL))
    {
        
        if(n3.head==NULL)
        {
            
            n3.head=newNode((carry+n1itr->data+n2itr->data)%10);
            carry=(carry+n1itr->data+n2itr->data)/10;
            itr=n3.head;
        }
        else
        {
            itr->next=newNode((carry+n1itr->data+n2itr->data)%10);
            carry=(carry+n1itr->data+n2itr->data)/10;
            itr=itr->next;
        }
        n1itr=n1itr->next;
        n2itr=n2itr->next;
    }
    
    while(n1itr)
    {
         if(n3.head==NULL)
        {
            n3.head=newNode((carry+n1itr->data)%10);
            carry=(carry+n1itr->data)/10;
            itr=n3.head;
        }
        else
        {
            itr->next=newNode((carry+n1itr->data)%10);
            carry=(carry+n1itr->data)/10;
            itr=itr->next;
        }
        n1itr=n1itr->next;
    }
    while(n2itr)
    {
         if(n3.head==NULL)
        {
            n3.head=newNode((carry+n2itr->data)%10);
            carry=(carry+n2itr->data)/10;
            itr=n3.head;
        }
        else
        {
            itr->next=newNode((carry+n2itr->data)%10);
            carry=(carry+n2itr->data)/10;
            itr=itr->next;
        }
        n2itr=n2itr->next;
    }
    while(carry!=0)
    {
        itr->next=newNode((carry)%10);
        carry=carry/10;
        itr=itr->next;
    }
     if(n3.head)
    {
    if(n3.head->next)
        removeextra(&n3);
    }
    if(s==1)
    {
        node *last3=lastnode(n3.head);
        last3->data=last3->data*-1;
        last1->data=last1->data*-1;
        last2->data=last2->data*-1;
    }
    
    return n3;
}
bigint sub(bigint n1,bigint n2)
{
   
    bigint n3;
    n3.head=NULL;
   
    node *n1itr=n1.head;
    node *n2itr=n2.head;
    int s=0;
    int z=0;
      node *last1=lastnode(n1.head);
        node *last2=lastnode(n2.head);
    if(last1->data<0&&last2->data<0)
    {
        z=1;
        last1->data=last1->data*-1;
        last2->data=last2->data*-1;
    }
    else if(last2->data<0)
    {
        last2->data=last2->data*-1;
        n3=add(n1,n2);
        last2->data=last2->data*-1;
         if(n3.head)
        {
        if(n3.head->next)
        removeextra(&n3);
        }
        return n3;
    }
    else if(last1->data<0&&last2->data>=0)
    {
        last1->data=last1->data*-1;
        n3=add(n1,n2);
        last1->data=last1->data*-1;
        if(n3.head)
        {
        if(n3.head->next)
        removeextra(&n3);
        }
        node *l3=lastnode(n3.head);
        l3->data=l3->data*-1;
       
        return n3;
    }
    int l1=length(n1);
    int l2=length(n2);
    
   int c=cmp(n1,n2);
   
   if(c<0)
   {
    node *t=n1itr;
    n1itr=n2itr;
    n2itr=t;
    s=1;
   }
  
    node *itr=NULL;
    int borrow=0;
    int num1[l1];
    int k=0;
    node *t=n1itr;
    while(t!=NULL)
    {
        num1[k++]=t->data;
        t=t->next;
    }
   t=n1itr; 
   
 

while((n1itr!=NULL)  &&  ( n2itr!=NULL))
    {
    
        
        if(n3.head==NULL)
        {
            if((n1itr->data<n2itr->data||n1itr->data<0)&& (n1itr->next))
            {
                borrow=10;
                n1itr->next->data-=1;
            }

            n3.head=newNode((n1itr->data+borrow)-n2itr->data);
             borrow=0;
            itr=n3.head;
        }
        else
        {
             if((n1itr->data<n2itr->data||n1itr->data<0)&& (n1itr->next))
            {
                borrow=10;
                n1itr->next->data-=1;
            }
            itr->next=newNode((n1itr->data+borrow)-n2itr->data);
            borrow=0;
            itr=itr->next;
        }
        n1itr=n1itr->next;
        n2itr=n2itr->next;
    }
    while(n1itr)
    {
        
        if(n3.head==NULL)
        {
            if(n1itr->data<0 && (n1itr->next))
            {
                borrow=10;
                n1itr->next->data-=1;
            }
            n3.head=newNode(n1itr->data+borrow);
            borrow=0;
            itr=n3.head;
        }
        else
        {
            if((n1itr->data<0)&& (n1itr->next))
            {
                borrow=10;
                n1itr->next->data-=1;
            }
            itr->next=newNode(n1itr->data+borrow);
            borrow=0;
            itr=itr->next;
        }
        n1itr=n1itr->next;
    }
     n1itr=t;
    for(int i=0;i<l1;i++)
    {
        n1itr->data=num1[i];
        n1itr=n1itr->next;
    }
    
     if(n3.head)
    {
    if(n3.head->next)
        removeextra(&n3);
    }
    if(s==1)
    {
        node *lastn3=lastnode(n3.head);
        lastn3->data=lastn3->data*-1;
    }
    if(z==1)
    {
         node *lastn3=lastnode(n3.head);
         last1->data=last1->data*-1;
        last2->data=last2->data*-1;
        lastn3->data=lastn3->data*-1;
    }
   
 
    return n3;
}
bigint mul(bigint n1,bigint n2)
{
   
   if(n1.head->next==NULL&&n1.head->data==0)
   {
    bigint n3;
    n3=initialize("0");
    return n3;
   }
   if(n2.head->next==NULL&&n2.head->data==0)
   {
    bigint n3;
    n3=initialize("0");
    return n3;
   }
  
    node *n1itr=n1.head;
    node *n2itr=n2.head;
    int sn1=1;
    int sn2=1;
    node *lastn2=lastnode(n2.head);
    node *lastn1=lastnode(n1.head);
    if(lastn2->data<0)
    {
        sn2=-1;
        lastn2->data=lastn2->data*-1;
    }
    if(lastn1->data<0)
    {
        sn1=-1;
        lastn1->data=lastn1->data*-1;
    }
      
    int l2=length(n2);
    
    bigint arr[l2];
    
    for(int i=0;i<l2;i++)
        arr[i]=initializeEmpty();
    
    int count=0;
    int i=0;
    node *itr;
    node *t=n1itr;
    int c=0;
   
    while(n2itr)
    {
       
        while(n1itr)
        {
            
        int digit=n1itr->data * n2itr->data;
        if(arr[i].head==NULL)
        {
            arr[i].head=newNode((digit+c)%10);
            c=(digit+c)/10;
            itr=arr[i].head;
        }
        else
        {
            itr->next=newNode((digit+c)%10);
            c=(digit+c)/10;
            itr=itr->next;
        }
        n1itr=n1itr->next;
        
        }
        while(c!=0)
        {
            itr->next=newNode(c%10);
            c=c/10;
            itr=itr->next;
        }
      
        for(int j=0;j<count;j++)
        {
            node *temp=newNode(0);
            temp->next=arr[i].head;
            arr[i].head=temp;
            
        }
        
        n2itr=n2itr->next;
        i=i+1;
        n1itr=t;
        count=count+1;
       
    }
   
     bigint n3;
    n3.head=NULL;
   
    if(l2==1)
    {
        n3=arr[0];
    }
    else
    {
    n3=add(arr[0],arr[1]);
    for(int j=2;j<l2;j++)
        n3=add(n3,arr[j]);
    }
     if(n3.head)
    {
    if(n3.head->next)
     removeextra(&n3);
    }
    node *lastn3=lastnode(n3.head);
    lastn3->data=lastn3->data*sn1*sn2;
    lastn1->data=lastn1->data*sn1;
    lastn2->data=lastn2->data*sn2;
   
   
    return n3;
}
int cmp(bigint n1,bigint n2)
{
    int l1=length(n1);
    int l2=length(n2);
    
    if(l1<l2)
    return -1;
    else if(l1>l2)
    return 1;
    
    else
    {
       
       int res=0;
       node *itr=n1.head;
       node *itr2=n2.head;
       while(itr)
       {
            if(itr->data<itr2->data)
            res=-1;
            else if(itr->data>itr2->data)
            res=1;
            
            itr=itr->next;
            itr2=itr2->next;
       }
      
        return res;
    }
}
bigint div1(bigint n1,bigint n2)
{
     if(n1.head->next==NULL&&n1.head->data==0)
   {
    bigint n3;
    n3=initialize("0");
    return n3;
   }
    if(n2.head->next==NULL&&n2.head->data==0)
   {
    bigint n3;
    
    n3=initializeEmpty();
    return n3;
   }
     int sn1=1;
    int sn2=1;
    node *lastn2=lastnode(n2.head);
    node *lastn1=lastnode(n1.head);
    if(lastn2->data<0)
    {
        sn2=-1;
        lastn2->data=lastn2->data*-1;
    }
    if(lastn1->data<0)
    {
        sn1=-1;
        lastn1->data=lastn1->data*-1;
    }
    

    bigint prev;
    prev=initialize("0");
    bigint q;
    bigint count=initialize("1");
    while(1)
    {
        
        q=add(prev,count);
        
        bigint multi=mul(q,n2);
        
       int c=cmp(multi,n1);
       
      
       if(c==0)
       {
            
             node *lastn3=lastnode(q.head);
             lastn3->data=lastn3->data*sn1*sn2;
             lastn1->data=lastn1->data*sn1;
             lastn2->data=lastn2->data*sn2;
            
            return q;
       }
       if(c==-1)
       {
      
        prev=q;
        count=add(count,count);
      
    
       }
       if(c==1)
       {
        if(cmp(count,initialize("1"))==0)
        {
            if(prev.head->next)
                removeextra(&prev);
             node *lastn3=lastnode(prev.head);
             lastn3->data=lastn3->data*sn1*sn2;
             lastn1->data=lastn1->data*sn1;
             lastn2->data=lastn2->data*sn2;
             
             return prev;
        }
        q=prev;
        count=initialize("1");
       }
    }

}
bigint  mod(bigint n1,bigint n2)
{
    int s=1;
    node* ln1=lastnode(n1.head);
    if(ln1->data<0)
        s=-1;
    bigint q=div1(n1,n2);
   if(q.head==NULL)
   {
    bigint n3;
    n3=initializeEmpty();
    return n3;
   }
    bigint multi=mul(q,n2);
    bigint re=sub(n1,multi);
    if(re.head->next)
         removeextra(&re);
 
    node*last=lastnode(re.head);
    if(last->data<0)
        last->data=last->data*-1;
    last->data=last->data*s;
    return re;
}
void removeextra(bigint*n)
{
   
    node*itr=n->head;
    node *ln=lastnode(n->head);
    node *prev=NULL;
    while(itr)
    {
        if(itr==ln&&itr->data==0&&n->head->next!=NULL)
        {
                free(itr);
                prev->next=NULL;
                ln=prev;
                itr=n->head;
                
            
        }
        else
        {
        prev=itr;
        itr=itr->next;
        }
        
    }
  
}
