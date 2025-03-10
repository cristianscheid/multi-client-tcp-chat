# Multi-Client TCP Chat

## Description

This project is a simple, terminal-based multi-client TCP chat application, developed using the C programming language and the SDL (Simple DirectMedia Layer) library, specifically the SDL_net module. Clients can connect to the server, send and receive messages, and chat in real time.

## Features

- Supports up to 10 clients connected simultaneously.
- Allows clients to set a username when connecting to the server.
- Messages sent by clients are broadcast to all connected clients (except the sender).
- Uses TCP protocol for reliable, connection-oriented communication between clients and server.
- Utilizes SDL_net for managing network connections and socket communication.

## Built With

![C][c-img-shield]
![SDL][sdl-img-shield]

## Visuals

https://github.com/user-attachments/assets/64f098e1-743c-4d32-9ed2-c7db2b385e1a

## Installation

To get started with this project, follow the steps below:

1. **Install build tools and SDL libraries**

   - Debian/Ubuntu:

     ```
     sudo apt install gcc make libsdl2-dev libsdl2-net-dev
     ```

   - Fedora/RHEL/CentOS:

     ```
     sudo dnf install gcc make SDL2-devel SDL2_net-devel
     ```

   - OpenSUSE:

     ```
     sudo zypper install gcc make SDL2-devel SDL2_net-devel
     ```

   - Arch Linux:

     ```
     sudo pacman -S gcc make sdl2 sdl2_net
     ```

   - If your Linux distribution is not listed, you can find instructions for installing the SDL libraries from source [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php).

2. **Clone the repository**

   ```
   git clone https://github.com/cristianscheid/space-crusher.git
   cd space-crusher
   ```

3. **Build the project**

   ```
   make
   ```

4. **Run the server**

   ```
   ./build/space-crusher
   ```

   - This will start the server, which listens for incoming client connections.

5. **Run the client(s)**

   ```
   ./build/client
   ```

   - Open a new terminal for each client you want to connect to the server. You can start up to 10 clients simultaneously.

## Usage

Once the server is running, open the client(s), set your name, type a message, and hit Enter. The server will display all received messages, while clients will see messages sent by other connected clients, just like a chat. To fully test the functionality, connect two or more clients. To stop the server or quit a client, simply press Ctrl + C.

By default, the server runs on `127.0.0.1` and port `2000`. To change these values, modify the `SERVER_HOST` and `SERVER_PORT` constants in both the `src/client.c` and `src/server.c` files. After making changes, run `make clean` followed by `make` to regenerate the executables.

## License

Distributed under the MIT License. See LICENSE.txt for more information.

<!-- Custom image shields for the Built With section -->

[c-img-shield]: https://img.shields.io/badge/C-C11-gray?&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAMAAABg3Am1AAABfVBMVEUAAAAkJJElOJcpNpIoNJIoNJEpNJInNpMoNJMnNZInNZInNJIoNZIoNJMnNZMoNZInNJMnNJInNJMoNJMnNJInNZInNJJXZrs2RaUtPJs1Q6BJV69MWbJKWbFLWbJMW7JOXbRPXrZQX7ZRX7dQXrZTYrhJWLBKWLBIVa9JVq1FU65GUq9HVqxEWbJHU6s4R54+SqlCTq0+PqIvQKA5UOcoNZMpNpQqOJUsOpkyP5oyP5g1QZsxQKAzQ6Q3R6g4SKo5SKs5Sas6S6w+TalCUa5HVa5JWLJNXLRTYbhZZ71bar9ca8BdbMBjb7xlcr5kcsNtdrZud7Zxfsl6hsx8iMyCjM2FkNCNltCSnNWVntKcpNWUmsmSmcirs9+utuCwtt+6vt29weDHy+PN0ObQ0+fKz+rV2e7W2u/a3vHc3/Hd3+7l6PXm6PXn6fbp6/bt7vbv8Pjx8vrz9Pr19fr4+fz7+/37/P7///9cZq5SXahQW6hGUaJET6FDTqE6R6LES/XxAAAANXRSTlMABxsoNj9EVWZ6gYiZqru/x9Hd5+72/fzYvq+jrbzBytrf5ujt9ZeCd2tfUEc8KyIVEAsFAiThxbMAAAIeSURBVHja1dLtQ9JAHMDxMynFtBQDejKy0rIseTogRHRpk+1WK0CjFCITUbQQBYeW/e2t8dvauBvgSz/v2P2+424buiz8DwTvhB/1KjztJSrvvRDqycwUAVPPUHezj4jJkxeoszkfsRIfvkL2AvcFQhEmAnZnfeolTN7pMGJ4bpw1Wyjv1+v75ULWOP0MNf5yEtak3A/FcJCT4PLjWevmfSIspPcUi920fnpf0BRMErBWU9ocrcMSf9sU6PdfP1EoJ1qRSnKLpkDfT01hOEoTYXmR45aoQNpTmHZXkhzHCnL6RC2fkeVMHv5v5z3HMQPpAOZLMtHIJfXHzzUOUEFWn5cIkEr1LyucbVCA/chEJ/KrMMwMyq0gT3S8etZOAXwSGRhPqeOdg3or0HakPfkLBCIfS1ABZ7+l1dcY40iiW7ADh079wS3RBSpgPdbDeWyYf0cH9IsrRjCIFJVvKSqgP41iHO5fVH80vvLsQPVJAdXN03j8dLMKr/7zG2YgLEe3Fabv0cQSFYhvYxifV1nzh78wji1YA1F98v80G/R8o6ktxZLm4C4GzSp1/yYGd0xBaMgNV39vt+3/HBbcQ33I7MqwB579x4piqHyAcc/IHGrnuInB2cZW5fi4srVxhsGoA7FcG8NMrgFkIzQ4jim3nH3IXuC6G1t4hv2os/4RD/7vRj/qzjGKwdhV1JPwgAurxgfDqFdBp8vlDKJL4i/XYomZyo+JUQAAAABJRU5ErkJggg==&style=for-the-badge
[sdl-img-shield]: https://img.shields.io/badge/SDL-2.0-gray?&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAMAAABg3Am1AAAA8FBMVEUAAABFYHNJYXVccYFmeYlGYXR0hpabprCwt76ywtDGzdTR1NfY29/R1tzHzNK9w8i3u8DCxcnJzNDJ1eC9zNu6xdG4ytu2ub2zusKutLuorbSZo66coKilq7OVpLOan6WPl6CHj5qAiJJ6gYtvdoJcboFPYnZaYXBbcINjeYtziJt5kKV8lauJpL2dr8GQlJt1iZp5jJyGlqWKobSVq7+Tqb2XqLerwda9wcfa3eDh5Ofm6Ora3eHW29/r7vHr7e729/j6+/vw8vPm6OtqgpdFXHJAWG07Umg2TWQwSGEsRF0nP1kiOlUdNVEZMU0TK0gwS/y6AAAARXRSTlMAJxQ6VkoEHC1RZXF4jYiHnqigtcfd5+jMwLLB1tTu7e309PX2/v365d7c2fH78t+1imuDhJRvlLlgZU9LOj0kGCkIDvzUYJ65AAACYUlEQVR42u2Ra1eiUBSGyQsZVxNLMYnLAWwa02qmhjsIgmSi///fzAbURTb2cT60fNY6Z79s9gNnrYOdOPF/8ayw8jRjeEEQ2uTMZQtIO4BuxLAssx9zOW8/T8lxyS2zDbpIhVigxLF8vp9qceQ2WVqSJLoeJ4nMJDt0IwwU6ICwN3i6DAK875sOyauFIA1uJCgxHaCqANQnTF4iebHQbAi43WcWi8UNhvkGVNlDsFUF/HXiFEKaplLb9KFDQAQBCyQINEpTpSpgZ/3bCIrwlpMiwcIJCLmADSAY6O0NhCrtOQG7g5Yl+iUBeyGwEHh1uTwQ6pPirSNo7wU6B1vRakPg1ff3A8GfjIuKe+xAWq5Wqx6sXAiHEDrqaoU+Cqw2h/u5nOU54rMs68HKBSrNMtVUs+xAcBUQ/BFivBCbDdfr9RWsoW3yI6i8r67XyLQBD9vf8T0GwmYzkqfqZrNROpsd62ErgFbJFC9PTk+1p0LYgghiFxPBxT4JkbjQG+CZA0kdjUby4AK3pwXDAVGD2xOmW/hSmEnxY61Ufdd1z6HrGpck2aU6Bm1RbZKk+jRNkxRp5kJgC/FdA1IOvq2mpIqKqvREEYmKqCJF6fUkhPI/4Iym3zXOsI9EjuN0nI9YrNOCm7Ek/UejCeYOiMcJOWGuPTaatUrPo4Ij01FgG3Pt/qkJ81UCmrP+4eCeIY3nP2G8/ukQEcFxtDkLo+05At+j+auH8fjxubn7/Cfn4k/3+rrLcX2ue3U7eXgY37zk03UYPwZea128/n4Bfr0+N/Lhs9r+MF9pJYezX0vYiW/EXxRqfbOSdzKHAAAAAElFTkSuQmCC&style=for-the-badge
