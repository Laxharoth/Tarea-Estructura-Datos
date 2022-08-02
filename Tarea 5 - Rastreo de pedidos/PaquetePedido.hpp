#ifndef PAQUETE_PEDIDO_HPP
#define PAQUETE_PEDIDO_HPP

#include <string>
using std::string;

static long long next_numero_pedido = 0;

struct PaquetePedido{
    string nombre_remitente;
    string nombre_destinatario;
    string estado_envio;
    string destino_direccion;
    PaquetePedido();
    PaquetePedido(long long numero_pedido);
    PaquetePedido(
        string nombre_remitente,
        string nombre_destinatario,
        string estado_envio,
        string destino_direccion
    );
    PaquetePedido(const PaquetePedido& other);
    bool operator<=(const PaquetePedido &other) const;
    bool operator>=(const PaquetePedido &other) const;
    bool operator<(const PaquetePedido &other) const;
    bool operator>(const PaquetePedido &other) const;
    bool operator==(const PaquetePedido &other) const;
    bool operator!=(const PaquetePedido &other) const;
    long long numero_pedido;
};

#endif