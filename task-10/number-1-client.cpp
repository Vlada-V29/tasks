#include <iostream>

#include <boost/asio.hpp>

void write_name(boost::asio::ip::tcp::socket & socket)
{
	std::cout << "Enter your name: ";
	std::string name;
	std::cin >> name;

	boost::asio::write(socket, boost::asio::buffer(name  + ": "));
}

void write_message(boost::asio::ip::tcp::socket & socket)
{
	std::cout << "Enter your message: ";
	std::string message;
	std::cin >> message;

	boost::asio::write(socket, boost::asio::buffer(message + "."));
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

	std::string raw_ip_address = "127.0.0.1";
	//std::string name;

	auto port = 3333;

	try 
	{
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::address::from_string(raw_ip_address), port);

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
		boost::asio::ip::tcp::socket socket_name(io_service, endpoint.protocol());

		socket_name.connect(endpoint);
		write_name(socket_name);
		
		socket.connect(endpoint);
		write_message(socket);
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
