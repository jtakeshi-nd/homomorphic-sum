Homorphic Sum - Using PALISADE to calculate the sum of x number of integers

Dependencies 
- PALISADE
  - [Github Repository](https://gitlab.com/ted537/palisade-development)
- Graphene SGX
  - [Install Page](https://graphene.readthedocs.io/en/latest/)

To Build:
1. `make`
2. `cd graphene`
3. `SGX=1 make -f mk_preprocess decrypt.manifest.sgx decrypt.token pal_loader`


To run full test:
1. `cd graphene`
2. `./timing.py`

