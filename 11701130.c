#include <stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
sem_t var1;
void p_available();
void pre_match();
int flag=0;
void pre_match()
{
    int choice;
    if(flag==0)
        {
            printf("Match has finished.Do you want to start new one?(yes:1/no:2)\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                p_available();
            }
            else
            {
                printf("Thanks for playing!");
                exit(0);
            }
        }    
    else
    if(flag==1)
    {
        printf("Match in progress!");
        exit(0);
    }
}
void *game()
{
    sem_wait(&var1);
    printf("All the three players are ready to play. Match started! ");
    flag=1;
    sem_post(&var1);
    exit(0);
}
void p_available()
{
    printf("Welcome!\n");
    int p[3];
    for(int i=0;i<3;i++)
    {
        printf("Is player %d ready to play?(yes:1/no:2)",i+1);
        scanf("%d",&p[i]);
    }
    if(p[0]==1&&p[1]==1&&p[2]==1)
        {
            pthread_t t1;
            pthread_create(&t1,NULL,&game,NULL);
            pthread_join(t1,NULL);
        }
    else
        {
            printf("Not all players ready to play. Try again!");
            p_available();
        }
}
int main()
{
    printf("Matchmaking game\n");
    sem_init(&var1,0,1);
    pre_match();
    p_available();
}