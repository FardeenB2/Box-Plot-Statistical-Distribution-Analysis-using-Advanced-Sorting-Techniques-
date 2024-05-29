#include "QuickSelect1.hpp"

/*
For method 2, using quickSelect 3 times, the idea is simple: call quickSelect on the entire input with the middle of the vector as the key, k. 
This will give you the median, around which your vector will be partitioned. 
Then, call quickSelect on the half of the vector before the median with the 25% mark of the vector as k.
Then, call quickSelect on the half of the vector after the median with the 75% mark as k.
Then, search for the minimum only before the 25% mark, and the maximum only after the 75% mark. 
Default to insertion sort when quickSelect is recursively called on a range of size 20 or less (this means you'll have to write a small in-place insertion sort).
*/



    void insertionSort(std::vector<int> & data)     //Practically all of this function is utilized from our TEXTBOOK, pg 293
    {
        for( int a = 1; a < data.size( ); ++a)
        {
            int tmp = std::move( data[ a ] );               //current element value stored in temp variable

            int z;
            for( z = a; z > 0 && tmp < data[ z - 1 ]; --z )     //for when the current element value is less than on the immediate value left of it, you must shift.
            {
                data[ z ] = std::move( data[ z - 1 ] );         //the shift.
            }
               
            data[ z ] = std::move( tmp );           //the temp variable element is placed in its sorted position
            
        }

    }


const int& median3( std::vector<int> & data, int left, int right )             //practically all of this function is utilized from our TEXTBOOK pg 316
{
    int middle = (left + right) / 2;

    if( data[middle] < data[left] )
    {
        std::swap( data[left], data[middle] );
    }
    if( data[right] < data[left ])
    {
        std::swap( data[left], data[right] );
    }
    if( data[right] < data[middle] )
    {
        std::swap( data[middle], data[right] );
    }

    // Place pivot at position right - 1
    std::swap( data[middle], data[right - 1] );

    return data[ right - 1 ];       //returns a value, NOT index.
}


void quick_select(std::vector<int> & data, int left, int right, int k)          //derived from textbook pg 322
{      

    //IMPORTANT: Most of this function is derived from the textbook pg 322, but there are a few nuances.
    //The overarching conditional that seperates quick_select and insertionSort is different here.
    //There are margin checks for the while loops needed to avoid out-of-bounds segmentation faults.


    if (data.size() > 20)
    {

        const int pivot = median3(data,left,right);       //pivot value finds an optimal element to choose

        //begin the partition:

        int i = left;           //leftmost index
        int j = right-1;        //rightmost index-1 (Because we don't count the pivot here)

        for( ; ; )
        {

//Important: The textbook implementation does not include right>i or left<j. The lack of these margin checks causes segmentation fault error. So, there is a out-of-bounds error.
 //data[++i] compares the current element with the pivot we chose (the current element is incremented before comparing). It checks if the data on the right is less than the pivot (which means it is out of order)
 //to avoid going beyond bounds, the right (which is the last index of the entire data vector) must be greater than our current i.

 //do the same on the opposite end and check if pivot is less than its left value (which means it is out of order).

            while(right > i && data[++i] < pivot) {}        
            while(left < j && pivot < data[--j]) {}        
            if (i < j)
            {
                std::swap(data[i], data[j]);        //when the current right-of-pivot i value is less than the current left-of-pivot j value, they are out of order. swap them like quicksort.
            }
            else
            {
                break;              //if we reach a point where this is not the case, then we have successfully partitioned around the pivot.
            }
        }

        std::swap(data[i], data[right-1]);      //restore the pivot by swapping the current i element with the pivot position (data[right-1])



        //recursion:

        if (k <= i)             //A large difference between quicksort and quickselect lies within the recursion. We now check to see whether the target key (50th or 25th or 75th percentile) is on the left or right partition.
        {
            quick_select(data, left, i-1, k);           //recursively call on left partition to find the key because it lies within that side only.
        }

        else if (k > i + 1)
        {
            quick_select(data, i+1, right, k);      //recursively call on right partition to find the key because it lies within that side only.
        }

    }

    else
    {
        insertionSort(data);
    }
       

    

}



void quickSelect1 (const std::string & header, std::vector<int> data)
{

    auto start = std::chrono::high_resolution_clock::now();

    int middle = data.size() / 2;               //for now just view this as the 50th percentile, not the 50th index. 50th index is not half of 100 elements (if we needed the middle index, we have to subtract 50 by 1 to get index 49 which is the 50th element)
    int firstQ = data.size() / 4;                   //25th
    int thirdQ = data.size() * 3 / 4;               //75th


    if (data.size() > 20)
    {

        quick_select(data, 0, data.size()-1, middle-1);        //leftmost index is 0, rightmost index is the last element data.size()-1. this one partitions the vector around the median key.
        quick_select(data, 0, middle-1, firstQ-1);              //this call partitions the vector around the 25th percentile key
        quick_select(data, middle, data.size()-1, thirdQ-1);    //this call partitions the vector around the 75th percentile key

        std::vector<int> firstQuartileVector;
        std::vector<int> thirdQuartileVector;


        for (int a=0; a < data.size(); a++)
        {
            if (a < firstQ)         //all indices below p25. the reason for this firstQuartileVector is so that we follow the instructions where we only check the first quartile to find the minimum.
            {
                firstQuartileVector.push_back(data[a]);         
            }
            else if (a > thirdQ)     //all indices above p75. the reason for this thirdQuartileVector is so that we follow the instructions in that we only check the third quartile for the maximum.
            {
                thirdQuartileVector.push_back(data[a]);
            }
        }


        auto minimum = std::min_element(firstQuartileVector.begin(), firstQuartileVector.end());
        auto maximum = std::max_element(thirdQuartileVector.begin(), thirdQuartileVector.end());



    
        std::cout << header << "\n";
        std::cout << "Min: " << *minimum << "\n";
        std::cout << "P25: " << data[firstQ-1] << "\n";         //we subtract 1 because for example out of a 100 elements, firstQ is 25. to access the 25th element, the index is 24 0-based. 
        std::cout << "P50: " << data[middle-1] << "\n";
        std::cout << "P75: " << data[thirdQ-1]<< "\n";
        std::cout << "Max: " << *maximum << "\n";
    
    }

    else
    {
        insertionSort(data);

        std::cout << header << "\n";
        std::cout << "Min: " << data[0] << "\n";            
        std::cout << "P25: " << data[firstQ-1] << "\n";
        std::cout << "P50: " << data[middle-1] << "\n";
        std::cout << "P75: " << data[thirdQ-1]<< "\n";
        std::cout << "Max: " << data[data.size()-2] << "\n";


    }

    //  {these timed tests were conducted while the above std::cout lines were commented out!}

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds\n";
        

}

