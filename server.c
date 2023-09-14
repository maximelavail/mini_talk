#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t g_bit_count = 0;
volatile sig_atomic_t g_received_char = 0;

void handler(int sig) {
    if (sig == SIGUSR1) {
        g_received_char |= (1 << g_bit_count);
    }

    g_bit_count++;

    if (g_bit_count == 8) {
        if (g_received_char == '\0') {
            write(1, "\n", 1);  // Affichage d'une nouvelle ligne
            exit(0);
        } else {
            unsigned char char_to_write = g_received_char;  // Copie de la valeur volatile
            write(1, &char_to_write, 1);  // Affichage du caractère
            g_received_char = 0;
            g_bit_count = 0;
        }
    }
}

int main(void) {
    printf("Server PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // Configuration des signaux
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1) {
        // Utilisation de pause() pour attendre les signaux
        pause();
    }

    return 0;
}
