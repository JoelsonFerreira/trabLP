#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

#include "includes/inputCode.h"

#define SIZE 50

int main(int argc, char *argv[])
{
    bool is_file = true;

    vDes[0] = 50;
    atual   = vDes.begin();

    // "compilamos" o codigo com 'main arquivo.hm [-o logOutput.txt]'
    if(argc < 2)
    {
        cout << "Voce nao esta usando o programa corretamente, modo de uso \"main [nome do arquivo]\"" << endl;
        return 1;
    }

    //lendo os argumentos
    for(int i = 1; i < argc; i++)
    {
        if(!iTokens(argv[i])){
            cout << "Arquivo " << argv[i] << " nao encontrado!!!" << endl;
        }
    }
    vOc.clear();
    vDes.clear();
}
