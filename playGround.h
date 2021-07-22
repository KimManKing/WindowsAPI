#pragma once
#include "gameNode.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "saveLoadTest.h"

#define SPEED 5
#define BULLETMAX 500 //hghjgjjgj346c


struct tagtest
{
	image* img;
	RECT chartest;
	int x, y;
	float speedX, speedY;
};

struct tagbullettt
{
	image* bulletImage;		//총알의 이미지
	RECT rc;
	float x, y;				// 중점
	float speed;
	float radius;
	float angle;
	float fireX, fireY;		//총알의 발사위치
	bool isFire;			//총알의 발사유무
	int count;
	int counttttt;
};

class playGround : public gameNode
{
private:
	spaceShip* _ship;
	enemyManager* _em;
	saveLoadTest* _slt;


	int _fadeIn;
	int _fadeOut;
	bool _isFadeInOut;

	RECT _rcObject;

	int _bulletCount;
	int _bulletCccount;
	// Camera
	RECT _camera;
	int _camX, _camY;
	int counttt = 0;
	int _xxx, _yyy;
	bool _testtest;

	char str[128];
	char str2[128];

	image* _background1;
	image* _background2;
	tagtest _char;

	tagbullettt _bullet[BULLETMAX];

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();	//그리기 함수

	void collision();
	void SetCamera(RECT& camera, int left, int top, int width, int height);
	void CameraMove(RECT& camera);
};

