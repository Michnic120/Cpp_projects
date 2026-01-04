#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#include "Room.h"
#include "Sched.h"
#include "Controller.h"

using namespace std;
VOID WINAPI Sleep(DWORD dwMilliseconds);

int main()
{
	CRoom room_buffer;
	vector<CAirConditioner> conds(5);
   	vector<CRoom> rooms(5);
	vector<int> tem(5);
	vector<CRoom>::size_type sz_room = rooms.size();

	for(short i=0; i<sz_room; i++)
        {
            room_buffer.cond1=&conds[i];
            room_buffer.minus =i/0.1;
            room_buffer.plus =i/0.01;
            room_buffer.number = i;
            rooms[i] = room_buffer;
        }


	cout  << "Set the temperature in every room" << endl<<endl;
	cout  << "Attic:  "; cin >> tem[0];
	cout  << "Living room:     "; cin >> tem[1];
	cout  << "Bed room: "; cin >> tem[2];
	cout  << "Garage:     "; cin >> tem[3];
	cout  << "Cellar:   "; cin >> tem[4];


	CController s1(&conds[0], &rooms[0], tem[0]),
                   s2(&conds[1], &rooms[1], tem[1]),
                   s3(&conds[2], &rooms[2], tem[2]),
                   s4(&conds[3], &rooms[3], tem[3]),
                   s5(&conds[4], &rooms[4], tem[4]);

	CSched shed(&rooms[0], &s1, &rooms[1], &s2, &rooms[2], &s3, &rooms[3], &s4, &rooms[4], &s5, 1000);

	shed.Starter();

	return 0;
}
