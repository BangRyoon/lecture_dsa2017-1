#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define MAX_SIZE 100
int team_num, teamA_life, teamB_life, winner = 0;	//team_Life 는 팀 전체 목숨의 합

typedef struct teamates {
	char *teamname;
	int id;
	int weapon;
	int life;
} teamate;

int getWeapon(int weapon) {	//50%확률로 적의 무기와 교환
	srand(time(NULL));
	int luck = (rand() % 2);
	if (luck == 0)
		return weapon;
}

void selection(teamate man[], char name[], int num)	//num개의 구조체 생성, teamname 으로 구분
{
	for (int i = 0; i < num; i++)
	{
		man[i].teamname = name;
		man[i].id = i + 1;
		man[i].weapon = (rand() % 3) + 1;//가위 = 1, 바위 = 2, 보 = 3
		man[i].life = 1;
	}
}

int main(void)
{
	char teamA[MAX_SIZE], teamB[MAX_SIZE];
	teamate *team_A, *team_B;

	int i = 0, j = 0;
	char ans[10];
	srand(time(NULL));

	printf("Input player's team name : ");
	gets(teamA);
	printf("Input opponent's team name : ");
	gets(teamB);
	printf("Input number of players in each team : ");
	scanf_s("%d", &team_num);	//
	printf("가위 = 1, 바위 = 2, 보 = 3 \n");
	teamA_life = team_num;
	teamB_life = team_num;

	team_A = (int *)malloc(team_num * sizeof(teamate));	//team_num의 구조체가 들어갈 수 있는 메모리 할당
	team_B = (int *)malloc(team_num * sizeof(teamate));

	for (int i = 0; i < team_num; i++) {	//구조체 생성
		selection(team_A, teamA, team_num);
		selection(team_B, teamB, team_num);
	}

	for (int i = 0; i < team_num; i++)	//각 팀의 상황 출력
		printf("팀이름 : %s  ID : %d 무기 : %d 목숨 : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
	printf("\n");
	for (int i = 0; i < team_num; i++)
		printf("팀이름 : %s  ID : %d 무기 : 0 목숨 : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);//무기상태 출력하지 않음
	printf("\n");

	do {	//적의 아이디 입력을 통해 다음 상대 선택
		printf("Choose the player(ID) in the opponent's team. \n");
		scanf_s("%d", &j);
		if (j > team_num + 1 || j < 1)
			continue;
		j = j - 1;
		if (team_B[j].life == 0)	//선택한 적의 목숨이 0일 경우 재선택
			continue;
		else break;
	} while (1);

	do {
		if (teamB_life == 0 || teamA_life == 0)	//한팀의 목숨의 합이 0이 될 때 종료
			break;

		if (team_A[i].weapon == team_B[j].weapon) {	//무승부시 무기 재분배
			printf("DRAW!! \n");

			team_A[i].weapon = (rand() % 3) + 1;
			team_B[i].weapon = (rand() % 3) + 1;
			continue;
		}
		if (team_A[i].weapon == team_B[j].weapon + 1 || team_A[i].weapon == team_B[j].weapon - 2) {	//teamA의 승리
			printf("%s %d Win!! \n", team_A[i].teamname, i + 1);

			teamB_life--;	//teamB의 목숨 1 감소
			team_B[j].life--;	//teamB의 플레이어 목숨 = 0
			getchar();

			for (int i = 0; i < team_num; i++)	//각 팀의 상황 출력
				printf("팀이름 : %s  ID : %d 무기 : %d 목숨 : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
			printf("\n");
			for (int i = 0; i < team_num; i++)
				printf("팀이름 : %s  ID : %d 무기 : 0 목숨 : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);
			printf("\n");

			if (teamB_life == 0 || teamA_life == 0)	//한팀의 목숨의 합이 0이 될 때 종료
				break;
			printf("Do you want exchange the weapon?(Y/N) \n");//무기 교환 의사 질문
			gets(ans);

			if (ans == "Y")	//교환 의사가 있는 경우 확률에 따라 교환
				team_A[i].weapon = getWeapon(team_B[j].weapon);

			do {	//적의 아이디 입력을 통해 다음 상대 선택
				printf("Choose the player(ID) in the opponent's team. \n");
				scanf_s("%d", &j);
				if (j > team_num + 1 || j < 1)
					continue;
				j = j - 1;
				if (team_B[j].life == 0)	//선택한 적의 목숨이 0일 경우 재선택
					continue;
				else break;
			} while (1);
			for (int i = 0; i < team_num; i++)	//각 팀의 상황 출력
				printf("팀이름 : %s  ID : %d 무기 : %d 목숨 : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
			printf("\n");
			for (int i = 0; i < team_num; i++)
				printf("팀이름 : %s  ID : %d 무기 : 0 목숨 : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);
			printf("\n");
			continue;
		}

		if (team_A[i].weapon == team_B[j].weapon - 1 || team_A[i].weapon == team_B[j].weapon + 2) {	//teamB의 승리
			printf("%s %d Win!! \n", team_B[j].teamname, j + 1);

			teamA_life--;	//teamA의 목숨 1 감소
			team_A[i].life--;	//teamA의 플레이서 목숨 = 0

			int luck = (rand() % 2);	//50%확률로 적의 무기 변화
			if (luck == 0)
				team_B[j].weapon = getWeapon(team_A[i].weapon);
			i++;	//teamA의 다음 선수 출전

			for (int i = 0; i < team_num; i++)	//각 팀의 상황 출력
				printf("팀이름 : %s  ID : %d 무기 : %d 목숨 : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
			printf("\n");
			for (int i = 0; i < team_num; i++)
				printf("팀이름 : %s  ID : %d 무기 : 0 목숨 : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);
			printf("\n");

			continue;
		}
	} while (1);
	winner = (teamA_life < teamB_life) ? 1 : -1;//목숨수가 많은 팀이 승리

	if (winner > 0)
		printf("winner is %s!\n", teamB);
	else if (winner < 0)
		printf("winner is %s!\n", teamA);

	free(team_A);	//메모리 할당 해제
	free(team_B);
	return 0;
}
