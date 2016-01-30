import sys
import math

n = int(input())  # Number of elements which make up the association table.
q = int(input())  # Number Q of file names to be analyzed.
dico = dict()
for i in range(n):
    # ext: file extension
    # mt: MIME type.
    ext, mt = input().split()
    dico[str(ext).lower()] = str(mt)
print(dico, file=sys.stderr)
for i in range(q):
    fname = input()  # One file name per line.
    if len(fname.split('.')) <= 1:
        print("UNKNOWN")
        continue
    extToTest = fname.split('.')[-1].lower()
    #print("Nom fichier = ", fname, " Ext = #",extToTest,"# ",len(extToTest), file=sys.stderr)
    if extToTest in dico:
    	print(dico[extToTest])
    else:
    	print("UNKNOWN")

# For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.

