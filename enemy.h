#pragma once
#include "gameNode.h"

//적을 찍어낼 부모클라쓰

class enemy : public gameNode
{
protected:
	image* _imageName;	//적이 사용할 이미지 이름
	RECT _rc;

	int _currentFrameX;	//프레임 번호로 사용할 변수
	int _currentFrameY;

	int _count;				//에너미 프레임 카운트 용
	int _fireCount;			//발사 시간 용
	int _rndFireCount;		//랜덤하게 발사할때 시간 용
public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();

	bool bulletCountFire();

	//에너미 렉트에 대한 접근자
	inline RECT getRect() { return _rc; }
};

