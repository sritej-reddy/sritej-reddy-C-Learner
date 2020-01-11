//moves_handling_functions.c
#include<stdio.h>
#include"fibonacci_checkers.c"
//functions declaration

void downMove(int *,int );
void shiftdown(int *,int , int , int ,int);
void upMove(int *,int );
void shiftUp(int *,int , int , int ,int);
void leftMove(int *,int );
void shiftLeft(int *,int , int , int ,int);
void rightMove(int *,int );
void shiftRight(int *,int , int , int ,int);
int handleInputs(char [],int ,int ,int *);
void removeZeroesOfColumnsForDownMove(int *,int );
void removeZeroesOfColumnsForUpMove(int *,int );
void removeZeroesOfRowsForRightMove(int *,int );
void removeZeroesOfRowsForLeftMove(int *,int );

int handleInputs(char name[],int moves,int n,int *a){
	char c;
	printf("enter w - UP / s - DOWN / d - RIGHT / a - LEFT\n\t\t\t any key to exit \n\t\t\tgame is saved automatically Don't worry \n: ");
	scanf(" %c",&c);
	if (c == 'w')
		upMove(a,n);
	else if (c == 's')
		downMove(a,n);
	else if (c == 'd')
		rightMove(a,n);
	else if (c == 'a')
		leftMove(a,n);
	else return 1;
	return 0;
}

void removeZeroesOfColumnsForDownMove(int *a,int n){ 
	int j=n-1;
	for(int k=0;k<n;k++){ //this gives a coloumn number in every iteration
		j=n-1;
		for(int i=n-1;i>=0;i--){ //this is for row index
			if(*(a+i*n+k)!=0){
				*(a+j*n+k)=*(a+i*n+k);
				j--;
			}
		}
		while(j>=0){
			*(a+j*n+k)=0;
			j--;
		}
	}
}

void removeZeroesOfColumnsForUpMove(int *a,int n){ 
	int j=0;
	for(int k=0;k<n;k++){ //this gives a coloumn number in every iteration
		j=0;
		for(int i=0;i<n;i++){ //this is for row index
			if(*(a+i*n+k)!=0){
				*(a+j*n+k)=*(a+i*n+k);
				j++;
			}
		}
		while(j<n){
			*(a+j*n+k)=0;
			j++;
		}
	}
}

void removeZeroesOfaRowLeftMove(int *a,int n){
	int j=0;
	for(int k=0;k<n;k++){		//this gives a coloumn number in every iteration
		j=0;
		for(int i=0;i<n;i++){ //this is for row 
			if(*(a+k*n+i)!=0){
				*(a+k*n+j)=*(a+k*n+i);
				j++;
			}
		}
		while(j<n){
			*(a+k*n+j)=0;
			j++;
		}
	}
}


void removeZeroesOfaRowRightMove(int *a,int n){
	int j;
	for(int k=0;k<n;k++){		//this gives a coloumn number in every iteration
		j=n-1;
		for(int i=n-1;i>=0;i--){ //this is for row 
			if(*(a+k*n+i)!=0){
				*(a+k*n+j)=*(a+k*n+i);
				j--;
			}
		}
		while(j>=0){
			*(a+k*n+j)=0;
			j--;
		}
	}
}
	
void downMove(int *a,int n) { // gets triggered when user choses DOWN move
	removeZeroesOfColumnsForDownMove(a,n);
	int k = n - 1, l = n - 2;
	while (l >= 0) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(*((a+l*n) + i), *((a+k*n) + i))) {
				shiftdown(a,i, k, l,n);
			}
		}
		
		k--;
		l--;
	}
}

void shiftdown(int *a,int col, int k, int l,int n) { // shifts down the tiles by 1
	*((a+k*n) + col) += *((a+l*n) + col);
	for (int i = l; i > 0; i--) {
		*((a+i*n) + col) = *((a+(i-1)*n) + col);
	}
	*((a+0*n) + col) = 0;
}

void upMove(int *a,int n) { // gets triggered when user choses UP move
	removeZeroesOfColumnsForUpMove(a,n);
	int k = 0, l = 1;
	while (l < n) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(*((a+l*n) + i), *((a+k*n) + i))) {
				shiftUp(a,i, k, l,n);
			}
		}
		k++;
		l++;
	}
}

void shiftUp(int *a,int col, int k, int l,int n) { // shifts up the tiles by 1
	*((a+k*n) + col) += *((a+l*n) + col);
	for (int i = l; i < n - 1; i++) {
		*((a+i*n) + col) = *((a+(i+1)*n) + col);
	}
	*((a+(n-1)*n) + col) = 0;
}

void leftMove(int *a,int n) {  // gets triggered when user choses LEFT move
	removeZeroesOfaRowLeftMove(a,n);
	int k = 0, l = 1;
	while (l < n) {
		for (int i = 0; i < n; i++) {
			if (isMergeble( *((a+i*n) + l),  *((a+i*n) + k))) {
				shiftLeft(a,i, k, l,n);
			}
		}
		k++;
		l++;
	}
}

void shiftLeft(int *a,int row, int k, int l,int n) { // shifts left the tiles by 1
	*((a+row*n) + k) += *((a+row*n) + l);
	for (int i = l; i < n - 1; i++) {
		*((a+row*n) + i) = *((a+row*n) + i+1);
	}
	*((a+row*n) + n-1) = 0;
}

void rightMove(int *a,int n) { // gets triggered when user choses RIGHT move
	removeZeroesOfaRowRightMove(a,n);
	int k = n - 1, l = n - 2;
	while (l >= 0) {
		for (int i = 0; i < n; i++) {
			if (isMergeble(*((a+i*n) + l),  *((a+i*n) + k))) {
				shiftRight(a,i, k, l,n);
			}
		}
		k--;
		l--;
	}
}

void shiftRight(int *a,int row, int k, int l,int n) { // shifts right the tiles by 1
	*((a+row*n) + k) += *((a+row*n) + l);
	for (int i = l; i > 0; i--) {
		*((a+row*n) + i) = *((a+row*n) + i-1);
	}
	*((a+row*n) + 0) = 0;
}