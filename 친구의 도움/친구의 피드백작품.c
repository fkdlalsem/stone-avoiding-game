#include<stdio.h>
#include<windows.h> 

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

char answer;
char *block[2]={"■","  "};
int player_input, player_x=24,player_y=26;
int point,i;
int sum_point=0,sleep_point = 10;
	
void loby()																					//로비구현 
{
	int temp;
	gotoxy(30,17);
	printf("---------------------------------------------------");
	gotoxy(30,7);
	printf("---------------------------------------------------");
	gotoxy(50,9);
	printf("돌 피하기 게임");
	gotoxy(48,14);
	printf("시작 : s 종료 : b"); 
	for(temp=1;temp<10;temp++)
	{
		gotoxy(30,7+temp);
		printf("|");
		gotoxy(80,7+temp);
		printf("|");
	}
	gotoxy(56,17);
	do{
	answer=getch();
	}while(answer!='s'&&answer!='b'&&answer!='S'&&answer!='B');
	system("cls");
}

void map()																				   //게임 스테이지맵 구현 
{
	int x,y;
	
	for(x=5;x<20;x++)
	{
		for(y=5;y<28;y++)
		{
			if((x==5)||(x==19)||(y==5)||(y==27))
			{
			gotoxy((x*2),y);
			printf("■");
			}
			Sleep(1);

		}
	}
	Sleep(100);
	gotoxy(22,3);
	printf("STAGE 1");
	gotoxy(45,6);
	printf("점수 : 0"); 
	gotoxy(25,28);
}

void count3(int count_input_delete,int x,int y)											//카운트 3 
{

	if(y==12||y==16||y==20||x==14)
		{
		gotoxy((x*2),y);
		printf("%s",block[count_input_delete]);
		Sleep(5);
		}
	gotoxy(25,28);
}

void count2(int count_input_delete,int x,int y)											//카운트 2 
{
		if(y==12||y==16||y==20||(x==14&&y<17)||(x==10&&y>16))
			{
			gotoxy((x*2),y);
			printf("%s",block[count_input_delete]);
			Sleep(5);
			}	
	gotoxy(25,28);
}

void count1(int count_input_delete,int x,int y)										   //카운트 1 
{
		if(x==12||(y==12&&x<=12)||y==20)
			{
			gotoxy((x*2),y);
			printf("%s",block[count_input_delete]);
			Sleep(5);
			}
	gotoxy(25,28);
}

void countdown()															          //카운트 틀 
{
	int x,y;
	int count_input_delete;
	int count;
	
	for(count=1;count<4;count++)
	{
		for(count_input_delete=0;count_input_delete<2;count_input_delete++)
		{
			for(x=10;x<15;x++)
			{
				for(y=12;y<21;y++)
				{	
					if(count==1)
					{
						count3(count_input_delete,x,y);
					}
					else if(count==2)
					{
						count2(count_input_delete,x,y);
					}
					else
					{
						count1(count_input_delete,x,y);
					}
				}
			}	
					Sleep(900);
		}
	}
}

void player_down()
{
	int y=23;
	for(y;y<27;y++)
	{
		gotoxy(24,y);
		printf("★");
		gotoxy(24,y-1);
		printf("  ");
		Sleep(500);
	}
	gotoxy(25,28);
}

void score(int stage){
	int score_speed[30]={100,80,60,50,20,10,9,8,7,6,5,4,3,2,1};
	
	 if(point++%sleep_point==0) sum_point++;
	Sleep(score_speed[stage-1]);
	gotoxy(52,6);
	printf("%d",sum_point);
	gotoxy(25,28);
}

void player_moving(int stage){
	int block_y[10]={0}; 
	int block_x[1000];
	int block_count[10];
	int n=1;
	
	srand(time(NULL));
	for(block_count[0]=0;block_count[0]<1000;block_count[0]++){
		block_x[block_count[0]]=11+rand()%24;
		if(block_x[block_count[0]]%2==1){
			block_x[block_count[0]]++;
		}
	}
	block_count[0]=0;
	 
	while(1){
		
		score(stage);
		for(i=0;i<n;i++){
		
			if(block_y[i]==0) block_y[i]=5;
			
			if(block_y[i]!=6)	{
				gotoxy(block_x[block_count[i]],block_y[i]-1);
				printf("  ");
			}
			
			if(block_y[i]!=27)	{
				gotoxy(block_x[block_count[i]],block_y[i]++);
				printf("■");
			}
			else	{
				block_y[i]=5;
				block_count[i]++;
			}
		}
		
		if(kbhit()){
			player_input=getch();
			
			if(player_input == 32){
				sleep_point+=10;
				n++;
			} 
			
			if(player_input==224){
				player_input=getch();
				
				switch(player_input){
					case 75: 
						if(player_x!=12){
							gotoxy(player_x,player_y);
							printf("  ");
							gotoxy(player_x=player_x-2,player_y);
							printf("★");
							}
						break;
					case 77:
						if(player_x!=36)	{
							gotoxy(player_x,player_y);
							printf("  ");
							gotoxy(player_x=player_x+2,player_y);
							printf("★");
							}
						break;
				}
			}
		}
	}
	gotoxy(25,28);
}
main()
{
	int speed;
	int stage;
	loby();
	
	
		for(stage=1;;stage++)
		{
			map();
			//Sleep(1000);
			//countdown();  빠른 디버깅을 위한 제어 
			player_down();
			player_moving(stage);
		}
}
