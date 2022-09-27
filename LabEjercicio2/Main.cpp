#include "ListaAlquileres.h"
#include "ListaCoches.h"


int main()
{
    ListaCoches lc = ListaCoches();
    bool leidoLc = lc.cargarCoches();

    if (leidoLc) std::cout << "\nLEIDO COCHES.TXT\n";
    else std::cout << "\nNO LEIDO COCHES.TXT\n";

    ListaAlquileres la = ListaAlquileres();
    bool leidoLa = la.leerAlquileres(lc);

    if (leidoLa) std::cout << "\nLEIDO ALQUILERES.TXT\n";
    else std::cout << "\nNO LEIDO ALQUILERES.TXT\n";

    la.mostrarAlquileres();
}