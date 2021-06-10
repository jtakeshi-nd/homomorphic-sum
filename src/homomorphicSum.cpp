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

    PALISADEContainer pc(8192,3,2048);

    auto d = std::chrono::high_resolution_clock::now().time_since_epoch();
    long unsigned int seed = d.count();
    std::mt19937 numbgen(seed); //initialize the random number generator with a seed

    std::vector<double> rawData;
    rawData.push_back(static_cast<double>(rand())/(static_cast<double>(RAND_MAX/1000)));
    Plaintext p = pc.context->MakeCKKSPackedPlaintext(rawData);
    ctext_typ ctext = pc.context->Encrypt(pc.pk,p);
    size_t duration = 0;

    for(int x=0; x<32;x++){
        std::vector<Plaintext> *ptext = new std::vector<Plaintext>(n/32);
        for(int i=0; i<n/32;i++){
            std::vector<double> dat = {static_cast<double>(rand())/(static_cast<double>(RAND_MAX/1000))};
            (*ptext)[i] = pc.context->MakeCKKSPackedPlaintext(rawData);
        }
        std::cout << "plaintexts" << std::endl;
        std::vector<ctext_typ> *sum = new std::vector<ctext_typ>(n/32); 
        for(int i=0; i<n/32; i++){
            (*sum)[i] = pc.context->Encrypt(pc.pk,(*ptext)[i]);
        }
        std::cout << "ciphertexts" << std::endl;

        delete ptext;

        auto beginning = clk::now();
        for(ctext_typ c: *sum){
            pc.context->EvalAddInPlace(ctext,c);
        }
        auto end = clk::now();
        std::cout << "sum " << std::endl;
        delete sum;
        duration += std::chrono::duration_cast<std::chrono::microseconds>(end-beginning).count();
    }


    Serial::SerializeToFile("ctext",ctext,SerType::BINARY);


    std::string outfile = "container";
    pc.serialize(outfile,true);

    std::cout << duration << std::endl;

    





}