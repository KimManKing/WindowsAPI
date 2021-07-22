#include "pch.h"
#include "playGround.h"

//헤더파일은 여러개의 cpp 파일을 거느릴(?) 수 있게되는데
//코드량이 많아진다 싶으면 함수별로 별도의 cpp파일을 만들어서
//관리하는 구조도 예전엔 많이 선호하였음 (특히 온라인 MMORPG는 코드량이 엄청 많았음)

void playGround::collision()
{
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _ship->getHellFire()->getVBullet().size(); j++)
		{
			RECT temp;
			RECT rc = _ship->getHellFire()->getVBullet()[j].rc;
			RECT rc1 = _em->getVMinion()[i]->getRect();
			if (IntersectRect(&temp, &rc, &rc1))
			{
				_em->removeMinion(i);
				_ship->getHellFire()->removeMissile(j);
				break;
			}
		}
	}


}


