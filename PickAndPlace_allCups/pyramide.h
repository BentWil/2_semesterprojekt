#include <iostream>
#include <vector>
#include "vec.h"


std::vector<Vec> pyramidAllCups()
{


	int cupn = 40;
	int cuph = 8;
	int cupd = 5;
	int cupspace = 2;
	
	int base = 0;
	int upper = 0;
	
	int a = cupn;
	int b = cupn;
	int c = cupn;
	
//basen vil stige, hvis der kommer for mange kopper til at færdiggøre et tårn starte med det mindste tårn af 3 kopper
	if (a > 2)
	{
		upper = 1;
		base = 2;
		a = a - 3;
	}
	
	for (int i = 3; i <= a; i++)	//hvis der er flere kopper tilovers bygges der en hel side mere til et helt tårn
	{
		base = base + 1;
		upper = (base*(base + 1))/2 - base;
		a = a - i;
	}
	
	for (int i = 1; i <= a; i++)	//hvis der er enkelte tilbage som ikke er nok til at færdiggøre et tårn
	{
		base = base + 1;
		a = a - 1;
		
		
		if ((a != 0) || (a < base))
		{
			upper = upper + a;
			a = 0;
		}
	}

//finde antal kopper på resten af lagene	
	int count = 0;
	int row;
	int setCup = 0;
	int cupInLine;
	float x = 0;
	float y = 0;
	float z = 0;
	
	Vec reference(0,0,0);
	Vec rowstart =  reference;
	Vec xshift(cupd + cupspace,0,0);
	Vec layershift((cupd + cupspace)/2, 0, cuph);
	std::vector<Vec> list;

	while (b > 0)
	{
		row = base - count;
		count++;
		b = b - row;
		
		cupInLine = c - (b + setCup);
		
		setCup = setCup + row;

//Sidste antal kopper i sidste række, hvis det ikke går op
		if (b < 0)
		{
			cupInLine = b + cupInLine;
		}
		
		//std::cout << "Row: " << row << ". Cups left after this line: " << b << ". Cups in line: " << cupInLine << std::endl;

//koordinater
		Vec placehere = rowstart;
		

//få sat koordinater på
		for(int i = 0; i < cupInLine; i++)
		{	
			
			
			
			list.push_back(placehere);
			
			//std::cout << "coordinates: ";
			//placehere.print();			
			//std::cout << ". Number cup in line: " << i + 1 << std::endl;
			
			placehere.move(xshift);   //placehere += cupd + cupspace;		
			
			
			
			
			
			/*
			
			x = (cupd * i);
			if (i > 0)
			{
				x = x + (i*2.5);
			}
			
			while(b > 0)
			{
				coor.push_back(x);
			}
			
			for (unsigned int q = 0; q < coor.size(); q++)
			{
				
			}*/
		}
		
		//efter hver række, flyttes starten på næste række
		rowstart.move(layershift);
		
		
	}
	
/*koordinater til kopperne
	std::cout << "upper: " << upper << "\n";
	std::cout << "base: " << base << "\n";
	std::cout << "cups left: " << a << "\n";
	std::cout << "cups start: " << cupn << "\n";*/
	
	
	
	return list;
	
}
