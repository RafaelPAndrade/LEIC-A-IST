#coding: utf-8

#1
"""
print("Escreva 2 números")
x= eval(input("x= "))
y= eval(input("y= "))
print("(x+3*y)*(x-y) =",((x+3*y)*(x-y)))
"""

#2a
"""
dist = eval(input("Distancia(km): "))
time = eval(input("Tempo gasto(min): "))

time = time/60

print("Velocidade média:", dist/time,"km/h.")
"""

#2b
"""
dist = eval(input("Distancia(km): "))
time = eval(input("Tempo gasto(min): "))

time = time*60
dist = dist*1000

print("Velocidade média:", dist/time,"m/s.")
"""

#3
"""
a=round(eval(input("N segundos: ")))

a = a/(60*60*24)

print("Nº de dias: ", a)
"""

#4
"""
a=round(eval(input("N segundos: ")))


day = a//(60*60*24)
a = a%(60*60*24)

hor = a//(60*60)
a = a%(60*60)

min = a//(60)
a = a%(60)

print("Dias:",day,"horas:",hor,"minutos:",min,"segundos:",a)
"""


#5
"""
from math import sqrt

a, b, c, d, e = eval(input("Escreva 5 números, separados por (,): "))
print()

med = (a+b+c+d+e)/5 #média

interm=(a-med)**2+(b-med)**2+(c-med)**2+(d-med)**2+(e-med)**2 #somatório para o desvio padrão


desvio=sqrt((1/4)*(interm)) #desvio padrão

print("Média:", med,"\nDesvio Padrão:", desvio)
"""

#6
"""
a,b,c = eval(input("Escreva 3 números, separados por (,): "))


if a>b and a>c:
	maior= a
elif b>a and b>c:
	maior= b
elif c>a and c>b:
	maior= c
else:
	maior="Nao ha um número maior do que os outros dois"


print("O maior número é:", maior)
"""

#7
"""
ano= int(input("Dê um ano à sua escolha: "))
print()


if ano%4 == 0:
	if ano%100 == 0 and ano%400 != 0:
		print("O ano indicado não é bissexto")
	else:
		print("O ano indicado é bissexto")
else:
	print("O ano indicado não é bissexto")
"""

#8
"""
horas = eval(input("Nº de horas de trabalho: "))
eur = eval(input("Euros/hora: "))

horasext = horas - 40 #N de horas extraordinárias
if horasext < 0:
	horasext = 0

horasnorm = horas - horasext #Horas normais de trabalho

salario= (horasnorm*eur) + (horasext*eur*2)

print("Nesta semana ganha:", salario)
"""

#9
"""
sec = 0

while sec >= 0:
	if sec > 0:
		print("Isso são",(sec/(60*60*24)),"dias")
	sec = round(eval(input("Escreva um número inteiro natural de segundos: ")))
"""

#10
"""
num = 0
dig = 0

while dig != -1:
	num = (num*10)+dig
	dig=round(eval(input("Escreva um dígito, -1 para terminar: ")))

print("O número digitado é", num)
"""


#11
"""
ordemAlgarismo = 0 #ordem do algarismo; vai aumentando, consoante o n de dígitos aumenta
num= round(eval(input("Escreva um inteiro positivo: ")))
imp=0

while num > 0:
	if num%2 != 0: #se o último dígito não for par:
		imp = imp+((num%10)*(10**ordemAlgarismo)) #coloca o algarismo em causa na posiçao das unidades(0) ou outra...
		ordemAlgarismo = 1 + ordemAlgarismo #o proximo impar que encontrar e de uma ordem acima

	num = num//10 #avancar para o proximo algarismo

print("Retirando todos os pares, fica o número", imp)
"""

#12
"""
num= round(eval(input("Escreva um inteiro positivo: ")))
inv = 0

while num !=0:
	dig = num%10 #pega num dígito
	inv = inv*10+dig #avança com o número invertido para a frente, deixando a casa das unidades para o mais recente dígito
	num = num//10 #avança para o próximo dígito + significativo

print("O número invertido é:", inv)
"""

#13
"""
from math import factorial

soma = 0
n= int(input("Qual o valor de n(inteiro): "))
x= int(input("Qual o valor de x: "))

while n >= 0:
	soma = soma+((x**n)/factorial(n))
	n = n - 1

print("O valor da soma é", soma)
"""

#14
"""
n=1
base=eval(input("Escreva um número: "))
print("A wild Tabuada of number", base,"appears!" )
print("It used Multiplication!")

while n <= 10:
	print(base, "x", n,"=", base*n)
	n = n+1

print("\nGot away safely!")
"""

#15
"""
soma = 0
num= round(eval(input("Podia dar um número inteiro, se faz favor? ")))
print("Obrigado!")

while num > 0:
	soma = soma + num%10
	num = num // 10

print("A soma dos dígitos do número que deu dá", soma)
"""

#16
"""
#igual ao 10??
#10

num = 0
dig = 0

while dig != -1:
	num = (num*10)+dig
	dig=round(eval(input("Escreva um dígito, -1 para terminar: ")))

print("O número digitado é", num)

"""

#17
"""
num= int(input("Escreva um número: "))
num_part_1 = num
n_dig=0
num_part_2 = 0

while num !=0:
    dig = num%10 #pega num dígito
    n_dig=n_dig+1
    num_part_2 = num_part_2*10+dig #avança com o número invertido para a frente, deixando a casa das unidades para o mais recente dígito
    num = num//10 #avança para o próximo dígito + significativo

num_part_1= num_part_1*(10**n_dig)

print("Capicua: ", num_part_1+num_part_2)
"""

#18
"""
nota= 0
n_positivas= 0
n_total= 0


while nota != -1:
	nota= eval((input("Vá introduzindo notas, -1 para acabar: ")))
	if nota!=-1:
		n_total= n_total+1
		if nota >= 9.5:
			n_positivas = n_positivas+1

taxa_aprov= (n_positivas/n_total)*100

print(n_positivas, "alunos passaram, sendo a taxa de aprovação", taxa_aprov, "%.")
"""

#19
"""
num= int(input("Escreva um número: "))
n_duplo0= 0

while num !=0:
	dig1_2=num%100
	if dig1_2==0:
		n_duplo0=n_duplo0+1
	num= num//10

print("Pares de zeros ocorrem", n_duplo0, "vezes no número")
"""

#20
"""
dinheiro=eval(input("Ponha uma quantidade de euros sem símbolo: "))
dinheiro= (round(dinheiro*100)) #porque há chico-espertos que consideram que existe 0.001 euros; e vou usar 1 cent como unidade

n_notas50_00=dinheiro//5000
dinheiro=dinheiro%5000

n_notas20_00=dinheiro//2000
dinheiro=dinheiro%2000

n_notas10_00=dinheiro//1000
dinheiro=dinheiro%1000

n_notas5_00=dinheiro//500
dinheiro=dinheiro%500

n_moedas2_00=dinheiro//200
dinheiro=dinheiro%200

n_moedas1_00=dinheiro//100
dinheiro=dinheiro%100

n_moedas0_50=dinheiro//50
dinheiro=dinheiro%50

n_moedas0_20=dinheiro//20
dinheiro=dinheiro%20

n_moedas0_10=dinheiro//10
dinheiro=dinheiro%10

n_moedas0_05=dinheiro//5
dinheiro=dinheiro%5

n_moedas0_02=dinheiro//2
dinheiro=dinheiro%2

n_moedas0_01=dinheiro

print("Notas de:")
print("\t50.0:", n_notas50_00)
print("\t20.0:", n_notas20_00)
print("\t10.0:", n_notas10_00)
print("\t5.00:", n_notas5_00)
print("Moedas de:")
print("\t2.00:", n_moedas2_00)
print("\t1.00:", n_moedas1_00)
print("\t0.50:", n_moedas0_50)
print("\t0.20:", n_moedas0_20)
print("\t0.10:", n_moedas0_10)
print("\t0.05:", n_moedas0_05)
print("\t0.02:", n_moedas0_02)
print("\t0.01:", n_moedas0_01)
"""


#21
"""
n=1 #nº da linha, vai de 1 a 9
base_mult = 0

while n <= 9:
	base_mult = base_mult*10+n
	resultado = ((base_mult)*8)+n
	print(int(base_mult), "x", 8, "+", n, "=", resultado)
	n= n+1
"""
