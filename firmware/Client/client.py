import socket

# Imposta l'indirizzo IP dell'ESP8266 e la porta del server (porta 80)
esp8266_ip = '192.168.1.100'  # Sostituisci con l'indirizzo IP del tuo ESP8266
port = 80

# Crea una connessione socket TCP
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connessione al server ESP8266
    client_socket.connect((esp8266_ip, port))
    print(f"Connesso a {esp8266_ip}:{port}")

    while True:
        # Riceve i dati inviati dall'ESP8266
        data = client_socket.recv(1024)  # Riceve fino a 1024 byte di dati
        if data:
            print("Dati ricevuti:", data.decode('utf-8'))
        else:
            print("Connessione chiusa dal server.")
            break

except Exception as e:
    print(f"Errore di connessione: {e}")

finally:
    # Chiude il socket alla fine
    client_socket.close()
    print("Connessione chiusa.")
