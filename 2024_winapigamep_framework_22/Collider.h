#pragma once
#include "Component.h"
#include "Action.h"
class Collider : public Component
{
public:
    Collider();
    ~Collider();
public:
    // Component을(를) 통해 상속됨
    void lateUpdate() override;
    void render(HDC hDC) override;
public:
    void enterCollision(Collider* _other); // 충돌진입
    void stayCollision(Collider* _other); // 충돌중
    void exitCollision(Collider* _other); // 충돌해제
    const UINT& getID() const { return _id; }
public:
    void setSize(Vector2 _vSize) { _size = _vSize; }
    const Vector2& getSize() const { return _size; }
    void setPosition(const Vector2& position) { _position = position; }
    const Vector2& getPosition() const { return _position; }
    void setOffset(Vector2 _vOffsetPos)
    {
        _offset = _vOffsetPos;
    }
    const Vector2& getOffset() const { return _offset; }
    void setFollowing(bool following) { _following = following; }
public:
    Action<Collider*> OnCollisionEnterEvent;
    Action<Collider*> OnCollisionStayEvent;
    Action<Collider*> OnCollisionExitEvent;
private:
    bool _showDebug = false;
    bool _following = true;
    UINT _id;
    static UINT _nextID;
    Vector2 _size; 
    Vector2 _offset;
    Vector2 _position;
};

