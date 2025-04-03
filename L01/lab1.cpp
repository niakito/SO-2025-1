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

bool valid_type(string t){ 
    //CAMBIAR PARA QUE RETORNE CERTAMEN 0 CONTROL 1 TAREA 2
    return (t == "certamen" || t == "control" || t == "tarea");
}

bool valid_num(string n){
    int num = stoi(n);
    return (num >= 1 && num <= 3);
}

bool valid_year(string y){
    if (y.length() < 6) return false;
    
    string year = y.substr(0, 4);
    string sem = string(1, y[5]);
    
    int year_ = stoi(year);
    int sem_ = stoi(sem);

    return (year_ <= 2025 && sem_ >= 1 && sem_ <= 2);
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
                                    cout << "Certamen valido" << endl; //EXITO ^V^ 
                                }
                            } else {
                                corruptos.push_back(file_name);
                            } 
                        }                                                                                                    
                    } else {
                        corruptos.push_back(file_name);
                    }
                } else {
                    if (type == "control" || type == "control\n" || type == "control\r"){
                        pos = texto.find("numero: ");
                        if (pos != string::npos){ // SI ES QUE SE ENCUENTRA NUMERO
                            pos += 8;
                            string numero = texto.substr(pos, texto.find("\n", pos));
                            if (valid_num(numero)){
                                pos = texto.find("semestre_publicacion: ");
                                if (pos != string::npos){ // SI SE ENCUENTRA EL SEMENSTRE
                                    pos += 22;
                                    string publicacion = texto.substr(pos, texto.find("\n", pos));
                                    if (valid_year(publicacion)){
                                        cout << "Control valido" << endl;
                                    } else {
                                        //INVALIDO
                                        cout <<"NO"<<endl;
                                    }
                                } else {
                                    //SEMESTRE INVALIDO
                                    cout <<"NO"<<endl;
                                }
                            } else {
                                //numero invalido
                                cout <<"NO"<<endl;
                            }
                        }
                    } else {
                        if (type == "tarea" || type == "tarea\n" || type == "tarea\r"){
                            cout << "HW" << endl;
                        } else {
                            cout << "lolaso No" << endl;
                        }
                    }
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
