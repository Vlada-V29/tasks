#include <iostream>
#include <thread>

#include <boost/asio.hpp>

bool flag_exit = false;


void write_name(boost::asio::ip::tcp::socket & socket)
{
	std::cout << "Enter your name: ";
	std::string name;
	std::cin >> name;

	boost::asio::write(socket, boost::asio::buffer(name  + ": "));
}


void enter_message(boost::asio::ip::tcp::socket & socket)
{
	//while (true)
	//{
		//std::cout << "Enter your message: ";
		std::string message;
		std::cin >> message;
		if(message == "\\exit")
		{
			flag_exit = true;
			//break;
		}

		boost::asio::write(socket, boost::asio::buffer(message));
		// m_mutex.lock();
		// m_mutex.unlock();
	//}
	
}

std::string read_message(boost::asio::ip::tcp::socket & socket) 
{
	boost::asio::streambuf buffer;
	boost::asio::read(socket, buffer);
	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message);

	if(message == "\\exit")
		{
			flag_exit = true;
		}

	return message;
}


void enter_m(boost::asio::ip::tcp::endpoint endpoint, 
		boost::asio::ip::tcp::socket socket_enter)
{
	while (!flag_exit)
		{
			socket_enter.connect(endpoint);
			enter_message(socket_enter);

		}
}


void read_m(boost::asio::ip::tcp::endpoint endpoint, 
		boost::asio::ip::tcp::socket socket_read)
{
	while (!flag_exit)
		{
			socket_read.connect(endpoint);
			std::cout << "server: " << read_message(socket_read) << std::endl;

		}
}




int main(int argc, char ** argv)
{
	system("chcp 1251");

	std::string raw_ip_address = "127.0.0.1";
	auto port = 3333;

	try 
	{
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::address::from_string(raw_ip_address), port);

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket_enter(io_service, endpoint.protocol());
		boost::asio::ip::tcp::socket socket_read(io_service, endpoint.protocol());

		socket_enter.connect(endpoint);
		write_name(socket_enter);
		

		while (flag_exit)
		{
			socket_enter.connect(endpoint);
			enter_message(socket_enter);
			
			if (!flag_exit)
			{
				socket_read.connect(endpoint);
				std::cout << read_message(socket_read) << std::endl;
				
			}

		}

		std::thread th_enter;
		std::thread th_print;

		th_enter = std::thread(enter_m, endpoint, socket_enter); 
		th_print = std::thread(read_m, endpoint, socket_read); 
		



	}
	catch (boost::system::system_error & e) 
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}
