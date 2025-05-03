# 🔐 TCP Server & Client (XOR Encrypted Chat) – C++

## 📝 Description
This project is a simple TCP server and client system written in C++. It enables real-time message exchange between multiple clients over a network using the WinSock2 library. All messages are encrypted with a basic XOR cipher for educational purposes.

> ⚠️ **Note:** This version does **not** support file transfers. Only encrypted text messages are supported.

---

## ⚙️ How It Works
- The **server** listens for multiple clients using `select()`.
- When a new client connects, it receives a welcome message encrypted with XOR.
- Clients can send messages that are:
  - XOR-encrypted on the client side
  - broadcasted by the server to all connected clients
- Messages include the sender's username (e.g. `Zakaria>Hello`).

---

## 🧪 Environment & Requirements

### ✅ System
- **OS:** Windows (tested)
- **Language:** C++
- **Compiler:** Dev-C++ or g++
- **Sockets API:** WinSock2 (Windows only)

### ⚠️ Dev-C++ Compilation Help
If you're using **Dev-C++** and your code doesn't compile, do the following:

1. Go to **Project > Project Options**
2. Click OK if prompted
3. Open the **"Parameters"** tab
4. In the **Linker** section, add: -lws2_32
5. 
### ⚠️ Running Client on Android (via Termux , NDK or Cxxdroid)
If you plan to run the client on a **mobile device**, you must:
- Replace WinSock headers with POSIX-compatible libraries (`#include <sys/socket.h>`, etc.)
- Adjust code for cross-platform compatibility

---

## 🔐 XOR Encryption
- Every message sent is encrypted using XOR with a **fixed key**.
- This method is used to demonstrate basic encryption concepts.
- ⚠️ **Do not use XOR in real-world security applications.**

---

## 🔄 Planned Features (Next Updates)
- [ ] AES encryption instead of XOR
- [ ] Command prompt (CMD) support on the server (e.g. `whois`, `list`, `kick`)
- [ ] File transfer support (send/receive)
- [ ] Authentication (username/password login)
- [ ] Android version of the client
- [ ] Image/video transfer support
- [ ] Cross-platform compatibility (Linux/Windows/Android)
- [ ] Multiple protocol support (TCP, UDP)
- [ ] **Custom Message Protocol:**
- [ ] Add message headers: `Type`, `Size`, and `Plaintext`
- [ ] Example: `| Type | Size | Message Content |`

---

## 💻 Usage

### ✅ Compile

#### Server
```bash
` g++ server.cpp -o server -lws2_32 `
` g++ client.cpp -o client -lws2_32 `
`./server `
`./client `

👤 Author
Zakaria
Cybersecurity student at FSR, Morocco.
Passionate about secure communications and ethical hacking.

📜 License
This project is free to use for learning and educational purposes.

