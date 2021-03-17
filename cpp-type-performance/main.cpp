#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <string>

int test_multiplier;
int average_accuracy;
char separator;
int sample_output_count;
int sample_count;



double GetAverage(std::vector<double> v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}



class Timer
{
public:
	Timer(std::vector<double>& average_input, int average_input_index, bool log=false)
	{
		m_average_input = &average_input;
		m_average_input_index = average_input_index; // I had to use this with arrays but somehow my whole program breaks when removing it so it's stuck here.
		m_log = log;
		m_startTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer() { Stop(); }
	double Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		
		auto duration = end - start;
		double ms = duration * 0.001;

		m_average_input->push_back(ms);

		if (m_log)
		{
			std::cout << ms << "ms";
			return 0;
		}
		else
		{
			return ms;
		}
	}
private:
	std::vector<double>* m_average_input;
	int m_average_input_index;
	bool m_log;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
};



template <typename TestType> void test_program();
template <typename T> void __test__(std::vector<double> &average_input)
{
	Timer time(average_input, 0);
	for (int big_i = 0; big_i < test_multiplier; big_i++)
	{
		test_program<T>();
	}
}

template <typename T>
void benchmark(std::string name=typeid(T).name())
{
	// Prints the type and the size of the type
	std::string size = std::to_string(sizeof(T)) + ' ';
	if (sizeof(T) == 1) size.append("byte");
	else size.append("bytes");
	std::cout << name << " (sizeof " << size << ") took: (in milliseconds)" << std::endl;
	
	// Making the numbers and making them even more accurate
	std::vector<double> averager;
	for (int a = 0; a < sample_output_count; a++)
	{
		for (int index = 0; index < sample_count; index++)
		{
			std::vector<double> average_input;
			for (int i = 0; i < average_accuracy; i++)
			{ // Runs the test round X amount of times
				__test__<T>(average_input);
			}
			double average = GetAverage(average_input);
			averager.push_back(average);
		}
		std::cout << GetAverage(averager) << separator;
	}
	std::cout << std::endl << std::endl;
}


// Any program in this function will be tested for performance
template <typename TestType>
void test_program()
{
	TestType value = 0;
	for (TestType i = 0; i < 127; i++)
		value += 1;
}



int main()
{
	// Used to get more accurate numbers by making the test last longer
	// Runs the test 1024 times by default
	test_multiplier = 512;

	// Gets more accurate numbers by running the code multiple times
	// and getting an average number from all the numbers (1024 by default)
	average_accuracy = 1048;

	// The amount of times to run the code and average it out
	// This does takes a HUGE hit on peformance and speed so be careful. 
	// (5 by default)
	sample_output_count = 10;

	// The accuracy of numbers (the bigger this is the bigger the input
	// of numbers to average a number out is)
	// 100 by default
	sample_count = 100;

	// The character that separates each number (, by default)
	separator = ',';

	benchmark<int>();
	benchmark<unsigned int>();
	benchmark<float>();
	benchmark<double>();
	benchmark<char>();
	benchmark<unsigned char>();
	benchmark<uint8_t>("uint8_t");
	benchmark<uint16_t>("uint16_t");
	benchmark<uint32_t>("uint32_t");
	benchmark<uint64_t>("uint64_t");
	std::cin.get();
}