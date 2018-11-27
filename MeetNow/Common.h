#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include<time.h>
#pragma warning(disable:4996)

#define _Max_PATH 260

// ����ö ����ü
// (����, ��ǥ)
typedef struct station {
	char name[24];
	double x, y;
}Station;

// �׷� ����ü
//  (�׷��ڵ�, �ѿ�, �����)
typedef struct group {
	char groupCode[5];
	int maxPersonCnt, currentPersonCnt;
}Group;

// ���� ����
FILE *fileOpen(const char * filename, const char * mode);


// ���� ���丮 ��� ���
void getPath(char * str);

void menu();

// �� ���� �Լ� ( ����ڰ� �׷��� ������ �Է��ϸ�, ������ ���ȣ�� �Բ� �� ������ ����)
// ������ true, ���н� false ��ȯ
// �������ڴ� ����, �Լ� ������ ������ ��� �Է¹޾� ���Ͽ� ��� �� ����
void createGroup();


// ���� 1���� ������ �Է��ϴ� �Լ�, ������ return true, ���н� false
// �������ڴ� ����, �Լ� ������ ������ ��� �Է¹޾� ���Ͽ� ��� �� ����
void inputInfo();


// ��� Ȯ�� �Լ� ( ����ڰ� ���ȣ �Է��ϸ�, ������� ���յ� ���� ��õ)
// ����ڰ� �Է��� ���ȣ �ڵ�� ������ ���� ��� ���
void showResult();


void loveLetter();


