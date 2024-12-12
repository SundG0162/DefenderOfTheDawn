#pragma once
class Player;
class PlayerDevice
{
public:
	virtual void initialize(Player* player) { _player = player; }
protected:
	Player* _player;
};