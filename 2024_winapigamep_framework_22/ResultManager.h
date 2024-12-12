#pragma once
class ResultManager
{
	DECLARE_SINGLETON(ResultManager);
public:
	void initialize() { _totalPower = 0; _totalDamage = 0; _totalCaughtEnemy = 0; }
public:
	void modifyTotalPower(int value) { _totalPower += value; }
	void modifyTotalDamage(int value) { _totalDamage += value; }
	void modifyTotalCaughtEnemy(int value) { _totalCaughtEnemy += value; }
	int getTotalPower() { return _totalPower; }
	int getTotalDamage() { return _totalDamage; }
	int getTotalCaughtEnemy() { return _totalCaughtEnemy; }
private:
	int _totalPower;
	int _totalDamage;
	int _totalCaughtEnemy;
};