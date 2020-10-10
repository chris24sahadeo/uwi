// ML
// * Error in arithmetic: converting area of room from square feet to square inches: needed to multiply by 144 not 12
// * Error in comprehension: You need to calculate the number of bags of grout required, not accept from the user
// * Error in comprehension: You need to calculate the number of bags of thinset required, not accept from the user


// TODO:
// * finish output code
// * test thoroughly
// * remember to save test data and correct output at the bottom of the file


#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;


// CONSTANTS
#define INCHES_PER_FOOT 12
#define GROUT_BAG_UNIT_WEIGHT 25.00
#define GROUT_BAG_UNIT_COST 60.00
#define GROUT_WEIGHT_PER_SQUARE_FOOT 0.13
#define THINSET_BAG_UNIT_WEIGHT 50.00       // irrelevant??
#define THINSET_BAG_UNIT_COST 45.00
#define AREA_PER_THINSET_BAG 90
#define VAT 0.125


int main(){

    double roomLengthInFeet, roomWidthInFeet;
    cout << "Enter room length (ft): ";
    cin >> roomLengthInFeet;
    cout << "Enter room width (ft): ";
    cin >> roomWidthInFeet;

    double tileLengthInInches, tileWidthInInches;
    cout << "Enter tile length (in): ";
    cin >> tileLengthInInches;
    cout << "Enter tile width (in): ";
    cin >> tileWidthInInches;

    double tileUnitCost;
    cout << "Enter tile unit cost ($): ";
    cin >> tileUnitCost;


    // assuming we can have fractions of a tile like in the real world

    // calculating the number and cost of tiles required for the job
    double roomLengthInInches = roomLengthInFeet*INCHES_PER_FOOT;
    double roomWidthInInches = roomWidthInFeet*INCHES_PER_FOOT;
    double roomAreaInSquareInches = roomLengthInInches*roomWidthInInches;
    double tileAreaInSquareInches = tileLengthInInches*tileWidthInInches;
    double numberOfTiles = ceil(roomAreaInSquareInches/tileAreaInSquareInches);
    double costOfTiles = numberOfTiles*tileUnitCost;

    // calculating amount and cost of grout needed
    double roomAreainSquareFeet = roomLengthInFeet*roomWidthInFeet;
    double groutWeightRequired = roomAreainSquareFeet*GROUT_WEIGHT_PER_SQUARE_FOOT;
    double numberOfGroutBags = ceil(groutWeightRequired/GROUT_BAG_UNIT_WEIGHT);
    double costOfGrout = numberOfGroutBags*GROUT_BAG_UNIT_COST;

    // calculating amount and cost of thinset needed
    double numberOfThinsetBags = ceil(roomAreainSquareFeet/AREA_PER_THINSET_BAG);
    double costOfThinset = numberOfThinsetBags*THINSET_BAG_UNIT_COST;

    // calculating subtotal, VAT and total
    double subTotal = costOfTiles + costOfGrout + costOfThinset;
    double vat = VAT*subTotal;
    double total = subTotal + VAT;


    // outputting the invoice
    printf(
        "*** Sally's One Stop Tile Shop Invoice ***\n\n"

        "Length of room in feet: %f\n"
        "Width of room in feet: %f\n"
        "Area of room in square feet: %f\n\n"

        "Length of tile in inches: %f\n"
        "Width of tile in inches: %f\n"
        "Area of a tile in square inches: %f\n\n"

        "Unit cost of tile: %f\n"
        "Unit cost of grout bad: %f\n"
        "Unit cost of thinset: %f\n\n"



    ,
        roomLengthInFeet,
        roomWidthInFeet,
        roomAreainSquareFeet,
        tileLengthInInches,
        tileWidthInInches,
        tileAreaInSquareInches,
        tileUnitCost,
        GROUT_BAG_UNIT_COST,
        THINSET_BAG_UNIT_COST
    );


    return 0;
}


/*
TEST DATA

SET 1:


*/
