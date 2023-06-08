#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct Articulo {
    int numero;
    float precio;
    string nombre;
    string descripcion;
    string clasificacion;
    string genero;
    string consola;
    float total;
    string status;
};

vector<Articulo> articulos;

void alta();
void listas();
void archivo();
void baja();
void modificar();

int main()
{
    int opcion;
    printf("\t ***MENU DE OPCIONES***\n");
    printf("1.- Alta de Articulos\n");
    printf("2.- Baja de Articulos\n");
    printf("3.- Modificacion de Articulo\n");
    printf("4.- Lista de Articulos\n");
    printf("5.- Limpiar Pantalla\n");
    printf("6.- Salir\n");
    printf("\nSeleccion:");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        alta();
        return main();
        break;
    case 2:
        baja();
        return main();
        break;
    case 3:
        modificar();
        return main();
        break;
    case 4:
        listas();
        return main();
        break;
    case 5:
        system("cls");
        return main();
        break;
    case 6:
        archivo();
        break;
    }

    return 0;
}

void alta()
{
    int numArticulo;
    printf("Digite el numero de articulos que desea registrar:\n");
    scanf("%d", &numArticulo);
    getchar();

    for (int i = 0; i < numArticulo; i++)
    {
        Articulo nuevoArticulo;
        printf("Numero de Articulo:\n");
        scanf("%d", &nuevoArticulo.numero);
        getchar();


        bool repetido = false;
        for (const Articulo& articulo : articulos)
        {
            if (articulo.numero == nuevoArticulo.numero)
            {
                repetido = true;
                break;
            }
        }

        if (repetido)
        {
            printf("El numero de articulo ya ha sido ingresado. Por favor, ingrese otro numero.\n");
            i--;
            continue;
        }

        printf("Nombre de Articulo:\n");
        getline(cin, nuevoArticulo.nombre);
        printf("Precio Unitario:\n");
        scanf("%f", &nuevoArticulo.precio);
        getchar();
        printf("Descripcion:\n");
        getline(cin, nuevoArticulo.descripcion);
        printf("Clasificacion:\n");
        getline(cin, nuevoArticulo.clasificacion);
        printf("Genero:\n");
        getline(cin, nuevoArticulo.genero);
        printf("Consola:\n");
        getline(cin, nuevoArticulo.consola);
        nuevoArticulo.total = nuevoArticulo.precio * 1.16;
        nuevoArticulo.status = "ACTIVO";

        articulos.push_back(nuevoArticulo);
    }
}

void listas()
{
    for (int i = 0; i < articulos.size(); i++)
    {
        if (articulos[i].status == "ELIMINADO")
        {
            printf("REGISTRO ELIMINADO %d\n", i + 1);
        }
        else
        {
            printf("Numero de Articulo: %d\n", articulos[i].numero);
            printf("Nombre de Articulo: %s\n", articulos[i].nombre.c_str());
            printf("Precio Unitario: %.2f\n", articulos[i].precio);
            printf("Descripcion: %s\n", articulos[i].descripcion.c_str());
            printf("Clasificacion: %s\n", articulos[i].clasificacion.c_str());
            printf("Genero: %s\n", articulos[i].genero.c_str());
            printf("Consola: %s\n", articulos[i].consola.c_str());
            printf("Precio con IVA: %.2f\n", articulos[i].total);
            printf("Status: %s\n\n", articulos[i].status.c_str());
        }
    }
}

void archivo()
{
    ofstream archivo;
    string nombrearchivo;
    int texto;
    string texto2;

    nombrearchivo = "La cueva del gamer.txt";

    archivo.open(nombrearchivo.c_str(), ios::out);

    if (archivo.fail())
    {
        printf("ERROR NO SE PUDO CREAR EL ARCHIVO\n");
        exit(1);
    }

    archivo << "NUMERO DE ARTICULO\t";
    archivo << "NOMBRE\t";
    archivo << "PRECIO UNITARIO\t";
    archivo << "DESCRIPCION\t";
    archivo << "CLASIFICACION\t";
    archivo << "GENERO\t";
    archivo << "CONSOLA\t";
    archivo << "PRECIO CON IVA\t";
    archivo << "STATUS\n";

    for (int i = 0; i < articulos.size(); i++)
    {
        if (articulos[i].status == "ELIMINADO")
        {
            texto2 = "REGISTRO ELIMINADO ";
            texto = i;
            archivo << texto2 << texto << "\n";
        }
        else
        {
            texto = articulos[i].numero;
            archivo << setw(18) << texto << "\t";
            texto2 = articulos[i].nombre;
            archivo << setw(7) << texto2 << "\t";
            texto = articulos[i].precio;
            archivo << setw(15) << fixed << setprecision(2) << texto << "\t";
            texto2 = articulos[i].descripcion;
            archivo << setw(13) << texto2 << "\t";
            texto2 = articulos[i].clasificacion;
            archivo << setw(15) << texto2 << "\t";
            texto2 = articulos[i].genero;
            archivo << setw(9) << texto2 << "\t";
            texto2 = articulos[i].consola;
            archivo << setw(8) << texto2 << "\t";
            texto = articulos[i].total;
            archivo << setw(14) << fixed << setprecision(2) << texto << "\t";
            archivo << articulos[i].status << "\n";
        }
    }

    archivo.close();

    printf("Archivo generado exitosamente.\n");
}

void baja()
{
    int numArticulo;
    printf("Digite el numero de articulo que desea eliminar:\n");
    scanf("%d", &numArticulo);
    getchar();

    bool encontrado = false;
    for (int i = 0; i < articulos.size(); i++)
    {
        if (articulos[i].numero == numArticulo)
        {
            articulos[i].status = "ELIMINADO";
            encontrado = true;
            break;
        }
    }

    if (encontrado)
    {
        printf("Articulo eliminado exitosamente.\n");
    }
    else
    {
        printf("No se encontró un articulo con el numero especificado.\n");
    }
}

void modificar()
{
    int numArticulo;
    printf("Digite el numero de articulo que desea modificar:\n");
    scanf("%d", &numArticulo);
    getchar();

    bool encontrado = false;
    for (int i = 0; i < articulos.size(); i++)
    {
        if (articulos[i].numero == numArticulo)
        {
            Articulo& articulo = articulos[i];

            printf("Numero de Articulo:\n");
            scanf("%d", &articulo.numero);
            getchar();


            bool repetido = false;
            for (const Articulo& a : articulos)
            {
                if (&a != &articulo && a.numero == articulo.numero)
                {
                    repetido = true;
                    break;
                }
            }

            if (repetido)
            {
                printf("El numero de articulo ya ha sido ingresado. Por favor, ingrese otro numero.\n");
                return;
            }

            printf("Nombre de Articulo:\n");
            getline(cin, articulo.nombre);
            printf("Precio Unitario:\n");
            scanf("%f", &articulo.precio);
            getchar();
            printf("Descripcion:\n");
            getline(cin, articulo.descripcion);
            printf("Clasificacion:\n");
            getline(cin, articulo.clasificacion);
            printf("Genero:\n");
            getline(cin, articulo.genero);
            printf("Consola:\n");
            getline(cin, articulo.consola);
            articulo.total = articulo.precio * 1.16;

            encontrado = true;
            break;
        }
    }

    if (encontrado)
    {
        printf("Articulo modificado exitosamente.\n");
    }
    else
    {
        printf("No se encontró un articulo con el numero especificado.\n");
    }
}