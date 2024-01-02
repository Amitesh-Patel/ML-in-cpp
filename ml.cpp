#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Training dataset
float train[][2] = {
    {0, 0},
    {1, 1},
    {2, 4},
    {3, 6},
    {4, 8},
};

#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void) {
    // srand(time(nullptr)); // Use current time as seed for random generator
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

//cost function 
float cost(float w,float b){
	float result = 0.0f;

	for(int i=0;i<train_count;++i){
		float x = train[i][0];
		float y = x * w + b;
		float d = y - train[i][1];
        result += d*d;
        // cout << "Actual: " << x << "  Expected: " << y << endl;
}
	result /= train_count;
	return result;
}

int main() {
	srand(69);
    // srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator
    float result = 0.0f;
    float w = rand_float()*1000;
    float b = rand_float();
    // cout << "Loss : " << cost(w) <<endl;
    // cout << "Random weight (w): " << w << endl;

    //Gradient descent 
    cout <<cost(w,b)<<endl;
    float eps = 1e-3,rate = 1e-3;
    for(int i=0;i<1000;i++){
	    //derivative of the cost function
	    float dw = (cost(w+eps,b) - cost(w,b))/eps; // Derivative of (y - train[j][1])^2 with respect to w
	    float db = (cost(w,b+eps) - cost(w,b))/eps;
	    w-=rate*dw;
	    b-=rate*db;
	    cout <<"cost = "<<cost(w,b)<<" w = "<<w<<"and bias = "<<b<<endl;
	}
	cout<<w<<endl;


    return 0;
}
