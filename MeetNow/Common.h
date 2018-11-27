#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include<time.h>
#pragma warning(disable:4996)

#define _Max_PATH 260

// 지하철 구조체
// (역명, 좌표)
typedef struct station {
	char name[24];
	double x, y;
}Station;

// 그룹 구조체
//  (그룹코드, 총원, 현재원)
typedef struct group {
	char groupCode[5];
	int maxPersonCnt, currentPersonCnt;
}Group;

// 파일 오픈
FILE *fileOpen(const char * filename, const char * mode);


// 현재 디렉토리 경로 얻기
void getPath(char * str);

void menu();

// 방 개설 함수 ( 사용자가 그룹의 정보를 입력하면, 랜덤의 방번호와 함께 방 파일이 생성)
// 성공시 true, 실패시 false 반환
// 전달인자는 없고, 함수 내에서 정보를 모두 입력받아 파일에 출력 후 저장
void createGroup();


// 유저 1명의 정보를 입력하는 함수, 성공시 return true, 실패시 false
// 전달인자는 없고, 함수 내에서 정보를 모두 입력받아 파일에 출력 후 저장
void inputInfo();


// 결과 확인 함수 ( 사용자가 방번호 입력하면, 현재까지 종합된 내용 추천)
// 사용자가 입력한 방번호 코드로 파일을 열어 결과 출력
void showResult();


void loveLetter();


