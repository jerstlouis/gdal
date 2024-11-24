/******************************************************************************
 *
 * Project:  Microstation DGN Access Library
 * Purpose:  Internal (privatE) datastructures, and prototypes for DGN Access
 *           Library.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2000, Avenza Systems Inc, http://www.avenza.com/
 *
 * SPDX-License-Identifier: MIT
 ****************************************************************************/

#ifndef DGNLIBP_H_INCLUDED
#define DGNLIBP_H_INCLUDED

#include "cpl_vsi.h"
#include "cpl_vax.h"
#include "dgnlib.h"

typedef struct
{
    VSILFILE *fp;
    int next_element_id;

    int nElemBytes;
    GByte abyElem[131076 + 1];

    bool got_tcb;
    int dimension;
    int options;
    double scale;
    double origin_x;
    double origin_y;
    double origin_z;

    bool index_built;
    int element_count;
    int max_element_count;
    DGNElementInfo *element_index;

    int got_color_table;
    GByte color_table[256][3];

    bool got_bounds;
    GUInt32 min_x;
    GUInt32 min_y;
    GUInt32 min_z;
    GUInt32 max_x;
    GUInt32 max_y;
    GUInt32 max_z;

    bool has_spatial_filter;
    bool sf_converted_to_uor;

    bool select_complex_group;
    bool in_complex_group;

    GUInt32 sf_min_x;
    GUInt32 sf_min_y;
    GUInt32 sf_max_x;
    GUInt32 sf_max_y;

    double sf_min_x_geo;
    double sf_min_y_geo;
    double sf_max_x_geo;
    double sf_max_y_geo;
} DGNInfo;

#define DGN_INT32(p) ((p)[2] + ((p)[3] << 8) + ((p)[1] << 24) + ((p)[0] << 16))
#define DGN_WRITE_INT32(n, p)                                                  \
    {                                                                          \
        GInt32 nMacroWork = (GInt32)(n);                                       \
        ((unsigned char *)p)[0] =                                              \
            (unsigned char)((nMacroWork & 0x00ff0000) >> 16);                  \
        ((unsigned char *)p)[1] =                                              \
            (unsigned char)((nMacroWork & 0xff000000) >> 24);                  \
        ((unsigned char *)p)[2] =                                              \
            (unsigned char)((nMacroWork & 0x000000ff) >> 0);                   \
        ((unsigned char *)p)[3] =                                              \
            (unsigned char)((nMacroWork & 0x0000ff00) >> 8);                   \
    }

int DGNParseCore(DGNInfo *, DGNElemCore *);
void DGNTransformPoint(DGNInfo *, DGNPoint *);
void DGNInverseTransformPoint(DGNInfo *, DGNPoint *);
void DGNInverseTransformPointToInt(DGNInfo *, DGNPoint *, unsigned char *);
#define DGN2IEEEDouble CPLVaxToIEEEDouble
#define IEEE2DGNDouble CPLIEEEToVaxDouble
void DGNBuildIndex(DGNInfo *);
void DGNRad50ToAscii(unsigned short rad50, char *str);
void DGNAsciiToRad50(const char *str, unsigned short *rad50);
void DGNSpatialFilterToUOR(DGNInfo *);
int DGNLoadRawElement(DGNInfo *psDGN, int *pnType, int *pnLevel);

#endif /* ndef DGNLIBP_H_INCLUDED */
