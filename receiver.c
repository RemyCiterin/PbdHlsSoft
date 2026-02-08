#include <stdio.h>
#include <strings.h>
#include <sys/types.h>

int receive_img(char* image, unsigned int size) // assumes square image of size*size pixels
{
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
		int n = recvfrom(listenfd, image, size, 0, (struct sockaddr*)&cliaddr, &len);
		
		printf("\n");
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				printf("%d,", image[i*size+j]);
			}
			printf("\n");
		}
	}
	return 0;
}
