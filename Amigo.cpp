#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Amigo {
private:
	string 	nombre;
	int		edad;
	char	sexo;
	char	estado;		//eliminado = E, activo = A

public:
	Amigo() {
		nombre = "";
		edad		= 0;
		sexo		= ' ';
		estado		= ' ';
	}
	
	Amigo(string nom, int ed, char sx) {
		nombre	= nom;
		edad	= ed;
		sexo	= sx;
		estado  = 'A';
	}
	
	void setAmigo(string nom, int ed, char sx) {
		nombre		= nom;
		edad		= ed;
		sexo		= sx;
		estado		= 'A';
	}

	string getNombre() {
		return(nombre);
	}

	int getEdad() {
		return(edad);
	}

	char getSexo() {
		return(sexo);
	}

	char getEstado() {
		return(estado);
	}

	void guardarArchivo(ofstream &fsalida) {
		fsalida.write(reinterpret_cast<char *>(&nombre), sizeof(nombre));
		fsalida.write(reinterpret_cast<char *>(&edad), sizeof(edad));
		fsalida.write(reinterpret_cast<char *>(&sexo), sizeof(sexo));
		fsalida.write(reinterpret_cast<char *>(&estado), sizeof(estado));
	}

	bool leerArchivo(ifstream &fentrada) {
		bool k = false;
		if (fentrada.is_open() == true) {
			fentrada.read(reinterpret_cast<char *>(&nombre), sizeof(nombre));
			if (fentrada.eof() == false) {				
				fentrada.read(reinterpret_cast<char *>(&edad), sizeof(edad));
				fentrada.read(reinterpret_cast<char *>(&sexo), sizeof(sexo));
				fentrada.read(reinterpret_cast<char *>(&estado), sizeof(estado));
				k = true;
			}else {
				//cout << endl << "Registro no existe";
			}
		}else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}

	bool eliminar(fstream &fes, int nroReg){
		bool k = false;
		if (fes.is_open() == true) {
			fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.read(reinterpret_cast<char *>(&nombre), sizeof(nombre));
			if (fes.eof() == false) {
				fes.read(reinterpret_cast<char *>(&edad), sizeof(edad));
				fes.read(reinterpret_cast<char *>(&sexo), sizeof(sexo));
				fes.read(reinterpret_cast<char *>(&estado), sizeof(estado));
		
				estado = 'E';
				fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
				fes.write(reinterpret_cast<char *>(&nombre), sizeof(nombre));
				fes.write(reinterpret_cast<char *>(&edad), sizeof(edad));
				fes.write(reinterpret_cast<char *>(&sexo), sizeof(sexo));
				fes.write(reinterpret_cast<char *>(&estado), sizeof(estado));
				k = true;
			}else {
				cout << endl << "Registro no existe";
			}			
		}else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}


	bool modificar(fstream &fes, int nroReg){
		bool k = false;
		if (fes.is_open() == true) {
			string nomAux;
			nomAux=nombre;
			fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.read(reinterpret_cast<char *>(&nombre), sizeof(nombre));
			if (fes.eof() == false) {
				nombre=nomAux;
				estado = 'A';
				fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
				fes.write(reinterpret_cast<char *>(&nombre), sizeof(nombre));
				fes.write(reinterpret_cast<char *>(&edad), sizeof(edad));
				fes.write(reinterpret_cast<char *>(&sexo), sizeof(sexo));
				fes.write(reinterpret_cast<char *>(&estado), sizeof(estado));
				k = true;
			}else {
				cout << endl << "Registro no existe";
			}			
		}else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}

	bool buscar(ifstream &fentrada, int nroReg) {
		bool k = false;
		if (fentrada.is_open() == true) {
			fentrada.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fentrada.read(reinterpret_cast<char *>(&nombre), sizeof(nombre));
			fentrada.read(reinterpret_cast<char *>(&edad), sizeof(edad));
			fentrada.read(reinterpret_cast<char *>(&sexo), sizeof(sexo));
			fentrada.read(reinterpret_cast<char *>(&estado), sizeof(estado));
			if (fentrada.eof() == false) {
				k = true;
			}
			else {
				//cout << endl << "Registro no XX existe";
			}
		}
		else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}

	int getTamBytesRegistro() {
		return(sizeof(nombre) + sizeof(edad) + sizeof(sexo) + sizeof(estado) );
	}

};
