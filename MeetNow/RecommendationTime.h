#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include"Common.h"
struct student {
	int id; // ��� ��ȣ
	char station[50]; // ����ö��
	int num[50]; // ���ɽð���
};

#define MAX 500 // ����ũ�� ����

// ����� �ð� ã�� �Լ�
// �׷� �ڵ带 �޾� �ش� ������ ���� ����ð��� ã�� ���� �� ����ð� �迭 ��ȯ
int findTime(char * code);