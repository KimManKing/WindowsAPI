#pragma once
#include "gameNode.h"


class pixelCollision : public gameNode
{
private:
	image* _background;	//��� ��
	image* _ball;		// �� �̹���

	RECT _rc;			//��Ʈ
	RECT _attackRc;
	float _x, _y;		//������ǥ
	int _probeY;		//Y�� Ž��

public:
	pixelCollision();
	~pixelCollision();

	HRESULT init();
	void release();
	void update();
	void render();

	void attack();

};

