#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy", "ufo.bmp", 0, 0, 530, 32, 10, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("전", "전.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("후", "후.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경1", "background1.bmp", 3072, 3072, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경2", "background2.bmp", 3072, 3072, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("char_idle", "char_crystal_idle.bmp", 276, 108, 4, 2, true, RGB(255, 0, 255));

	_background1 = IMAGEMANAGER->findImage("배경1");
	_background2 = IMAGEMANAGER->findImage("배경2");


	//스페이스 쉽 인스턴스 생성 및 초기화 함수 호출
	_ship = new spaceShip;
	_ship->init();

	_em = new enemyManager;
	_em->init();
	_em->setMinion();

	_ship->setEmMemoryAddressLink(_em);
	_em->setSpaceShipMemoryAddressLink(_ship);

	_slt = new saveLoadTest;

	_fadeOut = 255;
	_fadeIn = 0;
	_isFadeInOut = false;

	_char.img = IMAGEMANAGER->findImage("char_idle");
	_char.x = WINSIZEX / 2;
	_char.y = WINSIZEY / 2;
	_char.chartest = RectMakeCenter(_char.x, _char.y, 50, 50);
	_char.speedX = _char.speedY = 5.0f;


	// 카메라
	_camera.left = 200;
	_camera.right = WINSIZEX - 200;
	_camera.top = 200;
	_camera.bottom = WINSIZEY - 200;
	_camX = _camY = 0;


	_rcObject = RectMakeCenter(1500 + _camX, 1000 + _camY, 50, 50);

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].bulletImage = IMAGEMANAGER->findImage("bullet");
		_bullet[i].angle = _bullet[i].speed = _bullet[i].count = 0;
		_bullet[i].fireX = _char.x;
		_bullet[i].fireY = _char.y;
		_bullet[i].isFire = false;
		_bullet[i].radius = 10;
		_bullet[i].x = _bullet[i].y = 0;
		_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, _bullet[i].radius*2, _bullet[i].radius*2);
		_bullet[i].counttttt = 0;
	}

	_bulletCount = 0;

	_xxx = 585;
	_yyy = 735;

	_testtest = false;
	_bulletCccount = 0;

	return S_OK;
}

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();


}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();

	_ship->update();
	_em->update();
	_slt->update();
	//collision();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_isFadeInOut) _isFadeInOut = true;
	}

	if (_isFadeInOut)
	{
		_fadeIn++;
		_fadeOut--;

		if (_fadeIn > 254) _isFadeInOut = false;
	}



	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_char.x -= _char.speedX;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_char.x += _char.speedX;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_char.y -= _char.speedY;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_char.y += _char.speedY;
	}

	_char.chartest = RectMakeCenter(_char.x, _char.y, 50, 50);
	CameraMove(_camera);

	TIMEMANAGER->getElapsedTime();
	
	counttt++;
	if (counttt <= 100)
	{
		_testtest = true;
	}
	else if (counttt > 100)
	{
		_testtest = false;
		if (counttt > 200) counttt = 0;
	}


	if (_testtest)
	{
		_xxx += 10;
	}
	else if(!_testtest)
	{
		_xxx -= 10;
	}

	_rcObject = RectMakeCenter(_xxx + _camX, _yyy + _camY, 75, 115);
	
	RECT temp;
	if (IntersectRect(&temp, &_char.chartest, &_rcObject))
	{
		//if()
	}
	
	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_bulletCount++;
		if (_bulletCount % 5 == 0)
		{
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (_bullet[i].isFire == true) continue;

				_bullet[i].isFire = true;
				_bullet[i].fireX = _char.x;
				_bullet[i].fireY = _char.y;
				_bullet[i].x = _char.x;
				_bullet[i].y = _char.y;
				_bullet[i].speed = 11.0;
				_bullet[i].angle = getAngle(_bullet[i].fireX, _bullet[i].fireY, _ptMouse.x, _ptMouse.y)+ RND->getFloat(0.5);
				_bulletCccount++;
				
				if (_bulletCccount > 5)
				{
					_bulletCccount = 0;
					break;
				}
			}
		}
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire == false) continue;

		_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, _bullet[i].radius * 2, _bullet[i].radius * 2);
		_bullet[i].count++;

		if (_bullet[i].count > 100)
		{
			_bullet[i].isFire = false;
			_bullet[i].count = 0;
		}
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		RECT temp2;
		if (IntersectRect(&temp2, &_bullet[i].rc, &_rcObject))
		{
			int width = temp2.right - temp2.left;
			int height = temp2.bottom - temp2.top;
			_bullet[i].counttttt++;

			if (width >= height) // 상하단 부딪혔을 때.
			{
				_bullet[i].angle = 2 * PI - _bullet[i].angle;
			}
			if(width < height)// 좌우 부딪혔을 때.
			{
				_bullet[i].angle = PI - _bullet[i].angle;
			}

			if (_bullet[i].counttttt > 7)
			{
				_bullet[i].counttttt = 0;
				_bullet[i].isFire = false;
			}
		}
	}



}

//여기다 그려줘라!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============위에는 제발 건드리지 마라 ============

	//IMAGEMANAGER->findImage("배경")->render(getMemDC());
	//IMAGEMANAGER->findImage("후")->alphaRender(getMemDC(), _fadeIn);
	//IMAGEMANAGER->findImage("전")->alphaRender(getMemDC(), _fadeOut);
	_background1->render(getMemDC(), _camX, _camY);
	_background2->render(getMemDC(), _camX, _camY);
	
	_char.img->render(getMemDC(), _char.chartest.left, _char.chartest.top);
	Rectangle(getMemDC(), _camera);
	Rectangle(getMemDC(), _rcObject);
	Rectangle(getMemDC(), _char.chartest);


	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire == false) continue;

		Ellipse(getMemDC(), _bullet[i].rc);
	}

	sprintf_s(str, "camX = %d", _camX);
	TextOut(getMemDC(), 0, 60, str, strlen(str));
	sprintf_s(str2, "camY = %d", _camY);
	TextOut(getMemDC(), 0, 80, str2, strlen(str2));

	//_ship->render();
	//_em->render();

	TIMEMANAGER->render(getMemDC());

	//=============== 밑에도 건들지마라 ================
	_backBuffer->render(getHDC(), 0, 0);

}

void playGround::SetCamera(RECT& camera, int left, int top, int width, int height)
{
	camera.left = left;
	camera.right = _camera.left + width;
	camera.top = top;
	camera.bottom = _camera.top + height;
}

void playGround::CameraMove(RECT &camera)
{
	//CAMERAMANAGER->SetCamera(_camera, 200, 200, 400, 400);
    //CAMERAMANAGER->MoveCamera(_player.rc, _background, _player.speed, _camX, _camY);

// 카메라 체크 상자 설정
	SetCamera(camera, 200, 200, 200, 200);

	// camera 상자 안에서만 플레이어가 직접 이동(혹은 카메라 이동이 불가능할 경우)
	if (_background1->getHeight() <= WINSIZEY - _camY || _camY == 0 || _char.chartest.bottom < camera.bottom || _char.chartest.top > camera.top)
	{
		_char.speedX = _char.speedY = SPEED;
		//_char.y -= _player.jumpPower;
		//_player.jumpPower -= _player.gravity;
	}
	// 배경화면의 왼쪽 끝이 윈도우 창의 왼쪽이랑 같아지면 이동 정지
	// 배경화면의 오른쪽 끝이 윈도우 창의 오른쪽이랑 같아지면 이동 정지
	if (_camX >= 0 || _camX + WINSIZEX <= _background1->getWidth())
	{
		_char.speedX = _char.speedY = SPEED;
	}


	// 1. 사각형을 이용하는 방법
	// 일정 범위의 사각형 rc와 캐릭터의 rc의 같은 요소(left, right, top, bottom)의 값이 같아지면
	// 해당 방향으로 카메라 이동

	// 카메라 왼쪽으로 이동 (배경은 오른쪽으로)
	if (_char.x <= camera.left + 40 && KEYMANAGER->isStayKeyDown('A'))
	{
		if (_camX < 0)
		{
			_camX += SPEED;
			_char.speedX = 0;
			_char.x = _camera.left + 40;
		}
	}
	// 카메라 오른쪽으로 이동 (배경은 왼쪽으로)
	else if (_char.x >= camera.right - 40 && KEYMANAGER->isStayKeyDown('D'))
	{
		if (_camX + _background1->getWidth() >= WINSIZEX)
		{
			_camX -= SPEED;
			_char.speedX = 0;
			_char.x = _camera.right - 40;
		}
	}
	else
	{
		_char.speedX = SPEED;
	}


	// 카메라 위쪽으로 이동 (배경은 아래쪽으로)
	if (_char.y <= camera.top + 50 && KEYMANAGER->isStayKeyDown('W'))
	{
		if (_camY < 0)
		{
			_camY += SPEED;
			_char.speedY = 0;
			_char.y = camera.top + 50;
		}
	}
	// 카메라 아래쪽으로 이동 (배경은 위쪽으로)
	else if (_char.y >= camera.bottom - 50 && KEYMANAGER->isStayKeyDown('S'))
	{
		if (_background1->getHeight() >= WINSIZEY - _camY)
		{
			_camY -= SPEED;
			_char.speedY = 0;
			_char.y = camera.bottom - 50;
		}
	}
	else
	{
		_char.speedY = SPEED;
	}


	// 2. 좌표값을 이용하는 방법
	// 캐릭터의 중심 x,y좌표값을 일정 좌표값과 비교해서
	// 카메라 이동

}