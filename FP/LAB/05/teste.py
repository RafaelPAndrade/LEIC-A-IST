#coding:utf-8



def j(lst1,lst2):
	if lst1==[] or lst2==[]:
		return lst1+lst2
	elif lst1[0]<lst2[0]:
		return [lst1[0]]+j(lst1[1:],lst2)
	else:
		return [lst2[0]]+j(lst1,lst2[1:])
