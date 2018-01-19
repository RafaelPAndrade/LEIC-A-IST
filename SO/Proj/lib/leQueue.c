/*---------------------------------------------------------------------------+
|    Module : leQueue.c (versao de formacao)
+----------------------------------------------------------------------------+
|
|    Author  :         Luis Rodrigues & Henrique J. Fonseca
|
|    Copyright (c) 1990, INESC.
|    All Rights Reserved. Licensed Material-Property of INESC
+----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------+
|  Includes
+----------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include "leQueue.h"

/*---------------------------------------------------------------------------+
|  Main LSE Functions 
+----------------------------------------------------------------------------*/

/*------------------------------------------------------------------+
|  Function: lePrintQueue
--------------------------------------------------------------------*/

void lePrintQueue (qh_p)
     QueHead* qh_p;
     
{
    QueElem* qe_p;

    printf ("<");
    for (qe_p = (QueElem*) leQueGetFirst (qh_p); 
	 qe_p; 
	 qe_p = (QueElem*) leQueGetNext (qh_p, qe_p))
      printf (".%d.", qe_p->key);
    printf (">\n");
}


/*------------------------------------------------------------------+
|   Function: leQueRemElem
--------------------------------------------------------------------*/

QueElem* leQueRemElem (qh_p, qe_p)
     QueHead *qh_p;
     QueElem *qe_p;
     
{
    if (qh_p->nel)
    {
	qh_p->nel--;
	qe_p->prev->next = qe_p->next;
	qe_p->next->prev = qe_p->prev;
	return (qe_p);
    }
    else
	return (0);
}


/*------------------------------------------------------------------+
|  Function: leQueInsAfter
--------------------------------------------------------------------*/

void leQueInsAfter (qh_p, qe_aft_p, qe_p)
     QueHead *qh_p;
     QueElem *qe_aft_p, *qe_p;
     
{
    qh_p->nel++;
    qe_p->next       = qe_aft_p->next;
    qe_p->next->prev = qe_p;
    qe_p->prev       = qe_aft_p;
    qe_aft_p->next   = qe_p;
}


/*------------------------------------------------------------------+
|  Function: leQueFindKey
--------------------------------------------------------------------*/

QueElem* leQueFindKey (qh_p, key)
     QueHead* qh_p;
     int      key;
     
{
    QueElem* qe_p;
  
    for (qe_p = (QueElem*) leQueGetFirst (qh_p); 
	 qe_p && (qe_p->key != key); 
	 qe_p = (QueElem*) leQueGetNext (qh_p, qe_p));
    
    return (qe_p);
}


/*------------------------------------------------------------------+
|  Function: leQueueIsIn
--------------------------------------------------------------------*/

QueElem* leQueueIsIn (qh_p, elm)
     QueHead* qh_p;
     QueElem* elm;
     
{
    QueElem* qe_p;
  
    for (qe_p = (QueElem*) leQueGetFirst (qh_p); 
	 qe_p && (qe_p != elm); 
	 qe_p = (QueElem*) leQueGetNext (qh_p, qe_p));
  
    return (qe_p);
}


/*------------------------------------------------------------------+
|  Function: leQueExec
--------------------------------------------------------------------*/

void leQueExec (qh_p, func)
     QueHead* qh_p;
     int      (*func) ();
     
{
    QueElem* qe_p;
  
    for (qe_p = (QueElem*) leQueGetFirst (qh_p); 
	 qe_p; 
	 qe_p = (QueElem*) leQueGetNext (qh_p, qe_p))
	(*func) (qe_p);
}


/*------------------------------------------------------------------+
|  Function: leQueInsByKey
--------------------------------------------------------------------*/

void leQueInsByKey (qh_p, qe_p)
     QueHead* qh_p;
     QueElem* qe_p;
     
{
    QueElem* qet_p;
    QueElem* qel_p;
  
    for (qet_p = (QueElem*) leQueGetFirst (qh_p), qel_p = 0; 
	 qet_p && (qet_p->key < qe_p->key);
	 qel_p = qet_p, qet_p = (QueElem*) leQueGetNext (qh_p, qet_p));
  
    if (qel_p)
	leQueInsAfter (qh_p, qel_p, qe_p);
    else 
	leQueInsFirst (qh_p, qe_p);
}


/*------------------------------------------------------------------+
|  Function: leQueRemAllKey 
--------------------------------------------------------------------*/

void      leQueRemAllKey (QueHead* h, int k){
  QueElem* q_e;

  while ((q_e=leQueFindKey(h, k))) {
    leQueRemElem (h, q_e);
    free (q_e);
  }
}


/*------------------------------------------------------------------+
|  Function: leQuePush  
--------------------------------------------------------------------*/

void      leQuePush           (QueHead* q_h, int k) {
  QueElem* q_e = leQueNewElem();

  leQueElemInit(q_e);
  leQueSetKey(q_e, k);
  leQueRemAllKey (q_h, k);
  leQueInsLast(q_h, q_e);
  while(leQueNbElem(q_h)>leQueMaxElem(q_h)){
    q_e = leQueRemFirst(q_h);
    free (q_e);
  }
  /* lePrintQueue (q_h); */
}


/*------------------------------------------------------------------+
|  Function: leQueFreeAll
--------------------------------------------------------------------*/

void      leQueFreeAll (QueHead* q_h) {
  QueElem* q_e;

  while ((q_e = leQueRemFirst(q_h)))
    free (q_e);
}

/*------------------------------------------------------------------+
|  Function: leQueDup
--------------------------------------------------------------------*/

void      leQueDup (QueHead* to, QueHead* from) {
  QueElem* q_e = leQueGetFirst(from);

  while (q_e) {
    leQuePush (to, leQueGetKey (q_e));
    q_e = leQueGetNext(from, q_e);
  }
}

