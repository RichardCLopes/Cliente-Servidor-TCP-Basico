#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cliente TCP
 */
int main(argc, argv)
int argc;
char **argv;
{
    unsigned short port;                    
    struct hostent *hostnm;    
    struct sockaddr_in server; 
	char usuario[19], mensagem[79], op[2], resp[20];
    int s, opcao, cont;                     

    /*
     * O primeiro argumento (argv[1]) é o hostname do servidor.
     * O segundo argumento (argv[2]) é a porta do servidor.
     */
    if (argc != 3)
    {
        fprintf(stderr, "Use: %s hostname porta\n", argv[0]);
        exit(1);
    }

    // Obtendo o endereço IP do servidor

    hostnm = gethostbyname(argv[1]);
    if (hostnm == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname failed\n");
        exit(2);
    }
    port = (unsigned short) atoi(argv[2]);

    // Define o endereço IP e a porta do servidor

    server.sin_family      = AF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);

    /*
     * Cria um socket TCP (stream)
     */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(3);
    }

    /* Estabelece conexão com o servidor */
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connect()");
        exit(4);
    }
    
    do{
    do{
    printf("Opcoes:\n1 - Cadastrar Mensagem\n");
    printf("2 - Ler Mensagem\n");
    printf("3 - Apagar Mensagem\n");
    printf("4 - Sair da Aplicacao\n");  
    scanf("%s", op);
    opcao=atoi(op);
        }while(opcao<1 || opcao>4);
        
    switch (opcao)
    {
    case 1:
    printf("\nUsuario: ");
    setbuf(stdin,NULL);
    fgets(usuario,19,stdin);
    printf("Mensagem: ");
    setbuf(stdin,NULL);
    fgets(mensagem,79,stdin);
    
    if (send(s, op, strlen(op)+1, 0) < 0)

    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Opcao %s enviada ao servidor", op); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, resp, sizeof(resp), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    //printf("%s\n", resp);
    
    if (send(s, usuario, strlen(usuario)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Usuario %s enviado ao servidor", usuario); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, resp, sizeof(resp), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    //printf("%s\n", resp);
    
    if (send(s, mensagem, strlen(mensagem)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Mensagem %s enviado ao servidor", mensagem); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, resp, sizeof(resp), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("\n%s\n\n", resp);
    
    break;
    
    case 2:
    if (send(s, op, strlen(op)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Opcao %s enviada ao servidor", op); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, resp, sizeof(resp), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("\nMensagens cadastradas %s\n\n", resp);
    cont=atoi(resp);
    for(int i=0;i<cont;i++){
    strcpy(resp,"pega user");
    if (send(s, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Opcao %s enviada ao servidor", op); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, usuario, sizeof(usuario), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("Usuario: %s", usuario);
    strcpy(resp,"pega menssagem");
    if (send(s, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Opcao %s enviada ao servidor", op); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, mensagem, sizeof(mensagem), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("Mensagem: %s\n", mensagem);
    }
    break;
    
    case 3: 
    if (send(s, op, strlen(op)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
    //printf("Opcao %s enviada ao servidor", op); 
    
    /* Recebe a mensagem do servidor no buffer de recepção */

    if (recv(s, resp, sizeof(resp), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    //printf("\n%s\n", resp);
    
    printf("\nUsuario: ");
    setbuf(stdin,NULL);
    fgets(usuario,19,stdin);
    
    if (send(s, usuario, strlen(usuario)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    //printf("Opcao %s enviada ao servidor", op); 
    
    if (recv(s, resp, sizeof(resp), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("\nMensagens apagadas: %s\n\n", resp);
    
    cont=atoi(resp);
    
    for(int i=0;i<cont;i++){
    
    if (send(s, usuario, strlen(usuario)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    //printf("Opcao %s enviada ao servidor", op); 
    
    if (recv(s, mensagem, sizeof(mensagem), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("Usuario: %s", usuario);
    printf("Mensagem: %s\n", mensagem);
    
    }
    
    break;
    case 4:
    /* Fecha o socket */
    close(s);

    printf("Cliente terminou com sucesso.\n");
    exit(0);
    break;
    }
    }while(1);

}


