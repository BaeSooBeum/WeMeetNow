#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include"Common.h"
struct student {
	int id; // 사람 번호
	char station[50]; // 지하철역
	int num[50]; // 가능시간대
};

#define MAX 500 // 버퍼크기 지정

// 공통된 시간 찾는 함수
// 그룹 코드를 받아 해당 파일을 열어 공통시간을 찾아 저장 및 공통시간 배열 반환
int findTime(char * code);