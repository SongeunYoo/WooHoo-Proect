plate[4][4]
int i, j;
int item1, item2;
int overcount

int overCount () {
	for (i=0, i<4, i++) { 					//��ĭ�� �ִ��� Ȯ��
		for (j=0, j<4, j++) {
			if (plate[i][j] == 0)
				return 0;
		}
	}

	for (i=0, i<3, i++) { 					//���η� ������ ���� �ִ��� Ȯ��
		for (j=0, j<4, j++) {
			if (plate[i][j] == plate[i+1][j])
				return 0;
		}
	}

	for (j=0, j<3, j++) { 					//���η� ������ ���� �ִ��� Ȯ��
		for (i=0, i<4, i++) {
			if (plate[i][j] == plate[i][j+1])
				return 0;
		}
	}

*��ĭ�� ���� ���ӵ� ���� ���� ��� �������� ���� ������ ���� �����ϱ�

	if (item1 != 0 || item2 == 0)
		return 0;
	else
		return 1;
}

case 1 : 
	for (i=0, i<4, i++) {
		for (j=0, j<4, j++) { 				//��ü������ �Ⱦ
			if (plate[i][j] == 1 || plate[i][j] == 2) {	//1�� 2 ã�Ƴ���
				plate[i][j] = 0; 		//0���� �ٲ�
			}
		}
	}
	item1--;						//item1 ����