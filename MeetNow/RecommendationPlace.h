/*

장소 추천과 관련

*/

#pragma once

#include "Common.h"

#define radius 0.0001
#define allStation 642
#define HotPlaceStation 35

typedef struct location {
	double x, y;
}Location;


// 역이름을 전달받아 해당 역의 좌표를 반환
Station findStation(char * stationName);

// 입력받은 좌표를 기준으로 원을 탐색해 결과 배열에 추천지 이름 넣어
int inCircle(Location center, int count, char resultStation[5][22]);

// 그룹정보를 통해 출발역들의 평균을 구해 중심좌표를 반환
Location findCenterLocation(char * groupCode);

void test();
