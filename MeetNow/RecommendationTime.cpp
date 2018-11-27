#include "RecommendationTime.h"
#pragma warning(disable:4996)



int findTime(char * code) {
	
	char path[_MAX_PATH] = { '\0' }, tmp[22] = { '\0' };
	FILE * fp;
	int cnt, trash, maxPersonCnt, currentPersonCnt, max, trigger=-1;
	Station  findSt;
	int time[32] = { 0 }, num=0, start, end;
	char clock[33][10] = { { "9��" }, // �ð��� �˷��ִ� ����
	{ "9��30��" },
	{ "10��" },
	{ "10��30��" },
	{ "11��" } ,
	{ "11��30��" },
	{ "12��" } ,
	{ "12��30��" },
	{ "13��" } ,
	{ "13��30��" },
	{ "14��" } ,
	{ "14��30��" },
	{ "15��" } ,
	{ "15��30��" },
	{ "16��" } ,
	{ "16��30��" },
	{ "17��" } ,
	{ "17��30��" },
	{ "18��" } ,
	{ "18��30��" },
	{ "19��" } ,
	{ "19��30��" },
	{ "20��" } ,
	{ "20��30��" },
	{ "21��" } ,
	{ "21��30��" },
	{ "22��" } ,
	{ "22��30��" },
	{ "23��" } ,
	{ "23��30��" },
	{ "24��" } ,
	{"24�� ~ "} };

	strcpy(path, code);
	strcat(path, ".csv");

	fp = fileOpen(path, "r+");

	fscanf(fp, "%d,%d,%d,", &trash, &maxPersonCnt, &currentPersonCnt);
	for (int i = 0; i < 31; i++) fscanf(fp, ",%d", &trash);
	for (int i = 0; i < 32; i++) 	fscanf(fp, "%d,", &trash);

	for (int j = 0; j <= currentPersonCnt; j++) {
		fscanf(fp, "%d,", &trash);

		for (int i = 0; i < 32; i++) {
			fscanf(fp, "%d,", &num);
			time[i] += num;
		}
		//strcpy(tmp, "");
		fscanf(fp, "%s\n", tmp);
	}

	max = 0;
	for (int i = 0; i < 32; i++) {
		if (time[i] > max) max = time[i];
	}

	if (max == maxPersonCnt) {
		printf("\n       ��� ������ �ð� : " );
	}
	else if (max <= 1) {
		printf("\n       ��� ������ �ð��� �����ϴ�.... ");
		return 0;
	}
	else 
		printf("\n       %d�� ������ �ð� : ", max);


	for (int i = 0; i < 32; i++) {
		if (time[i] == max) {
			if (trigger == -1) {
				printf("%s ~ ", clock[i]);
				trigger = 0;
			}
			end = i;
		}
		if (time[i] != max && trigger == 0) {
			printf("%s, ", clock[i]);
			trigger = -1;
		}
	}

	return max;
}