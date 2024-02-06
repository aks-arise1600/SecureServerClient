# SecureServerClient
A Qt/C++ Exmaple for SSL Server over TCP, TLS Handshake



## Dependencies
1. [OpenSSL](https://www.openssl.org/source/)
2. [Qt](https://www.qt.io/product/development-tools)

## Install dependencies

		sudo apt-get update
		sudo apt-get install -y build-essential make cmake qtbase5-dev qt5-qmake git libssl1.0-dev

## Compile/build and Run Secure Server-Client


1. Cmake build

		git clone https://github.com/anil-arise1600/SecureServerClient.git
		cd SecureServerClient
		mkdir cBuild && cd cBuild
		cmake ..
		make
		
2. Qmake build
		
		git clone https://github.com/anil-arise1600/SecureServerClient.git
		cd SecureServerClient
		mkdir qBuild && cd qBuild
		qmake ..
		make
		
3. Run after build by anyone step 1 or 2

* Run server on Terminal 1

		cd <Path_to_build>/SecureServer
		./SecureServer
		
* Run Client on Terminal 2

		cd <Path_to_build>/SecureClient
		./SecureClient
		
		
## Helps

1. [Openssl command](https://www.openssl.org/docs/man1.1.1/man1/openssl.html)
2. [SSL Socket](https://doc.qt.io/qt-6/qsslsocket.html)
3. [TCP Server](https://doc.qt.io/qt-6/qtcpserver.html)


