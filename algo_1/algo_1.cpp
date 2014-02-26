// Goal of the project: 
// Divide a list of 100 unordered numbers [1-1500] so that 
// to minimize the difference in their sum
//
// Francisco Tort
// May 6th, 2013
// Salinas, PR
//
// Approach #1, Brute force, time consuming and memory hog. inpractical but on reserve... (dont know by how much)

// Approach #2, Create 2 trees (research similar structures) where the root node is the sum of the subtree. 
//				Allows for swapping subtrees if that will reduce the overall diff...
//				How to deal with repeats... custom tree...
//       12             30
//      5   7         14   16
//     3 2  1 6      7  7  8  8
// 
#include <iostream>
#include <string>
using namespace std;

void Randomize( int c, int arr [] )
{
	//int localArray [10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	//int x, y;
	//for ( int i = 0; i++;  i < 200)
	//{
	//	x = rand() * 10;
	//	y = rand() * 10;
	//	if ( (arr[x] != -1) && (localArray[y] == -1) )
	//	{
	//		arr[x] = localArray[y];
	//		arr[x] = -1;
	//	}
	//}
}

int main ( void )
{
	string in;
	int c = 0;
	int total, half = 0;
	int input[4] = {1, 1, 3, 100};
	int count = sizeof(input)/sizeof(int);


	cout << "Input: " << endl;
	for (c = 0; c < count; c++)
	{
		total =+ input[c]; 
		cout << input[c] << endl;
	}
	half = total / 2;






	cin >> in;

return 0;
}


