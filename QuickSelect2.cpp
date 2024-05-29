#include "QuickSelect2.hpp"

/*
For method 3, replace the key k in your quickSelect's parameters with a set of keys you're looking for (use whatever container you want to hold them), which will include position 0, the 25% mark, the 50% mark, the 75% mark, the the last position of the data vector. 
Rewrite the recursive portion of quickSelect so that it checks whether it needs to recurse on both sides (if there are keys you need to find on both sides of the range being called), or if it only needs to recurse on one side. 
This may be tricky to work out, but once you figure out the algorithm, it's not really much coding to implement. Again, default to insertion sort once you reach a size of 20 or less.
*/


//use the same as quickSelect1
//replace int k with a vector of the percentiles

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



void quick_select(std::vector<int> & data, int left, int right, std::vector<int>& keys)          //derived from textbook pg 322, except vector of keys replaces int k
{

    //IMPORTANT: Most of this function is derived from the textbook pg 322, but there are some nuances.
    //The overarching conditional that seperates quick_select and insertionSort is different here.
    //There are margin checks for the while loops needed to avoid out-of-bounds segmentation faults.

    //After we restore the pivot, we find all key percentiles that are less than the pivot index and place those to the left side of the data. If the key percentiles are greater than the pivot index, place those to the right side of the data.


    //the last if-condtional is very significant. We are using a vector of multiple keys now instead of only one key. 
        //if the left vector is not empty, recursively call quickselect on the left side.
        //if the right vector is not empty, recursively call quickselect on the right side.




    if (data.size() > 20)
    {

        std::vector<int> leftHalf;              //now we create seperate sections of the original vector.
        std::vector<int> rightHalf;

                //_______________________________________________

            const int pivot = median3(data,left,right);       //pivot value finds an optimal element to choose

            //begin the partition:
            //this ensures that the pivot is sorted to the correct position while other elements around it are partially sorted. (partitions data around the pivot basically)

            int i = left;
            int j = right-1;
                                                                   
            for( ; ; )
            {

//Important: The textbook implementation does not include right>i or left<j. The lack of these margin checks causes segmentation fault error. So, there is a out-of-bounds error.
 //data[++i] compares the current element with the pivot we chose (the current element is incremented before comparing). It checks if the data on the right is less than the pivot (which means it is out of order)
 //to avoid going beyond bounds, the right (which is the last index of the entire data vector) must be greater than our current i.

 //do the same on the opposite end and check if pivot is less than its left value (which means it is out of order).

                while(i < right && data[++i] < pivot) {}        
                while(j > left && pivot < data[--j]) {}
                if (i < j)
                {
                    std::swap(data[i], data[j]);        //when the current right-of-pivot i value is less than the current left-of-pivot j value, they are out of order. swap them like quicksort.
                }
                else
                {
                    break;          //if we reach a point where this is not the case, then we have successfully partitioned around the pivot.
                }
            }

            std::swap(data[i], data[right-1]);     //restore the pivot by swapping the current i element with the pivot position (data[right-1])

                //_______________________________________________

        for (int z=0; z < keys.size(); z++)                                                     //every recursive call, we keep placing the keys that are smaller than our pivot before the pivot, and bigger than the pivot after.
        {
            if (keys[z] < i)                        //i is the pivot index as of now.
            {
                leftHalf.push_back(keys[z]);
            }

            else if (keys[z] > i)
            {
                rightHalf.push_back(keys[z]);

            }
        } 




        int remainingInLeft=1;          //to check if there are remaining elements in each side.
        int remainingInRight=1;


        //recursion:



        if (leftHalf.empty())
        {
            remainingInLeft = 0;
        }

        if (rightHalf.empty())
        {
            remainingInRight = 0;
        }


        if (remainingInLeft != 0)           //if the left half is not empty yet
        {

                //if (k <= i)             //if key is in the left half. We DON't need this anymore. the lefthalf vector for-loop and righthalf vector for-loop now take this into consideration naturally, except with MULTIPLE keys instead of just 1 key. Even if we stuck to just 1 key, it would be very inefficient and not really follow the instructions well.
                                            //remember, left-half vector is left of pivot naturally, we don't need to check k <=i.
                    quick_select(data, left, i-1, leftHalf);        //recursively call starting from leftmost index to rightmost index (excluding the pivot index, and call with all the leftHalf keys.
                
        }
            // else if (k > i + 1)                 //if key is in the right half
                

        if (remainingInRight != 0)
        {

                    quick_select(data, i+1, right, rightHalf);

        }

    }

    else
    {
        insertionSort(data);
    }
            


    

}

void quickSelect2 (const std::string & header, std::vector<int> data)
{

    auto start = std::chrono::high_resolution_clock::now();


    int middle = data.size() / 2;               //for now just view this as the 50th percentile, not the 50th index. 50th index is not half of 100 elements (if we needed the middle index, we have to subtract 50 by 1 to get index 49 which is the 50th element)
    int firstQ = data.size() / 4;                   //25th
    int thirdQ = data.size() * 3 / 4;               //75th


    if (data.size() > 20)
    {

        int size = data.size()-1;

        std::vector<int> keys;                  //the keys parameter will have all these position targets
        keys.push_back(0);
        keys.push_back(firstQ-1);
        keys.push_back(middle-1);
        keys.push_back(thirdQ-1);
        keys.push_back(size);


        quick_select(data, 0, data.size()-1, keys);         //call only once with all the keys

    }

    else
    {
        insertionSort(data);

    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds\n";


        std::cout << header << "\n";
        std::cout << "Min: " << data[0] << "\n";            
        std::cout << "P25: " << data[firstQ-1] << "\n";
        std::cout << "P50: " << data[middle-1] << "\n";
        std::cout << "P75: " << data[thirdQ-1]<< "\n";
        std::cout << "Max: " << data[data.size()-2] << "\n";


}
