#include "receiver.h"
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>

int receive_img(float* image, unsigned int size) // assumes square image of size*size pixels
{
	char received[size*size];
	int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	while(1)
	{
		len = sizeof(cliaddr);
		int n = recvfrom(listenfd, received, size, 0, (struct sockaddr*)&cliaddr, &len);	//buffer au format 8 bits
		
		printf("\n");
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				image[i*size+j] = (float)received[i*size+j];	//cast en float
				//printf("%d,", received[i*size+j]);
			}
			//printf("\n");
		}
	}
	return 0;
}
