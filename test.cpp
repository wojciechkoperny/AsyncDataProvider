#include <DataInterface.hpp>

#include <iostream>

using namespace std::chrono_literals;

int main()
{
	try
	{
		vanilla::threads::DataInterface dataInterface{};

		auto data = dataInterface.RequestDataById(124);

		if (data.wait_for(2s) == std::future_status::ready)
		{
			std::cout << "Received data for id:123\n";
			auto dataVector = data.get();
		}
		else
		{
			std::cerr << "Error gettig data for id:123\n";
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}