#include <iostream>
#include <fstream>
#include <map>
#include<cstdlib>

using namespace std;

#include "includes/inputCode.h"

#define SIZE 50

int main(int argc, char *argv[])
{
    bool is_file = true;

    vDes[0] = 50;

    // "compilamos" o codigo com 'main arquivo.hm [-o logOutput.txt]'
    if(argc < 2)
    {
        cout << "Voce nao esta usando o programa corretamente, para ajuda use o comando 'main -h'" << endl;
        return 1;
    }

    //lendo os argumentos
    for(int i = 1; i < argc; i++)
    {
        //se arq é esse argumento
        if(argv[i][0] != '-' && is_file){
            if(iTokens(argv[i]))
            {
                //arquivo
                cout << endl << "[Fim...]" << endl;
            }
            else
            {
                cout << "Arquivo " << argv[i] << " nao encontrado!!!" << endl;
            }

        }
        else
        {
            is_file = true;
            switch (argv[i][1])
            {
                case 'o':
                    //criar logOutput.txt
                    is_file = false;
                break;

                case 'h':
                    //help
                    //print_help();
                break;

                default:
                    //
                break;
            }
        }
    }
    vOc.clear();
    vDes.clear();
}
