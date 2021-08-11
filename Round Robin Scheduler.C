#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<dos.h>
typedef struct node
 {
    int data;
    int priority;
    struct node* next;
} Node;
void round();
Node* newNode(int d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}
int peek(Node** head)
{
    return (*head)->data;
}
void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
void push(Node** head, int d, int p)
{
    Node* start = (*head);
    Node* temp = newNode(d, p);
    if ((*head)->priority > p)
    {
	temp->next = *head;
	(*head) = temp;
    }
    else
     {

	while (start->next != NULL &&
	       start->next->priority < p) {
	    start = start->next;
	}
	temp->next = start->next;
	start->next = temp;
    }
}
int isEmpty(Node** head)
{
    return (*head) == NULL;
}
int main()
{
    Node* pq = newNode(55, 1);
    push(&pq, 56, 2);
    push(&pq, 68, 3);
    push(&pq, 54, 0);
    push(&pq, 69, 4);
    push(&pq, 72, 5);
    push(&pq, 74, 6);
    clrscr();
    printf("\n\t\t***Process scheduling***\n\n\t\t");
    while (!isEmpty(&pq))
    {
	delay(1000);
	printf("\n\t\t%d ", peek(&pq));
	pop(&pq);
    }
    printf("\n\n\n\t\t ***Round Robin Implementation***\n");
    round();
    return 0;
}
void round()
{
  int count,j,n,time,remain,flag=0,time_quantum;
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10];
  printf("Enter Total Process:\t ");
  scanf("%d",&n);
  remain=n;
  for(count=0;count<n;count++)
  {
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1);
    scanf("%d",&at[count]);
    scanf("%d",&bt[count]);
    rt[count]=bt[count];
  }
  printf("Enter Time Quantum:\t");
  scanf("%d",&time_quantum);
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(time=0,count=0;remain!=0;)
  {
    if(rt[count]<=time_quantum && rt[count]>0)
    {
      time+=rt[count];
      rt[count]=0;
      flag=1;
    }
    else if(rt[count]>0)
    {
      rt[count]-=time_quantum;
      time+=time_quantum;
    }
    if(rt[count]==0 && flag==1)
    {
      remain--;
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
      wait_time+=time-at[count]-bt[count];
      turnaround_time+=time-at[count];
      flag=0;
    }
    if(count==n-1)
      count=0;
    else if(at[count+1]<=time)
      count++;
    else
      count=0;
  }
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n);
  getch();
}
