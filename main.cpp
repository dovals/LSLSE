#include <iostream>

struct SocioClub {
    int NumeroSocio;
    std::string NombreSocio;
    std::string domicilio;
    int AnioIngreso;
};

template<class T>
class LSLSE;

template<class T>
class node{
private:
    T data;
    node<T>* sig;
public:
    node():sig(nullptr){};
    friend class LSLSE<T>;
};

template<class T>
class LSLSE{
private:
    node<T>* lista;
public:
    LSLSE():lista(nullptr){};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir()const;
    void agregarUsuario(int NumeroSocio, std::string NombreSocio, std::string domicilio, int AnioIngreso);
    bool BajaSocio(int NumeroSocio);
    void GenerarReporte() const;
    void BuscarSocio(std::string NombreSocio, std::string domicilio)const;
    int TotalDeSocios();
    void ordenar();
};

template<class T>
void LSLSE<T>::imprimir()const{
    node<T>* aux=lista;
    while(aux!=nullptr){
        std::cout<<aux->data.NumeroSocio<<", "<<aux->data.NombreSocio<<", "<<aux->data.domicilio<<", "<<aux->data.AnioIngreso<<" -> \n";
        aux=aux->sig;
    }
}

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
    }
    if(pos==lista){
        lista=lista->sig;
    }
    else{
        anterior(pos)->sig=pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem){
    node<T>* aux= new node<T>;
    aux->data=elem;
    if(pos==nullptr){
        aux->sig=lista;
        lista=aux;
    }
    else{
        aux->sig=pos->sig;
        pos->sig=aux;
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}


template<class T>
node<T>* LSLSE<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux->sig!=nullptr){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
bool LSLSE<T>::vacia()const{
    if(lista==nullptr)
        return true;
    return false;
}

template<class T>
void LSLSE<T>::agregarUsuario(int NumeroSocio, std::string NombreSocio, std::string domicilio, int AnioIngreso) {
    SocioClub u;
    u.NumeroSocio = NumeroSocio;
    u.NombreSocio = NombreSocio;
    u.domicilio = domicilio;
    u.AnioIngreso = AnioIngreso;

    node<T>* aux=lista;
    while (aux != nullptr) {
        if (aux->data.NumeroSocio == NumeroSocio) {
            std::cout << "El numero de socio ya existe." << std::endl;
            return;
        }
        aux = aux->sig;
    }

    insertar(ultimo(), u);
    ordenar();

}

template<class T>
bool LSLSE<T>::BajaSocio(int NumeroSocio){
    node<T>* aux=lista;
    node<T>* anterior=nullptr;
    while(aux!=nullptr){
        if(aux->data.NumeroSocio==NumeroSocio){
            if(anterior==nullptr){
                lista=aux->sig;
            }
            else{
                anterior->sig=aux->sig;
            }
            delete aux;
            return true;
        }
        anterior=aux;
        aux=aux->sig;
    }
    return false;
}

template<class T>
void LSLSE<T>::GenerarReporte()const{
    node<T>* aux=lista;
    while(aux!=nullptr){
        std::cout<<"Numero del Socio: "<<aux->data.NumeroSocio<<"\nNombre: "<<aux->data.NombreSocio<<"\nDomicilio: "<<aux->data.domicilio<<"\nAnio de Ingreso: "<<aux->data.AnioIngreso<<"\n----------------------------\n";
        aux=aux->sig;
    }
}

template<class T>
void LSLSE<T>::BuscarSocio(std::string nombre, std::string domicilio) const {
    node<T>* aux = lista;
    bool encontrado = false;
    while (aux != nullptr) {
        if (aux->data.NombreSocio == nombre && aux->data.domicilio == domicilio) {
            std::cout << "Socio encontrado: \n";
            std::cout << "Numero de Socio: " << aux->data.NumeroSocio << std::endl;
            std::cout << "Nombre: " << aux->data.NombreSocio << std::endl;
            std::cout << "Domicilio: " << aux->data.domicilio << std::endl;
            std::cout << "Año de Ingreso: " << aux->data.AnioIngreso << std::endl;
            encontrado = true;
        }
        aux = aux->sig;
    }
    if (!encontrado) {
        std::cout << "No se encontró al socio con nombre " << nombre << " y domicilio " << domicilio << std::endl;
    }
}

template<class T>
int LSLSE<T>::TotalDeSocios(){
    node<T>* aux=lista;
    int cont = 0;
    while(aux!=nullptr){
        cont++;
        aux=aux->sig;
    }
    return cont;
}

template<class T>
void LSLSE<T>::ordenar() {
    node<T>* aux = lista;
    LSLSE<T> nueva_lista;
    while (aux != nullptr) {
        node<T>* pos = nueva_lista.primero();
        node<T>* ant = nullptr;
        while (pos != nullptr && pos->data.NumeroSocio < aux->data.NumeroSocio) {
            ant = pos;
            pos = pos->sig;
        }
        if (ant == nullptr) {
            nueva_lista.insertar(nullptr, aux->data);
        } else {
            nueva_lista.insertar(ant, aux->data);
        }
        aux = aux->sig;
    }
    lista = nueva_lista.primero();
}

int main()
{
    LSLSE<SocioClub> milista;
    int opc,NumeroSocio,AnioIngreso;
    std::string NombreSocio,domicilio;
    while(opc <= 6)
    {
        std::cout<<"1.-Agregar un nuevo Socio\n2.-Dar de baja a un Socio\n3.-Generar reportes de todos los socios\n4.-Buscar por nombre y domicilio\n5.-Calcular e imprimir el total de  socios registrados\n6.-Salir"<<std::endl;
        std::cin>>opc;
        system("cls");
        switch(opc)
        {
            case 1://agregar usuario
                std::cout<<"Ingrese el Numero de Socio"<<std::endl;
                std::cin>>NumeroSocio;
                std::cout<<"Ingrese el Nombre del Socio"<<std::endl;
                std::cin>>NombreSocio;
                std::cout<<"Ingrese el Domicilio del Socio"<<std::endl;
                std::cin>>domicilio;
                std::cout<<"Ingrese el Anio de Ingreso del Socio"<<std::endl;
                std::cin>>AnioIngreso;
                milista.agregarUsuario(NumeroSocio,NombreSocio,domicilio,AnioIngreso);
            break;

            case 2://dar de baja
                std::cout<<"Ingrese el Numero de Socio a dar de baja"<<std::endl;
                std::cin>>NumeroSocio;
                milista.BajaSocio(NumeroSocio);
            break;

            case 3://generar un reporte
                if(milista.vacia())
                {
                    std::cout<<"Lista vacia, favor de agregar Socios\n"<<std::endl;

                }
                else
                {
                   milista.GenerarReporte();
                }

            break;

            case 4://buscar por nombre y domicilio
                std::cout<<"Ingrese el Nombre del Socio"<<std::endl;
                std::cin>>NombreSocio;
                std::cout<<"Ingrese el Domicilio del Socio"<<std::endl;
                std::cin>>domicilio;
                milista.BuscarSocio(NombreSocio,domicilio);
            break;

            case 5://calcular e imprimir el total de  socios registrados
                std::cout<<"Total de Socios:"<<milista.TotalDeSocios()<<std::endl;
            break;

            case 6://salir del programa
                std::cout<<"Hasta Luego"<<std::endl;
                exit(0);
            break;

            default:
                std::cout<<"opcion invalida"<<std::endl;
            break;
        }
    }
    return 0;
}

