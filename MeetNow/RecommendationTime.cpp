#include "RecommendationTime.h"
#pragma warning(disable:4996)



int findTime(char * code) {
	
	char path[_MAX_PATH] = { '\0' }, tmp[22] = { '\0' };
	FILE * fp;
	int cnt, trash, maxPersonCnt, currentPersonCnt, max, trigger=-1;
	Station  findSt;
	int time[32] = { 0 }, num=0, start, end;
	char clock[33][10] = { { "9시" }, // 시간대 알려주는 변수
	{ "9시30분" },
	{ "10시" },
	{ "10시30분" },
	{ "11시" } ,
	{ "11시30분" },
	{ "12시" } ,
	{ "12시30분" },
	{ "13시" } ,
	{ "13시30분" },
	{ "14시" } ,
	{ "14시30분" },
	{ "15시" } ,
	{ "15시30분" },
	{ "16시" } ,
	{ "16시30분" },
	{ "17시" } ,
	{ "17시30분" },
	{ "18시" } ,
	{ "18시30분" },
	{ "19시" } ,
	{ "19시30분" },
	{ "20시" } ,
	{ "20시30분" },
	{ "21시" } ,
	{ "21시30분" },
	{ "22시" } ,
	{ "22시30분" },
	{ "23시" } ,
	{ "23시30분" },
	{ "24시" } ,
	{"24시 ~ "} };

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
		printf("\n       모두 가능한 시간 : " );
	}
	else if (max <= 1) {
		printf("\n       모두 가능한 시간이 없습니다.... ");
		return 0;
	}
	else 
		printf("\n       %d명 가능한 시간 : ", max);


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