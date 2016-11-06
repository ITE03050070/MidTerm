#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<time.h>
#include<stdlib.h>
int main(int argc , char *argv[])
{
int socket_desc , new_socket , c;
int ans[8];
int count1,count2,countA,countB;

struct sockaddr_in server , client;
char *message;
char reply[8],compare[8],message2[80];
//time_t mytime;
//mytime=time(NULL);
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8787 );
//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");
//Listen
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
{
puts("Connection accepted");

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
//Reply to the client
while(1)
{
	bzero(reply,8);
	read(new_socket,reply,8);
	compare[0]=(reply[0]-'0');
	compare[1]=(reply[1]-'0');
	compare[2]=(reply[2]-'0');
	compare[3]=(reply[3]-'0');
	
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
		write(new_socket , message, strlen(message)+1);
		return 1;
	}
	else
	{
		sprintf(message2,"%dA%dB",countA,countB);
		write(new_socket , message2, strlen(message2)+1);
		countA=0;countB=0;
	}
/*for(i=0;i<4&&(cn[i]=rand()%10+48);i++) //產生電腦數字

        	for(j=0;j<i;j++) cn[j]==cn[i]&&i--; //檢查重複

   	 do{

        	na=nb=i=scanf("%4s",un)&0; fflush(stdin);

        	for(;i<4;i++) for(j=0;j<4;j++) un[i]==cn[j]&&(i==j?na++:nb++); //計算幾A幾B

        	na-4&&--times&&printf("結果：%dA%dB，還有%d次機會...\n", na,nb,times);

   		 }	
	while(na-4&&times); //迴圈猜times次

   	 na==4?puts("您猜對了！"):printf("失敗，猜超過10次，答案是%s\n",cn);

    	return system("pause"); */ 
	
}

}
if (new_socket<0)
{
perror("accept failed");
return 1;
}
return 0;
}
