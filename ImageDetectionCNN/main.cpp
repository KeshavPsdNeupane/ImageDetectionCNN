#include"CnnRunner.h"
#include"CNN/CNN.h"
int main(){
	CNN c(1, 784, 100, 10);
	c.CnnOperate();
}