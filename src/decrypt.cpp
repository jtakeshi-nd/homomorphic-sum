#include "../include/PALISADEContainer.h"
#include <string>
#include <chrono>

using namespace lbcrypto;
using ctext_typ = Ciphertext<DCRTPoly>; 
typedef std::chrono::high_resolution_clock clk;

int main(int argc, char* argv[]){
    std::string container("container");
    std::string ciphertext("ctext.txt");
    for(int i=1; i < argc; i++){
        if(argv[i][0] == '-')
            switch (argv[i][1]){
                case 'p':
                    container = argv[++i];
                    break;
                case 'c':
                    ciphertext = argv[++i];
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
        else
            exit(EXIT_FAILURE);
    }

    PALISADEContainer pc(container,true);

    auto beginning = clk::now();
    ctext_typ ctext;
    Serial::DeserializeFromFile(ciphertext,ctext,SerType::BINARY);

    Plaintext ptext;
    pc.context->Decrypt(pc.sk,ctext,&ptext);

    auto end = clk::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-beginning);
    std::cout << duration.count() << std::endl;



}