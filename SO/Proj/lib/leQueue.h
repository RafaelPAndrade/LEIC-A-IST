/*---------------------------------------------------------------------------+
|    Module : leQueue.h (versao de formacao)
+----------------------------------------------------------------------------+
|
|    Author  :         Luis Rodrigues & Henrique J. Fonseca
|
|    Copyright (c) 1990, INESC.
|    All Rights Reserved. Licensed Material-Property of INESC
+----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------+
|                         Presentation
+----------------------------------------------------------------------+
|
| This module defines the following types:
|
|     type  QueHead
|     type  QueElem
|
| And the following functions or macros:
|
| - To create
|
|      QueHead*  leQueNewHead ( )
|      QueElem*  leQueNewElem ( )
|
| - To delete
|
|      void  leQueFreeHead ( QueHead* )
|      void  leQueFreeElem ( QueElem* )
|
| - To initialize
|
|      void      leQueHeadInit  ( QueHead* )
|      void      leQueElemInit  ( QueElem* )
|      void      leQueSetKey    ( QueElem* qe, int    k )
|      void      leQueGetKey    ( QueElem* qe )
|      void      leQueExec      ( QueHead* qh_p, int (*func) ()
|
| - To get
|
|      QueElem*  leQueGetFirst  ( QueHead* qh )
|      QueElem*  leQueGetLast   ( QueHead* qh )
|      QueElem*  leQueGetPrev   ( QueHead* qh, QueElem* qe )
|      QueElem*  leQueGetNext   ( QueHead* qh, QueElem* qe )
|      QueElem*  leQueFindKey   ( QueHead* qh, int      key )
|
| - To insert
|
|      void      leQueInsFirst  ( QueHead* qh, QueElem* qe )
|      void      leQueInsLast   ( QueHead* qh, QueElem* qe )
|      void      leQueInsBefore ( QueHead* qh, QueElem* before,  QueElem* qe )
|      void      leQueInsAfter  ( QueHead* qh, QueElem* after,  QueElem* qe )
|      void      leQueInsByKey  ( QueHead* qh, QueElem* qe )
|
| - To remove
|
|      QueElem*  leQueRemElem   ( QueHead* qh, QueElem* qe )
|      QueElem*  leQueRemFirst  ( QueHead* qh )
|      QueElem*  leQueRemLast   ( QueHead* qh )
|
| - To test
|
|      int       leQueTestEmpty ( QueHead* qh)
|      int       leQueSize      ( QueHead* qh)
|      int       leQueTestIsIn  ( QueHead* qh, QueElem* qe )
|
+----------------------------------------------------------------------*/


#ifndef LEQUEUE
#define LEQUEUE


/*---------------------------------------------------------------------+
|   Global Definitions
+----------------------------------------------------------------------*/

typedef	struct	QueElem  
{
    struct QueElem *prev;
    struct QueElem *next;
    int            key;
} QueElem;

#define  SzQueElem  sizeof (struct QueElem)

typedef struct QueHead	
{
  QueElem elem;
  int     nel;
  int     maxelem;
} QueHead;

#define  SzQueHead  sizeof (struct QueHead)

/*------------------------------------------------------------------+
|   Macros
--------------------------------------------------------------------*/

#define  leQueNewHead()  ((QueHead*) malloc (SzQueHead))
#define  leQueNewElem()  ((QueElem*) malloc (SzQueElem))

#define  leQueFreeHead(qh_p)  free (qh_p)
#define  leQueFreeElem(qe_p)  free (qe_p)

#define  leQueHeadInit(qh_p, max)			\
if (1) {\
  ((QueHead*)qh_p)->elem.next  = (QueElem*) &(qh_p->elem);	\
  ((QueHead*)qh_p)->elem.prev  = (QueElem*) &(qh_p->elem);	\
  ((QueHead*)qh_p)->nel        = 0; \
  ((QueHead*)qh_p)->maxelem    = max; \
} else

#define  leQueElemInit(qe_p)    \
if (1) {\
    ((QueElem*)qe_p)->prev = 0; \
    ((QueElem*)qe_p)->next = 0; \
} else

#define  leQueSetKey(qe_p, k)  ((QueElem*)qe_p)->key = k
#define  leQueGetKey(qe_p)     ((QueElem*)qe_p)->key

#define  leQueGetFirst(qh_p)      \
    (((QueHead*)qh_p)->nel ? ((QueHead*)qh_p)->elem.next : 0)
#define  leQueGetLast(qh_p)       \
    (((QueHead*)qh_p)->nel ? ((QueHead*)qh_p)->elem.prev : 0)
#define  leQueGetPrev(qh_p, qe_p) \
  ((((QueElem*)qe_p)->prev != (QueElem*)(&(qh_p->elem))) ? ((QueElem*)qe_p)->prev : 0)
#define  leQueGetNext(qh_p, qe_p) \
  ((((QueElem*)qe_p)->next != (QueElem*)(&(qh_p->elem))) ? ((QueElem*)qe_p)->next : 0)

#define  leQueInsFirst(qh_p, qe_p)        \
  leQueInsAfter (qh_p, &(qh_p->elem), ((QueElem*)qe_p))
#define  leQueInsLast(qh_p, qe_p)         \
  leQueInsAfter (qh_p, ((QueHead*)qh_p)->elem.prev, ((QueElem*)qe_p))
#define  leQueInsBefore(qh_p, qb_p, qe_p) \
  leQueInsAfter (qh_p, ((QueElem*)qb_p)->prev, ((QueElem*)qe_p))

#define  leQueRemFirst(qh_p)  leQueRemElem (qh_p, ((QueHead*)qh_p)->elem.next)
#define  leQueRemLast(qh_p)   leQueRemElem (qh_p, ((QueHead*)qh_p)->elem.prev)

#define  leQueTestEmpty(qh_p)  (((QueHead*)qh_p)->nel == 0)

#define  leQueSize(qh_p)  (((QueHead*)qh_p)->nel)
#define  leQueNbElem(qh_p)  (((QueHead*)qh_p)->nel)
#define  leQueMaxElem(qh_p)  (((QueHead*)qh_p)->maxelem)


/*------------------------------------------------------------------+
|   Functions
--------------------------------------------------------------------*/

QueElem*  leQueFindKey     (QueHead* h, int k);
void      leQueInsAfter    (QueHead* h, QueElem*, QueElem* e);
void      leQueInsByKey    (QueHead* h, QueElem* e);
QueElem*  leQueRemElem     (QueHead* h, QueElem* e);
QueElem*  leQueIsIn        (QueHead* h, QueElem* e);
void      leQueExec        (QueHead* h, int (*func) ());
void      leQueRemAllKey   (QueHead* h, int k);
void      leQuePush        (QueHead* h, int k);
void      leQueFreeAll     (QueHead* h);
void      leQueDup         (QueHead* to, QueHead* from);

#endif /* LEQUEUE */

