#include <iostream>
#include <vector>
#include "vec.h"

class Pyramid {

private:

    int cupn;
    float cuph;
    float cupd;
    float cupSpace = 0.02;

public:

Pyramid(int cupNum, int cupType){

    int cupn = cupNum;

    if(cupType == 1){
        float cuph = 0.08;
        float cupd = 0.05;
    }

}

    std::vector<Vec> pyramidAllCups() {
//Define variables
        //Cups information
       // int cupn = 14;
     //   float cuph = 0.08;
   //     float cupd = 0.05;
 //       float cupspace = 0.02;
        int a = cupn;
        int b = cupn;
        int c = cupn;

        //Cups in pyramid
        int base = 0;
        int upper = 0;


        int count = 0;
        int row;
        int setCup = 0;
        int cupInLine;
        float x = 0;
        float y = 0;
        float z = 0;

        //Vectors
        Vec reference(0, 0, 0);
        Vec rowstart = reference;
        Vec xshift(cupd + cupSpace, 0, 0);
        Vec layershift((cupd + cupSpace) / 2, 0, cuph);
        std::vector<Vec> list;

        Vec placehere = rowstart;

        //Only one cup
        if (a == 1) {
            base = 1;
            a = a - 1;
            cupInLine = 1;

            for (int i = 0; i < cupInLine; i++) {
                list.push_back(placehere);
                placehere.move(xshift);   //placehere += cupd + cupspace;
            }

            //Check high in z-axis
            rowstart.move(layershift);
        }

        //Only two cups
        if (a == 2) {
            base = 2;
            a = a - 2;
            cupInLine = 2;

            for (int i = 0; i < cupInLine; i++) {
                list.push_back(placehere);
                placehere.move(xshift);   //placehere += cupd + cupspace;
            }

            //Check high in z-axis
            rowstart.move(layershift);
        }

        //Making the smallest tower possible
        if (a > 2) {
            upper = 1;
            base = 2;
            a = a - 3;

            //Chech if a biggere complet tower can be builded with the remaining cups
            for (int i = 3; i <= a; i++) {
                base = base + 1;
                upper = (base * (base + 1)) / 2 - base;
                a = a - i;
            }

            //If a whole tower can not be builded
            for (int i = 1; i <= a; i++) {
                base = base + 1;
                a = a - 1;


                if ((a != 0) || (a < base)) {
                    upper = upper + a;
                    a = 0;
                }
            }

            //Count rows and cups in rows
            while (b > 0) {
                row = base - count;
                count++;
                b = b - row;

                //Cups in each row
                cupInLine = c - (b + setCup);

                setCup = setCup + row;

                //If not completed tower the rest of cups in last row
                if (b < 0) {
                    cupInLine = b + cupInLine;
                }

                //Rowstart increace high in z-axis
                placehere = rowstart;

                //Making coordinates in x-axis
                for (int i = 0; i < cupInLine; i++) {
                    list.push_back(placehere);

                    placehere.move(xshift);   //placehere += cupd + cupspace;
                }

                //Shift row if needed
                rowstart.move(layershift);
            }
        }
        return list;
    }
};