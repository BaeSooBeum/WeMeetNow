#include "Common.h"
#include "RecommendationPlace.h"
#include "RecommendationTime.h"

int main() {
	char button;

	while (1) {
		system("cls");
		menu();
		scanf("%c", &button);
		getchar();

		switch (button) {
		case'1':
			createGroup();
			break;
		case'2':		// ���� ���� �Է�
			inputInfo();
			break;
		case'3':		// ��� ���
			showResult();
			break;
		case'4':		// ����
			printf("\n\n    ��ſ� ���� �Ǽ���!    \n\n");
			return 0;
		case'5':
			system("cls");
			loveLetter();
		}
		system("pause");
	}
}