#include <algorithm>
#include <fstream> // Para Base de Datos (Archivos)
#include <iostream>
#include <sstream>
#include <stdexcept> // Para Excepciones
#include <string>
#include <vector>

using namespace std;

// ==========================================
// 1. EXCEPCIONES PERSONALIZADAS
// ==========================================
class ErrorBaseDatos : public runtime_error {
public:
  ErrorBaseDatos(const string &msg) : runtime_error("Error BD: " + msg) {}
};

class DatoInvalido : public invalid_argument {
public:
  DatoInvalido(const string &msg) : invalid_argument("Dato Invalido: " + msg) {}
};

class VehiculoNoEncontrado : public runtime_error {
public:
  VehiculoNoEncontrado()
      : runtime_error("El vehiculo solicitado no existe en el sistema.") {}
};

// ==========================================
// 2. CLASES COMPONENTES (Rúbrica: Composición)
// ==========================================
class Motor {
  string numeroSerie;
  int cilindrada;

public:
  Motor(string n, int c) : numeroSerie(n), cilindrada(c) {}
  string getDetalles() const {
    return "Motor V" + to_string(cilindrada) + "cc #" + numeroSerie;
  }
};

// ==========================================
// 3. CLASES ABSTRACTAS Y HERENCIA (Rúbrica: Abstracta, Herencia)
// ==========================================

// Interfaz para funcionalidad eléctrica (Para herencia múltiple)
class IElectrico {
public:
  virtual string getNivelBateria() const = 0;
};

// Clase Base Abstracta
class Vehiculo {
protected:
  string patente;
  string modelo;
  string anio;
  Motor motor; // COMPOSICIÓN: El vehículo "posee" un motor

public:
  Vehiculo(string p, string m, string a, string nMotor, int cc)
      : patente(p), modelo(m), anio(a), motor(nMotor, cc) {}

  virtual ~Vehiculo() {} // Destructor virtual importante

  string getPatente() const { return patente; }

  // Rúbrica: Método Virtual Puro (Clase Abstracta)
  virtual void mostrarInfo() const = 0;

  // Rúbrica: Sobrecarga de Operadores (<<)
  friend ostream &operator<<(ostream &os, const Vehiculo &v) {
    os << "[" << v.patente << "] " << v.modelo << " - " << v.anio << " - "
       << v.motor.getDetalles();
    return os;
  }
};

// Clase Derivada 1
class Auto : public Vehiculo {
  int puertas;

public:
  Auto(string p, string m, string a, string nM, int cc, int puertas)
      : Vehiculo(p, m, a, nM, cc), puertas(puertas) {}

  // Rúbrica: Sobreescritura de métodos
  void mostrarInfo() const override {
    cout << "Tipo: AUTO | " << *this << " | Puertas: " << puertas << endl;
  }
};

// Clase Derivada 2
class Moto : public Vehiculo {
  bool tieneCajon;

public:
  Moto(string p, string m, string a, string nM, int cc, bool cajon)
      : Vehiculo(p, m, a, nM, cc), tieneCajon(cajon) {}

  void mostrarInfo() const override {
    cout << "Tipo: MOTO | " << *this
         << " | Cajon: " << (tieneCajon ? "Si" : "No") << endl;
  }
};

// Clase con Herencia Múltiple (Rúbrica: Herencia Múltiple)
class AutoHibrido : public Auto, public IElectrico {
  int porcentajeBateria;

public:
  AutoHibrido(string p, string m, string a, string nM, int cc, int puertas,
              int bateria)
      : Auto(p, m, a, nM, cc, puertas), porcentajeBateria(bateria) {}

  string getNivelBateria() const override {
    return to_string(porcentajeBateria) + "%";
  }

  void mostrarInfo() const override {
    cout << "Tipo: HIBRIDO | " << patente << " | Bat: " << getNivelBateria()
         << endl;
  }
};

// ==========================================
// 4. GESTIÓN Y AGREGACIÓN
// ==========================================
class Cliente {
  string rut;
  string nombre;
  string apellido;
  string telefono;
  string direccion;
  // AGREGACIÓN: El cliente tiene vehículos, pero los vehículos son entidades
  // propias
  vector<Vehiculo *> misVehiculos;

public:
  Cliente(string r, string n, string a, string t, string d)
      : rut(r), nombre(n), apellido(a), telefono(t), direccion(d) {}

  string getRut() const { return rut; }
  string getNombre() const { return nombre; }
  string getApellido() const { return apellido; }
  string getTelefono() const { return telefono; }
  string getDireccion() const { return direccion; }

  // Rúbrica: Sobrecarga de métodos (Agregar vehículo existente vs nuevo)
  void agregarVehiculo(Vehiculo *v) { misVehiculos.push_back(v); }

  void mostrarCliente() const {
    cout << "Cliente: " << nombre << " " << apellido << " (RUT: " << rut << ")"
         << "\n   Tel: " << telefono << " | Dir: " << direccion << endl;
    for (auto v : misVehiculos) {
      cout << "   -> ";
      v->mostrarInfo();
    }
  }

  string serializar() const {
    return rut + ";" + nombre + ";" + apellido + ";" + telefono + ";" +
           direccion;
  }
};

// ==========================================
// 5. BASE DE DATOS (Rúbrica: Insertar, Modificar, Eliminar, Consultar)
// ==========================================
// Simularemos la BD usando archivos de texto para persistencia
class BaseDatos {
  string archivoDB;

public:
  BaseDatos(string archivo) : archivoDB(archivo) {}

  void insertar(const Cliente &c) {
    ofstream file(archivoDB, ios::app);
    if (!file.is_open())
      throw ErrorBaseDatos("No se pudo abrir la BD para escribir.");
    file << c.serializar() << endl;
    file.close();
  }

  vector<string> consultarTodos() {
    vector<string> registros;
    ifstream file(archivoDB);
    if (!file.is_open())
      return registros; // Si no existe, retorna vacío

    string linea;
    while (getline(file, linea)) {
      registros.push_back(linea);
    }
    file.close();
    return registros;
  }

  // Método "Dummy" para simular eliminación física en archivo
  // (En un sistema real SQL sería 'DELETE FROM...')
  void eliminarPorRut(string rut) {
    vector<string> datos = consultarTodos();
    ofstream file(archivoDB, ios::trunc); // Sobreescribir
    bool eliminado = false;
    for (const string &linea : datos) {
      if (linea.find(rut) == string::npos) { // Si no es el RUT a borrar
        file << linea << endl;
      } else {
        eliminado = true;
      }
    }
    file.close();
    if (!eliminado)
      throw DatoInvalido("RUT no encontrado para eliminar.");
  }
};

// ==========================================
// 6. CONTROLADOR PRINCIPAL DEL TALLER
// ==========================================
class Taller {
  vector<Cliente *> clientes;
  BaseDatos db;

public:
  Taller() : db("clientes_db.txt") { cargarDatos(); }

  void cargarDatos() {
    // Carga simple desde "BD"
    vector<string> rawData = db.consultarTodos();
    for (const string &s : rawData) {
      stringstream ss(s);
      string rut, nombre, apellido, telefono, direccion;
      getline(ss, rut, ';');
      getline(ss, nombre, ';');
      getline(ss, apellido, ';');
      getline(ss, telefono, ';');
      getline(ss, direccion, ';');
      if (!rut.empty())
        clientes.push_back(
            new Cliente(rut, nombre, apellido, telefono, direccion));
    }
  }

  void registrarCliente(string rut, string nombre, string apellido,
                        string telefono, string direccion) {
    if (rut.length() < 8)
      throw DatoInvalido("El RUT es muy corto.");
    Cliente *nuevo = new Cliente(rut, nombre, apellido, telefono, direccion);
    clientes.push_back(nuevo);
    db.insertar(*nuevo); // Persistencia
    cout << ">> Cliente registrado exitosamente en BD." << endl;
  }

  void listarClientes() {
    cout << "\n--- LISTA DE CLIENTES ---" << endl;
    if (clientes.empty())
      cout << "No hay clientes registrados." << endl;
    for (auto c : clientes) {
      c->mostrarCliente();
    }
    cout << "-------------------------" << endl;
  }

  void eliminarCliente(string rut) {
    // Eliminar de memoria
    auto it = remove_if(clientes.begin(), clientes.end(),
                        [&rut](Cliente *c) { return c->getRut() == rut; });

    if (it != clientes.end()) {
      clientes.erase(it, clientes.end());
      // Eliminar de BD
      db.eliminarPorRut(rut);
      cout << ">> Cliente eliminado." << endl;
    } else {
      throw DatoInvalido("Cliente no encontrado en memoria.");
    }
  }

  // Agregar un vehiculo a un cliente existente
  void agregarVehiculoACliente(string rutCliente, Vehiculo *v) {
    if (rutCliente.length() < 8)
      throw DatoInvalido("El RUT ingresado no es valido (muy corto).");

    bool encontrado = false;
    for (auto c : clientes) {
      if (c->getRut() == rutCliente) {
        c->agregarVehiculo(v);
        encontrado = true;
        break;
      }
    }
    if (!encontrado)
      throw DatoInvalido("Cliente no existe, registrelo primero.");
  }

  bool existeCliente(string rut) {
    for (auto c : clientes) {
      if (c->getRut() == rut)
        return true;
    }
    return false;
  }
};

// ==========================================
// 7. INTERFAZ GRÁFICA (Consola UI)
// ==========================================
void mostrarMenu() {
  cout << "\n=== SISTEMA TALLER MECANICO ===" << endl;
  cout << "1. Registrar Cliente" << endl;
  cout << "2. Agregar Auto a Cliente" << endl;
  cout << "3. Agregar Moto a Cliente" << endl;
  cout << "4. Ver Todo (Consultar BD)" << endl;
  cout << "5. Eliminar Cliente" << endl;
  cout << "6. Salir" << endl;
  cout << "Seleccione: ";
}

int main() {
  Taller miTaller;
  int opcion;

  do {
    mostrarMenu();
    if (!(cin >> opcion)) { // Validación básica de entrada
      cout << "Entrada invalida." << endl;
      cin.clear();
      cin.ignore(1000, '\n');
      continue;
    }

    try {
      if (opcion == 1) {
        string r, n, a, t, d;
        cout << "Ingrese RUT: ";
        cin >> r;
        cout << "Ingrese Nombre: ";
        cin.ignore();
        getline(cin, n);
        cout << "Ingrese Apellido: ";
        getline(cin, a);
        cout << "Ingrese telefono: ";
        getline(cin, t);
        cout << "Ingrese direccion: ";
        getline(cin, d);
        miTaller.registrarCliente(r, n, a, t, d);
      } else if (opcion == 2) {
        string r, p, m, anio, nm;
        int cc, pt;
        cout << "RUT del Dueño: ";
        cin >> r;
        if (r.length() < 8)
          throw DatoInvalido("El RUT es muy corto.");
        if (!miTaller.existeCliente(r))
          throw DatoInvalido("Cliente no existe, registrelo primero.");

        cout << "Patente: ";
        cin >> p;
        cout << "Modelo: ";
        cin >> m;
        cout << "Año: ";
        cin >> anio;
        cout << "Serie Motor: ";
        cin >> nm;
        cout << "CC Motor: ";
        cin >> cc;
        cout << "Puertas: ";
        cin >> pt;
        // Polimorfismo: Guardamos un Auto como Vehiculo*
        miTaller.agregarVehiculoACliente(r, new Auto(p, m, anio, nm, cc, pt));
        cout << ">> Auto agregado." << endl;
      } else if (opcion == 3) {
        string r, p, m, anio, nm;
        int cc;
        bool cajon;
        cout << "RUT del Dueño: ";
        cin >> r;
        if (r.length() < 8)
          throw DatoInvalido("El RUT es muy corto.");
        if (!miTaller.existeCliente(r))
          throw DatoInvalido("Cliente no existe, registrelo primero.");

        cout << "Patente: ";
        cin >> p;
        cout << "Modelo: ";
        cin >> m;
        cout << "Año: ";
        cin >> anio;
        cout << "Serie Motor: ";
        cin >> nm;
        cout << "CC Motor: ";
        cin >> cc;
        cout << "¿Tiene cajon? (1:Si / 0:No): ";
        cin >> cajon;
        miTaller.agregarVehiculoACliente(r,
                                         new Moto(p, m, anio, nm, cc, cajon));
        cout << ">> Moto agregada." << endl;
      } else if (opcion == 4) {
        miTaller.listarClientes();
      } else if (opcion == 5) {
        string r;
        cout << "RUT a eliminar: ";
        cin >> r;
        miTaller.eliminarCliente(r);
      }

    } catch (const ErrorBaseDatos &e) {
      cerr << "[ERROR CRITICO] " << e.what() << endl;
    } catch (const DatoInvalido &e) {
      cerr << "[ADVERTENCIA] " << e.what() << endl;
    } catch (const exception &e) {
      cerr << "[ERROR] " << e.what() << endl;
    }

  } while (opcion != 6);

  cout << "Cerrando sistema..." << endl;
  return 0;
}