/*
���� ���� ����
*/

#include "Common.h"
#include "RecommendationPlace.h"
#include "RecommendationTime.h"

// �޴� ��� �Լ�
// �游���, �����Է�, �������
void menu() {
	const char * menuName[] = { "\n\n       1.���� ����\n", "       2.���� ���� �Է�\n", "       3.��� ����\n", "       4.�� ��\n" , "       5.�� �� ��\n"  };

	printf("\n\n       �츮 ���� ���� :-)           \n");
	for (int i = 0; i < sizeof(menuName) / sizeof(menuName[0]); i++) {
		printf("%s", menuName[i]);
	}
	printf("\n\n-----------------------------------\n\n");
	printf("       ���� : ");
}

//---------------------------------------------------------------------------------------------------------
// �� ���� �Լ� ( ����ڰ� �׷��� ������ �Է��ϸ�, ������ ���ȣ�� �Բ� �� ������ ����)
// ������ true, ���н� false ��ȯ
// �������ڴ� ����, �Լ� ������ ������ ��� �Է¹޾� ���Ͽ� ��� �� ����
void createGroup() {
	int codeTmp, tmp, totalCnt, codeCnt, * codeList;		//�ִ� 5�ڸ� 0~32767
	char code[10] = { '0' }, path[100] = { '\0' };
	FILE * fp;

	srand(time(NULL));
	codeTmp = tmp = rand();
	for (int i = 4; i >= 0; i--) {
		code[i] = codeTmp % 10 + '0';
		codeTmp /= 10;
	}
	strcpy(path, code);
	strcat(path, ".csv");

	// code�� ���� ���� ������ �����ϰ�,
	fp = fileOpen(path, "r");
	if (fp == NULL) {
		fp = fileOpen(path, "w");

		// �ѿ� �Է¹ް�, ����� 0 �����ϰ�
		while (1) {
			printf("\n       ���� ���� �� �ο� ��(��) : ");
			scanf("%d", &totalCnt);
			getchar();
			if (totalCnt >= 2) break;
		}

		fprintf(fp, "%s,%d,0\n", code, totalCnt);

		// �ð� �迭 0���� �ʱ�ȭ�ϰ�
		for (int i = 0; i < 32; i++) {
			fprintf(fp, "0,");
		}
		fprintf(fp, "\n");

		// ���ϴݰ�
		fclose(fp);

		// ���� �ڵ� �ֽ�ȭ---------------------------
		strcpy(path, "code.csv");
		fp = fileOpen(path, "r");

		fscanf(fp, "%d", &codeCnt);
		codeList = (int *)malloc(sizeof(int) * (codeCnt+1));

		for (int i = 0; i < codeCnt; i++) {
			fscanf(fp, "%d", &codeList[i]);
		}

		fclose(fp);

		fp = fileOpen(path, "wt");

		codeList[codeCnt] = tmp;
		codeCnt++;
		
		for (int i = 0; i < codeCnt-1 ; i++) {
			if (codeList[i] > tmp) {
				for (int j =codeCnt-1; j>=i; j--) {
					codeList[j + 1] = codeList[j];
				}
			}
		}

		//fseek(fp, 0, SEEK_SET);

		fprintf(fp, "%d\n", codeCnt);
		for (int i = 0; i < codeCnt; i++) {
			fprintf(fp, "%d\n", codeList[i]);
		}
		fclose(fp);
		//-------------------------------------------

		// ����ڿ��� �ڵ� �˷��ְ�
		printf("\n       �׷� �ڵ� : %s\n\n\n", code);
		printf("\n       �ƹ�Ű�� ������ ���� �޴���...\n\n");
		getchar();

		return;
	}
	else {
		printf("\n       �ٽ� �õ��� �ּ���!!\n\n");
		return;
	}
}


//---------------------------------------------------------------------------------------------------------
	// ���� 1���� ������ �Է��ϴ� �Լ�, ������ return true, ���н� false
	// �������ڴ� ����, �Լ� ������ ������ ��� �Է¹޾� ���Ͽ� ��� �� ����
void inputInfo() {
	char code[6], path[100] = { '\0' }, station[22] = { '\0' };
	Station res;
	FILE * fp;
	int trash, totalCnt, currentCnt;

	int i, k, j, x[32] = { 0 };
	char select1[5], select2[5];

	printf("\n       �׷� �ڵ�(5�ڸ�) : ");
	scanf("%s", code);
	getchar();

	strcpy(path, code);
	strcat(path, ".csv");

	fp = fileOpen(path, "r+");
	if (fp == NULL) {
		printf("\n       �׷� �ڵ尡 �������� �ʽ��ϴ�!!\n\n");
		getchar();
		return;
	}
	fscanf(fp, "%d,%d,%d", &trash, &totalCnt, &currentCnt);
	if (totalCnt == currentCnt) {
		printf("\n       �̹� ��� �ο��� �Է��ϼ̽��ϴ�.\n\n");
		getchar();
		fclose(fp);
		return;
	}

	currentCnt++;
	fseek(fp, -1, SEEK_CUR);
	fprintf(fp, "%d", currentCnt);

	fseek(fp, 0, SEEK_END);
	
	while (1)
	{
		printf("\n       ������ �ð� ����(����� x) : ");
	
		scanf("%s", select1); //���ɽ��۽ð��Է�

		if (strcmp(select1, "x") == 0) // x �Է½�(���̻� �ð� ������) ����
			break;


		if (strcmp(select1, "0900") == 0) // ���۽ð��Ͻ� 30�� ������ �� ��
			i = 0;
		if (strcmp(select1, "0930") == 0)
			i = 1;
		if (strcmp(select1, "1000") == 0)
			i = 2;
		if (strcmp(select1, "1030") == 0)
			i = 3;
		if (strcmp(select1, "1100") == 0)
			i = 4;
		if (strcmp(select1, "1130") == 0)
			i = 5;
		if (strcmp(select1, "1200") == 0)
			i = 6;
		if (strcmp(select1, "1230") == 0)
			i = 7;
		if (strcmp(select1, "1300") == 0)
			i = 8;
		if (strcmp(select1, "1330") == 0)
			i = 9;
		if (strcmp(select1, "1400") == 0)
			i = 10;
		if (strcmp(select1, "1430") == 0)
			i = 11;
		if (strcmp(select1, "1500") == 0)
			i = 12;
		if (strcmp(select1, "1530") == 0)
			i = 13;
		if (strcmp(select1, "1600") == 0)
			i = 14;
		if (strcmp(select1, "1630") == 0)
			i = 15;
		if (strcmp(select1, "1700") == 0)
			i = 16;
		if (strcmp(select1, "1730") == 0)
			i = 17;
		if (strcmp(select1, "1800") == 0)
			i = 18;
		if (strcmp(select1, "1830") == 0)
			i = 19;
		if (strcmp(select1, "1900") == 0)
			i = 20;
		if (strcmp(select1, "1930") == 0)
			i = 21;
		if (strcmp(select1, "2000") == 0)
			i = 22;
		if (strcmp(select1, "2030") == 0)
			i = 23;
		if (strcmp(select1, "2100") == 0)
			i = 24;
		if (strcmp(select1, "2130") == 0)
			i = 25;
		if (strcmp(select1, "2200") == 0)
			i = 26;
		if (strcmp(select1, "2230") == 0)
			i = 27;
		if (strcmp(select1, "2300") == 0)
			i = 28;
		if (strcmp(select1, "2330") == 0)
			i = 29;
		if (strcmp(select1, "2400") == 0)
			i = 30;

		printf("\n       ������ �ð� ��(����� x) : ");
		scanf("%s", &select2); //��ñ��� �ð� �Ǵ��� select2������ �Է�.
		getchar();
		if (strcmp(select2, "x") == 0) // x �Է½�(���̻� �ð� ������) ����
			break;

		if (strcmp(select2, "0900") == 0)
			j = 0;
		if (strcmp(select2, "0930") == 0)
			j = 1;
		if (strcmp(select2, "1000") == 0)
			j = 2;
		if (strcmp(select2, "1030") == 0)
			j = 3;
		if (strcmp(select2, "1100") == 0)
			j = 4;
		if (strcmp(select2, "1130") == 0)
			j = 5;
		if (strcmp(select2, "1200") == 0)
			j = 6;
		if (strcmp(select2, "1230") == 0)
			j = 7;
		if (strcmp(select2, "1300") == 0)
			j = 8;
		if (strcmp(select2, "1330") == 0)
			j = 9;
		if (strcmp(select2, "1400") == 0)
			j = 10;
		if (strcmp(select2, "1430") == 0)
			j = 11;
		if (strcmp(select2, "1500") == 0)
			j = 12;
		if (strcmp(select2, "1530") == 0)
			j = 13;
		if (strcmp(select2, "1600") == 0)
			j = 14;
		if (strcmp(select2, "1630") == 0)
			j = 15;
		if (strcmp(select2, "1700") == 0)
			j = 16;
		if (strcmp(select2, "1730") == 0)
			j = 17;
		if (strcmp(select2, "1800") == 0)
			j = 18;
		if (strcmp(select2, "1830") == 0)
			j = 19;
		if (strcmp(select2, "1900") == 0)
			j = 20;
		if (strcmp(select2, "1930") == 0)
			j = 21;
		if (strcmp(select2, "2000") == 0)
			j = 22;
		if (strcmp(select2, "2030") == 0)
			j = 23;
		if (strcmp(select2, "2100") == 0)
			j = 24;
		if (strcmp(select2, "2130") == 0)
			j = 25;
		if (strcmp(select2, "2200") == 0)
			j = 26;
		if (strcmp(select2, "2230") == 0)
			j = 27;
		if (strcmp(select2, "2300") == 0)
			j = 28;
		if (strcmp(select2, "2330") == 0)
			j = 29;
		if (strcmp(select2, "2400") == 0)
			j = 30;

		for (k = i; k < j; k++)
			x[k]++;  // ������ ������ �ð��뿡 �´� �迭�� ���Ҹ� 1�� ����
	}
	fprintf(fp, "%d,", currentCnt);
	for (i = 0; i < 32; i++) 
		fprintf(fp, "%d,", x[i]);
	

	while (1) {
		printf("\n       ��߿� : ");
		scanf("%s", station);
		getchar();

		res = findStation(station);
		if (strcmp(res.name, "error") == 0) {
			printf("\n       �������� �ʴ� ���Դϴ�\n\n");
		}
		else {
			printf("\n       �Է� �Ϸ�");
			break;
		}
	}

	getchar();
	fprintf(fp, "%s\n", station);

	fclose(fp);
}


//---------------------------------------------------------------------------------------------------------
// ��� Ȯ�� �Լ� 
//�������ڴ� ����, �Լ� ������ ������ ��� �Է¹޾� ���Ͽ� ��� �� ����
void showResult() {
	char code[6], path[100] = { '\0' }, result[5][22] = { '\0' };
	FILE * fp;
	Location lo;
	int placeCnt, cnt = 1, max;

	printf("\n       �׷� �ڵ�(5�ڸ�) : ");
	scanf("%s", code);
	getchar();

	strcpy(path, code);
	strcat(path, ".csv");

	fp = fileOpen(path, "r+");
	if (fp == NULL) {
		printf("\n       �׷� �ڵ尡 �������� �ʽ��ϴ�!!\n\n");
		getchar();
		return;
	}
	fclose(fp);


	max = findTime(code);
	
	if (max == 0) {
		getchar();
		return;
	}

	lo = findCenterLocation(code);

	printf("��ǥ : %lf %lf", lo.x, lo.y);
	while (1) {
		placeCnt = inCircle(lo, cnt, result);
		if (placeCnt != false) break;
		cnt++;
	}

	printf("\n       ��õ���� : ");
	for (int i = 0; i < placeCnt; i++) {
		printf(" %s�� �α�,  ", result[i]);
	}


	getchar();
}








// ���� ���丮 ��� ���
void getPath(char * path) {

	char * pstrBuffer = NULL;
	char tmp[260] = { '\0' };

	pstrBuffer = getcwd(path, _MAX_PATH);
}


// �Է¹��� ���� ���� ����
FILE *fileOpen(const char *filename, const char *mode)
{
	FILE *fp;
	if ((fp = fopen(filename, mode)) == NULL)
	{
		//printf("File open error!\n");
	}
	return fp;
}

void loveLetter() {
	printf("\n\n\n\n       To. ����~��\n");
	printf("\n       �ȳ��ϼ��� �ͽ������Դϴ�.\n");
	printf("\n       ���񽺴� ����������Ű���??\n");
	printf("\n       ���� ü�� ���̶��!! ���� ü���غ�����!!\n");
	printf("\n       ü���غ��̴ٸ�,,, �ǵ����,,,(������ ������,,)\n");
	printf("\n       1000�� ����ù��� ����� ������\n");
	printf("\n       ' �� ��   �� ��   �� �� ' �� �� �� ! ! \n");
	printf("\n\n\n       ���� : �����, �ڻ��, ������, ������\n");
	printf("\n       ���߱Ⱓ : 2018.09.03 ~ 2018.11.21(�׽�Ʈ1)\n");
	printf("\n       version : �׽�Ʈ1\n");
	printf("\n                  �����մϴ�.\n\n\n");
}