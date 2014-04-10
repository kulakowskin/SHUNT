#include <cstring>
#include <string>
#include <cmath>
#include <sstream>
#include <stdlib.h>
#include "Sqrt.h"

Sqrt::Sqrt(){
	this->in = 0;
}
Sqrt::Sqrt(string expression){
	this->expression = strstr((char*)expression.c_str(),expression.c_str());
	parseNumbers();
}
float Sqrt::getIn(){
	return this->in;
}
string Sqrt::simRoots(){
	this->factor_c = 0;
	this->mf = this->in/2;
	for(int i = this->mf; i > 0; i--) {
		if((this->in / i) == int(this->in / i)) {
			if(sqrt(this->in / i) == int(sqrt(this->in / i))) {
				this->multiplier = sqrt(this->in / i);
				this->radicand = this->in / (this->in / i);
				this->factor_c++;
			}
		}
	}
	if (this->factor_c > 0) {
			if (this->radicand == 1) {
				stringstream bb;
				bb << this->multiplier;
				return "( " + bb.str() + " )";
			}
			else {
				stringstream ss;
				ss << this->multiplier;
				stringstream bb;
				bb << this->radicand;
				return "( " + ss.str() + " * sqrt:" + bb.str() + " )";
			}
		}
        else {
            stringstream ss; 
            ss << this->in;
            return "( sqrt:" + ss.str() + " )";
		}
}
void Sqrt::parseNumbers(){
	char* p;
  	p = strtok(this->expression,"sqrt:");
	this->in = atoi(p);
}
