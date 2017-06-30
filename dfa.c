#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int i,j,length,no=0,termno,nodeno=1,len,l;
int state[20][20],newstate[10],status=1;
typedef struct tree
{
    char ch;
    int pos;
    int nullable;
    int fpos[5];
    int lpos[5];
    struct tree *lc;
    struct tree *rc;
}node;
typedef struct simulatedfa
{
char ch;
int follow[20];
}dfa;
dfa ladder[20];
node* alloc(char ch)
{
    node *temp;
    temp=(node *)malloc(sizeof(node));
    temp->nullable=1;
    temp->lc=NULL;
    temp->rc=NULL;
    temp->ch=ch;
    temp->fpos[0]=-1;
    temp->lpos[0]=-1;
    return temp;  
}
void initialize()
{int i,j;
  for(i=1;i<=length;i++)
 {
   
     ladder[i].follow[1]=-1;
   }
   }

void print_follow(int l)
{
    printf("FOLLOWPOS\n");
    printf("POS\tNAME\tFOLLOWPOS\n");
    for( i=1;i<=termno;i++)
    {
        printf("%d\t%c\t",i,ladder[i].ch);
        int j=1;
        while(ladder[i].follow[j]!=-1)
        {
            printf("%d ",ladder[i].follow[j]);
            j++;
        }
        printf("\n");

    }
}
void print_nullable(node *root)
{

    if(root!=NULL)
    {
        print_nullable(root->lc);
        print_nullable(root->rc);
        printf("%c\t",root->ch);
        int i=0;
        while(root->fpos[i]!=-1)
        {
            printf("%d ",root->fpos[i]);
            i++;
        }
        printf("\t");
        i=0;
        while(root->lpos[i]!=-1)
        {
            printf("%d ",root->lpos[i]);
            i++;
        }
        printf("\n");

    }

}
void findfollow(int value,int arr[])
 
{ int i,j;
  i=value; 
  j=1;
  // printf("print %d\n",ladder[i].follow[j]);
  while(ladder[i].follow[j]!=-1)
   {//printf("hello3\n");
    j++;
   }
 // printf("value of j after while loop %d \n",j);
  int index,found,h,m,k;
  index =j;
  int add[10];
  h=0;
 //printf("i am at find follow  %d\n",value);
  for(j=0;arr[j]!=-1;j++)
    { found=0;
     for(k=0;k<=index;k++)
     {
      if(ladder[i].follow[k]==arr[j])
         {
         found=1;
         break;
         }
     }
     if(found==0)
       {add[h]=arr[j];
        h++;
       } 
    }
  for(k=index,m=0;m<h;k++,m++)
    ladder[i].follow[k]=add[m];
  ladder[i].follow[k]=-1;
  int c;
  /*printf("\n");
 for(c=1;c<k;c++)
     printf("jop %d  %d\n",i,ladder[i].follow[c]);*/
} 

char findchar(node *root,int num)
{
 if(root!=NULL)
    {
        findchar(root->lc,num);
        if(root->pos==num)
        ladder[num].ch= root->ch;
        findchar(root->rc,num);
    }

}
void goforfollow(node *root)
{  // printf("i am in go for follow %c\n",root->ch);
    int i=0;
     if(root->ch=='*')
    {// printf("hello\n");
        while(root->lpos[i]!=-1)
        { //printf("hello 1 %d \n ",root->lpos[i]);
            
             
            findfollow(root->lpos[i],root->fpos);
            i++;
        }
    }
     if(root->ch=='.')
    {   // printf("i am in go for follow %c\n",root->ch);
         while(root->lc->lpos[i]!=-1)
         {  ladder[i].ch=findchar(root,i);
            findfollow(root->lc->lpos[i],root->rc->fpos);
            i++;
         }
    }
  
     
   
}
node * create(char str[],int l)
{
    node * nw;
     nw=alloc(str[l]);
     //printf("length %d \n",l);
    // printf("ch %c \n",nw->ch);
    if(str[l]=='*'||str[l]=='/'||str[l]=='.')
    {
        if(str[l]!='*')
        {
            l=len-nodeno;
            nodeno=nodeno+1;
            nw->nullable=0;
            nw->rc=create(str,l);
        }
       l=len-nodeno;
       nodeno=nodeno+1;
        nw->lc=create(str,l);
    }
    else
        nw->nullable=0;
    
    return nw;
}

void inorder(node *root)
{    if(root!=NULL)
    {
       inorder(root->lc);
       printf("%c\n ",root->ch);
       inorder(root->rc);
    }
}
void sort(int a[])
{    

    int i,j,temp;
    for(i=1;a[i]!=-1;i++)
    {
        temp=a[i];
        for(j=i-1;j>=0&&temp<a[j];j--)
            a[j+1]=a[j];
        a[j+1]=temp;
    }
 
}
void first(node *root,node *child)
{  // printf("i got u  %c\n",root->ch);
    int i,j=0;
    while(root->fpos[j]!=-1)
        j++;
     printf("  j-%d \n",j);
     int m,index,found;
     index=j;
   for(i=0;child->fpos[i]!=-1;i++)
      {found=0;
       for(m=0;m<index;m++)
         if(child->fpos[i]==root->fpos[m])
            { found=1;
             break;}
        if (found==0)
        root->fpos[j++]=child->fpos[i]; 
}

  root->fpos[j]=-1;
/*for(i=0;i<=j;i++)
        {
            
         printf("array  %d\n",root->fpos[i]);  
   
        }*/
  
}

void last(node *root,node *child)
{
  // printf("i got u  %c\n",root->ch);
    int i=0,j=0;
    while(root->lpos[j]!=-1)
        j++;
    for(i=0;child->lpos[i]!=-1;i++,j++)
         root->lpos[j]=child->lpos[i]; 
root->lpos[j]=-1;
}
void create_nullable(node *root)
{   //printf("root  %c\n",root->ch);
    if(root->lc!=NULL)
        create_nullable(root->lc);
    if(root->rc!=NULL)
        create_nullable(root->rc);
    if(root->lc==NULL && root->rc==NULL)
    {  //printf("i am here  %c\n",root->ch);
        
        root->pos=(status);
         //printf("hey position  %d\n",root->pos);
        root->fpos[0]=root->lpos[0]=(status);
        root->fpos[1]=root->lpos[1]=-1;
        ++status;   
        
    }
    else
    {
        if(root->ch=='/')

        {   int f,l; 
            i=0;  
            root->fpos[0]=-1;
            root->lpos[0]=-1;
            first(root,root->lc);
            first(root,root->rc);
            last(root,root->lc);
            last(root,root->rc);
           
        }
        else if(root->ch=='*')
        {
            first(root,root->lc);
            last(root,root->lc);
        }
        else if(root->ch=='.')
        {
            if(root->lc->nullable==1)
            {
                first(root,root->rc);
                first(root,root->lc);
            }
                first(root,root->lc);
                sort(root->fpos);
            if(root->rc->nullable==1)
            {
                last(root,root->lc);
            }
                last(root,root->rc);
                sort(root->lpos);
        }
       goforfollow(root);;
    }
}
void getstates(int arr[])
{ 
  int i=0,j=1,k,found=0,h=0;
  newstate[0]=-1;
  while(arr[i]!=-1)
   {  j=1;
   // printf("i am here at while %d\n",arr[i]);
      while(ladder[arr[i]].follow[j]!=-1)
        { found=0;
       // printf("i am inside %d\n",ladder[arr[i]].follow[j]);
          for(k=0;newstate[k]!=-1;k++)
           {
        if(newstate[k]==ladder[arr[i]].follow[j])
        {
          found=1;
          break;
         }
       }
        if(found==0)
        {
         newstate[h]=ladder[arr[i]].follow[j];
         h++;
         newstate[h]=-1;
        }
        j++;
     }
   i++;
  }int w;
  /* printf("\nstate"); 
 for(w=0;newstate[w]!=-1;w++)
                printf(" %d",newstate[w]);
  printf("\n*****");*/
 }
void addstate(int newstate[])
{int m,found=0,u,arr[20],count=0;
 int long1=0,long2=0,w;
 for(w=0;newstate[w]!=-1;w++)
        long1++;  
     while(count<=no)
             { long2=0;
              for(w=0;state[count][w]!=-1;w++)
                long2++;
              
                found=0;
        if(long2<long1)
        {
     for(u=0;newstate[u]!=-1;u++)
           {
              if(state[count][u]!=newstate[u])
                 {found=1;
                  break;
                }
            }
}
else
              {
                for(u=0;state[count][u]!=-1;u++)
                  {
                     if(state[count][u]!=newstate[u])
                      {found=1;
                       break;
                      }
                  }
             }
              
         arr[count]=found;
         count++;
              
         }
 count=0;
 found=0;
 
 while(count<=no)
{
if(arr[count]==0)
 { found=1;
  break;

}
count++;
}

 if(found==0)
{for(i=no+1,j=0;newstate[j]!=-1;j++)
   state[i][j]=newstate[j];
   state[i][j]=-1;
    no++;
   // printf("\nadded new state"); 
 }

  
}
void drawdfa(node *root)
{printf("TRANSITION TABLE\n");
  printf("\t   LETTER    \t\n");
 int i ,j,m,dstate[10],first=0;
 i=0;
 j=0;
 while(i<=no)
{ 
   if(first==0)
    {
     while(root->fpos[j]!=-1)
     {state[i][j]=root->fpos[j];
      j++;
     }
     first=1;
     state[i][j]=-1;
    }
  
  j=0;
  int w,n;
  int temp1[10],temp2[10]; 
  m=0,n=0;
  while(state[i][j]!=-1)
    {  
        
       if(ladder[state[i][j]].ch=='a')
           { 
            temp1[m]=state[i][j];
            m++;j++;
            }
       else
          {temp2[n]= state[i][j];
           n++;j++;
                     
            } 
          }    
            temp2[n]=-1;
            temp1[m]=-1;
          /* printf("drawdfa"); 
           for(w=0;temp1[w]!=-1;w++)
                printf(" %d",temp1[w]);*/ 
            getstates(temp1);
            sort(newstate);
            
            for(w=0;state[i][w]!=-1;w++)
                printf(" %d",state[i][w]);
            printf("         a->   ");
            for(w=0;newstate[w]!=-1;w++)
                printf(" %d",newstate[w]);
            printf("\n"); 
            addstate(newstate);          
            getstates(temp2);
            
             for(w=0;state[i][w]!=-1;w++)
                printf(" %d",state[i][w]);
            printf("        b->   ");
            for(w=0;newstate[w]!=-1;w++)
                printf(" %d",newstate[w]);
            printf("\n"); 
           sort(newstate);         
           addstate(newstate);
           i++;
    
     
 }    
      
}





void main()
{
    
    char *str;
    char *input;
    printf("Enter the postfix expression\n");
    scanf("%s",str);
    node * root;  
    int f;
    strcat(str,"#.\0");
    l=strlen(str);
    int g=0;
    printf("Enter the length of string  %d\n",l);
    length=l;
    l--;
    len=l;
    termno=8;//strlen(input);
    initialize();
    root=create(str,l);
    inorder(root); 
    create_nullable(root);
    for(i=1;i<=7;i++)
    findchar(root,i);
    //printf("NULLABLE TABLE\nElement\tFPOS\tLPOS\n");
   // print_nullable(root);
   // print_follow(length);
    drawdfa(root);
    //display_dfa();
    //inorder(root); 
}




 
