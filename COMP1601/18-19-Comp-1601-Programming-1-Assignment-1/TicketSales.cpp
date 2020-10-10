// ML
// * Error in comprehension: You were supposed to accept the cost per ticket from the user via keyboard, not set it int the code


#include <iostream>
using namespace std;


int main(){

    double moundTicketsUnitPrice, standTicketsUnitPrice, premiumTicketsUnitPrice, vipTicketsUnitPrice;
    int moundTicketsQuantity, standTicketsQuantity, premiumTicketsQuantity, vipTicketsQuantity;

    cout << "Price of Mound Tickets? ";
    cin >> moundTicketsUnitPrice;
    cout << "Number of Mound Tickets sold? ";
    cin >> moundTicketsQuantity;
    cout << endl;

    cout << "Price of Stand Tickets? ";
    cin >> standTicketsUnitPrice;
    cout << "Number of Stand Tickets sold? ";
    cin >> standTicketsQuantity;
    cout << endl;

    cout << "Price of Premium Tickets? ";
    cin >> premiumTicketsUnitPrice;
    cout << "Number of Premium Tickets sold? ";
    cin >> premiumTicketsQuantity;
    cout << endl;

    cout << "Price of VIP Tickets? ";
    cin >> vipTicketsUnitPrice;
    cout << "Number of VIP Tickets sold? ";
    cin >> vipTicketsQuantity;
    cout << endl;


    double moundsSales = moundTicketsQuantity*moundTicketsUnitPrice;
    double standsSales = standTicketsQuantity*standTicketsUnitPrice;
    double premiumSales = premiumTicketsQuantity*premiumTicketsUnitPrice;
    double vipSales = vipTicketsQuantity*vipTicketsUnitPrice;

    cout << "Mounds Sales: $" << moundsSales << endl;
    cout << "Stands Sales: $" << standsSales << endl;
    cout << "Premium Sales: $" << premiumSales << endl;
    cout << "VIP Sales: $" << vipSales << endl;


    int totalQuantity = moundTicketsQuantity + standTicketsQuantity + premiumTicketsQuantity + vipTicketsQuantity;
    double totalMoney = moundsSales + standsSales + premiumSales + vipSales;

    cout << totalQuantity << " ticket(s) were sold" << endl;
    cout << "Total money collected was $" << totalMoney << endl;


    return 0;
}


/*
TEST DATA:
SET 1:
40
8000
60
4000
75
100
220
50


SET 2:
19.99
1651
25.99
2045
52.25
3516
64.59
4544

*/
