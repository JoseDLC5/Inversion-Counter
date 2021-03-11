/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Breanna Shinn & Jose de la Cruz
 * Version     : 1.0
 * Date        : October 27, 2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count = 0;
    for (int i = 0; i<length-1; i++)
    {
    	for (int j = i+1; j<length; j++)
    	{
    		if (array[i] > array[j])
    		{
    			count++;
			}
		}
	}
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int*arr = new int[length];
    long count = mergesort(array, arr, 0, length-1);
    delete [] arr;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    int mid;
    int L;
    int H;
    long count = 0;
    if (low < high)
    {
    	mid = low + (high - low) /2;
    	count += mergesort(array, scratch, low, mid);
    	count += mergesort(array, scratch, mid+1, high);
    	L = low;
    	H = mid + 1;
    	for (int k=low; k<=high; k++)
    	{
    		if ( (L <= mid) && ( (H > high) || (array[L] <= array[H]) ) )
    		{
    			scratch[k] = array[L];
    			L = L+1;
			}
			else 
			{
                count += mid-L+1;
				scratch[k] = array[H];
				H = H+1;
			}
		}
		for (int j = low; j<=high; j++)
		{
			array[j] = scratch[j];
		}
	}

    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	istringstream is;
	string slow;
	if (!(argc == 1 || argc == 2)) {
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
	if (argc == 2) {
		is.str(argv[1]);
		is >> slow;
		if (slow != "slow"){
			cerr << "Error: Unrecognized option '" << slow << "'." << endl;
			return 1;
		}
	}
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    
    if(values.size() == 0){
    	cerr << "Error: Sequence of integers not received.";
    	return 1;
	}

    int size = values.size();
    int* arr = new int[size];
    copy(values.begin(), values.end(), arr);
    long inversion_count;
    if (argc == 1)
    {
    	inversion_count = count_inversions_fast(arr, size);
	}
	else 
	{
		inversion_count = count_inversions_slow(arr, size);
	}
    
    // TODO: produce output
    cout << "Number of inversions: " << inversion_count << endl;
    delete [] arr;
    return 0;
}
