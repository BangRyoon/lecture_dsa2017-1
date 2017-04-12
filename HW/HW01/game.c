#define _GNU_SOURCE	
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<time.h>
#include<math.h>
#define MAX_SIZE 100
int luck, team_num, teamA_life, teamB_life, winner = 0;
char temp[MAX_SIZE];
char *teamA, *teamB, *ans;
int i = 0, j = 0;

typedef struct teamates {
	char *teamname;
	int id;
	int weapon;
	int life;
} teamate;

int getWeapon(int weapon) {
	luck = (rand() % 2);
	if (luck == 0)
		return weapon;
}

void selection(teamate man[], char name[], int num){
	int i;
	for (i = 0; i < num; i++){
		man[i].teamname = name;
		man[i].id = i + 1;
		man[i].weapon = (rand() % 3) + 1;
		man[i].life = 1;
	}
}

void printInfoA(teamate man[]) {
	int i;
	for (i = 0; i < team_num; i++)
		printf("Team name : %s  ID : %d weapon : %d Life : %d\n", man[i].teamname, man[i].id, man[i].weapon, man[i].life);
	printf("\n");
}

void printInfoB(teamate man[]) {
	int i;
	for (i = 0; i < team_num; i++)
		printf("Team name : %s  ID : %d weapon : 0 Life : %d\n", man[i].teamname, man[i].id, man[i].life);
	printf("\n");
}
int main(void){
	teamate *team_A, *team_B;
	srand(time(NULL));

	printf("Input player's team name : ");
	fgets(temp, sizeof(temp), stdin);
	teamA = (char*)malloc(strlen(temp) + 1);
	strcpy(teamA, temp);
	printf("Input opponent's team name : ");
	fgets(temp, sizeof(temp), stdin);
	teamB = (char*)malloc(strlen(temp) + 1);
	strcpy(teamB, temp);

	printf("Input number of players in each team : ");
	scanf("%d", &team_num);
	teamA_life = team_num;
	teamB_life = team_num;

	team_A = (teamate *)malloc(team_num * sizeof(teamate));
	team_B = (teamate *)malloc(team_num * sizeof(teamate));

	printf("\n");
	printf("Scissor = 1, Rock = 2, Paper = 3 \n");
	printf("\n");

	int k;
	for (k = 0; k < team_num; k++) {
		selection(team_A, teamA, team_num);
		selection(team_B, teamB, team_num);
	}

	printInfoA(team_A);
	printInfoB(team_B);

	do {
		printf("Choose the player(ID) in the opponent's team. \n");
		scanf("%d", &j);
		if (j > team_num + 1 || j < 1)
			continue;
		j = j - 1;
		if (team_B[j].life == 0)
			continue;
		else 
			break;
	} while (1);

	do {
		printInfoA(team_A);
		printInfoB(team_B);

		if (teamB_life == 0 || teamA_life == 0)
			break;

		if (team_A[i].weapon == team_B[j].weapon) {
			printf("DRAW!! \n");
			team_A[i].weapon = (rand() % 3) + 1;
			team_B[i].weapon = (rand() % 3) + 1;
			continue;
		}

		if (team_A[i].weapon == team_B[j].weapon + 1 || team_A[i].weapon == team_B[j].weapon - 2) {
			printf("%s %d Win!! \n", team_A[i].teamname, i + 1);
			teamB_life--;
			team_B[j].life--;
			getchar();

			if (teamB_life == 0 || teamA_life == 0)
				break;
			printInfoA(team_A);
			printInfoB(team_B);

			printf("Do you want exchange the weapon?(Y/N) \n");
			fgets(temp, sizeof(temp), stdin);
			ans = (char*)malloc(strlen(temp) + 1);
			strcpy(ans, temp);

			if (strcmp("Y\n", ans) == 0) {
				team_A[i].weapon = getWeapon(team_B[j].weapon);
				if (team_A[i].weapon == team_B[j].weapon)
					printf("weapon is changed to %d\n", team_A[i].weapon);
				else
					printf("weapon is not changed \n");
			}
			free(ans);

			do {
				printf("Choose the player(ID) in the opponent's team. \n");
				scanf("%d", &j);
				if (j > team_num + 1 || j < 1)
					continue;
				j = j - 1;
				if (team_B[j].life == 0)	continue;
				else	break;
			} while (1);
			continue;
		}

		if (team_A[i].weapon == team_B[j].weapon - 1 || team_A[i].weapon == team_B[j].weapon + 2) {
			printf("%s %d Win!! \n", team_B[j].teamname, j + 1);
			teamA_life--;
			team_A[i].life--;
			team_B[j].weapon = getWeapon(team_A[i].weapon);
			i++;
			continue;
		}
	} while (1);
	winner = (teamA_life < teamB_life) ? 1 : -1;
	if (winner > 0)
		printf("winner is %s!\n", teamB);
	else if (winner < 0)
		printf("winner is %s!\n", teamA);

	free(team_A);
	free(team_B);
	system("pause");
	return 0;
}