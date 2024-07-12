# Trivia Project

## Overview
This project is a multi-threaded (MT) server implemented in C++ and a client application developed using C# and WPF (Windows Presentation Foundation). It serves as the final project for the second year of the Magshimim program. The project demonstrates advanced C++ programming skills and client-server architecture. We received a perfect score (100) on this project.

## Features
- Multi-threaded server capable of handling multiple clients concurrently.
- Client application with a graphical user interface (GUI) built using WPF.
- High-level C++ code structure for the server.
- Real-time trivia game where clients can join, answer questions, and view scores.

## Prerequisites
### Server
- Visual Studio (2019 or later) with C++ development tools
- Boost libraries (for threading and networking)

### Client
- Visual Studio (2019 or later) with .NET desktop development tools

## Setup and Installation

### Server
1. **Install Visual Studio:**
   - Ensure you have Visual Studio 2019 or later installed with the C++ development tools.
   

2. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/trivia-project.git
   cd trivia-project/server
   
3. **Open the Project:**
   - Open the `TriviaServer.sln` solution file in Visual Studio.

4. **Build the Project:**
   - Build the solution by selecting `Build > Build Solution` from the menu.

### Client
1. **Install Visual Studio:**
   - Ensure you have Visual Studio 2019 or later installed with the .NET desktop development tools.

2. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/trivia-project.git
   cd trivia-project/client
   ```

3. **Open the Project:**
   - Open the `TriviaClient.sln` solution file in Visual Studio.

4. **Build the Project:**
   - Build the solution by selecting `Build > Build Solution` from the menu.

## Running the Application

### Server
1. After building the project, run the server by pressing `Ctrl+F5` in Visual Studio.
2. The server will start and listen for incoming client connections.

### Client
1. After building the project, run the client application by pressing `Ctrl+F5` in Visual Studio.
2. Connect to the server by entering the server's IP address and port number to the 'serverConfig.txt' file
3. Join a trivia game and start playing!

---