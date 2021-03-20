#include <DataInterface.hpp>

#include <iostream>
#include <unistd.h>
using namespace std::chrono_literals;

int main()
{
	try
	{
		vanilla::threads::DataInterface dataInterface{};

		std::vector<std::future<std::vector<uint8_t>>> vecFuture;
		//std::vector<std::vector<uint8_t>> dataVector;
		for (uint8_t j = 0; j < 2; j++)
		{
			vecFuture.erase(vecFuture.begin(), vecFuture.end());
			for (uint16_t i = 0; i < 10; i++)
			{
				vecFuture.push_back(dataInterface.RequestDataById(i));
			}

			for (uint16_t i = 0; i < 10; i++)
			{
				vecFuture[i].wait();
			}

			for (uint16_t i = 0; i < 10; i++)
			{
				auto dataVector = vecFuture[i].get();
				for (auto ii = dataVector.begin(); ii != dataVector.end(); ++ii)
				{
					std::cout << *ii /* << ' ' */;
				}
				std::cout << "\n";
			}
		}

		std::vector<uint8_t> PutVector;
		PutVector.push_back('d');
		PutVector.push_back('u');
		PutVector.push_back('p');
		PutVector.push_back('a');
		std::future<uint16_t> putFuture;
		putFuture = dataInterface.EmplaceData(PutVector);
		putFuture.wait();

		std::cout << "koniec testu\n";

		// if (data.wait_for(2s) == std::future_status::ready)
		// {
		// 	//std::cout << "Received data for id:123\n";
		// 	auto dataVector = data.get();

		// 	std::cout << "vector: ";
		// 	for (auto i = dataVector.begin(); i != dataVector.end(); ++i)
		// 	{
		// 		std::cout << *i << ' ';
		// 	}
		// 	std::cout<<"\n";
		// }
		// else
		// {
		// 	std::cerr << "Error gettig data for id:123\n";
		// }

		// data = dataInterface.RequestDataById(5);
		// if (data.wait_for(2s) == std::future_status::ready)
		// {
		// 	auto dataVector = data.get();

		// 	std::cout << "vector: ";
		// 	for (auto i = dataVector.begin(); i != dataVector.end(); ++i)
		// 	{
		// 		std::cout << *i << ' ';
		// 	}
		// 	std::cout<<"\n";
		// }

		// data = dataInterface.RequestDataById(9);
		// if (data.wait_for(2s) == std::future_status::ready)
		// {
		// 	auto dataVector = data.get();

		// 	std::cout << "vector: ";
		// 	for (auto i = dataVector.begin(); i != dataVector.end(); ++i)
		// 	{
		// 		std::cout << *i << ' ';
		// 	}
		// 	std::cout<<"\n";
		// }

		// data = dataInterface.RequestDataById(15);
		// if (data.wait_for(2s) == std::future_status::ready)
		// {
		// 	auto dataVector = data.get();

		// 	std::cout << "vector: ";
		// 	for (auto i = dataVector.begin(); i != dataVector.end(); ++i)
		// 	{
		// 		std::cout << *i << ' ';
		// 	}
		// 	std::cout<<"\n";
		// }

		// data = dataInterface.RequestDataById(5);
		// if (data.wait_for(2s) == std::future_status::ready)
		// {
		// 	auto dataVector = data.get();

		// 	std::cout << "vector: ";
		// 	for (auto i = dataVector.begin(); i != dataVector.end(); ++i)
		// 	{
		// 		std::cout << *i << ' ';
		// 	}
		// 	std::cout<<"\n";
		// }

		/* 		sleep(5); 
		std::cout << "koniec czekania\n"; */
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << "\n\n\n\n";
}