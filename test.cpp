#include <DataInterface.hpp>

#include <iostream>
#include <unistd.h>
using namespace std::chrono_literals;

int main()
{
	try
	{
		vanilla::threads::DataInterface dataInterface{};

		auto data = dataInterface.RequestDataById(2);

		if (data.wait_for(2s) == std::future_status::ready)
		{
			//std::cout << "Received data for id:123\n";
			auto dataVector = data.get();

			std::cout << "vector: ";
			for (auto i = dataVector.begin(); i != dataVector.end(); ++i)
			{
    			std::cout << *i << ' ';
			}
			std::cout<<"\n";
		}
		else
		{
			std::cerr << "Error gettig data for id:123\n";
		}

/* 		sleep(5); 
		std::cout << "koniec czekania\n"; */
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}