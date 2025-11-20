<div align="center">

# ShadowSniff

![C++](https://img.shields.io/badge/C++-Linux_Network_Stack-blue?style=flat&logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green)
![Permissions](https://img.shields.io/badge/Requires-ROOT_(sudo)-red)

<p>
  <strong>A raw socket packet sniffer for analyzing TCP traffic on Linux.</strong>
</p>

[Report Bug](https://github.com/your-username/shadowsniff/issues) · [Request Feature](https://github.com/your-username/shadowsniff/issues)

</div>

---

## Description

**ShadowSniff** is a minimalist network sniffer written in C++. It bypasses the standard operating system network stack by using **Raw Sockets**, allowing it to intercept and inspect TCP packets flowing through the network interface.

This tool demonstrates how low-level network protocols (IP and TCP headers) are structured and parsed programmatically. It acts similarly to tools like Wireshark or TCPDump but is stripped down to the bare essentials for educational purposes.

### Key Features

  **Raw Packet Capture:** Intercepts traffic at the IP layer.
  **Header Parsing:** Manually decodes IP and TCP headers using pointer arithmetic.
  **Traffic Monitoring:** Displays Source IP/Port and Destination IP/Port in real-time.
  **Linux Exclusive:** Built specifically for Linux network architecture.

---

## Usage

**Warning:** This tool requires `root` privileges to open a raw socket.

1. **Compile:**
   ```bash
   make
   ```

2. **Run (with sudo):**
   ```bash
   sudo ./shadowsniff
   ```

### How to Test
While ShadowSniff is running in one terminal, open another terminal or a web browser and generate traffic:

```bash
# Generate some traffic
curl [https://www.google.com](https://www.google.com)
```

**ShadowSniff Output:**
```text
[*] ShadowSniff Started. Monitoring TCP Packets...
-----------------------------------------------------------
[TCP] 192.168.1.35:54322 -> 142.250.187.100:443 | Size: 60 bytes
[TCP] 142.250.187.100:443 -> 192.168.1.35:54322 | Size: 1240 bytes
```

---

## ⚠️ Legal Disclaimer

**ShadowSniff is strictly for educational purposes.** Sniffing network traffic on networks you do not own or have explicit permission to audit is illegal and punishable by law. The author accepts no responsibility for any misuse of this software.

---

## 📝 License

Distributed under the MIT License. See `LICENSE` for more information.
