#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

// fonction pour la conversation entre le serveur et le client
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// création de la boucle pour le chat 
	for (;;) { 
		bzero(buff, MAX); 

		// lecture du message du client et le copier dans le buffer 
		read(sockfd, buff, sizeof(buff)); 

		// fais voir la reponse du client
		printf("Du client: %s\t Au client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		// copier le message du serveur dans le buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// Envoyer ce buffer au client 
		write(sockfd, buff, sizeof(buff)); 

		// le serveur arrete la conversation en écrivant 'sortir'
		if (strncmp("sortir", buff, 4) == 0) { 
			printf("Conversation terminée...\n"); 
			break; 
		} 
	} 
} 

// création de la fonction principale 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// création du socket et la vérification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("erreur de création du socket...\n"); 
		exit(0); 
	} 
	else
		printf("création du socket a réussi avec succes..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// attribution des IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// liaison du socket crée à une IP et verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("la liaison du socket a échoué...\n"); 
		exit(0); 
	} 
	else
		printf("liaison du socket réussi avec succès..\n"); 

	// maintenant le serveur est pret à l'écoute et à la vérification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("erreur d'écoute...\n"); 
		exit(0); 
	} 
	else
		printf("Serveur est à l'écoute..\n"); 
	len = sizeof(cli); 

	// Accepte les données du client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("erreur d'acceptation du serveur...\n"); 
		exit(0); 
	} 
	else
		printf("serveur acccepte le client...\n"); 

	// fonction pour le chat entre client et serveur
	func(connfd); 

	// fermeture du socket après le chat 
	close(sockfd); 
} 

