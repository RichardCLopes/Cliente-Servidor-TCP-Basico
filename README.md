# Descrição da Atividade
Esta atividade tem como objetivo introduzir conceitos básicos de desenvolvimento de software para ambientes TCP/IP, com foco na implementação de clientes e servidores utilizando o protocolo TCP.

# Implementação
A atividade consiste no desenvolvimento de uma aplicação para compartilhamento de mensagens utilizando
sockets TCP.

Para tal, será necessário implementar um programa cliente TCP e um programa servidor TCP.

Ao executar o programa servidor o usuário deve informar o número da porta na qual o programa servidor
aguardará por requisições, como no exemplo a seguir:

```./servidor 5000```

O servidor deve aguardar por requisições enviadas pelos clientes e realizar as operações solicitadas,
exibindo na tela mensagens de log contendo informações resumidas das operações solicitadas. As
mensagens de log devem exibir informações como o endereço IP e a porta do cliente que solicitou a
operação, além da operação solicitada e o resultado retornado pelo servidor informando sucesso ou falha
na realização da operação.

Ao executar o programa cliente o usuário deve informar o nome do computador (ou o endereço IP) e a porta
onde se encontra o programa servidor, como no exemplo a seguir:

```./cliente localhost 5000```

ou

```./cliente 192.168.1.2 5000```

Em seguida, o programa cliente deve exibir um menu com as seguintes opções:
```
Opções: 
1 - Cadastrar mensagem
2 - Ler mensagens
3 - Apagar mensagens 
4 - Sair da Aplicação
```

O programa cliente só deve ser encerrado, caso o usuário selecione a opção 4.

Caso o usuário selecione a opção 1, o programa cliente deve solicitar o nome do usuário e a mensagem
que será cadastrada, como no exemplo a seguir:

```
Usuário: fulano
Mensagem: Testando o cadastramento de mensagens.
```

O nome do usuário deve conter no máximo 19 caracteres.

A mensagem digitada deve conter no máximo 79 caracteres.

Após a leitura do nome do usuário e da mensagem, o programa cliente deve enviar uma requisição ao
servidor solicitando o cadastramento de tais informações.

O servidor deve então realizar a operação solicitada, retornando ao cliente uma resposta informando se a
solicitação foi atendida corretamente ou não, especificando o motivo da falha caso a requisição não possa
ser atendida por algum motivo.

O servidor deve permitir o cadastramento de no máximo 10 mensagens no total.

Caso o usuário selecione a opção 2, o programa cliente deve enviar uma requisição ao servidor solicitando
o envio das mensagens existentes.

O servidor deve então realizar a operação solicitada, retornando ao cliente uma resposta informando
quantas mensagens cadastradas existem e, caso existam mensagens cadastradas, uma listagem contendo
o nome do usuário e a respectiva mensagem.

O programa cliente, após receber a resposta do servidor, deve exibir uma mensagem adequada na tela
contendo as informações recebidas, como no exemplo a seguir:
```
Mensagens cadastradas: 2
Usuário: fulano Mensagem: Testando o cadastramento de mensagens.
Usuário: ciclano Mensagem: Compartilhamento de mensagens funcionando!
```

Caso o usuário selecione a opção 3, o programa cliente deve solicitar o nome do usuário para o qual as
mensagens serão apagadas no servidor:

```Usuário: fulano```

Após obter o nome do usuário, o cliente deve enviar uma requisição adequada ao servidor, que deve então
realizar a operação solicitada, retornando ao cliente uma resposta informando quantas mensagens foram
apagadas e uma listagem contendo o nome de usuário e as mensagem apagadas, caso existam.

O programa cliente, após receber a resposta do servidor, deve exibir uma mensagem adequada na tela
contendo as informações recebidas, como no exemplo a seguir:
```
Mensagens apagadas: 1
Usuário: fulano Mensagem: Testando o cadastramento de mensagens.
```
