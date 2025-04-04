#include <bits/stdc++.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
using namespace std;

string readFile(ifstream &f){
    string text, content;
    while (getline (f, text)){
        content += text + "\n";
    }
    return content;
}

bool valid_num(string n){
    int num = stoi(n);
    return (num >= 1 && num <= 3);
}

bool valid_year(string y, int n){
    int y_ = stoi(y);
    if (y_ < 2026 && n >= 1 && n <= 2){
        return true;
    }
    return false;
}

bool valid_hw(string name){
    vector<string> Tareas = {"onda certera", "laser vs. plasma", "quantumanio", "atomoX", "bitfase", "red-aracnida", "debug & dragons", "thread wars", "crypto knight", "bugzilla", "stack attack", "compile & conquer", "algorhythm", "cyberkarma"};
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (int i = 0; i < Tareas.size(); i++){
        if (name == Tareas[i] || name == Tareas[i]+"\r" || name == Tareas[i]+"\n"){
            return true;
        }
    }
    return false;
}

void leer_dir(){
    DIR *dir1;
    struct dirent *entrada;
    vector<string> corruptos;

    dir1 = opendir("/home/isidora/OneDrive/Escritorio/uni/so/Lab1/Pruebas/Pruebas/General"); // CAMBIAR POR LA DIRECCION CORRESPONDIENTE

    if (dir1 == NULL){
        cout << "Error abriendo el directorio." << endl;
        return;
    }

    while ((entrada = readdir(dir1)) != NULL){
        string file_name = entrada->d_name;
        if (file_name == "." || file_name == ".."){
            continue;
        }
        string f = "/home/isidora/OneDrive/Escritorio/uni/so/Lab1/Pruebas/Pruebas/General/" + file_name;
        ifstream file(f);
        if (file.is_open()){
            string texto = readFile(file);
            size_t pos = texto.find("tipo: ");
            if (pos != string::npos){ //SI SE ENCUENTRA TIPO
                pos += 6;
                string type = texto.substr(pos, texto.find("\n", pos) - pos); //DESDE POS A SALTO DE LINEA
                if (type == "certamen" || type == "certamen\n" || type == "certamen\r"){
                    pos = texto.find("numero: ");
                    if (pos != string::npos){ //SI SE ENCUENTRA NUMERO
                        pos += 8;
                        int num = stoi(texto.substr(pos, texto.find("\n", pos) - pos));
                        if (num > 3 || num < 0){
                            corruptos.push_back(file_name); //INVALIDO
                        } else {
                            pos = texto.find("semestre_publicacion: ");
                            if (pos != string::npos){ //SI ES QUE SE ENCUENTRA SEMESTRE
                                pos += 22;
                                string anio = texto.substr(pos, 4);
                                int sem = stoi(texto.substr(pos + 5, 1));
                                if (stoi(anio) > 2025 || sem < 1 || sem > 2){ //INVAlIDO
                                    corruptos.push_back(file_name);
                                } else {
                                    cout << "Certamen valido: "; //EXITO ^V^ 
                                    cout << sem << " " << anio << " " << num << endl;
                                }
                            } else {
                                cout << "NO" << endl; // INVALIDO
                            } 
                        }                                                                                                    
                    } else {
                        cout << "NO" << endl; // INVALIDO
                    }
                } else if (type == "control" || type == "control\n" || type == "control\r"){
                    pos = texto.find("numero: ");
                    if (pos != string::npos){ // SI ES QUE SE ENCUENTRA NUMERO
                        pos += 8;
                        string numero = texto.substr(pos, texto.find("\n", pos) - pos);
                        if (valid_num(numero)){
                            pos = texto.find("semestre_publicacion: ");
                            if (pos != string::npos){ // SI SE ENCUENTRA EL SEMESTRE
                                pos += 22;
                                string anio = texto.substr(pos, 4);
                                int sem = stoi(texto.substr(pos + 5, 1));
                                if (valid_year(anio, sem)){
                                    cout << "Control valido: ";
                                    cout << anio << " " << sem << " " << numero << endl;
                                } else {
                                    cout << "NO" << endl; //INVALIDO
                                }
                            } else {
                                cout << "NO" << endl; //SEMESTRE INVALIDO
                            }
                        } else {
                            cout << "NO" << endl; //NUMERO INVALIDO
                        }
                    }
                } else if (type == "tarea" || type == "tarea\n" || type == "tarea\r"){
                    pos = texto.find("semestre_publicacion: ");
                    if (pos != string::npos){
                        pos += 22;
                        string anio = texto.substr(pos, 4);
                        int sem = stoi(texto.substr(pos + 5, 1));
                        if (valid_year(anio, sem)){
                            size_t pos2 = texto.find("nombre: ");
                            if (pos2 != string::npos){
                                pos2 += 8;
                                string nombre = texto.substr(pos2, texto.find("\n", pos2) - pos2);
                                if (valid_hw(nombre)){
                                    cout << "Tarea valida: ";
                                    cout << sem << " " << anio << " " << nombre << endl;
                                } else {
                                    cout << "NO" << endl; //INVALIDO
                                }
                            } else {
                                cout << "NO" << endl; //INVALIDO
                            }
                        } else {
                            cout << "NO" << endl; // INVALIDO
                        }
                    } else {
                        cout << "NO" << endl; // INVALIDO
                    }
                } else {
                    cout << "lolaso No" << endl;
                }
            } else {
                corruptos.push_back(file_name);
            }
            file.close();
        } else {
            cout << "No se pudo abrir :C" << endl;
        }
    }

    if (closedir(dir1) == -1){
        cout << "Error cerrando el directorio." << endl;
        return;
    }
}

int main(){
    leer_dir();
    return 0;
}
