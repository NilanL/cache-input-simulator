/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Name: Cache data-input simulator
    Author: Nilan Larios
    Date: 5/6/2021
    Update: 5/6/2021

    Description: Simulates the input of data into a cache-like data structure
    using an "Last Recently Used" replacement policy and set associativity.

    Notes:
        > Blocks and associativity cannot be over 65535 (0xffff)
            >> Will return -1073741819 if input is too high
        > Does not currently handle type exception cases
        > Does not currently empty cache
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "cache_set.h"
#include <stdlib.h>

using namespace std;

class Operations {
    public:
        unsigned short get_digits_amount(short n)
        {
            short temp = n;
            unsigned short counter = 0;

            while (temp != 0)
            {
                counter++;
                temp /= 10;
            }

            return counter;
        }
};

class Cache {
    private:
        unsigned short associativity;
        unsigned short total_block_amount;
        unsigned short set_amount;
        cache_set *set_array;

    public:
        unsigned short hits;
        unsigned short misses;
        unsigned short data_max_digits; // Stores the longest number's digits

    public:
        //** Default constructor
        Cache()
        {
            this->total_block_amount = 0;
            this->associativity = 0;
            this->set_amount = 0;

            this->hits = 0;
            this->misses = 0;

            this->data_max_digits = 0;
        }

        //** Parameterized constructor
        Cache(unsigned short block, unsigned short assoc)
        {
            // Sets cache information
            this->total_block_amount = block;
            this->associativity = assoc;
            this->set_amount = total_block_amount / associativity;

            this->set_array = new cache_set [associativity];

            // Initializes each set and its blocks
            for (int i = 0; i < set_amount; i++)
            {
                this->set_array[i].LRU_index = 0;
                this->set_array[i].is_full = false;
                this->set_array[i].blocks = new short [associativity];

                // Sets all blocks in set to empty flag -1
                for (int j = 0; j < associativity; j++)
                {
                    this->set_array[i].blocks[j] = -1;
                }
            }

            this->hits = 0;
            this->misses = 0;

            this->data_max_digits = 0;
        }

        //** Get/Set for associativity
        unsigned short get_associativity()
        {
            return associativity;
        }
        void set_associativity(unsigned short n)
        {
            this->associativity = n;
        }

        //** Get/Set for total_block_amount
        unsigned short get_block_amount()
        {
            return total_block_amount;
        }
        void set_block_amount(unsigned short n)
        {
            this->total_block_amount = n;
        }

        //** Finds spot in cache to input data
        void input_data(short n)
        {
            unsigned short input_index = n % set_amount; // Determines the set index to input into
            unsigned short LRU = set_array[input_index].LRU_index;
            unsigned short curr_digits;
            Operations oper;

            // Determines if the current number has more digits
            curr_digits = oper.get_digits_amount(n);
            if (curr_digits > data_max_digits) data_max_digits = curr_digits;

            // Determines if all blocks are filled
            if (set_array[input_index].blocks[associativity - 1] != -1)
            {
                set_array[input_index].is_full = true;
            }

            if (!set_array[input_index].is_full) // If the blocks are not all filled
            {
                for (int i = 0; i < associativity; i++) // Traverse through each block
                {
                    // Return if cache hit is detected
                    if (set_array[input_index].blocks[i] == n)
                    {
                        this->hits += 1;
                        cout << "(Hit: " << n << ")" << endl;
                        return;
                    }

                    // Find empty block in cache
                    if (set_array[input_index].blocks[i] == -1)
                    {
                        set_array[input_index].blocks[i] = n;
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < associativity; i++) // Traverse through each block
                {
                    // Return if cache hit is detected
                    if (set_array[input_index].blocks[i] == n)
                    {
                        this->hits += 1;
                        cout << "(Hit: " << n << ")" << endl;
                        return;
                    }
                }

                set_array[input_index].blocks[LRU] = n;
                set_array[input_index].LRU_index += 1;

                // Determines if the LRU_index is an invalid index
                if (set_array[input_index].LRU_index > associativity - 1)
                {
                    set_array[input_index].LRU_index = 0; // Back to first block
                }
            }
        }

        //** Outputs the data in each set and block
        void print()
        {
            for (int i = 0; i < set_amount; i++) // Traverse through each set
            {
                for (int j = 0; j < associativity; j++) // Traverse through each block
                {
                    if (set_array[i].blocks[j] != -1)
                    {
                        cout << "Data in set# " << i << " block " << j << ": " << "[ " << left << setw((int)data_max_digits) << set_array[i].blocks[j] << " ]" << endl;
                    }
                    else
                    {
                        cout << "Data in set# " << i << " block " << j << ": " << "[-empty-]" << endl;
                    }
                }
                cout << endl;
            }

            cout << "Cache Hits: " << this->hits << endl;
            cout << "Cache Misses: " << this->misses << endl;
        }
};

int main()
{
    unsigned short blocks_input, associativity_input;
    short data_input;
    char continue_input;
    bool input_error;

    cout << "**NOTE: Blocks are filled from start position zero and the replacement policy is LRU (Least Recently Used)**" << endl << endl;
    cout << "----------------Cache Simulator----------------" << endl;

    do
    {
        try
        {
            input_error = false;
            cout << "Number of blocks in cache: ";
            cin >> blocks_input;

            // Determines if input is negative or not a multiple of 2
            if (blocks_input < 0 || blocks_input % 2)
            {
                throw (blocks_input);
            }
        }
        catch (unsigned short input)
        {
            input_error = true;
            cout << "ERROR - Blocks amount must be positive and a multiple of 2" << endl;
        }
    } while (input_error);

    cout << endl;
    cout << "(For 4-way set associative input \"4\")" << endl;

    do
    {
        try
        {
            input_error = false;
            cout << "Reading operations set associativity: ";
            cin >> associativity_input;

            // Determines if input is negative or not a multiple of 2
            if (associativity_input < 0 || associativity_input % 2)
            {
                throw (associativity_input);
            }
        }
        catch (unsigned short input)
        {
            input_error = true;
            cout << "ERROR - Set associativity must be positive and a multiple of 2" << endl;
        }
    } while (input_error);

    // Creates the cache
    cout << endl;
    Cache _cache(blocks_input, associativity_input);
    cout << "Virtual cache created..." << endl;

    do
    {
        cout << "Data input: ";
        cin >> data_input;

        _cache.input_data(data_input);

        cout << "Continue (Y/N): ";
        cin >> continue_input;
    } while (continue_input == 'y' || continue_input == 'Y');

    // Prints the cache
    cout << endl;
    cout << "Printing cache..." << endl;
    _cache.print();

    return 0;
}
