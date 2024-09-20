/*
  @author: Blas - eLite (c) 2024
  @def Networking on the same internet
  @copyright eLite (c) 2024
  @category networking, lan
  @since 1.0
*/

#include "imports.cpp"
#include <winhttp.h>
#include <atomic>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib
#pragma comment(lib, "Wlanapi.lib") // Link with Wlanapi.lib
#pragma comment(lib, "winhttp.lib") // Link with winhttp.lib
#pragma comment(lib, "Ws2_32.lib")

/*
 @def Function for sending text to another computer on the same network
 @brief Send text to another computer
 @example netwsendt("255.255.255", 8080, "Hello World!");
 @param ipAddress IP of the server to send
 @param port Port of connection with the server
 @param data Text to send
 @throws runtime_error If the connection had an error
*/
void netwsendt(const char* ipAddress, int port, const std::string& data) {
    try {
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);

        int wsOK = WSAStartup(ver, &wsData);
        if (wsOK != 0) {
            throw std::runtime_error("Can't initialize Winsock!");
        }

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            throw std::runtime_error("Can't create socket!");
        }

        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        hint.sin_addr.s_addr = inet_addr(ipAddress);

        int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
        if (connResult == SOCKET_ERROR) {
            throw std::runtime_error("Can't connect to server!");
        }

        int sendResult = send(sock, data.c_str(), data.size() + 1, 0);
        if (sendResult == SOCKET_ERROR) {
            throw std::runtime_error("Can't send data to server!");
        }

        closesocket(sock);
        WSACleanup();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
/*
 @def Function for recieving text from another computer on the same network
 @brief Recieve text from another computer
 @example netwrecit(8080);
 @param port Port in which the connection will be started
 @throws runtime_error If the connection had an error
 @return Text that the server sent
*/
std::string netwrecit(int port) {
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        throw std::runtime_error("Can't initialize Winsock!");
    }

    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        throw std::runtime_error("Can't create socket!");
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.s_addr = INADDR_ANY; // Use any address for the server

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    listen(listening, SOMAXCONN);

    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        throw std::runtime_error("Can't accept client connection!");
    }

    char buf[4096];
    std::string receivedData;

    while (true) {
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived > 0) {
            receivedData.append(buf, bytesReceived);
            break; // Break the loop if data received
        } else if (bytesReceived == 0) {
            // Connection closed by client
            break;
        } else {
            // Error in receiving data
            throw std::runtime_error("Error in receiving data!");
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return receivedData;
}
std::string netwgetip() {
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    if (WSAStartup(ver, &wsData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        WSACleanup();
        throw std::runtime_error("gethostname failed");
    }

    hostent* host = gethostbyname(hostname);
    if (host == nullptr || host->h_addr_list[0] == nullptr) {
        WSACleanup();
        throw std::runtime_error("gethostbyname failed");
    }

    in_addr* address = reinterpret_cast<in_addr*>(host->h_addr_list[0]);
    std::string ipAddress = inet_ntoa(*address);

    WSACleanup();
    return ipAddress;
}
/*
 @def Function for checking if the selected ip and port is a valid socket
 @brief Check if a port and an ip can be a socket
 @example netwcheck("225.225.225", 8080)
 @param ipAddress IPv4 of the server
 @param port Port of the server
 @throws runtime_error If the connection had an error
 @returns true If valid
 @returns false If not valid
*/
bool netwcheck(const char* ipAddress, int port) {
    WSADATA wsaData;
    int wsOK = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsOK != 0) {
        throw std::runtime_error("Failed to initialize Winsock!");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket!");
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.s_addr = inet_addr(ipAddress);

    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return false; // Connection failed
    }

    // Connection successful
    closesocket(sock);
    WSACleanup();
    return true;
}
/*
 @def Function for getting a list of all wifi networks the computer can connect to
 @brief List WiFi networks
 @example netwwifilist
 @throws runtime_error If an error occurs
 @returns vector<string> WiFi list
*/
std::vector<std::string> netwwifilist() {
    std::vector<std::string> networks;

    HANDLE handle = NULL;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;

    // Open WLAN handle
    if (WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &handle) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to open WLAN handle");
    }

    WLAN_AVAILABLE_NETWORK_LIST* pAvailableNetworkList = NULL;
    // Get available network list
    if (WlanGetAvailableNetworkList(handle, NULL, 0, NULL, &pAvailableNetworkList) != ERROR_SUCCESS) {
        WlanCloseHandle(handle, NULL);
        throw std::runtime_error("Failed to get available network list");
    }

    // Process available networks
    for (DWORD i = 0; i < pAvailableNetworkList->dwNumberOfItems; i++) {
        WLAN_AVAILABLE_NETWORK network = pAvailableNetworkList->Network[i];
        // Convert character array to string
        std::string ssid(reinterpret_cast<const char*>(network.dot11Ssid.ucSSID), network.dot11Ssid.uSSIDLength);
        networks.push_back(ssid);
    }

    WlanFreeMemory(pAvailableNetworkList);
    WlanCloseHandle(handle, NULL);

    return networks;
}
/*
 @def Function for host a local folder and acess it from internet.
 @brief Host a local folder
 @example netwlocalserver("documents", 8080, "logFile.log")
 @param folderPath Folder to host
 @param port Port to use for hosting
 @param logFile (optional) File for outputting the results.
 @throws runtime_error If an error occurs
 @returns nothing
*/
void netwlocalserver(const std::string& folderPath, int port, const std::string& logFile = "") {
    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        throw std::runtime_error("WSAStartup failed: " + std::to_string(iResult));
    }

    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Error at socket(): " + std::to_string(WSAGetLastError()));
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(port);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        throw std::runtime_error("bind() failed: " + std::to_string(WSAGetLastError()));
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        throw std::runtime_error("Error at listen(): " + std::to_string(WSAGetLastError()));
    }

    std::atomic<bool> stopFlag(false);
    std::thread monitorThread([&](){
        HANDLE hDir = CreateFileW(
            std::wstring(folderPath.begin(), folderPath.end()).c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );


        if (hDir == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("CreateFile failed: " + std::to_string(GetLastError()));
        }

        char buffer[1024];
        DWORD bytesReturned;

        while (!stopFlag.load()) {
            if (ReadDirectoryChangesW(
                    hDir,
                    buffer,
                    sizeof(buffer),
                    TRUE,
                    FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES |
                    FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION,
                    &bytesReturned,
                    NULL,
                    NULL
                )) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (!logFile.empty()) {
                    std::ofstream logStream(logFile, std::ios::out | std::ios::app);
                    if (logStream.is_open()) {
                        logStream << "Folder change detected. Re-uploading folder..." << std::endl;
                        // Implement folder re-upload code here
                        logStream.close();
                    } else {
                        throw std::runtime_error("Failed to open log file.");
                    }
                }
            }
        }

        CloseHandle(hDir);
    });

    SOCKET clientSocket;
    while (true) {
        clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            if (!logFile.empty()) {
                std::ofstream logStream(logFile, std::ios::out | std::ios::app);
                if (logStream.is_open()) {
                    logStream << "accept failed: " << WSAGetLastError() << std::endl;
                    logStream.close();
                }
            }
            closesocket(serverSocket);
            WSACleanup();
            stopFlag.store(true);
            monitorThread.join();
            throw std::runtime_error("accept failed: " + std::to_string(WSAGetLastError()));
        }

        char buffer[1024] = {0};
        int bytesReceived = recv(clientSocket, buffer, 1024, 0);
        if (bytesReceived > 0) {
            std::string request(buffer, bytesReceived);
            std::istringstream requestStream(request);
            std::string method, path, version;
            requestStream >> method >> path >> version;

            if (method == "GET") {
                std::string filePath = folderPath + path;
                std::ifstream file(filePath, std::ios::in | std::ios::binary);
                std::string fileContent;

                if (file) {
                    std::ostringstream contents;
                    contents << file.rdbuf();
                    file.close();
                    fileContent = contents.str();
                }

                std::string response;
                if (!fileContent.empty()) {
                    response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(fileContent.size()) + "\r\n\r\n" + fileContent;
                } else {
                    std::string notFound = "404: File not found";
                    response = "HTTP/1.1 404 Not Found\r\nContent-Length: " + std::to_string(notFound.size()) + "\r\n\r\n" + notFound;
                }

                send(clientSocket, response.c_str(), response.size(), 0);
                if (!logFile.empty()) {
                    std::ofstream logStream(logFile, std::ios::out | std::ios::app);
                    if (logStream.is_open()) {
                        logStream << "Served: " << filePath << std::endl;
                        logStream.close();
                    }
                }
            }
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    if (!logFile.empty()) {
        stopFlag.store(true);
        monitorThread.join();
    }
}
/*
 @def Function for reading a file from internet using the URL
 @brief Read a file from internet
 @example netwreadfile("https://e--explore.web.app")
 @throws runtime_error If the connection had an error
 @return String Content of the file.
*/
std::string netwreadfile(const std::string& url) {
    // Convert the URL to a wide string
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), (int)url.size(), NULL, 0);
    std::wstring wUrl(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, url.c_str(), (int)url.size(), &wUrl[0], size_needed);

    // Parse the URL
    URL_COMPONENTS urlComp;
    ZeroMemory(&urlComp, sizeof(urlComp));
    urlComp.dwStructSize = sizeof(urlComp);

    wchar_t hostName[256];
    wchar_t urlPath[256];
    urlComp.lpszHostName = hostName;
    urlComp.dwHostNameLength = _countof(hostName);
    urlComp.lpszUrlPath = urlPath;
    urlComp.dwUrlPathLength = _countof(urlPath);

    if (!WinHttpCrackUrl(wUrl.c_str(), (DWORD)wUrl.length(), 0, &urlComp)) {
        throw std::runtime_error("Failed to crack URL");
    }

    // Initialize WinHTTP session
    HINTERNET hSession = WinHttpOpen(L"A WinHTTP Example Program/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        throw std::runtime_error("Failed to open WinHTTP session");
    }

    // Connect to the server
    HINTERNET hConnect = WinHttpConnect(hSession, urlComp.lpszHostName, urlComp.nPort, 0);
    if (!hConnect) {
        WinHttpCloseHandle(hSession);
        throw std::runtime_error("Failed to connect to server");
    }

    // Create an HTTP request
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", urlComp.lpszUrlPath,
                                            NULL, WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            urlComp.nScheme == INTERNET_SCHEME_HTTPS ? WINHTTP_FLAG_SECURE : 0);
    if (!hRequest) {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        throw std::runtime_error("Failed to open HTTP request");
    }

    // Send the request
    BOOL bResults = WinHttpSendRequest(hRequest,
                                       WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                       WINHTTP_NO_REQUEST_DATA, 0,
                                       0, 0);
    if (!bResults) {
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        throw std::runtime_error("Failed to send HTTP request");
    }

    // Receive the response
    bResults = WinHttpReceiveResponse(hRequest, NULL);
    if (!bResults) {
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        throw std::runtime_error("Failed to receive HTTP response");
    }

    // Read the response data
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    std::string result;
    do {
        dwSize = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
            WinHttpCloseHandle(hRequest);
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            throw std::runtime_error("Error querying data availability");
        }

        if (dwSize == 0)
            break;

        char* buffer = new char[dwSize + 1];
        ZeroMemory(buffer, dwSize + 1);

        if (!WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwDownloaded)) {
            delete[] buffer;
            WinHttpCloseHandle(hRequest);
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            throw std::runtime_error("Error reading data");
        }

        result.append(buffer, dwDownloaded);
        delete[] buffer;

    } while (dwSize > 0);

    // Clean up handles
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return result;
}
