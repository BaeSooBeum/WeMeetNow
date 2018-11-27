#include "RecommendationPlace.h"



//-------------------------------------------------------------------------------------
// 역이름을 전달해 해당 역의 좌표를 반환
// 있으면 그 역의 정보
// 없으면 역이름을 error로
Station findStation(char * stationName) {
	char tmp[24] = { '\0' }, path[_MAX_PATH] = { '\0' };
	Station st = { '\0' };
	FILE * fp;
	int i = 0;

	getPath(path);
	//strcpy(path,"C:\\Users\\tmvoa\\source\\repos\\MeetNow\\MeetNow\\");.0
	strcat(path, "\\AllStationList.csv");
	fp = fileOpen(path, "r");			// 파일 열기

	// 반복적으로 파일을 읽어 찾는 역이 있는지 확인
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
// 그룹정보를 전달해 입력된 출발역들의 평균 좌표를 구해 반환
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
	fp = fileOpen(path, "r+");			// 파일 열기

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
		printf("전원 입력 완료,,, 계산중,,,\n");
	}
	else {
		printf("현재 %d/%d명 입력,,,계산중,,,\n", currentPersonCnt, maxPersonCnt);
	}*/

	for (int i = 0; i < currentPersonCnt; i++) {
		free(find[i]);
	}
	free(find);

	return lo;
}





//-------------------------------------------------------------------------------------
/*
location 중심으로 반지름 r의 원안에 번화가가 포함되는지 확인 후 반환

#전달인자
center : 검색의 중심역 좌표
count : 몇번째 확장인지
resultStation : 탐색된 번화가역 이름

#변수
cnt : 탐색하는 역 카운트
findCnt : 포함된 번화가 역 수
tmpX, tmpY : 좌표계산을 위함 임시 변수
realRadius : 확장 횟수를 반영한 확장된 반지름
hotStation : 파일로부터 읽어올 중심역 정보
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
	fp = fileOpen(path, "r");			// 파일 열기


	while (1) {
		// 파일 입출력으로 hotStation 에 번화가 정보 입력
		fscanf(fp, "%lf,%lf,%s", &hotStation.x, &hotStation.y, hotStation.name);

		tmpX = hotStation.x - center.x;
		tmpY = hotStation.y - center.y;

		tmpX *= tmpX;
		tmpY *= tmpY;

		tmpX = tmpX;
		tmpY = tmpY;

		if (tmpX + tmpY < realRadius*realRadius) {		// 만약 범위안에 포함되면
			strcpy(resultStation[findCnt++], hotStation.name);
			//printf("%s\n", hotStation.name);
		}

		cnt++;

		if (cnt == HotPlaceStation) break;
	}

	if (findCnt == 0) return false;				// false = 0 임.
	else return findCnt;								// 탐색된 역의 갯수 반환
}


