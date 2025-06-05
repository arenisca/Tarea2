#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Cliente {
    string nombre;
    int numero;
};

int main() {
    queue<Cliente> filaClientes;

    filaClientes.push({"Pedro", 1});
    filaClientes.push({"Seba", 2});
    filaClientes.push({"Lizandro", 3});

    cout << "Ultimo cliente en la fila:" << filaClientes.back().nombre << endl;

    cout << "Estado inicial de la fila de clientes:" << endl;
    while (!filaClientes.empty()) {
        cout << "Cliente " << filaClientes.front().nombre << " (Número " << filaClientes.front().numero << ")" << endl;
        filaClientes.pop();
    }

    filaClientes.push({"Tomás", 4});
    filaClientes.push({"Franche", 5});

    while (!filaClientes.empty()) {
        cout << "Cliente " << filaClientes.front().nombre << " (Número " << filaClientes.front().numero << ")" << endl;
        filaClientes.pop();
    }

    return 0;
}