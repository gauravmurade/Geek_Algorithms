#include <iostream>
#include <queue>
using namespace std;

typedef struct petrolPump {
	int petrol;
	int distance;
} petrolPump;

int printTour(petrolPump arr[], int arrLength) {

	int startingNode = 0;
	int nodeBeingChecked;
	int numberOfNodesChecked;
	int totalPetrol;
	int totalDist;

	while (startingNode < arrLength) {

		nodeBeingChecked = startingNode;
		totalPetrol = arr[nodeBeingChecked].petrol;
		totalDist = arr[nodeBeingChecked].distance;
		numberOfNodesChecked = 0;

		while ((totalPetrol > totalDist) && (numberOfNodesChecked < arrLength)) {
			nodeBeingChecked = (nodeBeingChecked + 1) % arrLength;
			totalPetrol += arr[nodeBeingChecked].petrol;
			totalDist += arr[nodeBeingChecked].distance;			
			numberOfNodesChecked++;
		}
		if(numberOfNodesChecked == arrLength) {
			return startingNode;
		}
	startingNode++;
	}	
	return -1;
}

int main()
{
   	petrolPump arr[] = {{4, 6}, {6, 5}, {7, 3}, {4, 5}};
 
    int arrLength = sizeof(arr)/sizeof(arr[0]);
    int start = printTour(arr, arrLength);
 
    (start == -1)? cout << "No solution" << endl: cout << "Start = " << start << endl;
 
    return 0;
}