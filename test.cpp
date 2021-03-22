#include <DataInterface.hpp>

#include <iostream>
#include <unistd.h>

#define AMOUNT_OF_PASSES 2U
#define READ_SIGNALS 10U
using namespace std::chrono_literals;

vanilla::threads::DataInterface dataInterface{};

int main()
{
	try
	{

		std::vector<std::future<std::vector<uint8_t>>> vecFuture;
		//std::vector<std::vector<uint8_t>> dataVector;

		for (uint8_t j = 0; j < AMOUNT_OF_PASSES; j++)
		{
			vecFuture.erase(vecFuture.begin(), vecFuture.end());
			for (uint16_t i = 0; i < READ_SIGNALS; i++)
			{
				vecFuture.push_back(dataInterface.RequestDataById(i));
			}

			for (uint16_t i = 0; i < READ_SIGNALS; i++)
			{
				vecFuture[i].wait();
			}

			for (uint16_t i = 0; i < READ_SIGNALS; i++)
			{
				auto dataVector = vecFuture[i].get();
				for (auto ii = dataVector.begin(); ii != dataVector.end(); ++ii)
				{
					std::cout << *ii /* << ' ' */;
				}
				std::cout << "\n";
			}
		}

		std::cout << "add testu\n";
		std::vector<uint8_t> PutVector;
		PutVector.push_back('d');
		PutVector.push_back('u');
		PutVector.push_back('p');
		PutVector.push_back('a');
		std::future<uint16_t> putFuture;
		putFuture = dataInterface.EmplaceData(PutVector);
		putFuture.wait();
		uint16_t redeivedData{putFuture.get()};
		std::cout << "id :" << redeivedData << "\n";

		// auto data{dataInterface.RequestDataById(4)};
		// data.wait();
		// auto dataVector = data.get();
		// for (auto ii = dataVector.begin(); ii != dataVector.end(); ++ii)
		// {
		// 	std::cout << *ii /* << ' ' */;
		// }

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