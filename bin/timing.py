#!/usr/bin/env python3
import subprocess
import csv

file = open("stats.csv",'w' )
csvWriter = csv.writer(file,csv.get_dialect('excel'))

subprocess.run(['./write'])

for i in range(100000,1000001,100000):
    for j in range(10):
        row = [i]
        result = subprocess.run(['./homomorphicSum','-n',f'{i}'],stdout=subprocess.PIPE,stderr=subprocess.DEVNULL)
        row+= bytes.decode(result.stdout).strip().split('\n')
        result = subprocess.run(['graphene-sgx',' decrypt'], stdout=subprocess.PIPE)
        row+= bytes.decode(result.stdout).strip().split('\n')
        csvWriter.writerow(row)

