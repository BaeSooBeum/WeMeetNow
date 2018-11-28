/*
공통 사항 관련
*/

#include "Common.h"
#include "RecommendationPlace.h"
#include "RecommendationTime.h"

// 메뉴 출력 함수
// 방만들기, 개인입력, 결과보기
void menu() {
	const char * menuName[] = { "\n\n       1.모임 개설\n", "       2.개인 정보 입력\n", "       3.결과 보기\n", "       4.종 료\n" , "       5.도 움 말\n"  };

	printf("\n\n       우리 지금 만나 :-)           \n");
	for (int i = 0; i < sizeof(menuName) / sizeof(menuName[0]); i++) {
		printf("%s", menuName[i]);
	}
	printf("\n\n-----------------------------------\n\n");
	printf("       선택 : ");
}

//---------------------------------------------------------------------------------------------------------
// 방 개설 함수 ( 사용자가 그룹의 정보를 입력하면, 랜덤의 방번호와 함께 방 파일이 생성)
// 성공시 true, 실패시 false 반환
// 전달인자는 없고, 함수 내에서 정보를 모두 입력받아 파일에 출력 후 저장
void createGroup() {
	int codeTmp, tmp, totalCnt, codeCnt, * codeList;		//최대 5자리 0~32767
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

	// code와 같은 파일 없으면 생성하고,
	fp = fileOpen(path, "r");
	if (fp == NULL) {
		fp = fileOpen(path, "w");

		// 총원 입력받고, 현재원 0 셋팅하고
		while (1) {
			printf("\n       모임 참가 총 인원 수(명) : ");
			scanf("%d", &totalCnt);
			getchar();
			if (totalCnt >= 2) break;
		}

		fprintf(fp, "%s,%d,0\n", code, totalCnt);

		// 시간 배열 0으로 초기화하고
		for (int i = 0; i < 32; i++) {
			fprintf(fp, "0,");
		}
		fprintf(fp, "\n");

		// 파일닫고
		fclose(fp);

		// 파일 코드 최신화---------------------------
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

		// 사용자에게 코드 알려주고
		printf("\n       그룹 코드 : %s\n\n\n", code);
		printf("\n       아무키나 누르면 이전 메뉴로...\n\n");
		getchar();

		return;
	}
	else {
		printf("\n       다시 시도해 주세요!!\n\n");
		return;
	}
}


//---------------------------------------------------------------------------------------------------------
	// 유저 1명의 정보를 입력하는 함수, 성공시 return true, 실패시 false
	// 전달인자는 없고, 함수 내에서 정보를 모두 입력받아 파일에 출력 후 저장
void inputInfo() {
	char code[6], path[100] = { '\0' }, station[22] = { '\0' };
	Station res;
	FILE * fp;
	int trash, totalCnt, currentCnt;

	int i, k, j, x[32] = { 0 };
	char select1[5], select2[5];

	printf("\n       그룹 코드(5자리) : ");
	scanf("%s", code);
	getchar();

	strcpy(path, code);
	strcat(path, ".csv");

	fp = fileOpen(path, "r+");
	if (fp == NULL) {
		printf("\n       그룹 코드가 존재하지 않습니다!!\n\n");
		getchar();
		return;
	}
	fscanf(fp, "%d,%d,%d", &trash, &totalCnt, &currentCnt);
	if (totalCnt == currentCnt) {
		printf("\n       이미 모든 인원이 입력하셨습니다.\n\n");
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
		printf("\n       가능한 시간 시작(종료시 x) : ");
	
		scanf("%s", select1); //가능시작시간입력

		if (strcmp(select1, "x") == 0) // x 입력시(더이상 시간 없을시) 종료
			break;


		if (strcmp(select1, "0900") == 0) // 시작시간일시 30분 단위로 쭉 비교
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

		printf("\n       가능한 시간 끝(종료시 x) : ");
		scanf("%s", &select2); //몇시까지 시간 되는지 select2변수에 입력.
		getchar();
		if (strcmp(select2, "x") == 0) // x 입력시(더이상 시간 없을시) 종료
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
			x[k]++;  // 위에서 응답한 시간대에 맞는 배열의 원소를 1씩 증가
	}
	fprintf(fp, "%d,", currentCnt);
	for (i = 0; i < 32; i++) 
		fprintf(fp, "%d,", x[i]);
	

	while (1) {
		printf("\n       출발역 : ");
		scanf("%s", station);
		getchar();

		res = findStation(station);
		if (strcmp(res.name, "error") == 0) {
			printf("\n       존재하지 않는 역입니다\n\n");
		}
		else {
			printf("\n       입력 완료");
			break;
		}
	}

	getchar();
	fprintf(fp, "%s\n", station);

	fclose(fp);
}


//---------------------------------------------------------------------------------------------------------
// 결과 확인 함수 
//전달인자는 없고, 함수 내에서 정보를 모두 입력받아 파일에 출력 후 저장
void showResult() {
	char code[6], path[100] = { '\0' }, result[5][22] = { '\0' };
	FILE * fp;
	Location lo;
	int placeCnt, cnt = 1, max;

	printf("\n       그룹 코드(5자리) : ");
	scanf("%s", code);
	getchar();

	strcpy(path, code);
	strcat(path, ".csv");

	fp = fileOpen(path, "r+");
	if (fp == NULL) {
		printf("\n       그룹 코드가 존재하지 않습니다!!\n\n");
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

	printf("좌표 : %lf %lf", lo.x, lo.y);
	
	if (lo.x >= 37.610812 && lo.x <= 37.656953)
	{
		if (lo.y >= 126.935148 && lo.y <= 126.956389)
		{
			printf("\n    북한산 좌측이 중심입니다.");
			printf("\n    추천역은 연신내와 종로역입니다.");
		}

		if (lo.y >= 126.956389 && lo.y <= 126.990038)
		{
			printf("\n    북한산 중앙이 중심입니다.");
			printf("\n    추천역은 종로역입니다.");
		}

		if (lo.y >= 126.990038 && lo.y <= 127.005648)
		{
			printf("\n    북한산 좌측이 중심입니다.");
			printf("\n    추천역은 수유역과 종로역입니다.");
		}
		return;
	}
	
	while (1) {
		placeCnt = inCircle(lo, cnt, result);
		if (placeCnt != false) break;
		cnt++;
	}

	printf("\n       추천지역 : ");
	for (int i = 0; i < placeCnt; i++) {
		printf(" %s역 인근,  ", result[i]);
	}


	getchar();
}








// 현재 디렉토리 경로 얻기
void getPath(char * path) {

	char * pstrBuffer = NULL;
	char tmp[260] = { '\0' };

	pstrBuffer = getcwd(path, _MAX_PATH);
}


// 입력받은 모드로 파일 열기
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
	printf("\n\n\n\n       To. 유저~님\n");
	printf("\n       안녕하세요 믹스볼팀입니다.\n");
	printf("\n       서비스는 만족스러우신가요??\n");
	printf("\n       아직 체험 전이라면!! 당장 체험해보세요!!\n");
	printf("\n       체험해보셨다면,,, 피드백을,,,(마음이 여려요,,)\n");
	printf("\n       1000만 서울시민의 약속을 도와줄\n");
	printf("\n       ' 우 리   지 금   만 나 ' 입 니 다 ! ! \n");
	printf("\n\n\n       팀원 : 배수범, 박상언, 김은선, 임현주\n");
	printf("\n       개발기간 : 2018.09.03 ~ 2018.11.21(테스트1)\n");
	printf("\n       version : 테스트1\n");
	printf("\n                  감사합니다.\n\n\n");
}
