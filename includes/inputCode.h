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

/*
 *
 * receebe uma palavra chave e seus argumentos... 
 * realiza a simulacao feita em vOc(ED que representea a memoria desocupada) 
 * e vDes(ED que representa a memoria desocupada)
 *
*/
void simulando(string tokenKey, string args[2])
{
    // palavra chave new, aloca um pedaço de memoria do tamanho args[1] chamado pelo id args[0]
    if(tokenKey == "new")
    {
        int argInt = stoi(args[1]);

        // pegando primeira posicao de memoria disponivel (first fit)
        map<int, int>::iterator it = vDes.begin();
        int beginPos, amount;

        beginPos = it->first;
        amount = it->second;

        for(; it != vDes.end() && it->second < argInt; it++)
        {
            beginPos = it->first;
            amount = it->second;
        }

        // caso exista uma posicao disponivel...
        if(it != vDes.end())
        {
            // Desocupa
            vDes.erase(it);
            vDes[beginPos + argInt] = amount - argInt;

            // Ocupa
            struct Ocupados aux;
            aux.comeco = beginPos;
            aux.quant  = argInt;

            vOc[args[0]] = aux;
        }
        else
        {
            cout << "Espaco insuficiente para alocar " << args[0] << "!" << endl;
        }
    }
    // palavra chave "del", apaga o espaco de memoria com o id = args[0]
    else if(tokenKey == "del")
    {
        // buscando o id
        map<string, struct Ocupados>::iterator it = vOc.find(args[0]);
        struct Ocupados aux = it->second;

        // se o id existe nos ocupados...
        if(it != vOc.end())
        {
            // apaga
            vOc.erase(it);  

            // mescla com espaco de memoria que ja estava livre caso seja conticua
            int endPos = aux.comeco + aux.quant;
            if(vDes.find(endPos) != vDes.end())
            {
                int d = vDes[vDes.find(endPos)->first];
                vDes.erase(vDes.find(endPos));
                vDes[aux.comeco] = aux.comeco + d;
            }
            // caso nao seja continua
            else
            {
                vDes[aux.comeco] = aux.quant;
            }
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


/*
 * separa as palavras chaves dos argumentos e chama a funcao simulando
 */
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