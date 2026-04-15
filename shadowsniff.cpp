#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>  // IP Header yapısı için
#include <netinet/tcp.h> // TCP Header yapısı için
#include <arpa/inet.h>
#include <unistd.h>

// Renkler
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

using namespace std;

void startSniffing() {
    int sock_raw;
    struct sockaddr_in saddr;
    unsigned char *buffer = (unsigned char *)malloc(65536); // Paketleri tutacak bellek alanı
    
    // 1. Raw Socket Oluşturma (AF_INET, SOCK_RAW, IPPROTO_TCP)
    // Bu işlem sadece ROOT yetkisiyle çalışır.
    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    
    if (sock_raw < 0) {
        perror("Socket Error");
        cout << RED << "[!] Hata: Raw Socket açılamadı. 'sudo' ile çalıştırdın mı?" << RESET << endl;
        return;
    }

    cout << GREEN << "[*] ShadowSniff Başlatıldı. TCP Paketleri izleniyor..." << RESET << endl;
    cout << "-----------------------------------------------------------" << endl;

    while (true) {
        socklen_t saddr_size = sizeof(saddr);
        
        // 2. Paketi Yakala
        int data_size = recvfrom(sock_raw, buffer, 65536, 0, (struct sockaddr *)&saddr, &saddr_size);
        
        if (data_size < 0) {
            cout << RED << "[!] Paket okuma hatası." << RESET << endl;
            return;
        }

        // 3. IP Başlığını (Header) Ayıkla
        // Buffer'ın başlangıcı IP başlığıdır.
        struct iphdr *iph = (struct iphdr *)buffer;
        
        // IP Başlığının uzunluğunu hesapla (TCP başlığına geçmek için lazım)
        unsigned short iphdrlen = iph->ihl * 4;

        // 4. TCP Başlığını Ayıkla
        // Buffer + IP Header Uzunluğu = TCP Header Başlangıcı
        struct tcphdr *tcph = (struct tcphdr *)(buffer + iphdrlen);

        // 5. Bilgileri Ekrana Bas
        // Kaynak IP ve Port -> Hedef IP ve Port
        
        // Sadece HTTP (80) veya HTTPS (443) trafiğini vurgulayalım
        string color = CYAN;
        if (ntohs(tcph->dest) == 80 || ntohs(tcph->dest) == 443) {
            color = YELLOW; // Web trafiği sarı olsun
        }

        struct in_addr source_ip, dest_ip;
        source_ip.s_addr = iph->saddr;
        dest_ip.s_addr = iph->daddr;

        cout << color << "[TCP] " 
             << inet_ntoa(source_ip) << ":" << ntohs(tcph->source) 
             << " -> " 
             << inet_ntoa(dest_ip) << ":" << ntohs(tcph->dest) 
             << " | Boyut: " << data_size << " bytes" 
             << RESET << endl;
    }
    
    close(sock_raw);
}

int main() {
    // Root kontrolü
    if (getuid() != 0) {
        cout << RED << "[!] UYARI: Bu program ROOT yetkisi gerektirir." << RESET << endl;
        cout << "Lütfen 'sudo ./shadowsniff' komutuyla çalıştırın." << endl;
        return 1;
    }

    cout << R"(
   _____ __               __            _____       _  __  __
  / ___// /_  ____ ______/ /___      __/ ___/____  (_)/ /_/ /
  \__ \/ __ \/ __ `/ __  / __ \ | /| / /\__ \/ __ \/ / / __/ 
 ___/ / / / / /_/ / /_/ / /_/ / |/ |/ /___/ / / / / / / /_   
/____/_/ /_/\__,_/\__,_/\____/|__/|__//____/_/ /_/_/_/\__/   
    )" << endl;

    startSniffing();
    return 0;
}
