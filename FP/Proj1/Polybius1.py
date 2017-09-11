"""
FP-2016/2017
Projeto 1- codificador/descodificador usando o quadrado de Polybius
Rafael Pestana de Andrade, nº 86503

Versão 1.1-Simplificada
"""

def gera_chave1(letras):
	"""
	Nome da funcao: gera_chave1
	-A partir de um dado tuplo, gera uma chave que pode ser usada para encriptar/desencriptar strings, baseada no quadrado de Polybius

	Input:
		-letras: tuplo com 25 caracteres
	Output:
		-chave: tuplo com 5 elementos, cada elemento de chave-> 1 tuplo com 5 caracteres

	Funcoes (externas ao Python) usadas: Nenhuma
	"""

	chave= ()
	for i in range(5):
		#linha=tuplo de 5 caracteres, que forma as linhas horizontais do quadrado de Polybius
		linha= letras[(i*5):(i*5)+5] 
		chave= chave+(linha,)
	return chave


def obtem_codigo1(car,chave):
	"""
	Nome da funcao: obtem_codigo1
	-Dada um caractere singular e uma chave, codifica esse caractere

	Input:
		-car: 1 caractere, em principio pertencente a chave
		-chave: tuplo de tuplos; vide funcao gera_chave1/Output/chave
	Output:
		-cod: string da forma "xy", em que <chave>[x][y]= <car>

	Funcoes (externas ao Python) usadas: Nenhuma
	"""
	#procura em linha
	for x in range(len(chave)):
		#elementos da linha em questao
		for y in range(len(chave[x])):
			if car== chave[x][y]:
				cod= str(x)+str(y)
				return cod


def codifica1(cad, chave):
	"""
	Nome da funcao: codifica1
	-Dada uma string de caracteres e uma chave, codifica toda essa string

	Input:
		-cad: string de caracteres de comprimento variavel
		-chave: tuplo de tuplos; vide funcao gera_chave1/Output/<chave>
	Output:
		-cad_codificada: string de algarismos, que vem da substituicao de cada caractere de <cad> pelo codigo correspondente; vide obtem_codigo1

	Funcoes (externas ao Python) usadas: obtem_codigo1
	"""

	cad_codificada= ""
	for car in cad:
		cad_codificada= cad_codificada+obtem_codigo1(car,chave)
	return cad_codificada



def obtem_car1(cod,chave):
	"""
	Nome da funcao: obtem_car1
	-Dado um codigo e a chave correspondente, devolve o caractere descodificado

	Input:
		-cod: string da forma "xy"; vide funcao obtem_codigo1/Output/cod
		-chave: tuplo de tuplos; vide funcao gera_chave1/Output/chave
	Output:
		-car: 1 caractere de <chave>; vide funcao obtem_codigo1/Input/car

	Funcoes (externas ao Python) usadas: Nenhuma
	"""

	x= int(cod[0]) #1o caractere da cadeia "cod"
	y= int(cod[1]) #2o caractere da cadeia "cod"

	car= chave[x][y]
	return car


def descodifica1(cad_codificada,chave):
	"""
	Nome da funcao: descodifica1
	-Dada uma string codificada e a chave correspondente, devolve a string descodificada

	Input:
		-cad_codificada: string de algarismos; vide funcao codifica1/Output/cad_codificada
		-chave: tuplo de tuplos; vide funcao gera_chave1/Output/<chave>
	Output:
		-cad: string de caracteres de comprimento variavel

	Funcoes (externas ao Python) usadas: obtem_car1
	"""

	#2 caracteres de cad_codificada corresponde a 1 caractere de cad:
 	#usa-se metade de len(cad_codif.), para depois usar cada indice gerado
 	#para obter cod- uma string de dois algarismos;


	cad= ""
	for i in range(len(cad_codificada)//2):
		cod= cad_codificada[(2*i):(2*i+2)]
		cad= cad+obtem_car1(cod,chave)
	return cad









