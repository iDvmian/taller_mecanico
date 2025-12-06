# 💻 EJEMPLOS DE CÓDIGO - CONCEPTOS OOP

## 1️⃣ CLASE ABSTRACTA

### Definición - vehiculo.h (líneas 27-57)
```cpp
class Vehiculo {
protected:
    int id;
    int clienteId;
    QString patente;
    QString modelo;
    int anio;
    Motor motor;  // COMPOSICIÓN

public:
    Vehiculo();
    Vehiculo(int clienteId, const QString &patente, const QString &modelo, int anio, const Motor &motor);
    virtual ~Vehiculo() = default;

    // MÉTODOS VIRTUALES PUROS - Hacen la clase abstracta
    virtual QString getTipo() const = 0;
    virtual QString getInfoAdicional() const = 0;
    
    // Métodos normales
    int getId() const;
    QString getPatente() const;
    
    // SOBRECARGA DE OPERADORES
    bool operator==(const Vehiculo &otro) const;
    bool operator!=(const Vehiculo &otro) const;
};
```

### ¿Por qué es abstracta?
- Tiene métodos **virtuales puros** (`= 0`)
- **No se puede** instanciar directamente
- **Obliga** a las clases hijas a implementar estos métodos

---

## 2️⃣ HERENCIA SIMPLE

### Auto hereda de Vehiculo - auto.h
```cpp
class Auto : public Vehiculo {
private:
    int numeroPuertas;

public:
    Auto();
    Auto(int clienteId, const QString &patente, const QString &modelo, 
         int anio, const Motor &motor, int puertas);

    // SOBREESCRITURA de métodos virtuales puros (POLIMORFISMO)
    QString getTipo() const override;
    QString getInfoAdicional() const override;
    
    // SOBRECARGA DE MÉTODOS
    void mostrarInfo() const;
    void mostrarInfo(bool detallado) const;
    
    int getNumeroPuertas() const;
};
```

### Implementación - auto.cpp
```cpp
// Constructor llama al constructor de la clase base
Auto::Auto(int clienteId, const QString &patente, const QString &modelo, 
           int anio, const Motor &motor, int puertas)
    : Vehiculo(clienteId, patente, modelo, anio, motor),  // Llama al padre
      numeroPuertas(puertas) 
{
}

// Implementación del método virtual puro
QString Auto::getTipo() const {
    return "AUTO";
}

QString Auto::getInfoAdicional() const {
    return QString("Puertas: %1").arg(numeroPuertas);
}
```

---

## 3️⃣ HERENCIA MÚLTIPLE

### Interfaz IElectrico - vehiculo.h
```cpp
class IElectrico {
public:
    virtual ~IElectrico() = default;
    virtual QString getNivelBateria() const = 0;
};
```

### AutoHibrido hereda de Auto e IElectrico - autohibrido.h
```cpp
class AutoHibrido : public Auto, public IElectrico {
private:
    QString nivelBateria;

public:
    AutoHibrido();
    
    // Constructor que llama a ambas clases base
    AutoHibrido(int clienteId, const QString &patente, const QString &modelo,
                int anio, const Motor &motor, int puertas, const QString &bateria);

    // De IElectrico
    QString getNivelBateria() const override;
    
    // SOBRECARGA DE MÉTODOS
    void cargarBateria();
    void cargarBateria(int porcentaje);
    
    // Sobreescribe el método de Auto
    QString getInfoAdicional() const override;
};
```

### Implementación - autohibrido.cpp
```cpp
AutoHibrido::AutoHibrido(int clienteId, const QString &patente, 
                         const QString &modelo, int anio, const Motor &motor,
                         int puertas, const QString &bateria)
    : Auto(clienteId, patente, modelo, anio, motor, puertas),  // Llama a Auto
      nivelBateria(bateria)  // Inicializa propio atributo
{
}

// Implementa método de IElectrico
QString AutoHibrido::getNivelBateria() const {
    return nivelBateria;
}

// SOBRECARGA - Método sin parámetros
void AutoHibrido::cargarBateria() {
    nivelBateria = "100%";
}

// SOBRECARGA - Método con parámetro
void AutoHibrido::cargarBateria(int porcentaje) {
    nivelBateria = QString("%1%").arg(porcentaje);
}
```

---

## 4️⃣ COMPOSICIÓN

### Motor es PARTE de Vehiculo - vehiculo.h
```cpp
class Vehiculo {
protected:
    Motor motor;  // ◆ COMPOSICIÓN - Motor es PARTE del vehículo
    // Si se destruye el Vehiculo, se destruye el Motor
};
```

### Clase Motor - motor.h
```cpp
class Motor {
private:
    QString tipo;
    int cilindrada;
    int potencia;
    QString combustible;

public:
    Motor();
    Motor(const QString &tipo, int cilindrada, int potencia, const QString &combustible);

    // Getters
    QString getTipo() const;
    int getCilindrada() const;
    
    // SOBRECARGA DE OPERADORES
    bool operator==(const Motor &otro) const;
    bool operator!=(const Motor &otro) const;
    bool operator>(const Motor &otro) const;
    bool operator<(const Motor &otro) const;
    friend QTextStream &operator<<(QTextStream &out, const Motor &m);
};
```

### Uso en Vehiculo - vehiculo.cpp
```cpp
Vehiculo::Vehiculo(int clienteId, const QString &patente, 
                   const QString &modelo, int anio, const Motor &motor)
    : id(0), clienteId(clienteId), patente(patente), 
      modelo(modelo), anio(anio), motor(motor)  // Copia el motor
{
}

Motor Vehiculo::getMotor() const {
    return motor;  // El motor es parte integral
}
```

---

## 5️⃣ AGREGACIÓN

### Cliente TIENE Vehiculos - cliente.h
```cpp
class Cliente {
private:
    int id;
    QString rut;
    QString nombre;
    QString telefono;
    QString direccion;
    // Los vehículos se almacenan en la BD, no como atributos
    // ◇ AGREGACIÓN - Cliente tiene vehículos, pero existen independientes

public:
    Cliente();
    Cliente(const QString &rut, const QString &nombre, 
            const QString &telefono, const QString &direccion);

    // SOBRECARGA DE MÉTODOS
    bool validarRut();  // Valida el RUT del objeto
    static bool validarRut(const QString &rut);  // Valida cualquier RUT
    
    bool coincide(const QString &texto) const;
    bool coincide(const QString &texto, const QString &criterio) const;
    
    // SOBRECARGA DE OPERADORES
    bool operator==(const Cliente &otro) const;
    bool operator!=(const Cliente &otro) const;
    bool operator<(const Cliente &otro) const;
    friend QTextStream &operator<<(QTextStream &out, const Cliente &c);
};
```

### Relación en la Base de Datos
```cpp
// En vehiculos tabla:
// cliente_id → clientes.id (FK)
// El vehículo referencia al cliente pero puede existir independientemente
```

---

## 6️⃣ POLIMORFISMO

### Ejemplo de uso polimórfico - databasemanager.cpp
```cpp
Vehiculo* vehiculo = nullptr;

// Crear diferentes tipos en tiempo de ejecución
if (tipo == "AUTO") {
    vehiculo = new Auto(clienteId, patente, modelo, anio, motor, puertas);
} else if (tipo == "MOTO") {
    vehiculo = new Moto(clienteId, patente, modelo, anio, motor, tipoMoto);
} else if (tipo == "HIBRIDO") {
    vehiculo = new AutoHibrido(clienteId, patente, modelo, anio, motor, 
                               puertas, nivelBateria);
}

// POLIMORFISMO - llama al método correcto según el tipo real
QString tipo = vehiculo->getTipo();  // Llama a Auto::getTipo() o Moto::getTipo()
QString info = vehiculo->getInfoAdicional();  // Comportamiento específico de cada clase

delete vehiculo;  // Destructor virtual asegura limpieza correcta
```

---

## 7️⃣ SOBRECARGA DE MÉTODOS

### En Cliente - cliente.h/cpp
```cpp
// SOBRECARGA 1 - Validar el RUT del objeto actual
bool Cliente::validarRut() {
    return validarRut(this->rut);  // Llama a la versión estática
}

// SOBRECARGA 2 - Validar cualquier RUT (método estático)
bool Cliente::validarRut(const QString &rut) {
    QString rutLimpio = rut;
    rutLimpio.remove('.').remove('-');
    // ... lógica de validación
    return true;
}

// SOBRECARGA 3 - Buscar en todos los campos
bool Cliente::coincide(const QString &texto) const {
    return nombre.contains(texto, Qt::CaseInsensitive) ||
           rut.contains(texto, Qt::CaseInsensitive) ||
           telefono.contains(texto);
}

// SOBRECARGA 4 - Buscar en campo específico
bool Cliente::coincide(const QString &texto, const QString &criterio) const {
    if (criterio == "nombre") {
        return nombre.contains(texto, Qt::CaseInsensitive);
    } else if (criterio == "rut") {
        return rut.contains(texto);
    }
    // ...
    return false;
}
```

### En AutoHibrido - autohibrido.cpp
```cpp
// SOBRECARGA 1 - Cargar batería al 100%
void AutoHibrido::cargarBateria() {
    nivelBateria = "100%";
    qDebug() << "Batería cargada al 100%";
}

// SOBRECARGA 2 - Cargar batería a porcentaje específico
void AutoHibrido::cargarBateria(int porcentaje) {
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 100) porcentaje = 100;
    nivelBateria = QString("%1%").arg(porcentaje);
    qDebug() << "Batería cargada al" << porcentaje << "%";
}
```

---

## 8️⃣ SOBRECARGA DE OPERADORES

### En Vehiculo - vehiculo.cpp
```cpp
// Operador de igualdad
bool Vehiculo::operator==(const Vehiculo &otro) const {
    return patente == otro.patente;  // Dos vehículos son iguales si tienen misma patente
}

// Operador de desigualdad
bool Vehiculo::operator!=(const Vehiculo &otro) const {
    return !(*this == otro);  // Usa el operador ==
}

// Operador menor que (para ordenar)
bool Vehiculo::operator<(const Vehiculo &otro) const {
    return patente < otro.patente;  // Ordena alfabéticamente por patente
}

// Operador de salida para QTextStream
QTextStream &operator<<(QTextStream &out, const Vehiculo &v) {
    out << v.getTipo() << ": " << v.patente << " - " << v.modelo;
    return out;
}
```

### En Motor - motor.cpp
```cpp
// Comparar motores por potencia
bool Motor::operator==(const Motor &otro) const {
    return potencia == otro.potencia;
}

bool Motor::operator>(const Motor &otro) const {
    return potencia > otro.potencia;  // Motor más potente
}

bool Motor::operator<(const Motor &otro) const {
    return potencia < otro.potencia;  // Motor menos potente
}

// Salida formateada
QTextStream &operator<<(QTextStream &out, const Motor &m) {
    out << m.tipo << " " << m.cilindrada << "cc " 
        << m.potencia << "HP (" << m.combustible << ")";
    return out;
}
```

### Uso de operadores sobrecargados
```cpp
// Comparar vehículos
Auto auto1("ABC123", "Toyota Corolla", 2020, motor, 4);
Auto auto2("XYZ789", "Honda Civic", 2021, motor, 4);

if (auto1 == auto2) {  // Usa operator==
    qDebug() << "Misma patente";
}

if (auto1 < auto2) {  // Usa operator<
    qDebug() << "auto1 viene antes alfabéticamente";
}

// Salida con QTextStream
QTextStream stream(&file);
stream << auto1 << "\n";  // Usa operator<<
```

---

## 9️⃣ EXCEPCIONES PERSONALIZADAS

### Definición - databasemanager.h
```cpp
// Clase base de todas las excepciones: std::exception
class ErrorBaseDatos : public std::exception {
private:
    std::string mensaje;

public:
    ErrorBaseDatos(const std::string &msg) : mensaje(msg) {}
    
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

class ErrorValidacion : public std::exception {
private:
    std::string mensaje;

public:
    ErrorValidacion(const std::string &msg) : mensaje(msg) {}
    
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};
```

### Lanzar excepciones - databasemanager.cpp
```cpp
bool DatabaseManager::insertarCliente(Cliente &cliente) {
    QSqlQuery query;
    query.prepare("INSERT INTO clientes (rut, nombre, telefono, direccion) "
                  "VALUES (:rut, :nombre, :telefono, :direccion)");
    
    query.bindValue(":rut", cliente.getRut());
    query.bindValue(":nombre", cliente.getNombre());
    query.bindValue(":telefono", cliente.getTelefono());
    query.bindValue(":direccion", cliente.getDireccion());

    if (!query.exec()) {
        // LANZAR EXCEPCIÓN PERSONALIZADA
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    
    cliente.setId(query.lastInsertId().toInt());
    return true;
}
```

### Capturar excepciones - mainwindow.cpp
```cpp
void MainWindow::onAgregarCliente() {
    ClienteDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        try {
            Cliente cliente = dialog.getCliente();
            
            // Validación
            if (!cliente.validarRut()) {
                throw ErrorValidacion("RUT inválido");
            }
            
            // Intentar insertar
            db->insertarCliente(cliente);
            
            actualizarTablaClientes();
            QMessageBox::information(this, "Éxito", "Cliente agregado correctamente.");
            
        } catch (const ErrorBaseDatos &e) {
            // Capturar error de base de datos
            QMessageBox::critical(this, "Error de Base de Datos", e.what());
            
        } catch (const ErrorValidacion &e) {
            // Capturar error de validación
            QMessageBox::warning(this, "Error de Validación", e.what());
            
        } catch (const std::exception &e) {
            // Capturar cualquier otra excepción
            QMessageBox::critical(this, "Error", e.what());
        }
    }
}
```

---

## 🔟 PATRÓN SINGLETON

### Implementación - databasemanager.h
```cpp
class DatabaseManager {
private:
    // CONSTRUCTOR PRIVADO - no se puede crear desde fuera
    DatabaseManager();
    
    // ELIMINAR constructor de copia y operador de asignación
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    
    QSqlDatabase db;

public:
    // MÉTODO ESTÁTICO para obtener la única instancia
    static DatabaseManager* getInstance();
    
    // Métodos públicos
    bool connect(const QString &host, int port, const QString &dbName,
                 const QString &user, const QString &password);
    bool createTables();
    // ... CRUD methods
};
```

### Implementación - databasemanager.cpp
```cpp
// Variable estática para almacenar la única instancia
static DatabaseManager* instance = nullptr;

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();  // Se crea solo una vez
    }
    return instance;
}

// Constructor privado
DatabaseManager::DatabaseManager() {
    // Inicialización
}
```

### Uso del Singleton
```cpp
// En cualquier parte del código
DatabaseManager *db = DatabaseManager::getInstance();  // Siempre retorna la misma instancia
db->insertarCliente(cliente);

// En otro lugar
DatabaseManager *db2 = DatabaseManager::getInstance();  // db2 == db (misma instancia)
```

---

## 📊 EJEMPLO COMPLETO DE USO

```cpp
int main() {
    // 1. SINGLETON - Obtener instancia única de BD
    DatabaseManager *db = DatabaseManager::getInstance();
    db->connect("", 0, "", "", "");
    
    // 2. COMPOSICIÓN - Motor es parte del vehículo
    Motor motor("Gasolina", 1600, 120, "Gasolina");
    
    // 3. HERENCIA SIMPLE - Auto hereda de Vehiculo
    Auto *auto1 = new Auto(1, "ABC123", "Toyota Corolla", 2020, motor, 4);
    
    // 4. HERENCIA MÚLTIPLE - AutoHibrido hereda de Auto e IElectrico
    AutoHibrido *hibrido = new AutoHibrido(1, "XYZ789", "Toyota Prius", 
                                           2022, motor, 4, "80%");
    
    // 5. POLIMORFISMO - Usar puntero de clase base
    Vehiculo *vehiculo = hibrido;
    qDebug() << vehiculo->getTipo();  // "HIBRIDO" - llama a AutoHibrido::getTipo()
    
    // 6. SOBRECARGA DE MÉTODOS
    hibrido->cargarBateria();     // Carga al 100%
    hibrido->cargarBateria(75);   // Carga al 75%
    
    // 7. SOBRECARGA DE OPERADORES
    if (*auto1 == *hibrido) {  // Usa operator==
        qDebug() << "Misma patente";
    }
    
    // 8. EXCEPCIONES
    try {
        Cliente cliente("12345678-9", "Juan Pérez", "912345678", "Calle 123");
        
        if (!cliente.validarRut()) {  // SOBRECARGA de validarRut()
            throw ErrorValidacion("RUT inválido");
        }
        
        db->insertarCliente(cliente);  // Puede lanzar ErrorBaseDatos
        
    } catch (const ErrorBaseDatos &e) {
        qDebug() << "Error BD:" << e.what();
    } catch (const ErrorValidacion &e) {
        qDebug() << "Error validación:" << e.what();
    }
    
    // 9. AGREGACIÓN - Cliente tiene vehículos
    db->insertarVehiculo(auto1);     // Asocia vehículo con cliente
    db->insertarVehiculo(hibrido);   // Vehículos existen independientemente
    
    delete auto1;
    delete hibrido;
    
    return 0;
}
```

---

**FIN DE LOS EJEMPLOS** ✅


