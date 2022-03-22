Sistemas Operativos II - Laboratorio I IPC
### Lihué Leandro Luna - MAT:39129465 - Ingeniería en Compitación - FCEFyN - UNC
# Interprocess Communication

## Desarrollo
Con el fin de resolver el trabajo con soluciones incrementales primero se implemento solo un servidor ipv4 tcp que era testeado con la herramienta `netcat`
Dicho servidor cumple con el siguente diagrama de flujo.
![Diagrama de flujo servidor](/img/tcpserverflowdiagram.png)
Teniendo un servidor funcionando se modifico para que pueda ser programable, es decir, ahora el programa era capaz de recibir como parametros la direccion ip y el puerto a escuchar.
Satisfecho con la construccion del servidor se paso a la implementacion del cliente ipv4 tcp que cumple con el siguiente diagrama de flujo
![Diagrama de flujo cliente](/img/tcpclientflowdiagram.png)
El cliente tambien es programable, se le pasa como argumentos la direccion ip, puerto y cantidad de bytes a mandar.
Hasta ahora el servidor era secuencial, solo podia antender de un cliente a la vez. Haciendo uso de `fork()` se gestionan los hijos necesarios para el manejo de clientes en simultaneo
Una vez completada la estructura cliente servidor se implmentaron aparte las versiones en ipv4 udp y ipv6 tcp cambiando los argumentos correspondientes en `socket()`
De esta forma ahora el servidor crea y gestiona 3 sockets distintos y utiliza procesos hijos para gestionar las conexiones entrantes.
Para contabilizar la velocidad se creo una region de memoria compartida, haciendo uso de la siguente estructura
```
typedef struct
{
    long int ipv4_tcp;
    long int ipv4_udp;
    long int ipv6_tcp;
    long int total;
}   Bytes;
```
Se pasa la direccion de memoria correspondiente a su protocolo a los procesos hijos para que sumen la cantidad de bytes recibidos ahí y cada un segundo se realiza el calculo, se imprime en pantalla y se guarda en un archivo log.txt
## Funcionamiento
### Cliente
El cliente se instancia de la siguiente forma:
```
./client <protocol> <address> <port> <bytes> <interface>
ej: ./client tcp 127.0.0.1 8080 100 lo
```
En este caso se esta instanciando un cliente ipv4 tcp que va a enviar mensajes que tienen un tamaño de buffer de 100 bytes constantemente usando la interface de loopback.
### Servidor
El servidor se instancia de la siguiente forma:
```
./server <ipv4address> <ipv6address> <port> <interface>
ej: ./server 127.0.0.1 ::1 8080 lo
```
En este caso se esta instanciando un server que esta escuchando en el puerto 8080 en la direccion de loopback
![Captura de pantalla](/img/screenshot.png)
En esta caputra se pueden ver dos clientes tcp ipv4 dos clientes tcp ipv6 y dos clientes udp ipv4 (las terminales pequeñas), el servidor (en la terminal de vscode) printeando la velocidad en Mbits/s y el `nload` viendo el trafico de la interfaz de loopback y los resultados se corresponden bastante bien.