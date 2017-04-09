#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define MAX_SIZE 100
int team_num, teamA_life, teamB_life, winner = 0;	//team_Life �� �� ��ü ����� ��

typedef struct teamates {
	char *teamname;
	int id;
	int weapon;
	int life;
} teamate;

int getWeapon(int weapon) {	//50%Ȯ���� ���� ����� ��ȯ
	srand(time(NULL));
	int luck = (rand() % 2);
	if (luck == 0)
		return weapon;
}

void selection(teamate man[], char name[], int num)	//num���� ����ü ����, teamname ���� ����
{
	for (int i = 0; i < num; i++)
	{
		man[i].teamname = name;
		man[i].id = i + 1;
		man[i].weapon = (rand() % 3) + 1;//���� = 1, ���� = 2, �� = 3
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
	printf("���� = 1, ���� = 2, �� = 3 \n");
	teamA_life = team_num;
	teamB_life = team_num;

	team_A = (int *)malloc(team_num * sizeof(teamate));	//team_num�� ����ü�� �� �� �ִ� �޸� �Ҵ�
	team_B = (int *)malloc(team_num * sizeof(teamate));

	for (int i = 0; i < team_num; i++) {	//����ü ����
		selection(team_A, teamA, team_num);
		selection(team_B, teamB, team_num);
	}

	for (int i = 0; i < team_num; i++)	//�� ���� ��Ȳ ���
		printf("���̸� : %s  ID : %d ���� : %d ��� : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
	printf("\n");
	for (int i = 0; i < team_num; i++)
		printf("���̸� : %s  ID : %d ���� : 0 ��� : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);//������� ������� ����
	printf("\n");

	do {	//���� ���̵� �Է��� ���� ���� ��� ����
		printf("Choose the player(ID) in the opponent's team. \n");
		scanf_s("%d", &j);
		if (j > team_num + 1 || j < 1)
			continue;
		j = j - 1;
		if (team_B[j].life == 0)	//������ ���� ����� 0�� ��� �缱��
			continue;
		else break;
	} while (1);

	do {
		if (teamB_life == 0 || teamA_life == 0)	//������ ����� ���� 0�� �� �� ����
			break;

		if (team_A[i].weapon == team_B[j].weapon) {	//���ºν� ���� ��й�
			printf("DRAW!! \n");

			team_A[i].weapon = (rand() % 3) + 1;
			team_B[i].weapon = (rand() % 3) + 1;
			continue;
		}
		if (team_A[i].weapon == team_B[j].weapon + 1 || team_A[i].weapon == team_B[j].weapon - 2) {	//teamA�� �¸�
			printf("%s %d Win!! \n", team_A[i].teamname, i + 1);

			teamB_life--;	//teamB�� ��� 1 ����
			team_B[j].life--;	//teamB�� �÷��̾� ��� = 0
			getchar();

			for (int i = 0; i < team_num; i++)	//�� ���� ��Ȳ ���
				printf("���̸� : %s  ID : %d ���� : %d ��� : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
			printf("\n");
			for (int i = 0; i < team_num; i++)
				printf("���̸� : %s  ID : %d ���� : 0 ��� : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);
			printf("\n");

			if (teamB_life == 0 || teamA_life == 0)	//������ ����� ���� 0�� �� �� ����
				break;
			printf("Do you want exchange the weapon?(Y/N) \n");//���� ��ȯ �ǻ� ����
			gets(ans);

			if (ans == "Y")	//��ȯ �ǻ簡 �ִ� ��� Ȯ���� ���� ��ȯ
				team_A[i].weapon = getWeapon(team_B[j].weapon);

			do {	//���� ���̵� �Է��� ���� ���� ��� ����
				printf("Choose the player(ID) in the opponent's team. \n");
				scanf_s("%d", &j);
				if (j > team_num + 1 || j < 1)
					continue;
				j = j - 1;
				if (team_B[j].life == 0)	//������ ���� ����� 0�� ��� �缱��
					continue;
				else break;
			} while (1);
			for (int i = 0; i < team_num; i++)	//�� ���� ��Ȳ ���
				printf("���̸� : %s  ID : %d ���� : %d ��� : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
			printf("\n");
			for (int i = 0; i < team_num; i++)
				printf("���̸� : %s  ID : %d ���� : 0 ��� : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);
			printf("\n");
			continue;
		}

		if (team_A[i].weapon == team_B[j].weapon - 1 || team_A[i].weapon == team_B[j].weapon + 2) {	//teamB�� �¸�
			printf("%s %d Win!! \n", team_B[j].teamname, j + 1);

			teamA_life--;	//teamA�� ��� 1 ����
			team_A[i].life--;	//teamA�� �÷��̼� ��� = 0

			int luck = (rand() % 2);	//50%Ȯ���� ���� ���� ��ȭ
			if (luck == 0)
				team_B[j].weapon = getWeapon(team_A[i].weapon);
			i++;	//teamA�� ���� ���� ����

			for (int i = 0; i < team_num; i++)	//�� ���� ��Ȳ ���
				printf("���̸� : %s  ID : %d ���� : %d ��� : %d\n", team_A[i].teamname, team_A[i].id, team_A[i].weapon, team_A[i].life);
			printf("\n");
			for (int i = 0; i < team_num; i++)
				printf("���̸� : %s  ID : %d ���� : 0 ��� : %d\n", team_B[i].teamname, team_B[i].id, team_B[i].life);
			printf("\n");

			continue;
		}
	} while (1);
	winner = (teamA_life < teamB_life) ? 1 : -1;//������� ���� ���� �¸�

	if (winner > 0)
		printf("winner is %s!\n", teamB);
	else if (winner < 0)
		printf("winner is %s!\n", teamA);

	free(team_A);	//�޸� �Ҵ� ����
	free(team_B);
	return 0;
}
