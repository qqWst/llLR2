#pragma once
#include "../structs/array.h"
#include <iostream>

void sortInsert(Array<char>& arr);
void countAndDeleteRepeats(Array<char>& arr, Array<int>& counts);
void printHistogram(const Array<char>& chars, const Array<int>& counts);