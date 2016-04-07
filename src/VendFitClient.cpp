#include "../inc/VendFitClient.h"

VendFitClient::VendFitClient(std::string host, int port){
	this->host = host;
	this->port = port;
	this->stayConnected();
}

bool VendFitClient::conn()
{
    //create socket if it is not already created
    if(this->socketFD == -1)
    {
        //Create socket
        this->socketFD = socket(AF_INET , SOCK_STREAM , 0);
        if (this->socketFD == -1)
        {
            perror("Could not create socket");
            return false;
        }
         
        std::cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }
     
    //setup address structure
    if(inet_addr(this->host.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( this->host.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            perror("gethostbyname");
            std::cout<<"Failed to resolve hostname\n";
             
            return false;
        }
         
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
             
            std::cout<<this->host<<" resolved to "<<inet_ntoa(*addr_list[i])<<std::endl;
             
            break;
        }
    }
     
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( this->host.c_str() );
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    //Connect to remote server
    if (connect(this->socketFD , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return false;
    }
     
    std::cout<<"Connected\n";
    return true;
}

void VendFitClient::stayConnected(){
	int retval = 0;
	int error = 0;
	socklen_t len = sizeof(error);
	do{
		std::cout << "Testing connection..." << std::endl;
		retval = getsockopt(this->socketFD, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
		if(retval != 0 || error != 0)
		{
			std::cout << "Not Connected. Trying now..." << std::endl;
			close(this->socketFD);
			this->socketFD = -1;
        	this->conn();
		}
	}while(retval != 0 || error != 0);
}

void VendFitClient::sendData(std::string data)
{
	//add the <END> tag
	data = data + this->END;
	//Send some data
    if( send(this->socketFD , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        close(this->socketFD);
        this->socketFD = -1;
        this->conn();
    }
    std::cout << "Data send" << std::endl;
}

int VendFitClient::parseResponse(char opcode[], int opcodeLength){
    //Receive a reply from the server
    for(int i = 0; i < opcodeLength; i++)
    {
    	opcode[i] = 0;
    }
    std::cout << "Getting response" << std::endl;
    int r = 0;
    if((r = read(this->socketFD , opcode , sizeof(opcode))) <= 0)
    {
    	std::cout << r << std::endl;
    	// if(r < 0)
    	// {
        	close(this->socketFD);
        	this->socketFD = -1;
        	this->conn();
        	return -1;
        // }
        // return 0;
    }
    std::cout << r << std::endl;
    return 1;
}