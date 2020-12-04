﻿#include "FloppyDisk.h"

void FloppyDisk::comand()
{
	std::string name_file;
	int size_file;
	
	std::cin >> name_file >> size_file;

	char com = 0;
	std::cin >> com;
	switch (com)
	{
	case '1':
		try
		{
			this->write_file(name_file, size_file);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}
		break;
	case '0':
		try
		{
			this->delete_file(name_file, size_file);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}
		break;
	default:

		std::cout << "\nErorr!";
		std::cout << "No comand: ";
		break;
	}
	
}

void FloppyDisk::print_list()
{
	std::for_each(begin(busy), end(busy), [](auto& el) {

		std::cout << el.name_file << " " << el.size_file << "  Bit" << std::endl;

		});



}

void FloppyDisk::write_file(std::string name_file, int size_file)
{
	/*auto sum_size = std::accumulate(busy.begin(), busy.end(), 1, [](auto a, auto b) { return a.size_file + b.size_file});
	if (sum_size > MAXdiskSpace*1024)*/

	bool flag = true;
	std::for_each(begin(free), end(free), [&flag, size_file](auto& el) {
		if (size_file < el)
		{
			el -= size_file;
			flag = false;
		}
		});

	if (flag)
		throw std::exception("Error!\n No disk space.\n");///////////////////////////////////////////////////////////////
	else
	{
		try
		{
			busy.push_back(File(name_file, size_file));
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();

		}
	}

}

void FloppyDisk::delete_file(std::string name_file, int size_file)
{
	auto it = std::find_if(begin(busy), end(busy), [name_file, size_file](auto el)
		{
			return (el.name_file == name_file) && (el.size_file == size_file);
		});

	if (it == busy.end())
		throw std::exception("Error!\n No disk file.\n");///////////////////////////////////////////////////////////////
	else
	{
		free.push_front(it->size_file);
		busy.erase(it);
	}

}
