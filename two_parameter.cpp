#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

// Training dataset
//Or gate 
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}
};

//AND gate
float train2[][3] = {
    {0, 0, 1},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 0}
};

//NAND gate
float train3[][3] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};

//XOR gate - not modable using single neurons 
float train4[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};


#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void) {
    // srand(time(nullptr)); // Use current time as seed for random generator
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float sigmoidf(float x){
	float y = 1.f / (1.f + expf(-x));
	return y;
}

//cost function 
float cost(float w1,float w2,float b){
	float result = 0.0f;

	for(int i=0;i<train_count;++i){
		float x1 = train[i][0];
		float x2 = train[i][1];
		float y = sigmoidf(x1*w1 + x2*w2+b);
		float d = y - train[i][1];
        result += d*d;
}
	result /= train_count;
	return result;
}

int main() {
	srand(69);
    float result = 0.0f;
    float w1 = rand_float()*1000;
    float w2 = rand_float()*10;
    float b = rand_float()*10;


    //Gradient descent 
    cout <<cost(w1,w2,b)<<endl;
    float eps = 1e-3,rate = 1e-1; // play with learning rate you will see the differnce why it is important
    for(int i=0;i<5000;i++){
	    //derivative of the cost function
	    float c = cost(w1,w2,b);
	    float dw1 = (cost(w1+eps,w2,b) - c)/eps; // Derivative of (y - train[j][1])^2 with respect to w
	    float dw2 = (cost(w1,w2+eps,b) - c)/eps;
	    float db = (cost(w1,w2,b+eps) - c)/eps;
	    w1-=rate*dw1;
	    w2-=rate*dw2;
	    b-=rate*db; // remove the bias term and your or gate will not work properly
	    cout <<"cost = "<<cost(w1,w2,b)<<" weight1 = "<<w1<<" and weight2 = "<<w2<<" bias :"<<b<<endl;
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			cout<<i<<" OR "<<j<<" "<<sigmoidf(i*w1+j*w2+b)<<endl;

		}
	}
    return 0;
}
