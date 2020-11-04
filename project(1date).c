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
	gotoxy(25,28);
}
main()
{
	int speed;
	int score;
	int stage;
	int player_input, player_x=22,player_y=26;
	loby();
	
	
		for(stage=1;;stage++)
		{
			map();
			while(1)
			{
				if(kbhit())
				{
					player_input=getch();
					if(player_input==224)
					{
					player_input=getch();
						switch(player_input)
							{
								case 75: 
							if(player_x!=12)
								{
									gotoxy(player_x,player_y);
									printf("  ");
									gotoxy(player_x=player_x-2,player_y);
									printf("★");
								}
							break;
								case 77:
							if(player_x!=36)
								{
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
		}
}
