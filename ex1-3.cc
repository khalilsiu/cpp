#include <iostream>
#include "Sales_item.h"

int main()
{
    // std::cout << "Hello, World";
    // std::cout << "Enter 2 numbers: ";
    // int v1 = 0, v2 = 0;
    // std::cin >> v1;
    // std::cin >> v2;
    // std::cout << "The product of ";
    // std::cout << v1 ;
    // std::cout << " and " ;
    // std::cout << v2 ;
    // std::cout << " is " ;
    // std::cout << v1 * v2 ;
    // std::cout << std::endl;

    // ex 1.9
    // int sum = 0, val = 50;
    // while (val <= 100){
    //     sum += val;
    //     ++val;
    // }
    // std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

    // ex1.10
    // int val = 10;
    // std::cout << "The value is ";
    // while(val > 0){
    //     std::cout << val << std::endl;
    //     --val;
    // }

    // ex1.11
    // std::cout << "Enter 2 numbers ";
    // int v1 = 0, v2 = 0, store = 0, store2 = 0;
    // std::cin >> v1 >> v2;
    // store = v1;
    // store2 = v2;
    // while (v1 > 0){
    //     std::cout << store << std::endl;
    //     --v1;
    // }
    // while (v2 > 0){
    //     std::cout << store2 << std::endl;
    //     --v2;
    // }
//1.4.2
    // int sum = 0;
    // for (int val = 1; val <= 10; ++val)
    //     sum += val;
    // std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

//1.4.3
    // int sum = 0, value = 0;
    // while (std::cin >> value)
    //     sum += value;
    // std::cout << "Sum is: " << sum << std::endl;

//1.4.4
    // int currVal = 0, val = 0;
    // if (std::cin >> currVal){
    //     int cnt = 1;
    //     while(std::cin >> val){
    //         if(val == currVal)
    //             ++cnt;
    //         else {
    //             std::cout << currVal << " occurs "
    //                       << cnt << " times " << std::endl;
    //             currVal = val;
    //             cnt = 1;
    //         }
    //     }

    //     std::cout << currVal << " occurs "
    //               << cnt << " times" << std::endl;
    // }

// ex 1.20
    // Sales_item item1;
    // Sales_item item2;
    // while (std::cin >> item1 >> item2){
    //     if (item1 == item2){
    //         std::cout << "Items: " << item1 + item2;

    //     }
    // }  

    Sales_item total;
    if (std::cin >> total){
        Sales_item trans;
        while (std::cin >> trans){
            if (total.isbn()==trans.isbn()){
                total += trans;
            }else{
                std::cout << total << std::endl;
                total = trans;
            }
        }
        std::cout << total << std:: endl;
    }else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;


}