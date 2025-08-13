//
// Created by Manoloon.
//
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

bool Compare(const char* s1, const char* s2, unsigned int l);

int main() 
{
	constexpr unsigned int L = ..., N = ...;
	std::unique_ptr<char[]> s(new char[L]);
	std::vector<const char*> vs(N);
	size_t count = 0;
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	std::sort(vs.begin(),vs.end(),[&](const char* a,const char* b)
	{
		++count;
		return Compare(a,b,L);
	});
	std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
	std::cout << "Sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count() << "ms (" << count << " comparisons)" << std::endl;
	return 0;
}