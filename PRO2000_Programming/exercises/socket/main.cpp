#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main(int argc, char* argv[]) {
    const int PORT = 8080;
    const int BUFFER_SIZE = 1024;

    if (argc != 2) {
        cout << "Usage:\n";
        cout << "  socket_demo.exe server\n";
        cout << "  socket_demo.exe client\n";
        return 1;
    }

    // Start Winsock
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed.\n";
        return 1;
    }

    SOCKET serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // Use the local computer
    inet_pton(
        AF_INET,
        "127.0.0.1",
        &address.sin_addr
    );

    string mode = argv[1];

    if (mode == "server") {
        int option = 1;

        setsockopt(
            serverSocket,
            SOL_SOCKET,
            SO_REUSEADDR,
            reinterpret_cast<char*>(&option),
            sizeof(option)
        );

        if (bind(
                serverSocket,
                reinterpret_cast<sockaddr*>(&address),
                sizeof(address)
            ) == SOCKET_ERROR) {
            cout << "Bind failed.\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        if (listen(serverSocket, 1) == SOCKET_ERROR) {
            cout << "Listen failed.\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        cout << "Server waiting on port " << PORT << "...\n";

        sockaddr_in clientAddress{};
        int clientAddressSize = sizeof(clientAddress);

        SOCKET clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientAddressSize
        );

        if (clientSocket == INVALID_SOCKET) {
            cout << "Accept failed.\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        char buffer[BUFFER_SIZE]{};

        int bytesReceived = recv(
            clientSocket,
            buffer,
            BUFFER_SIZE - 1,
            0
        );

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';

            cout << "Client sent: " << buffer << '\n';

            string response = "Server received: ";
            response += buffer;

            send(
                clientSocket,
                response.c_str(),
                static_cast<int>(response.length()),
                0
            );
        }

        closesocket(clientSocket);
        closesocket(serverSocket);

        cout << "Server closed.\n";
    } 
    else if (mode == "client") {
        if (connect(
                serverSocket,
                reinterpret_cast<sockaddr*>(&address),
                sizeof(address)
            ) == SOCKET_ERROR) {
            cout << "Connection failed.\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        string message;

        cout << "Enter a message: ";
        getline(cin, message);

        send(
            serverSocket,
            message.c_str(),
            static_cast<int>(message.length()),
            0
        );

        char buffer[BUFFER_SIZE]{};

        int bytesReceived = recv(
            serverSocket,
            buffer,
            BUFFER_SIZE - 1,
            0
        );

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            cout << "Server response: " << buffer << '\n';
        }

        closesocket(serverSocket);
    } 
    else {
        cout << "Invalid mode. Use server or client.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Shut down Winsock
    WSACleanup();

    return 0;
}