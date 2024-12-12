#pragma once
class Collider;
union COLLIDER_ID
{
	struct
	{
		UINT left_ID;
		UINT right_ID;
	};
	ULONGLONG ID;
};
class CollisionManager
{
	DECLARE_SINGLETON(CollisionManager);
public:
	void update();
	void checkLayer(LAYER _left, LAYER _right);
	void checkReset();
private:
	void collisionLayerupdate(LAYER _left, LAYER _right);
	bool isCollision(Collider* _left, Collider* _right);
private:
	// 그룹 간의 충돌체크 배열
	UINT _layers[(UINT)LAYER::END];
	map<ULONGLONG, bool> _coliisionInfoMap;
};