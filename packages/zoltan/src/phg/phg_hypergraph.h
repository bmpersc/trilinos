/*****************************************************************************
 * Zoltan Dynamic Load-Balancing Library for Parallel Applications           *
 * Copyright (c) 2000, Sandia National Laboratories.                         *
 * For more info, see the README file in the top-level Zoltan directory.     *
 *****************************************************************************/
/*****************************************************************************
 * CVS File Information :
 *    $RCSfile$
 *    $Author$
 *    $Date$
 *    $Revision$
 ****************************************************************************/

#ifndef __PHG_HYPERGRAPH_H
#define __PHG_HYPERGRAPH_H

#ifdef __cplusplus
/* if C++, define the rest of this header file as extern C */
extern "C" {
#endif


typedef struct {
   int info;    /* primarily for debugging recursive algorithms;initially 0 */
   int nVtx;    /* number of vertices, |V| */
   int nEdge;   /* Size of neigh array; 2|E| */
   int nDim;    /* Number of dimensions for a vertex's coordinate */
   int VtxWeightDim;  /* number of weight dimensions for a vertex */
   int EdgeWeightDim;    /* number of weight dimensions for an edge */
   int redl;             /* Working Reduction limit. */

   int *vtxdist;  /* distributions of vertices to processors, as in ParMETIS.
                     Vertices vtxdist[n] to vtxdist[n+1]-1 are stored on
                     processor n.   KDD:  temporary; may change later. */

   /* physical coordinates of each vertex, optional */
   double *coor; /*  |V| long by CoordinateDim */

   /* arrays with vertex and edge weights */
   float *vwgt;  /* weights of vertices, |V| long by VtxWeightDim */
   float *ewgt;  /* weights of hypergraph edges, 2|E| long by EdgeWeightDim */

   /* arrays to look up the neighbors of a vertex */
   int *nindex;  /* length |V|+1 index to neigh, last is 2|E| */
   int *neigh;   /* length 2|E|, list of neighbors for each vertex */
} PGraph;
  
typedef struct {
  int info;       /* primarily for debugging recursive algorithms;initially 0 */
  PHGComm *comm;  /* this is a pointer to storage PHGPartParamsStruct: (set in phg_build)
                     UVCUVC: I've included here because nProc_x, nProc_y was here
                     for convenience.
                   */
  int *dist_x;    /* distributions of vertices to processor columns. Vertices
                   * dist_x[n] to dist_x[n+1]-1 are stored in col block n */
  int *dist_y;    /* distribution of hyperedges to processor rows as above */                  
  int nVtx;             /* number of vertices on this processor */
  int nEdge;            /* number of hyperedges on this processor */
  int nNonZero;         /* number of nonzeros (pins) on this processor */
  
  int VtxWeightDim;  /* number of weight dimensions for a vertex */
  int EdgeWeightDim;    /* number of weight dimensions for a hyperedge */

  int redl;             /* working reduction limit */

  /* physical coordinates of each vertex, optional */
  int nDim;         /* number of coordinate dimensions for a vertex */
  double *coor;     /* |V| long by CoordinateDim */

  /* arrays with vertex and edge weights */
  float *vwgt;    /* weights of vertices, nVtx long by VtxWeightDim */
  float *ewgt;    /* weights of hypergraph edges, nEdge long by EdgeWeightDim */

  /* arrays to look up vertices given a hyperedge */
  int *hindex;      /* length nEdge+1 index into hvertex, last is nNonZero */
  int *hvertex;     /* length nNonZero array containing associated vertices */

  /* arrays to look up hyperedges given a vertex */
  int *vindex;      /* length nVtx+1 index into vedge, last is nNonZero */
  int *vedge;       /* length nNonZero array containing associated hyperedges */
  
  int *vmap;        /* used when recursively dividing for p > 2 */
  double ratio;     /* split when recursively dividing for p > 2 */
} PHGraph;


#ifdef __cplusplus
} /* closing bracket for extern "C" */
#endif

#endif   /* ZOLTAN_HYPERGRAPH_H */
