#include "PaquetePedido.hpp"

bool PaquetePedido::operator<=(const PaquetePedido &other) const { return this->numero_pedido <= other.numero_pedido; }
bool PaquetePedido::operator>=(const PaquetePedido &other) const { return this->numero_pedido >= other.numero_pedido; }
bool PaquetePedido::operator<( const PaquetePedido &other) const { return this->numero_pedido <  other.numero_pedido; }
bool PaquetePedido::operator>( const PaquetePedido &other) const { return this->numero_pedido >  other.numero_pedido; }
bool PaquetePedido::operator==(const PaquetePedido &other) const { return this->numero_pedido == other.numero_pedido; }
bool PaquetePedido::operator!=(const PaquetePedido &other) const { return this->numero_pedido != other.numero_pedido; }

PaquetePedido::PaquetePedido():numero_pedido(++next_numero_pedido){}
PaquetePedido::PaquetePedido( string nombre_remitente, string nombre_destinatario, string estado_envio, string destino_direccion ):
    numero_pedido(++next_numero_pedido), 
    nombre_remitente(nombre_remitente),nombre_destinatario(nombre_destinatario), 
    estado_envio(estado_envio),destino_direccion(destino_direccion){}
PaquetePedido::PaquetePedido(const PaquetePedido& other):
    numero_pedido(other.numero_pedido), 
    nombre_remitente(nombre_remitente),nombre_destinatario(nombre_destinatario),
    estado_envio(estado_envio),destino_direccion(destino_direccion){}
