// ===============================================================
// cachesim.cpp
// ===============================================================
// Name: Jennifer King
// Date: 2/8/2019
// Class: CSCI 241 TR 4:30PM
// Professor: Andrew Clifton
// Description:
//      This program simulates how three levels of cache within one
//      CPU register would run.
// ===============================================================

#include <iostream>
#include <cstdlib>
#include <array>
using namespace std;

struct Cache
{
    int lines;
    int numBytes;
    int numCycles;
    int hits = 0;
    int array[][2];
};

// func prototypes
void InitMatrix(Cache &cache);
bool StoreAddress(Cache &cache, int address);
bool TraverseCache(Cache &cache, int address);


int     main()
{
    int address;

    // Level 1 Cache
    Cache L1;
    L1.lines = 4;
    L1.numBytes = 256;
    L1.numCycles = 1;
    InitMatrix(L1);

    // Level 2 Cache
    Cache L2;
    L2.lines = 64;
    L2.numBytes = 1000;
    L2.numCycles = 10;
    InitMatrix(L2);

    // Level 3 Cache
    Cache L3;
    L3.lines = 256;
    L3.numBytes = 4000;
    L3.numCycles = 100;
    InitMatrix(L3);

    // recieve addresses
    for(int x = 0; x < 11; x++)
    {
        cout << "load ";
        cin >> hex >> address;
        StoreAddress(L1, address);
    }

    return 0;
}

// == InitMatrix =================================================
// This function initializes all members of the cache's array
// member to 0.
// ===============================================================
void InitMatrix(Cache &cache)
{
    for(int x = 0; x < cache.lines; x++)
    {
        for(int y = 0; y < 2; y++)
        {
            cache.array[x][y] = 0;
        }
    }
}

// == StoreAddress ===============================================
// This function stores the addresses in the cache if the cache
// has room.
// It returns a true value if the address was successfully
// inserted, and a false value if not.
// ===============================================================
bool StoreAddress(Cache &cache, int address)
{
    int x = 0;
    int y = 0;

    if(cache.array[0][0] == 0) // if the cache is completely empty
    {
        cache.array[0][0] = address;
        cache.array[0][1] = address + cache.numBytes;
        return true;
    }
    else if(TraverseCache(cache, address) == false) // if addr not in cache
    {
        for(; x < cache.lines; x++)
        {
            for(; y < 2; y++)
            {
                if(cache.array[x][y] == 0)
                {
                    break;
                }
            }
        }
        if(cache.array[x][y] != 0)
        {
            return false; // there is no space in the cache to add
        }
        else
        {
            cache.array[x][0] = address;
            cache.array[x][1] = address + cache.numBytes;
            return true;
        }
    }

    return false;

}

// == TraverseCache ==============================================
// This function traverses the cache to determine if the given
// address can be found in the cache.
// If the address is found, it adds a hit and returns a value
// of true.
// ===============================================================
bool TraverseCache(Cache &cache, int address)
{
    for(int x = 0; x < cache.lines; x++)
    {
        if(address >= cache.array[x][0] && address <= cache.array[x][1])
        {
            cache.hits ++;
            return true;
        }
    }

    return false;
}
