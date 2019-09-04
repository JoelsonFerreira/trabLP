#include <fstream>
#include <string>
#include <iostream>
#include <map>

struct Ocupados
{
    int comeco, quant;
};

map<string, struct Ocupados> vOc;
map<int, int> vDes;

using namespace std;

#define SIZE_KEYWORD1 2
#define SIZE_KEYWORD2 1

// Palavras chaves do codigo
string keyWord0[1] = 
{
    "exibe"
};
string keyWord1[SIZE_KEYWORD1] = 
{
    "del",
    "heap"
};
string keyWord2[SIZE_KEYWORD2] = 
{
    "new"
};
string heap[4]=
{
    "first",
    "best",
    "worst",
    "next"
};


// recebe 2 numeros a e b, e retorna o maior deles
int max(int a, int b)
{
    if(a > b)   return a;
    return b;
}

// recebe uma keyWord e retorna a quantidade de argumentos esperadas pra aquela key
int sizeKeyWord(string str)
{
    for(int i = 0; i < max(SIZE_KEYWORD1, SIZE_KEYWORD2); i++)
    {
        if(str == keyWord1[i] && i < SIZE_KEYWORD1)
        {
            return 1;
        }else if(str == keyWord2[i] && i < SIZE_KEYWORD2)
        {
            return 2;
        }
    }
    return 0;
}

void simulando(string tokenKey, string args[2])
{
    if(tokenKey == "new")
    {
        int c = stoi(args[1]);

        map<int, int>::iterator it = vDes.begin();
        int a, b;

        a = it->first;
        b = it->second;

        for(; it != vDes.end() && it->second < c; it++)
        {
            a = it->first;
            b = it->second;
        }

        if(it != vDes.end())
        {
            // Desocupa
            vDes.erase(it);
            vDes[a + c] = b - c;

            // Ocupa
            struct Ocupados aux;
            aux.comeco = a;
            aux.quant  = c;

            vOc[args[0]] = aux;
        }
        else
        {
            cout << "Espaco insuficiente para alocar " << args[0] << "!" << endl;
        }
    }
    else if(tokenKey == "del")
    {
        map<string, struct Ocupados>::iterator it = vOc.find(args[0]);
        struct Ocupados b = it->second;

        vOc.erase(it);

        int c = b.comeco + b.quant;

        if(vDes.find(c) != vDes.end())
        {
            int d = vDes[vDes.find(c)->first];
            vDes.erase(vDes.find(c));
            vDes[b.comeco] = b.comeco + d;
        }
        else
        {
            vDes[b.comeco] = b.quant;
        }
    }
    else if(tokenKey == "heap")
    {

    }
    else if(tokenKey == "exibe")
    {
        cout << "============== DESOCUPADOS ================" << endl;
        for(auto it = vDes.begin(); it != vDes.end(); it++)
        {
            cout << "POS: " << it->first << "\tQUANT: " << it->second << endl;
        }
        cout << endl << "==============   OCUPADOS   ================" << endl;
        for(auto it = vOc.begin(); it != vOc.end(); it++)
        {
            cout << "ID: " << it->first << "\tPOS: " << it->second.comeco << "\tQUANT: " << it->second.quant << endl;
        }
        cout << endl << endl;
    }
    else // atribui
    {
        
    }
    
}

int iTokens(string fname)
{
    /*  tokens  */
    ifstream file(fname);
    
    if(file.is_open())
    {
        while(!file.eof())
        {
            string tokenKey;
            
            file >> tokenKey;
            //cout << "Key Word - " << tokenKey << endl;

            string tokenArg[2];
            
            for(int i = 0; i < sizeKeyWord(tokenKey); i++)
            {
                file >> tokenArg[i];
            }

            simulando(tokenKey, tokenArg);
        }

        file.close();
        return 1;
    }
    else
    {
        return 0;
    }
    /*          */ 
}