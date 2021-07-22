#pragma once
#include "gameNode.h"


class pixelCollision : public gameNode
{
private:
	image* _background;	//배경 벽
	image* _ball;		// 공 이미지

	RECT _rc;			//렉트
	RECT _attackRc;
	float _x, _y;		//중점좌표
	int _probeY;		//Y축 탐사

public:
	pixelCollision();
	~pixelCollision();

	HRESULT init();
	void release();
	void update();
	void render();

	void attack();

};

