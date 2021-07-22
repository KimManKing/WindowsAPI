#include "pch.h"
#include "enemyManager.h"
#include "spaceShip.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 30, 700); //총알이미지 키값, 총알맥스값, 사거리

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	minionBulletFire();

	collision();

	_bullet->update();
}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void enemyManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo;
			ufo = new minion;
			ufo->init("enemy", PointMake(80 + j * 80, 80 + i * 100));
			_vMinion.push_back(ufo);
		}
	}

}

void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		//값이 true가 되면
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();

			//_bullet->fire((rc.left + rc.right) / 2, rc.bottom + 5, -(PI / 2), 7.0f);
			_bullet->fire((rc.left + rc.right) / 2,
				rc.bottom + 5,
				getAngle((rc.left + rc.right) / 2, rc.bottom,
					_ship->getShipImage()->getCenterX(),
					_ship->getShipImage()->getCenterY()), 7.0f);
		}
	}
}

void enemyManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = RectMake(_ship->getShipImage()->getX(), _ship->getShipImage()->getY(),
			_ship->getShipImage()->getWidth(), _ship->getShipImage()->getHeight());

		if (IntersectRect(&temp, &_bullet->getVBullet()[i].rc,
			&rc))
		{
			_bullet->removeBullet(i);
			_ship->hitDamage(10.0f);
			//플레이어 체력깍아주면 됨

			break;
		}
	}
}
