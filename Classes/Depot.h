#pragma once
class Depot
{
private:
	
	Depot(void);
	~Depot(void);
public:
	bool isRetractAble;
	int score;
	double score_size;
	static Depot* aDepot;
	static Depot* getADepot();
	
};

