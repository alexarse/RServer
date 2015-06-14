
#include "axServer.h"
#include "axServerCore.h"
#include "axUtils.h"
#include "CudaKMean.h"

struct KMeanInfo
{
	int nrow, ncol, nCluster;
};

namespace R
{
	class Server : public ax::Server::Core
	{
	public:
		Server(const std::string& port):
		ax::Server::Core(port)
		{

		}

	protected:
		virtual std::string ConnectionCallback(ax::Server::Core* server, const int& sock_fd)
		{
			// int nElement = 0; // Number of elements in the double* array.
			KMeanInfo kmean_info;

			// Receive a int msg for the amount of element in a double* vector.
			if(ax::Server::Receive<KMeanInfo>(sock_fd, kmean_info) <= 0)
			{
				ax::Error("Error in receive.");
			}

			int nElement = kmean_info.nrow * kmean_info.ncol; // Number of elements in the double* array.

			const int totalByteToReceive = sizeof(double) * nElement;

			unsigned char* raw_bytes = new unsigned char[totalByteToReceive];

			int total_bytes_receive = 0;

			do
			{
				int bytes_left = totalByteToReceive - total_bytes_receive;
				
				unsigned char* raw_buffer = raw_bytes + total_bytes_receive;
				int bytes = ax::Server::Receive<unsigned char>(sock_fd, raw_buffer, bytes_left);
				
				total_bytes_receive += bytes;

			} while(total_bytes_receive < totalByteToReceive);

			double* data = (double*)raw_bytes;






			double* answer = new double[kmean_info.ncol * kmean_info.nCluster];

			/////////////
			int dim = 2;
			CudaKMean(data, &dim, &kmean_info.nrow, &kmean_info.ncol, &kmean_info.nCluster, answer);


			ax::Server::Send<double>(sock_fd, answer, sizeof(double) * kmean_info.ncol * kmean_info.nCluster);

			// double average = 0.0;
			// for(int i = 0; i < nElement; i++)
			// {
			// 	average += values[i];
			// }

			// ax::Server::Send<double>(sock_fd, average / double(nElement));

			// delete[] raw_bytes; 

			return "Nothing";
		}
	};
}

int main()
{
	ax::Print("main");
	R::Server server("9000");
	server.MainLoop();

	return 0;
}