# dfs_setrule.py
# Python script to generate pop2osc format of rule restrictions
# Gets a rule range from the clipboard and converts it to a C++ function
# Rule range should be the output of get_all_iso_rules.py (No negation of neighbourhoods allowed)
# Result is copied to clipboard

import sys
import re

Btransitions = 'B0-0 B1c-1 B1e-2 B2c-3 B2e-4 B2k-5 B2a-6 B2i-7 B2n-8 B3c-9 B3e-10 B3k-11 B3a-12 B3i-13 B3n-14 B3y-15 B3q-16 B3j-17 B3r-18 B4c-19 B4e-20 B4k-21 B4a-22 B4i-23 B4n-24 B4y-25 B4q-26 B4j-27 B4r-28 B4t-29 B4w-30 B4z-31 B5c-32 B5e-33 B5k-34 B5a-35 B5i-36 B5n-37 B5y-38 B5q-39 B5j-40 B5r-41 B6c-42 B6e-43 B6k-44 B6a-45 B6i-46 B6n-47 B7c-48 B7e-49 B8-50'.split()
Stransitions = 'S0-51 S1c-52 S1e-53 S2c-54 S2e-55 S2k-56 S2a-57 S2i-58 S2n-59 S3c-60 S3e-61 S3k-62 S3a-63 S3i-64 S3n-65 S3y-66 S3q-67 S3j-68 S3r-69 S4c-70 S4e-71 S4k-72 S4a-73 S4i-74 S4n-75 S4y-76 S4q-77 S4j-78 S4r-79 S4t-80 S4w-81 S4z-82 S5c-83 S5e-84 S5k-85 S5a-86 S5i-87 S5n-88 S5y-89 S5q-90 S5j-91 S5r-92 S6c-93 S6e-94 S6k-95 S6a-96 S6i-97 S6n-98 S7c-99 S7e-100 S8-101'.split()
Btrans = {}
Strans = {}

for t in Btransitions:
    tr, val = t.split('-')
    Btrans[tr] = val

for t in Stransitions:
    tr, val = t.split('-')
    Strans[tr] = val

neighbourhoods = {'1': '1ce',
                  '2': '2aceikn',
                  '3': '3aceijknqry',
                  '4': '4aceijknqrtwyz',
                  '5': '5aceijknqry',
                  '6': '6aceikn',
                  '7': '7ce'}

def parsetransitions(transitionstr):
    bors = transitionstr[0]
    for val in re.findall(r'([1-7])(?=[2-9])', transitionstr + '9'):
        transitionstr = transitionstr.replace(val, neighbourhoods[val])
    transList = []
    num = ''
    for c in transitionstr[1:]:
        if c in '08':
            transList.append(bors+c)
        elif c in '1234567':
            num = c
        else:
            transList.append(bors+num+c)
    return transList

all_iso_rules = sys.argv[1]
if not (all_iso_rules[0] == 'B' and ' - ' in all_iso_rules):
    print('Usage: first argument must be a rule range, e.g.')
    print('\n    python %s "B2a/S - B2345678/S012345678\n')
    sys.exit()
minrule, maxrule = all_iso_rules.split(' - ')

birth, survival = minrule.split('/')
b_need = parsetransitions(birth)
s_need = parsetransitions(survival)
birth, survival = maxrule.split('/')
b_ok = parsetransitions(birth)
s_ok = parsetransitions(survival)
b_forbid = [tr for tr in Btrans.keys() if not tr in b_ok]
s_forbid = [tr for tr in Strans.keys() if not tr in s_ok]

setrule = '\nvoid setrule(int rule[number_of_transitions]){\n'
setrule += '  // b_need\n'
for tr in b_need:
    setrule += '  rule[%s] = 1; // %s\n' % (Btrans[tr], tr)

setrule += '  // s_need\n'
for tr in s_need:
    setrule += '  rule[%s] = 1; // %s\n' % (Strans[tr], tr)

setrule += '  // b_forbid\n'
for tr in b_forbid:
    setrule += '  rule[%s] = 0; // %s\n' % (Btrans[tr], tr)

setrule += '  // s_forbid\n'
for tr in s_forbid:
    setrule += '  rule[%s] = 0; // %s\n' % (Strans[tr], tr)

setrule += '}\n'

print(setrule)

