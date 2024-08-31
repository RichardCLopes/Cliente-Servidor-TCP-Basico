#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define TAM 10

 //Servidor TCP
 
int main(argc, argv)
int argc;
char **argv;
{
    unsigned short port;                
    struct sockaddr_in client; 
    struct sockaddr_in server; 
    struct registro{
    char user[19], mens[79];
    int ocupado;
    };
    struct registro banco[TAM];
    int cont = 0;
    char op[2], usuario[19], mensagem[79], resp[20];
    int s, opcao, cad;                     /* Socket para aceitar conexões       */
    int ns;                    /* Socket conectado ao cliente        */
    int namelen;               

    /* O primeiro argumento (argv[1]) é a porta
     * onde o servidor aguardará por conexões */
    if (argc != 2)
    {
        fprintf(stderr, "Use: %s porta\n", argv[0]);
        exit(1);
    }

    port = (unsigned short) atoi(argv[1]);

    // Cria um socket TCP (stream) para aguardar conexões
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(2);
    }

   /* Define a qual endereço IP e porta o servidor estará ligado.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os endereços IP */
    server.sin_family = AF_INET;   
    server.sin_port   = htons(port);       
    server.sin_addr.s_addr = INADDR_ANY;

    /*
     * Liga o servidor à porta definida anteriormente.
     */
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
       perror("Bind()");
       exit(3);
    }

    /* Prepara o socket para aguardar por conexões e
     * cria uma fila de conexões pendentes. */
    if (listen(s, 1) != 0)
    {
        perror("Listen()");
        exit(4);
    }

    /*
     * Aceita uma conexão e cria um novo socket através do qual
     * ocorrerá a comunicação com o cliente.
     */
    namelen = sizeof(client);
    if ((ns = accept(s, (struct sockaddr *)&client, &namelen)) == -1)
    {
        perror("Accept()");
        exit(5);
    }
    
    for(int i=0;i<TAM;i++)
    {
    banco[i].ocupado=0;
    }
    
    
    do{
    /* Recebe uma operaçao do cliente através do novo socket conectado */
    if (recv(ns, op, sizeof(op), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
    printf("Recebido a opcao %s do endereco IP %s da porta %d\n", op, inet_ntoa(client.sin_addr), client.sin_port);
    
    opcao=atoi(op);
    switch (opcao)
    {
    case 1:
    strcpy(resp, "resposta");
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
	printf("Mandando confirmacao de recebimento da opcao ao cliente\n");
    
    if (recv(ns, usuario, sizeof(usuario), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
	printf("Recebi o nome -> cliente\n");
    
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    
     if (recv(ns, mensagem, sizeof(mensagem), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }

    printf("Recebi a mensagem -> cliente\n");

    for(int i=0;i<TAM;i++){
    if(banco[i].ocupado==0){
    strcpy(banco[i].user, usuario);
    strcpy(banco[i].mens, mensagem);
    banco[i].ocupado=1;
    cad=1;
    break;
    }
    if(i==TAM-1)
    {
    cad=0;
    }
    }
    
    if(cad==1){
    strcpy(resp, "cadastrado");
    printf("cadastrado na struct\n");
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    }
    else{
    strcpy(resp, "sem espaco");
    printf("Sem espaco na struct\n");
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    }

    break;
    
    case 2:
    cont=0;
    for(int i=0;i<TAM;i++){
    if(banco[i].ocupado==1){
    cont++;
    }
    }
    sprintf(resp, "%d", cont);
    printf("Mandando quantidade de mensagem ao cliente\n");
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    int j =0;
    printf("Mandando usuarios e mensagens ao cliente\n");
    for(int i=0; i<cont;i++){
    
    if (recv(ns, resp, sizeof(resp), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
    
    while(banco[j].ocupado==0){
    j++;
    }
    
    strcpy(usuario, banco[j].user);
    if (send(ns, usuario, strlen(usuario)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    
    if (recv(ns, resp, sizeof(resp), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
    
    strcpy(mensagem, banco[j].mens);
    if (send(ns, mensagem, strlen(mensagem)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    j++;   
    }
    break;
    
    case 3:
    
    strcpy(resp,"operacao recebida");
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    
    if (recv(ns, usuario, sizeof(usuario), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
    printf("Recebi o nome -> cliente\n");
    cont=0;
    printf("Mandando quantidade de mensagens referente ao nome\n");
    for(int i=0;i<TAM;i++){
    if(strcmp(banco[i].user, usuario)==0){
    cont++;
    }
    }
    sprintf(resp, "%d", cont);
    if (send(ns, resp, strlen(resp)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    
    int k=0;
    printf("Mandando mensagens excluidas\n");
    for(int i=0;i<cont;i++){
    
    if (recv(ns, usuario, sizeof(usuario), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
    
    while(strcmp(banco[k].user,usuario)!=0){
    k++;
    }
    
    strcpy(mensagem, banco[k].mens);
    banco[k].ocupado=0; 
    banco[k].user[0]='\0'; 
    banco[k].mens[0]='\0'; 
     
    
    if (send(ns, mensagem, strlen(mensagem)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }
    k++;
    }
    
    break;
    
    case 4:
     /* Fecha o socket conectado ao cliente */
    close(ns);

    /* Fecha o socket aguardando por conexões */
    close(s);

    printf("Servidor terminou com sucesso.\n");
    exit(0);
    break;
    };
    }while(1);
}


