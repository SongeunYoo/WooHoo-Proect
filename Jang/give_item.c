
void give_item (int score) {
	item1 = 1;			// 기본값 삭제
	item2 = 3; 			// 되돌아가기

	scoitem1 = 100;
	scoitem2 = 500;




	if (scoitem1 <= score) 		//점수가 아이템1 기준 점수보다 높으면
	{
		item1++;			//아이템1 갯수 증가
		scoitem1 *= 2;		//아이템1 기준 점수는 100 증가
	}

	else if (scoitem2 <= score)
	{
		item2++;
		scoiterm2 += 500;
	}
}