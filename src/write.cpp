#include "../include/PALISADEContainer.h"
#include <chrono>
#include <random>
#include <vector>
#include <climits>
#include <string>


using namespace lbcrypto;
using ctext_typ = Ciphertext<DCRTPoly>;
typedef std::chrono::high_resolution_clock clk;

int main(int argc, char* argv[]){
    int p = 1024;

    for(int i=1; i < argc; i++){
        if(argv[i][0] == '-')
            switch (argv[i][1]){
                case 'p':
                    p = atoi(argv[++i]);
                    break;
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
        else
            exit(EXIT_FAILURE);
    }


    PALISADEContainer pc(1024,1,0);

    auto d = std::chrono::high_resolution_clock::now().time_since_epoch();
    long unsigned int seed = d.count();
    std::mt19937 numbgen(seed); //initialize the random number generator with a seed


    Plaintext ptx;
    for(int i=0; i<1000000;i++){
        std::vector<double> dat;
        for(int i=0; i<p;i++){
            dat.push_back(static_cast<double>(rand())/(static_cast<double>(RAND_MAX/1000)));
        }
        ptx = pc.context->MakeCKKSPackedPlaintext(dat);
        ctext_typ ctx;
        ctx = pc.context->Encrypt(pc.pk,ptx);
        Serial::SerializeToFile("ctexts/ctx" + std::to_string(i),ctx,SerType::BINARY);
    }
    std::string container = "container";
    pc.serialize(container,true);

    exit(EXIT_SUCCESS);

}