all:bankingServer bankingClient

bankingServer:bankingServer.c 
	gcc -lm -pthread -o bankingServer bankingServer.c

bankingClient:bankingClient.c 
	gcc -lm -pthread -o bankingClient  bankingClient.c 
  
clean:
	rm -rf bankingClient 
	rm -rf bankingServer
