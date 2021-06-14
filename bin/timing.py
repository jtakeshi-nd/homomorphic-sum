#!/usr/bin/env python3
import subprocess
import csv

capacities = ['1G','2G','4G','8G', '16G']

def increaseCapacity(capacityAttempt):
    '''Rewrites the template file to have more capacity in the enclave
    then remakes the manifes.sgx, token, and .sig files'''
    manifest = open('decrypt.manifest.template','r')
    content = manifest.readlines()
    content[28] = f'sgx.enclave_size = "{capacities[capacityAttempt]}"\n'
    manifest.close()
    manifest = open('decrypt.manifest.template', 'w')
    manifest.writelines(content)
    manifest.close()
    subprocess.run(['make', 'SGX=1', '-f', 'mk_preprocess', 'decrypt.manifest.sgx', 'decrypt.token', 'pal_loader'],stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def resetCapacity():
    '''Rewrites the template file to have the original capacity in the enclave
    then remakes the manifes.sgx, token, and .sig files'''
    manifest = open('decrypt.manifest.template','r')
    content = manifest.readlines()
    content[28] = f'sgx.enclave_size = "512M"\n'
    manifest.close()
    manifest = open('decrypt.manifest.template', 'w')
    manifest.writelines(content)
    manifest.close()
    subprocess.run(['make', 'SGX=1', '-f', 'mk_preprocess', 'decrypt.manifest.sgx', 'decrypt.token', 'pal_loader'],stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


file = open("stats.csv",'w' )
csvWriter = csv.writer(file,csv.get_dialect('excel'))

i = 1000000
capacityAttempt = 0
subprocess.run(['./write'])

while i < 10000000:
    j=0
    while j < 10:
        row = [i]
        result = subprocess.run(['./homomorphicSum','-n',f'{i}'],stdout=subprocess.PIPE,stderr=subprocess.DEVNULL)
        row+= bytes.decode(result.stdout).strip().split('\n')
        result = subprocess.run(['graphene-sgx',' decrypt'], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
        row+= bytes.decode(result.stdout).strip().split('\n')
        csvWriter.writerow(row)
        j+=1
    i+=1000000

