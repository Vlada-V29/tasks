#include <iostream>

#include <boost/asio.hpp>

bool flag_exit = false;

// std::string read_data(boost::asio::ip::tcp::socket & socket) 
// {
// 	const std::size_t length = 10;
// 	char buffer[length];
// 	boost::asio::read(socket, boost::asio::buffer(buffer, length));
// 	return std::string(buffer, length);
// }

std::string read_name(boost::asio::ip::tcp::socket & socket) 
{
	boost::asio::streambuf buffer;

	boost::asio::read_until(socket, buffer, ':');

	std::string message;

	// Because buffer 'buf' may contain some other data
	// after '\n' symbol, we have to parse the buffer and
	// extract only symbols before the delimiter.
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, ':');

	return message;
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

void enter_message(boost::asio::ip::tcp::socket & socket)
{
	while (true)
	{
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
	}
	
}

int main(int argc, char ** argv)
{
	system("chcp 1251");
	
	const std::size_t size = 30;

	auto port = 3333;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;

	try 
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

		acceptor.bind(endpoint);

		acceptor.listen(size);

		boost::asio::ip::tcp::socket socket_enter(io_service);
		boost::asio::ip::tcp::socket socket_read(io_service);

		acceptor.accept(socket_read);
		std::string user_name = read_name(socket_read);
		std::cout << user_name << "\t";//<< std::endl;

		// acceptor.accept(socket_read);
		// std::cout << read_message(socket_read) << std::endl;

		while (flag_exit)
		{
			acceptor.accept(socket_read);
			std::cout << user_name << "\t" << read_message(socket_read) << std::endl;

			if (!flag_exit)
			{
				acceptor.accept(socket_enter);
				enter_message(socket_enter);
			}

		}
		



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