#coding:utf-8

def conta_menores(t,n):
	res=0

	for e in t:
		if e<n:
			res+=1
	
	return res
