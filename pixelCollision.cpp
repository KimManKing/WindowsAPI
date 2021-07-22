#include "pch.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage("�ȼ��浹���", "background3.bmp", 768, 768, true, RGB(255, 0, 255));

	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 10, 10, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 100;	//���� x��ǥ
	_y = WINSIZEY / 2 + 100;	//���� y��ǥ

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	_probeY = _y + _ball->getHeight() / 2;


	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 5;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += 5;


	_probeY = _y + _ball->getHeight() / 2;

	//
	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�ȼ��浹���")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//����Ÿ �ȼ��� �ƴϸ�
		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	attack();
}

void pixelCollision::attack()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_attackRc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 50, 50);
	}
}

void pixelCollision::render()
{
	IMAGEMANAGER->findImage("�ȼ��浹���")->render(getMemDC());

	_ball->render(getMemDC(), _rc.left, _rc.top);

	HPEN newPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("�ȼ��浹���")->getMemDC(), newPen);
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("�ȼ��浹���")->getMemDC(), brush);
	Ellipse(IMAGEMANAGER->findImage("�ȼ��浹���")->getMemDC(), _attackRc);
	SelectObject(IMAGEMANAGER->findImage("�ȼ��浹���")->getMemDC(), oldBrush);
	DeleteObject(brush);
	SelectObject(IMAGEMANAGER->findImage("�ȼ��浹���")->getMemDC(), oldPen);
	DeleteObject(newPen);
}


