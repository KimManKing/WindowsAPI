#include "pch.h"
#include "playGround.h"

//��������� �������� cpp ������ �Ŵ���(?) �� �ְԵǴµ�
//�ڵ差�� �������� ������ �Լ����� ������ cpp������ ����
//�����ϴ� ������ ������ ���� ��ȣ�Ͽ��� (Ư�� �¶��� MMORPG�� �ڵ差�� ��û ������)

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

