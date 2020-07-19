# Client_serveur

le code de client lui permet d'envoyer des requetes au seveur et ce dernier peut le recevoir pour en savoir plus on va voir le code de pret et quelque explication necessaire

# client 

ce fonction permet d etablir la conversation entre le serveur et le client
	void func(int sockfd) 
	{ 
		char buff[MAX]; 
		int n; 

ici on creer un bouche necesaire pour le chat
	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("Veuillez svp écrire votre message : "); 
		n = 0;  
		while ((buff[n++] = getchar()) != '\n');  
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 

ce bloc de code permet la lecture et le copie du message du serveur dans le buffer
		read(sockfd, buff, sizeof(buff)); 
		printf("Du Serveur : %s", buff); 
		if ((strncmp(buff, "sortir", 4)) == 0) { 
			printf("Conversation terminée...\n");
			break; 

ici on fait appel a la fonction principale
	int main() 
	{ 
		int sockfd, connfd; 
		struct sockaddr_in servaddr, cli; 

ce code permet de faire la creation du socket et sa verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("erreur de la création du socket...\n"); 
		exit(0); 
	} 
	else
		printf("Socket crée avec succès..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

permet de donner les attribution des IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

ici on fait la connection du socket du client au socket du serveur 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("erreur de connexion avec le serveur...\n"); 
		exit(0); 
	} 
	else
		printf("connection au socket..\n"); 

ce fonction permet le chat 
	func(sockfd); 

et enfin celuici ce pour la fermeture du socket 
	close(sockfd); 
}      
      
# serveur

ce fonction aussi permet la conversation entre le serveur et le client
	void func(int sockfd) 
	{ 
		char buff[MAX]; 
		int n; 

ici on fait aussi une création de boucle pour le chat 
	for (;;) { 
		bzero(buff, MAX); 

cette ligne permet de faire la lecture du message du client et le copier dans le buffer 
		read(sockfd, buff, sizeof(buff)); 

ce bloc de code permet d'afficher la reponse du client
		printf("Du client: %s\t Au client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 

cette ligne permet de copier le message du serveur dans le buffer 
		while ((buff[n++] = getchar()) != '\n') ;
		
cette ligne de code permet d'ennvoyer le buffer au client 
		write(sockfd, buff, sizeof(buff)); 

pour sortir le serveur de la conversation il faut ecrire 'sortir'
		if (strncmp("sortir", buff, 4) == 0) { 
			printf("Conversation terminée...\n"); 
			break; 

création de la fonction principale 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

ici aussi il y aura une création du socket et la vérification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("erreur de création du socket...\n"); 
		exit(0); 
	} 
	else
		printf("création du socket a réussi avec succes..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

ici aussi il y aura la creation de attribution des IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

ce code permet une liaison du socket crée à une IP et verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("la liaison du socket a échoué...\n"); 
		exit(0); 
	} 
	else
		printf("liaison du socket réussi avec succès..\n"); 

celui ci permet la verification et l'ecoute du serveur 
	if ((listen(sockfd, 5)) != 0) { 
		printf("erreur d'écoute...\n"); 
		exit(0); 
	} 
	else
		printf("Serveur est à l'écoute..\n"); 
	len = sizeof(cli); 

cette etape permet l'acception et la verification des donnees du client 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("erreur d'acceptation du serveur...\n"); 
		exit(0); 
	} 
	else
		printf("serveur acccepte le client...\n"); 

cette fonction permet le chat entre client et serveur
	func(connfd); 

et pour finir le la ligne qui permet la fermeture du socket après le chat 
	close(sockfd); 
