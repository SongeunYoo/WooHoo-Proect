
void give_item (int score) {
	item1 = 1;			// �⺻�� ����
	item2 = 3; 			// �ǵ��ư���

	scoitem1 = 100;
	scoitem2 = 500;




	if (scoitem1 <= score) 		//������ ������1 ���� �������� ������
	{
		item1++;			//������1 ���� ����
		scoitem1 *= 2;		//������1 ���� ������ 100 ����
	}

	else if (scoitem2 <= score)
	{
		item2++;
		scoiterm2 += 500;
	}
}