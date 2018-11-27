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
		case'2':		// 유저 정보 입력
			inputInfo();
			break;
		case'3':		// 결과 출력
			showResult();
			break;
		case'4':		// 종료
			printf("\n\n    즐거운 만남 되세요!    \n\n");
			return 0;
		case'5':
			system("cls");
			loveLetter();
		}
		system("pause");
	}
}