#pragma once
class Player;
class PlayerManager
{
	DECLARE_SINGLETON(PlayerManager);
public:
	void setPlayer(Player* player) { _player = player; }
	Player* getPlayer() { return _player; }
private:
	Player* _player;
};