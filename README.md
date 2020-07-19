# Client_serveur

# client 
 // fonction pour la conversation entre le serveur et le client
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// création de la boucle pour le chat 
	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("Veuillez svp écrire votre message : "); 
		n = 0;  
		while ((buff[n++] = getchar()) != '\n') 
			; 
		  
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 

		// lecture du message du serveur et le copier dans le buffer
		read(sockfd, buff, sizeof(buff)); 
		printf("Du Serveur : %s", buff); 
		if ((strncmp(buff, "sortir", 4)) == 0) { 
			printf("Conversation terminée...\n");
			break; 
		} 
	} 
} 

//fonction principale
int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	//creation du socket et varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("erreur de la création du socket...\n"); 
		exit(0); 
	} 
	else
		printf("Socket crée avec succès..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// attribution des IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connection du socket du client au socket du serveur 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("erreur de connexion avec le serveur...\n"); 
		exit(0); 
	} 
	else
		printf("connection au socket..\n"); 

	// fonction pour le chat 
	func(sockfd); 

	// Fermeture du socket 
	close(sockfd); 
}      
      
# serveur

