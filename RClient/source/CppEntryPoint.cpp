#include <iostream>
#include <vector>
#include "axUtils.h"
#include "RClient.h"

extern "C"
{
	void SendVector(double* data, int* size, double* average)
	{
		R::Client client("localhost", "9000");

		int sockfd = client.GetSocketFd();

		int bytes = ax::Server::Send<int>(sockfd, *size);

		bytes = ax::Server::Send<double>(sockfd, data, sizeof(double) * *size);

		ax::Print("Byte sent :", bytes);

		bytes = ax::Server::Receive<double>(sockfd, *average);
	}
}
