#include "Depot.h"
#include <iostream>
using namespace std;


Depot* Depot::aDepot= NULL;
Depot* Depot::getADepot(){
	if(aDepot==NULL){
		aDepot = new Depot();
	}
	return aDepot;
}

Depot::Depot(void)
{
	score = 0;
	score_size = 0.17;
}


Depot::~Depot(void)
{
}
