/*

��� ��õ�� ����

*/

#pragma once

#include "Common.h"

#define radius 0.0001
#define allStation 642
#define HotPlaceStation 35

typedef struct location {
	double x, y;
}Location;


// ���̸��� ���޹޾� �ش� ���� ��ǥ�� ��ȯ
Station findStation(char * stationName);

// �Է¹��� ��ǥ�� �������� ���� Ž���� ��� �迭�� ��õ�� �̸� �־�
int inCircle(Location center, int count, char resultStation[5][22]);

// �׷������� ���� ��߿����� ����� ���� �߽���ǥ�� ��ȯ
Location findCenterLocation(char * groupCode);

void test();
