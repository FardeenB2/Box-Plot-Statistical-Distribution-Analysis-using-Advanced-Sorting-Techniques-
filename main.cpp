#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "StdSort.hpp"
#include "QuickSelect1.hpp"
#include "QuickSelect2.hpp"
#include "InsertionSort.hpp"
#include "CountingSort.hpp"



int main() {

    
   std::vector<int> numbersContainer;

   std::ifstream file("testinput.txt");

   std::string header;

   if (!file.is_open())
   {
    std::cerr << "error in opening file";
    return 1;
   }

   std::string firstLine;    //for each line of the file
   if (std::getline(file, firstLine))
   {
        header = firstLine;


        std::string fileLine;
        while (std::getline(file, fileLine))
        {

                std::istringstream reader(fileLine);     //reader essentially takes in the current line to read and parse through.
                
                    int number;

                    while (reader >> number)
                    {
                        numbersContainer.push_back(number);
                        
                    }
            
        }

   }


   stdSort(header, numbersContainer);
    //quickSelect1(header, numbersContainer);

  //quickSelect2(header, numbersContainer);

   //countingSort(header, numbersContainer);


    file.close();

    return 0;
}