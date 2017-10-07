#Rafael P Andrade
#Ficha 11: Programao com objetos (classes)
#9/XII/16

#1)

class estacionamento:

	def __init__(self, lugares):
		self.lug_total=lugares
		self.lug_vagos=lugares

	def lugares(self):
		return self.lug_vagos

	def entra(self):
		if self.lug_vagos>0:
			self.lug_vagos-=1
		else:
			raise ValueError('Sem lugares')

	def sai(self):
		if self.lug_vagos<self.lug_total:
			self.lug_vagos+=1
		else:
			raise ValueError('Sem carros')

#2)
class racional:
#a)
	def __init__(self, num, den):
		if not ( isinstance(num, int) and isinstance(den, int) ):
			raise TypeError('Argumentos invalidos')
		elif den == 0:
			raise ValueError('Erro: denominador nao pode ser nulo')
		self.num= num
		self.den= den


	def __repr__(self):
	#Com ajuda, usando algoritmo de Euclides para simplificacao (mdc)
		def gcd(a,b):
			while b:
				a, b = b, a%b
			return a

		if self.den//maior_div_comum == 1:
			return str(1)
		else:
			maior_div_comum=gcd(self.num, self.den)
			return str(self.num//maior_div_comum) + '/' + \
			       str(self.den//maior_div_comum)


	def iguais(self, r):
		if not isinstance(r, racional):
			raise TypeError('Evite comparar alhos e bugalhos...')

		if self.num*r.den == r.num*self.den:
			return True
		else:
			return False

	def nume(self):
		return self.num

	def deno(self):
		return self.den

#b)
	def __add__(self, r):
		if not isinstance(r, racional):
			raise TypeError('Soma com alhos e bugalhos')
		return racional(self.num*r.den + r.num*self.den, self.den*r.den )


	def __mul__(self, r):
		# O enunciado tem um erro aqui...
		if not isinstance(r, racional):
			raise TypeError('Soma com alhos e bugalhos')
		return racional(self.num*r.num, self.den*r.den)

#3)
class automovel:

	def __init__(self, deposito, combustivel, consumo):
		if not ( isinstance(deposito, (int, float)) and \
		         isinstance(combustivel, (int, float)) and \
		         isinstance(consumo, (int, float)) ):
			raise TypeError('Reveja argumentos')

		if combustivel>deposito:
			raise ValueError('Nao pode levar garrafoes')
		if consumo <=0:
			raise ValueError('Carro nao pode ser eletrico')
		if deposito<0 or combustivel<0:
			raise ValueError('Numeros positivos,sff')


		self.deposit = deposito
		self.fuel = combustivel
		self.consumo = consumo

	def combustivel(self):
		return self.fuel

	def autonomia(self):
		return (self.fuel*100)//self.consumo

	def abastece(self, litros):
		if litros+self.fuel>self.deposit:
			raise ValueError('Impossivel, overflow')
		else:
			self.fuel+=litros

	def percorre(self, km):
		if km > self.autonomia():
			raise ValueError('Impossivel, muito longe')
		else:
			self.fuel= self.fuel - ((km//100)*self.consumo)
			print('Viagem feita')


#4)
#E para usar a notacao de class? nao parece, pela especificacao
class conjunto:
	#usando lista para guardar os elementos

	def __repr__(self):
		return str(self.elementos)

	#Construtores
	def __init__(self):
		self.elementos=[]

	def insere(self, el):
		if el not in self.elementos:
			self.elementos+=[el]
		return self

	#Seletores
	def el_conj(self):
		if len(self.elementos)>0:
			from random import random
			return self.elementos[ int( random()* len(self.elementos) )]


	def retira_conj(self, el):
		if el in self.elementos:
			for i in range(len(self.elementos)-1, -1, -1):
				if el== self.elementos[i]:
					del(self.elementos[i])
		return self


	def cardinal(self):
		return len(self.elementos)


	#Reconhecedores
	def e_conj_vazio(self):
		if self.cardinal() == 0:
			return True
		else:
			return False

	#Testes
	def pertence(self, el):
		if el in self.elementos:
			return True
		else:
			return False

	#Adicionais
	def subconjunto(self, c):
		if not isinstance(c, conjunto):
			raise ValueError('Bugalhos nao pode ser subconjunto de alhos')

		for el in self.elementos:
			if not c.pertence(el):
				return False
		return True

	def uniao(self, c):
		if not isinstance(c, conjunto):
			raise ValueError('Bugalhos nao pode ser unido com alhos')

		if self.subconjunto(c)== True:
			return c
		if c.subconjunto(self)== True:
			return self

		res=conjunto()
		for el in self.elementos:
			res.insere(el)
		for el in c.elementos:
			res.insere(el)
		return res

	def intersecao(self, c):
		if not isinstance(c, conjunto):
			raise ValueError('Bugalhos nao pode ser intersetado com alhos')

		if self.subconjunto(c)== True:
			return self
		if c.subconjunto(self)== True:
			return c

		res=conjunto()
		for el in self.elementos:
			if c.pertence(el):
				res.insere(el)

	def diferenca(self,c):
		if not isinstance(c, conjunto):
			raise ValueError('Bugalhos nao pode ser diferenciado de alhos')

		res=conjunto()

		if not self.subconjunto(c):
			for el in self.elementos:
				if not c.pertence(el):
					res.insere(el)
		return res


#5)
class mem_A:

	def __init__(self):
		self.values={}


	def val(self,m,n):
		if (m,n) not in self.values:
			if m == 0:
				self.values[(m,n)]=n+1
			elif m > 0 and n == 0:
				self.values[(m,n)]=self.val(m-1,1)
			else:
				self.values[(m,n)]=self.val(m-1, self.val(m, n-1))

		return self.values[(m,n)]



	def mem(self):
		return self.values
