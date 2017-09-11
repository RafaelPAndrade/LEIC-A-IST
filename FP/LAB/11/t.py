#Rafael Pestana de Andrade
#n. 86503
#12/XII/16

#Usando e adaptando funcoes anteriores
#dia 9 de outubro

def bissexto(ano):
	if ano%4==0:
		if ano%100==0 and ano%400!=0:
			return False
		else:
			return True
	else:
		return False


def teste_dia_mes(dia, mes, ano):
	if mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12:
		if dia> 31:
			raise ValueError('Dia nao pode ser maior do que 31')

	elif mes==2:
		if bissexto(ano):
			if dia> 29:
				raise ValueError('Fevereiro tem 29 dias no maximo')
		else:
			if dia>28:
				raise ValueError('Ano nao bissexto tem 28 dias em Fevereiro')

	elif mes==4 or mes==6 or mes==9 or mes==11:
		if dia> 30:
			raise ValueError('Dia nao pode ser maior do que 30 neste mes')

	else:
		raise ValueError('Mes invalido')


class data:

	def __init__(self, dia, mes, ano):
		if not (isinstance(dia, int) and \
		        isinstance(mes, int) and \
		        isinstance(ano, int)):
			raise TypeError('Argumentos invalidos')

		teste_dia_mes(dia, mes, ano)

		self.dia=dia
		self.mes=mes
		self.ano=ano

	def __repr__(self):
		if self.dia < 10:
			dia_string='0'+str(self.dia)
		else:
			dia_string=str(self.dia)

		if self.mes < 10:
			mes_string='0'+str(self.mes)
		else:
			mes_string=str(self.mes)


		ano_string=str(abs(self.ano))
		digitos_em_falta=4-len(ano_string)
		ano_string = '0'*digitos_em_falta+ano_string

		if self.ano < 0:
			ano_string += 'AC'

		return dia_string+'/'+mes_string+'/'+ano_string


	def dia(self):
		return self.dia

	def mes(self):
		return self.mes

	def ano(self):
		return self.ano

