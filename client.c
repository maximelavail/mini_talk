#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int g_bit_index = 0;

// Fonction pour envoyer un bit à un processus avec le signal approprié
void send_bit(int pid, int bit) {
    if (bit)
        kill(pid, SIGUSR1);
    else
        kill(pid, SIGUSR2);
    usleep(50);  // Attente courte pour synchroniser les signaux
}

// Fonction pour envoyer un caractère (8 bits) à un processus
void send_char(int pid, char c) {
    g_bit_index = 0;
    while (g_bit_index < 8) {
        send_bit(pid, (c >> g_bit_index) & 1);
        g_bit_index++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        return 1;
    }

    int server_pid = atoi(argv[1]);
    char *message = argv[2];

    // Envoi du message caractère par caractère
    int i = 0;
    while (message[i] != '\0') {
        send_char(server_pid, message[i]);
        i++;
    }

    // Envoi du caractère de fin
    send_char(server_pid, '\0');
    return 0;
}
