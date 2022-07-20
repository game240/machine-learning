#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random() {
	return ((double)(rand() % RAND_MAX) / (double)RAND_MAX); //return random double x value
}

double square(double n) {
	return n * n;
}

double hypothesis(double w, double x, double b) { 
	return w * x + b;
}

double loss(double w, double x, double b, double y) { //variance of each element
	return square(hypothesis(w, x, b) - y);
}
double loss_all(double w, double* x, double b, double* y) { //variance
	double sum = 0;
	for(int i=0; i<5; i++) {
		sum += loss(w, x[i], b, y[i]);
	}
	return sum/5.0;
}

double derivative_w(double w, double x, double b, double y) { // (d(wx+b)^2 / dw) of each element
	return 2 * (hypothesis(w, x, b) - y) * x;
}
double derivative_w_all(double w, double* x, double b, double* y) { // d(wx+b)^2 / dw
	double sum = 0;
	for (int i = 0; i < 5; i++) {
		sum += derivative_w(w, x[i], b, y[i]);
	}
	return sum / 5.0;
}

double derivative_b(double w, double x, double b, double y) { // (d(wx+b)^2 / db) of each element
	return 2 * (hypothesis(w, x, b) - y) * 1;
}
double derivative_b_all(double w, double* x, double b, double* y) { // d(wx+b)^2 / db
	double sum = 0;
	for (int i = 0; i < 5; i++) {
		sum += derivative_b(w, x[i], b, y[i]);
	}
	return sum / 5.0;
}

int main() {
	srand((unsigned int)time(NULL)); //random seed setting
	random(); //cycling for variety
	
	double w = random();
	double b = random();

	double x[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	double y[5] = { 5.0, 9.0, 13.0, 17.0, 21.0};

	printf("데이터의 x값 입력(5개): ");
	for (int i = 0; i < 5; i++) {
		scanf_s("%f", &x[i]);
	}
	printf("데이터의 y값 입력(5개): ");
	for (int i = 0; i < 5; i++) {
		scanf_s("%f", &y[i]);
	}
	printf("\n");

	for (int i = 0; i < 5000; i++) {
		double w_derivative = derivative_w_all(w, x, b, y);
		double b_derivative = derivative_b_all(w, x, b, y);
		
		w -= 0.01 * w_derivative;
		b -= 0.01 * b_derivative;
		printf("%3d: loss: %f \n", i, loss_all(w, x, b, y));
	}
	printf("hypothesis: y = %fx + (%f)", w, b);

}