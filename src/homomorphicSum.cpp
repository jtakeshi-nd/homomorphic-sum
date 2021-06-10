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

    for(int x=0; x<n;x+=200000){
        std::vector<Plaintext> *ptext = new std::vector<Plaintext>(200000);
        for(int i=0; i<200000;i++){
            std::vector<double> dat = {static_cast<double>(rand())/(static_cast<double>(RAND_MAX/1000))};
            (*ptext)[i] = pc.context->MakeCKKSPackedPlaintext(rawData);
        }
        std::vector<ctext_typ> *sum = new std::vector<ctext_typ>(200000); 
        for(int i=0; i<200000; i++){
            (*sum)[i] = pc.context->Encrypt(pc.pk,(*ptext)[i]);
        }

        delete ptext;

        clk::time_point beginning = clk::now();
        for(ctext_typ c: *sum){
            pc.context->EvalAddInPlace(ctext,c);
        }
        clk::time_point end = clk::now();
        delete sum;
        duration += std::chrono::duration_cast<std::chrono::microseconds>(end-beginning).count();
    }


    Serial::SerializeToFile("ctext",ctext,SerType::BINARY);


    std::string outfile = "container";
    pc.serialize(outfile,true);

    std::cout << duration << std::endl;

    





}