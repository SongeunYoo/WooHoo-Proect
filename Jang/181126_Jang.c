plate[4][4]
int i, j;
int item1, item2;
int overcount

int overCount () {
	for (i=0, i<4, i++) { 					//빈칸이 있는지 확인
		for (j=0, j<4, j++) {
			if (plate[i][j] == 0)
				return 0;
		}
	}

	for (i=0, i<3, i++) { 					//세로로 동일한 값이 있는지 확인
		for (j=0, j<4, j++) {
			if (plate[i][j] == plate[i+1][j])
				return 0;
		}
	}

	for (j=0, j<3, j++) { 					//가로로 동일한 값이 있는지 확인
		for (i=0, i<4, i++) {
			if (plate[i][j] == plate[i][j+1])
				return 0;
		}
	}

*빈칸도 없고 연속된 블럭도 없을 경우 아이템을 쓰게 해줄지 말지 결정하기

	if (item1 != 0 || item2 == 0)
		return 0;
	else
		return 1;
}

case 1 : 
	for (i=0, i<4, i++) {
		for (j=0, j<4, j++) { 				//전체적으로 훑어서
			if (plate[i][j] == 1 || plate[i][j] == 2) {	//1과 2 찾아내기
				plate[i][j] = 0; 		//0으로 바꿈
			}
		}
	}
	item1--;						//item1 감소