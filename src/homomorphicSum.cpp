#include "../include/PALISADEContainer.h"
#include <chrono>
#include <random>
#include <vector>
#include <climits>


using namespace lbcrypto;
using ctext_typ = Ciphertext<DCRTPoly>;
typedef std::chrono::high_resolution_clock clk;


int main(int argc, char* argv[]){
    size_t n =1000000;

    for(int i=1; i < argc; i++){
        if(argv[i][0] == '-')
            switch (argv[i][1]){
                case 'n':
                    n = atoi(argv[++i]);
                    break;
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
        else
            exit(EXIT_FAILURE);
    }

    PALISADEContainer pc("container",true);

    ctext_typ ctext;
    Serial::DeserializeFromFile("ctexts/ctx" + std::to_string(0),ctext,SerType::BINARY);
    size_t duration = 0;

    for(int i=1;i<n;i++){
        ctext_typ tmp;
        Serial::DeserializeFromFile("ctexts/ctx" + std::to_string(i),tmp,SerType::BINARY);
        auto begin = clk::now();
        pc.context->EvalAddInPlace(ctext,tmp);
        auto end = clk::now();
        duration += std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
    }


    Serial::SerializeToFile("ctext",ctext,SerType::BINARY);



    std::cout << duration << std::endl;

    





}