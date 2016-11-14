#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/socket.h>
#include<time.h>
void doprocessing (int sock) {
int n,m;
int ans[8];
int count1,count2,countA,countB;
char reply[8],compare[8],message2[80];
char *message;
char buffer[256];
//bzero(buffer,256);
//n = read(sock,buffer,256);


    if (n < 0) {
       perror("ERROR reading from socket");
       exit(1);
    }
countA=0; countB=0;
srand( time(NULL) ); 
for(count1=0;count1<4;count1++)
 {
   ans[count1]=rand()%10; 
   for(count2=0;count2<count1;count2++) 
   { 
      if(ans[count1]==ans[count2]) 
      {
      count1--; 
      } 
   }
 } 
 printf("Ans:%d%d%d%d\n",ans[0],ans[1],ans[2],ans[3]);
    while(1){
    	bzero(buffer,256);
 	n=read(sock,buffer,256);
 	compare[0]=(buffer[0]-'0');
 	compare[1]=(buffer[1]-'0');
 	compare[2]=(buffer[2]-'0');
 	compare[3]=(buffer[3]-'0');
 	
 	for(count1=0;count1<4;count1++)
 	{
 		if(ans[count1]==compare[count1]) 
 		{
 			countA+=1;
 		}
 	}
 	
 	for(count2=0;count2<=3;count2++)
 	{
 		for(count1=0;count1<=3;count1++)
 		{
 			if(compare[count1]==ans[count2] && count1!=count2)
 			{
 				countB++;
 			}
 		}
 	}
 
 	if(countA==4)
 	{
 	
 		message="This game end!!";
		write(sock , message, strlen(message)+1);
 		
 	}
 	else
 	{
 		sprintf(message2,"%dA%dB",countA,countB);
 	        write(sock,message2,strlen(message2)+1);
 		countA=0;countB=0;
 	}
    }
	//printf("Here is the message: %s\n",buffer);
       //n = write(sock,"I got your message",18);
    
    if (n < 0) {
       perror("ERROR writing to socket");
       exit(1);
    }
 	
 }
