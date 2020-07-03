/* Aim: Write A Program for implementing Railway Ticket Counter Simulation.
   Author: Pratik.A.Bhudke
   Std.: S.E   Div.: COMPUTER   Roll No.:
   Date: 
*/
/******************* Assingment No. 2 *******************/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int sum_tst=0,user_tst,pn=0,at_m=0,at_h=0,max_wt=0;
char t[9],d[9];

struct rtcs
{
       char status[10];
       int twt;
       int at_mm;
       int at_hh;
       int tst;
       char tot[3];
       struct rtcs *next;
}*front,*rear,*var,*temp,*temp1,*temp2;

void enqueue_rear()
{
      temp=front;
      var=(struct rtcs *)malloc(sizeof (struct rtcs));
      if(front==NULL)
      {
                     rear=front=var;
                     front->next=NULL;
      }
      else
      {
          rear=(rear->next=var);
          rear->next=NULL;
      }
}

int cti(char z)
{
    switch(z)
    {
             case '0':return 0;
             case '1':return 1;
             case '2':return 2;
             case '3':return 3;
             case '4':return 4;
             case '5':return 5;
             case '6':return 6;
             case '7':return 7;
             case '8':return 8;
             case '9':return 9;
    }
}

void chk_time()
{
     if(temp2->at_mm>=60)
     {
                         temp2->at_mm-=60;
                         temp2->at_hh+=1;
                         if(temp2->at_hh>=24)
                         temp2->at_hh-=24;
     }
}

void initialize()
{
     char a[8]="  T.W.O",c[3]=" - ";
     enqueue_rear();
     temp1=rear;
     strcpy(rear->status,a);
     rear->at_mm=(((cti(t[3]))*10)+(cti(t[4])));
     rear->at_hh=(((cti(t[0]))*10)+(cti(t[1])));
     rear->twt=-1;
     rear->tst=0;
     strcpy(rear->tot,c);
}

void idle()
{
     char a[10]="   IDLE  \0",c[3]=" - ";
     int y=(rand()%2)+1;
     enqueue_rear();
     temp2=rear;
     strcpy(rear->status,a);
     temp2->at_mm=at_m+sum_tst;
     chk_time();
     rear->twt=-1;
     rear->tst=(y<2) ? 1 : 2;
     strcpy(rear->tot,c);
     sum_tst+=rear->tst;
     temp1=temp2;
}

void busy(int x,int h)
{
     char a[10]="Passenger\0",c[3]=" - ",e[3]=" I ",f[3]=" II",g[3]="M.P",z='0';
     int i;
     enqueue_rear();
     temp2=rear;
     strcpy(rear->status,a);
     temp2->at_mm=front->at_mm+at_m+sum_tst;
     temp2->at_hh=front->at_hh+at_h;
     rear->tst=x;
     (x==1) ? strcpy(rear->tot,e) : (x==2) ? strcpy(rear->tot,f) : strcpy(rear->tot,g);
     if(temp1->twt==-1)
     temp2->twt=0;
     else
     temp2->twt=(temp1->twt+temp1->tst);
     temp1=temp2;
     sum_tst+=rear->tst;
     for(i=0;i<=h;i++)
     chk_time();
}

int max_wait()
{
     int a[2]={0,0};
     temp=front->next;
     while(temp!=rear->next && pn)
     {
                      if(temp->twt!=-1)
                      {
                                        if(temp->twt >= max_wt) { max_wt=temp->twt; }
                                        a[0]++;
                                        if(a[0]>a[1]) { a[1]=a[0]; }
                      }
                      else { a[0]=0; }
                      temp=temp->next;
     }
     return a[1];
}
     
void notes()
{
     printf("\n\n\n* Note:-\n\n1) This program will work only between time 9 a.m to 10 p.m");
     printf("\n\n2) If tried to run this program forcefully except the above time limit\nthen the program will automatically exit.");
     printf("\n\n3) Employee running this program must first enter his service time\nfor that particular day.");
}

void notations()
{
     printf("\n\n\n* Notations:-");
     printf("\nSome of the short-forms used in program are:");
     printf("\n\n1) A.T    \e  Arrival Time (of passenger)");
     printf("\n2) T.W.T  \e  Total Waiting Time (of passengers in queue)");
     printf("\n3) T.S.T  \e  Total Service Time (of passenger at ticket window)");
     printf("\n4) T.O.T  \e  Type Of Ticket (1st class, 2nd class or monthly pass)");
     printf("\n5) T.W.O  \e  Ticket Window Opens (Opening time of ticket window counter)");
     printf("\n6) I      \e  1st class Ticket (Takes only 1 minute of service time)");
     printf("\n7) II     \e  2nd class Ticket (Takes 2 minutes of service time)");
     printf("\n8) M.P    \e  Monthly Pass (Takes 3 minutes of service time)");
}
     
void display_stat()
{
     temp=front;
     printf("\n\n\n\t\tSTATISTICS REPORT");
     printf("\n\t\t=================");
     printf("\n\n|------------|-------|-------|-------|-------|");
     printf("\n|  Status    |  A.T  | T.W.T | T.S.T | T.O.T |");
     printf("\n|------------|-------|-------|-------|-------|");
     printf("\n|%s     | %02d:%02d |   -   |   %d   |  %s  |",temp->status,temp->at_hh,temp->at_mm,temp->tst,temp->tot);
     printf("\n|------------|-------|-------|-------|-------|");
     printf("\n|************|*******|*******|*******|*******|");
     printf("\n|------------|-------|-------|-------|-------|");
     temp=temp->next;
     if(temp!=rear)
     {
         while(temp!=rear->next)
         {
                          
                          if(temp->twt==-1)
                          printf("\n|%s   |   -   |   -   |   %d   |   -   |",temp->status,temp->tst);
                          else
                          printf("\n|%s%-3d| %02d:%02d |   %-2d  |   %d   |  %s  |",temp->status,++pn,temp->at_hh,temp->at_mm,temp->twt,temp->tst,temp->tot);
                          printf("\n|------------|-------|-------|-------|-------|");
                          temp=temp->next;
         }
     }
}

void display_info(int it_h,int it_m,int bt_h,int bt_m,int h,int m)
{
     int a=max_wait();
     printf("\n\n\n\t\tOTHER STATISTICS");
     printf("\n\t\t================");
     printf("\n\n=> Total Idle Time = %02d:%02d",it_h,it_m);
     printf("\n\n* This number indicates that the ticket counter\nwas Idle for %d hours & %02d minutes\nout of the total service time of %d hours & %02d minutes.",it_h,it_m,h,m);
     printf("\n\n\n=> Total Busy Time = %02d:%02d",bt_h,bt_m);
     printf("\n\n* This number indicates that the ticket counter\nwas Busy for %d hours & %02d minutes\nout of the total service time of %d hours & %02d minutes.",bt_h,bt_m,h,m);
     printf("\n\n\n=> Maximum Passengers = %d",pn);
     printf("\n\n* This number estimates that the ticket counter can handle\nonly %d passengers in %d hours & %02d minutes.",pn,h,m);
     printf("\n\n* This number also tells us that if the expected number of passengers\nis more than the estimated number of passengers (now it is %d)\nthen we will require more ticket window counters\nto handle all the passengers perfectly.");
     printf("\n\n\n=> Maximum Queue Size = %d",a);
     printf("\n\n* This number indicates that there are maximum of %d passengers\nsimultaneously in queue at some instance of time.",a);
     printf("\n\n\n=> Maximum Waiting Time = %d",max_wt);
     printf("\n\n* This number denotes that the passengers had to wait\nfor a maximum time of %d minutes in the queue\nbefore accessing the Ticket Window Counter.\n\n",max_wt);
     
}

void iab_time(int h,int m)
{
     int it_m=0,it_h,bt_m=0,bt_h;
     temp=front->next;
     while(temp!=rear->next)
     {
                      if(temp->twt==-1)
                      it_m+=temp->tst;
                      else
                      bt_m+=temp->tst;
                      temp=temp->next;
     }
     it_h=(it_m/60);
     it_m=(it_m%60);
     bt_h=(bt_m/60);
     bt_m=(bt_m%60);
     display_info(it_h,it_m,bt_h,bt_m,h,m);
}

int main()
{
    int x,ch,hh,h,m;
    system("color a");
    printf("======>>>>  RAILWAY  TICKET  COUNTER  SIMULATION  <<<<======");
    printf("\n\n\n* Designed By:- Pratik A. Bhudke");
    _strdate(d);       //  Gets  System  DATE
    _strtime(t);      //  Gets  System  TIME
    printf("\n\n\n* Date: %s\n* Time: %s",d,t);
    notes();
    notations();
    hh=((cti(t[0])*10)+(cti(t[1])));
    if(hh<9 || hh>21)
    {
            printf("\n\n\n\tOut Of TIME LIMIT.\nYou cannot access this program at this time.");
            printf("\nThis Program will now exit.\nPress any key to EXIT.");
            ch=getch();
            if(ch=='-')
            {
                       printf("\n\n\n    EMERGENCY   PROGRAMMER   MODE.");
                       system("color c");
                       goto L;
            }
            exit(0);
    }
L:  printf("\n\n\nEnter your service time (in hours & min):\nHours=");
    scanf("%d",&h);
    printf("Min=");
    scanf("%d",&m);
    if((h<0) || (m<0) || ((h==0) && (m==0)) || (m>=60) || (h>13))
    {
             system("color c");
             if(h>13) printf("\n\nYou cannot work for more than 13 hours in a day.\ni.e From 9 a.m to 10 p.m");
             printf("\nInvalid Time Entry. Please Enter Again.");
             goto L;
    }
    user_tst=((h*60)+m);
    initialize();
    temp1=rear;
    do
    {
               x=(rand()%4)+1;
               (x==4) ? idle() : busy(x,h);
    }while(sum_tst<=user_tst);
    display_stat();
    iab_time(h,m);
    system("color e");
    getch();
    return 0;
}
