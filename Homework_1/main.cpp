// Задание 1
// Очередь клиентов

#include <iostream>
#include <Windows.h>
#include <thread>
#include <execution>

// Clients global
int clients = 0;
int served_clients = 0;
bool exitFlag = false;

void add_client();

void serve_client();

void print_quenue();

void clear_screen();

void manage_screen();

// max amount of clients

#define MAX_CLIENTS 10

// time

using namespace std::chrono_literals;

int main(int argc, char ** argv)
{
	clear_screen();

	std::thread t1 (add_client);
	std::thread t2 (serve_client);
	std::thread t3 (manage_screen);

	// Finish

	if (t1.joinable())
		t1.join();

	if (t2.joinable())
		t2.join();

	if (t3.joinable())
		t3.join();
	
	// EXIT
	std::cout << std::endl;
	system("pause");
	return EXIT_SUCCESS;
} // !main

void add_client()
{
	while (clients != MAX_CLIENTS)
	{
		++clients;

		std::this_thread::sleep_for(1000ms);
	}
} // !add

void serve_client()
{
	do
	{
		clients--;
		++served_clients;

		std::this_thread::sleep_for(2000ms);

	} while (clients != 0);

	exitFlag = true;
	
} // !serve

void print_quenue()
{
	clear_screen();
	std::cout << " ------------- Q -------------\n\n";
	std::cout << "  > Currently in Q: " << clients;
	std::cout << "\n  > Served clients: " << served_clients;
}

void clear_screen()
{
#ifdef _WIN32
	std::system("cls");
#else
	// Assume POSIX
	std::system("clear");
#endif

} // END OF clear_screen()

void manage_screen()
{
	while (!exitFlag)
	{
		print_quenue();
		std::this_thread::sleep_for(100ms);
	}

	std::cout << "\n  > All clients served successfuly!\n";
}