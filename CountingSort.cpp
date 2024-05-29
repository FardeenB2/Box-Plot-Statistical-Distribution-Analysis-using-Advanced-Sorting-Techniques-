#include "CountingSort.hpp"

/*
Method 4 (counting sort) is the only of these methods that isn't in-place. You'll need to read the integers from the data vector and insert them into a hash map, with the data value as the hash key, and a count of times that particular data value was seen as the hash value. 
So the first time you see a new value X in the data, you insert it into the hash using X as the key, and you set that key's hash value to 1. 
The second time you see X, you find that it's already in the hash, so you increment its hash value to 2. 
The third time you see X, you increment its hash value to 3, and so on.
Once you have a hash map of all the unique data values and the number of times each data value appeared in the data, iterate through the hash map, pushing the key-value pairs in the hash map to a vector.
Then, sort that vector using std::sort (in an input with many duplicates, a vector of unique values will be much smaller than a vector of all the values). 
Finally, iterate through that vector finding P25, P50, and P75. You'll have to count how many data points you've seen along the way, since each element of the vector represents multiple data point, not just one. Finding the minimum and maximum should be self-explanatory.
*/




void countingSort (const std::string & header, std::vector<int> data)
{

    auto start = std::chrono::high_resolution_clock::now();


    std::unordered_map<int, int> hashMap;               //the main hashmap

    std::vector<std::pair<int, int> > keyValuePairs;        //a vector where each index contains a keyValuePair from the hashMap;
    


    for (int i=0; i < data.size(); i++)
    {
        if (hashMap.count(data[i]) > 0)             //if the hash key (data-value) is found in hashMap, increment the hash value (data-count)
        {
            hashMap[data[i]] +=1;   
        }

        else
        {
            hashMap[data[i]] = 1;           //if the data value is not found in the hashMap, we add it to the hashMap and we also have our data-count as 1.
        }
    }


    for (const auto& hashPair: hashMap)
    {
        keyValuePairs.push_back(hashPair);          //each keyvaluepair in the hashmap is now placed in the keyValuePairs vector.
    }


    std::sort(keyValuePairs.begin(), keyValuePairs.end());

    int middle = data.size() / 2;               //for now just view this as the 50th percentile, not the 50th index. 50th index is not half of 100 elements (if we needed the middle index, we have to subtract 50 by 1 to get index 49 which is the 50th element)
    int firstQ = data.size() / 4;                   //25th
    int thirdQ = data.size() * 3 / 4;               //75th

    int dataCountCounter=0;
    int uniqueValuesCounter=0;

    
    int found25=0;
    int found50=0;
    int found75=0;
    int foundMax=0;


    std::cout << header << "\n";

    for (int a=0; a < keyValuePairs.size(); a++)
    {
        if (dataCountCounter == 0)                  //0th index, which is first value. After stdsort, this has to be the minimum
        {
            std::cout << "Min: " << keyValuePairs[a].first << "\n";         //we print out the first part of the pair (the key which is the percentile value)
        }

        dataCountCounter += keyValuePairs[a].second;            // with each iteration of the for loop, we add the keyValuePair's value.
            //this^ is because each keyValuePair can have multiple values for one key (through CHAINING collision resolution method). So keyValuePairs vector naturally has less indices than the original total vector of data. So we must keep track of the number of values we came across to find the percentiles. 


        if (dataCountCounter >= firstQ && found25 == 0)              //Note to self: firstQ-1 is the 24th INDEX, which is the 25th PERCENTILE
        {   
            //once we reached the 25th percentile or went right beyond it, we print out the current key of the keyValuePair, and increment found25 so that we may never use this condition again.

            std::cout << "P25: " << keyValuePairs[a].first << "\n";
            found25++;          //this ensures that once this conditional has been found, we can fully ignore it for the rest of the iterations. NEEDED.
        }

        else if (dataCountCounter >= middle && found50 == 0)              //49th index. The idea for the >= instead of == is because the dataCountCounter can skip from 4 to 7 or 15 to 17 depending on the current keyValuePair's value. So we may not always get the exact dataCount to percentile comparison.
        {
            std::cout << "P50: " << keyValuePairs[a].first << "\n";
            found50++;
        }

        else if (dataCountCounter >= thirdQ && found75 == 0)              //74th index
        {
            std::cout << "P75: " << keyValuePairs[a].first << "\n";
            found75++;

        }

        else if (dataCountCounter >= data.size() && foundMax == 0)
        {
            std::cout << "Max: " << keyValuePairs[a].first << "\n";
            foundMax++;
        }
        
       
        uniqueValuesCounter++;      //count all values of this chaining method vector, through iteration.
        

    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds\n";
 

    std::cout <<"Unique: "<< uniqueValuesCounter << "\n";

}