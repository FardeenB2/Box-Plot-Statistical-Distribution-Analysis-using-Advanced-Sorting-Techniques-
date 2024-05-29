#include "StdSort.hpp"

/*
For method 1, just use std::sort and print out the appropriate data points. 
This is to ensure that you have the correct answer and are printing correctly, and to give you a baseline to time your other algorithms against.
*/



//This function is called "middle", but will find the median of the vector, then the 25th percentile, and the 75th percentile.
int stdSortMiddle(const std::vector<int>& sortedData, const std::string& position)    
{
    int middle;
    int middle_index;

    if (position == "median")
    {

            if (!sortedData.empty()) //vector size is always gonna be divisble by 100, so always even
            {
               
                    middle_index = sortedData.size() / 2 - 1;       //pretty sure we choose the lower number of the two medians of an even total count.

                    middle = sortedData[middle_index];          //get the middle value of the data.      

                    return middle;

    
            }
    }

    else if (position == "firstQuartile")
    {
            if (!sortedData.empty())            //vector size is always gonna be divisble by 100, so always even
            {
                    middle_index = sortedData.size() / 4 - 1;                           //finds the 25th percentile index

                    middle = sortedData[middle_index];                  //finds the 25th percentile value

                    return middle;

            }
            
    }

    else if (position == "thirdQuartile")
    {
            if (!sortedData.empty())                    //vector size is always gonna be divisble by 100, so always even
            {
                
                    middle_index = sortedData.size() * 3 / 4 - 1;                       //finds the 75th percentile index

                    middle = sortedData[middle_index];                          //find the 75th percentile value.

                    return middle;

                

            }
    }

    return -1;                  //if the position parameter is none of these, then there is an issue, return -1

}



void stdSort(const std::string & header, std::vector<int> data)
{

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(data.begin(), data.end());

    int min = data.front();                 //front() and back() are constant time dereferencing pointer operations.
    int max = data.back();

    int median = stdSortMiddle(data, "median");       

    int firstQuartile = stdSortMiddle(data, "firstQuartile");

    int thirdQuartile = stdSortMiddle(data, "thirdQuartile");


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds\n";

    std::cout << header << "\n";
    std::cout << "Min: " << min << "\n";
    std::cout << "P25: " << firstQuartile << "\n";
    std::cout << "P50: " << median << "\n";
    std::cout << "P75: " << thirdQuartile << "\n";
    std::cout << "Max: " << max << "\n";



}



