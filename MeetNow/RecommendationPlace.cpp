#include "RecommendationPlace.h"



//-------------------------------------------------------------------------------------
// ���̸��� ������ �ش� ���� ��ǥ�� ��ȯ
// ������ �� ���� ����
// ������ ���̸��� error��
Station findStation(char * stationName) {
	char tmp[24] = { '\0' }, path[_MAX_PATH] = { '\0' };
	Station st = { '\0' };
	FILE * fp;
	int i = 0;

	getPath(path);
	//strcpy(path,"C:\\Users\\tmvoa\\source\\repos\\MeetNow\\MeetNow\\");.0
	strcat(path, "\\AllStationList.csv");
	fp = fileOpen(path, "r");			// ���� ����

	// �ݺ������� ������ �о� ã�� ���� �ִ��� Ȯ��
	while (i<allStation) {
		//fscanf(fp, "%[^,]s%lf,%lf", st.name, &st.x, &st.y);
		//fscanf(fp, "%[^,]s%lf,%lf", st.name, &st.x, &st.y);
		fscanf(fp, "%lf,%lf,%s", &st.x, &st.y, st.name);
		if (strcmp(st.name, stationName) == 0) {
			return st;
			break;
		}

		i++;
	}
	strcpy(st.name, "error");

	fclose(fp);
	return st;
}



//-------------------------------------------------------------------------------------
// �׷������� ������ �Էµ� ��߿����� ��� ��ǥ�� ���� ��ȯ
Location findCenterLocation(char * groupCode) {						
	char path[_MAX_PATH] = { '\0' }, code[10] = { '\0' }, **find=NULL;
	FILE * fp;
	int cnt, trash, maxPersonCnt, currentPersonCnt;
	Station  findSt;
	Location lo = { 0,0 };

	//getPath(path);
	////strcpy(path,"C:\\Users\\tmvoa\\source\\repos\\MeetNow\\MeetNow\\");
	//strcat(path, "\\");

	strcpy(path, groupCode);
	strcat(path, ".csv");
	fp = fileOpen(path, "r+");			// ���� ����

	fscanf(fp, "%d,%d,%d,",&trash, &maxPersonCnt, &currentPersonCnt);
	for (int i = 0; i < 31; i++) fscanf(fp, ",%d", &trash);

	find = (char **)malloc(sizeof(char *)*currentPersonCnt);
	for (int i = 0; i < currentPersonCnt; i++) {
		find[i] = (char *)malloc(sizeof(char) * 22);
	}

	for (int i = 0; i < 32; i++) 	fscanf(fp, "%d,", &trash);

	for (int j = 0; j < currentPersonCnt; j++) {
		for (int i = 0; i < 33; i++) 	fscanf(fp, "%d,", &trash);
		fscanf(fp, "%s\n", find[j]);
	}
	//for (int i = 0; i < currentPersonCnt; i++) {
	//	fscanf(fp, "%s\n", find[i]);
	//	fseek(fp, -34, SEEK_CUR);
	//}

	for (int i = 0; i < currentPersonCnt; i++) {
		findSt = findStation(find[i]);
		lo.x += findSt.x;
		lo.y += findSt.y;
	}
	lo.x /= currentPersonCnt;
	lo.y /= currentPersonCnt;

	/*if (currentPersonCnt == maxPersonCnt) {
		printf("���� �Է� �Ϸ�,,, �����,,,\n");
	}
	else {
		printf("���� %d/%d�� �Է�,,,�����,,,\n", currentPersonCnt, maxPersonCnt);
	}*/

	for (int i = 0; i < currentPersonCnt; i++) {
		free(find[i]);
	}
	free(find);

	return lo;
}





//-------------------------------------------------------------------------------------
/*
location �߽����� ������ r�� ���ȿ� ��ȭ���� ���ԵǴ��� Ȯ�� �� ��ȯ

#��������
center : �˻��� �߽ɿ� ��ǥ
count : ���° Ȯ������
resultStation : Ž���� ��ȭ���� �̸�

#����
cnt : Ž���ϴ� �� ī��Ʈ
findCnt : ���Ե� ��ȭ�� �� ��
tmpX, tmpY : ��ǥ����� ���� �ӽ� ����
realRadius : Ȯ�� Ƚ���� �ݿ��� Ȯ��� ������
hotStation : ���Ϸκ��� �о�� �߽ɿ� ����
*/
int inCircle(Location center, int count, char resultStation[5][22]) {
	int cnt = 0, findCnt=0, i=0;
	double tmpX, tmpY, realRadius;
	Station hotStation;
	char path[_MAX_PATH] = { '\0' };
	FILE * fp;

	realRadius = radius * count;

	getPath(path);
	//strcpy(path,"C:\\Users\\tmvoa\\source\\repos\\MeetNow\\MeetNow\\");
	strcat(path, "\\HotPlaceList.csv");
	fp = fileOpen(path, "r");			// ���� ����


	while (1) {
		// ���� ��������� hotStation �� ��ȭ�� ���� �Է�
		fscanf(fp, "%lf,%lf,%s", &hotStation.x, &hotStation.y, hotStation.name);

		tmpX = hotStation.x - center.x;
		tmpY = hotStation.y - center.y;

		tmpX *= tmpX;
		tmpY *= tmpY;

		tmpX = tmpX;
		tmpY = tmpY;

		if (tmpX + tmpY < realRadius*realRadius) {		// ���� �����ȿ� ���ԵǸ�
			strcpy(resultStation[findCnt++], hotStation.name);
			//printf("%s\n", hotStation.name);
		}

		cnt++;

		if (cnt == HotPlaceStation) break;
	}

	if (findCnt == 0) return false;				// false = 0 ��.
	else return findCnt;								// Ž���� ���� ���� ��ȯ
}


