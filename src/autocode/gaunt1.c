/*
 * Copyright (C) 2013-  Qiming Sun <osirpt.sun@gmail.com>
 * Description: code generated by  gen-code.cl
 */
#include <stdlib.h>
#include "cint_bas.h"
#include "cart2sph.h"
#include "g1e.h"
#include "g2e.h"
#include "optimizer.h"
#include "cint1e.h"
#include "cint2e.h"
#include "misc.h"
#include "c2f.h"
/* <k i|GAUNT |SIGMA DOT P j SIGMA DOT P l> : i,j \in electron 1; k,l \in electron 2
 * = (i SIGMA DOT P j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_int2e_ssp1ssp2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
G2E_D_L(g1, g0, envs->i_l+0, envs->j_l+1, envs->k_l+0, envs->l_l+0);
G2E_D_J(g2, g0, envs->i_l+0, envs->j_l+0, envs->k_l, envs->l_l);
G2E_D_J(g3, g1, envs->i_l+0, envs->j_l+0, envs->k_l, envs->l_l);
double s[9];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 9; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[n*16+0] = + s[8] + s[4];
gout[n*16+1] = - s[1];
gout[n*16+2] = - s[2];
gout[n*16+3] = + s[5] - s[7];
gout[n*16+4] = - s[3];
gout[n*16+5] = + s[8] + s[0];
gout[n*16+6] = - s[5];
gout[n*16+7] = - s[2] + s[6];
gout[n*16+8] = - s[6];
gout[n*16+9] = - s[7];
gout[n*16+10] = + s[4] + s[0];
gout[n*16+11] = + s[1] - s[3];
gout[n*16+12] = + s[7] - s[5];
gout[n*16+13] = - s[6] + s[2];
gout[n*16+14] = + s[3] - s[1];
gout[n*16+15] = + s[0] + s[4] + s[8];
} else {
gout[n*16+0] += + s[8] + s[4];
gout[n*16+1] += - s[1];
gout[n*16+2] += - s[2];
gout[n*16+3] += + s[5] - s[7];
gout[n*16+4] += - s[3];
gout[n*16+5] += + s[8] + s[0];
gout[n*16+6] += - s[5];
gout[n*16+7] += - s[2] + s[6];
gout[n*16+8] += - s[6];
gout[n*16+9] += - s[7];
gout[n*16+10] += + s[4] + s[0];
gout[n*16+11] += + s[1] - s[3];
gout[n*16+12] += + s[7] - s[5];
gout[n*16+13] += - s[6] + s[2];
gout[n*16+14] += + s[3] - s[1];
gout[n*16+15] += + s[0] + s[4] + s[8];
}}}
void int2e_ssp1ssp2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {0, 1, 0, 1, 2, 4, 4, 1};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_ssp1ssp2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 1, 0, 1, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_ssp1ssp2;
envs.common_factor *= -1;
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_ssp1ssp2_cart
int int2e_ssp1ssp2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 1, 0, 1, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_ssp1ssp2;
envs.common_factor *= -1;
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_ssp1ssp2_sph
int int2e_ssp1ssp2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 1, 0, 1, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_ssp1ssp2;
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1i, &c2s_si_2e2i);
} // int2e_ssp1ssp2_spinor
ALL_CINT(int2e_ssp1ssp2)
ALL_CINT_FORTRAN_(int2e_ssp1ssp2)
/* <SIGMA DOT P k i|GAUNT |SIGMA DOT P j l> : i,j \in electron 1; k,l \in electron 2
 * = (i SIGMA DOT P j|GAUNT |SIGMA DOT P k l) */
static void CINTgout2e_int2e_ssp1sps2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
G2E_D_K(g1, g0, envs->i_l+0, envs->j_l+1, envs->k_l+0, envs->l_l);
G2E_D_J(g2, g0, envs->i_l+0, envs->j_l+0, envs->k_l, envs->l_l);
G2E_D_J(g3, g1, envs->i_l+0, envs->j_l+0, envs->k_l, envs->l_l);
double s[9];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 9; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[n*16+0] = + s[8] + s[4];
gout[n*16+1] = - s[1];
gout[n*16+2] = - s[2];
gout[n*16+3] = + s[5] - s[7];
gout[n*16+4] = - s[3];
gout[n*16+5] = + s[8] + s[0];
gout[n*16+6] = - s[5];
gout[n*16+7] = - s[2] + s[6];
gout[n*16+8] = - s[6];
gout[n*16+9] = - s[7];
gout[n*16+10] = + s[4] + s[0];
gout[n*16+11] = + s[1] - s[3];
gout[n*16+12] = - s[7] + s[5];
gout[n*16+13] = + s[6] - s[2];
gout[n*16+14] = - s[3] + s[1];
gout[n*16+15] = - s[0] - s[4] - s[8];
} else {
gout[n*16+0] += + s[8] + s[4];
gout[n*16+1] += - s[1];
gout[n*16+2] += - s[2];
gout[n*16+3] += + s[5] - s[7];
gout[n*16+4] += - s[3];
gout[n*16+5] += + s[8] + s[0];
gout[n*16+6] += - s[5];
gout[n*16+7] += - s[2] + s[6];
gout[n*16+8] += - s[6];
gout[n*16+9] += - s[7];
gout[n*16+10] += + s[4] + s[0];
gout[n*16+11] += + s[1] - s[3];
gout[n*16+12] += - s[7] + s[5];
gout[n*16+13] += + s[6] - s[2];
gout[n*16+14] += - s[3] + s[1];
gout[n*16+15] += - s[0] - s[4] - s[8];
}}}
void int2e_ssp1sps2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {0, 1, 1, 0, 2, 4, 4, 1};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_ssp1sps2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 1, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_ssp1sps2;
envs.common_factor *= -1;
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_ssp1sps2_cart
int int2e_ssp1sps2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 1, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_ssp1sps2;
envs.common_factor *= -1;
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_ssp1sps2_sph
int int2e_ssp1sps2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 1, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_ssp1sps2;
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1i, &c2s_si_2e2i);
} // int2e_ssp1sps2_spinor
ALL_CINT(int2e_ssp1sps2)
ALL_CINT_FORTRAN_(int2e_ssp1sps2)
/* <k SIGMA DOT P i|GAUNT |j SIGMA DOT P l> : i,j \in electron 1; k,l \in electron 2
 * = (SIGMA DOT P i j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_int2e_sps1ssp2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
G2E_D_L(g1, g0, envs->i_l+1, envs->j_l+0, envs->k_l+0, envs->l_l+0);
G2E_D_I(g2, g0, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_D_I(g3, g1, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
double s[9];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 9; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[n*16+0] = + s[8] + s[4];
gout[n*16+1] = - s[1];
gout[n*16+2] = - s[2];
gout[n*16+3] = - s[5] + s[7];
gout[n*16+4] = - s[3];
gout[n*16+5] = + s[8] + s[0];
gout[n*16+6] = - s[5];
gout[n*16+7] = + s[2] - s[6];
gout[n*16+8] = - s[6];
gout[n*16+9] = - s[7];
gout[n*16+10] = + s[4] + s[0];
gout[n*16+11] = - s[1] + s[3];
gout[n*16+12] = + s[7] - s[5];
gout[n*16+13] = - s[6] + s[2];
gout[n*16+14] = + s[3] - s[1];
gout[n*16+15] = - s[0] - s[4] - s[8];
} else {
gout[n*16+0] += + s[8] + s[4];
gout[n*16+1] += - s[1];
gout[n*16+2] += - s[2];
gout[n*16+3] += - s[5] + s[7];
gout[n*16+4] += - s[3];
gout[n*16+5] += + s[8] + s[0];
gout[n*16+6] += - s[5];
gout[n*16+7] += + s[2] - s[6];
gout[n*16+8] += - s[6];
gout[n*16+9] += - s[7];
gout[n*16+10] += + s[4] + s[0];
gout[n*16+11] += - s[1] + s[3];
gout[n*16+12] += + s[7] - s[5];
gout[n*16+13] += - s[6] + s[2];
gout[n*16+14] += + s[3] - s[1];
gout[n*16+15] += - s[0] - s[4] - s[8];
}}}
void int2e_sps1ssp2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 1};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_sps1ssp2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_sps1ssp2;
envs.common_factor *= -1;
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_sps1ssp2_cart
int int2e_sps1ssp2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_sps1ssp2;
envs.common_factor *= -1;
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_sps1ssp2_sph
int int2e_sps1ssp2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_sps1ssp2;
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1i, &c2s_si_2e2i);
} // int2e_sps1ssp2_spinor
ALL_CINT(int2e_sps1ssp2)
ALL_CINT_FORTRAN_(int2e_sps1ssp2)
/* <SIGMA DOT P k SIGMA DOT P i|GAUNT |j l> : i,j \in electron 1; k,l \in electron 2
 * = (SIGMA DOT P i j|GAUNT |SIGMA DOT P k l) */
static void CINTgout2e_int2e_sps1sps2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
G2E_D_K(g1, g0, envs->i_l+1, envs->j_l+0, envs->k_l+0, envs->l_l);
G2E_D_I(g2, g0, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_D_I(g3, g1, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
double s[9];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 9; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[n*16+0] = + s[8] + s[4];
gout[n*16+1] = - s[1];
gout[n*16+2] = - s[2];
gout[n*16+3] = - s[5] + s[7];
gout[n*16+4] = - s[3];
gout[n*16+5] = + s[8] + s[0];
gout[n*16+6] = - s[5];
gout[n*16+7] = + s[2] - s[6];
gout[n*16+8] = - s[6];
gout[n*16+9] = - s[7];
gout[n*16+10] = + s[4] + s[0];
gout[n*16+11] = - s[1] + s[3];
gout[n*16+12] = - s[7] + s[5];
gout[n*16+13] = + s[6] - s[2];
gout[n*16+14] = - s[3] + s[1];
gout[n*16+15] = + s[0] + s[4] + s[8];
} else {
gout[n*16+0] += + s[8] + s[4];
gout[n*16+1] += - s[1];
gout[n*16+2] += - s[2];
gout[n*16+3] += - s[5] + s[7];
gout[n*16+4] += - s[3];
gout[n*16+5] += + s[8] + s[0];
gout[n*16+6] += - s[5];
gout[n*16+7] += + s[2] - s[6];
gout[n*16+8] += - s[6];
gout[n*16+9] += - s[7];
gout[n*16+10] += + s[4] + s[0];
gout[n*16+11] += - s[1] + s[3];
gout[n*16+12] += - s[7] + s[5];
gout[n*16+13] += + s[6] - s[2];
gout[n*16+14] += - s[3] + s[1];
gout[n*16+15] += + s[0] + s[4] + s[8];
}}}
void int2e_sps1sps2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 1, 0, 2, 4, 4, 1};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_sps1sps2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_sps1sps2;
envs.common_factor *= -1;
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_sps1sps2_cart
int int2e_sps1sps2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_sps1sps2;
envs.common_factor *= -1;
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_sps1sps2_sph
int int2e_sps1sps2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_sps1sps2;
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1i, &c2s_si_2e2i);
} // int2e_sps1sps2_spinor
ALL_CINT(int2e_sps1sps2)
ALL_CINT_FORTRAN_(int2e_sps1sps2)
/* <k RC CROSS SIGMA i|GAUNT |j SIGMA DOT P l> : i,j \in electron 1; k,l \in electron 2
 * = (RC CROSS SIGMA i j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_int2e_cg_ssa10ssp2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
double dri[3];
dri[0] = envs->ri[0] - envs->env[PTR_COMMON_ORIG+0];
dri[1] = envs->ri[1] - envs->env[PTR_COMMON_ORIG+1];
dri[2] = envs->ri[2] - envs->env[PTR_COMMON_ORIG+2];
G2E_D_L(g1, g0, envs->i_l+1, envs->j_l+0, envs->k_l+0, envs->l_l+0);
G2E_RCI(g2, g0, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_RCI(g3, g1, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
double s[9];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 9; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[n*48+0] = + s[5] - s[7];
gout[n*48+1] = 0;
gout[n*48+2] = 0;
gout[n*48+3] = + s[8] + s[4];
gout[n*48+4] = + s[6];
gout[n*48+5] = + s[5];
gout[n*48+6] = + s[8];
gout[n*48+7] = - s[3];
gout[n*48+8] = - s[3];
gout[n*48+9] = - s[4];
gout[n*48+10] = - s[7];
gout[n*48+11] = - s[6];
gout[n*48+12] = + s[4] + s[8];
gout[n*48+13] = - s[3];
gout[n*48+14] = - s[6];
gout[n*48+15] = + s[7] - s[5];
gout[n*48+16] = - s[2];
gout[n*48+17] = - s[7];
gout[n*48+18] = - s[8];
gout[n*48+19] = - s[1];
gout[n*48+20] = 0;
gout[n*48+21] = - s[2] + s[6];
gout[n*48+22] = 0;
gout[n*48+23] = + s[8] + s[0];
gout[n*48+24] = + s[0];
gout[n*48+25] = + s[1];
gout[n*48+26] = + s[6];
gout[n*48+27] = - s[7];
gout[n*48+28] = - s[1];
gout[n*48+29] = + s[0] + s[8];
gout[n*48+30] = - s[7];
gout[n*48+31] = - s[6] + s[2];
gout[n*48+32] = + s[1];
gout[n*48+33] = + s[4];
gout[n*48+34] = + s[5];
gout[n*48+35] = - s[2];
gout[n*48+36] = - s[0];
gout[n*48+37] = - s[3];
gout[n*48+38] = - s[2];
gout[n*48+39] = - s[5];
gout[n*48+40] = 0;
gout[n*48+41] = 0;
gout[n*48+42] = + s[1] - s[3];
gout[n*48+43] = + s[4] + s[0];
gout[n*48+44] = - s[2];
gout[n*48+45] = - s[5];
gout[n*48+46] = + s[0] + s[4];
gout[n*48+47] = + s[3] - s[1];
} else {
gout[n*48+0] += + s[5] - s[7];
gout[n*48+1] += 0;
gout[n*48+2] += 0;
gout[n*48+3] += + s[8] + s[4];
gout[n*48+4] += + s[6];
gout[n*48+5] += + s[5];
gout[n*48+6] += + s[8];
gout[n*48+7] += - s[3];
gout[n*48+8] += - s[3];
gout[n*48+9] += - s[4];
gout[n*48+10] += - s[7];
gout[n*48+11] += - s[6];
gout[n*48+12] += + s[4] + s[8];
gout[n*48+13] += - s[3];
gout[n*48+14] += - s[6];
gout[n*48+15] += + s[7] - s[5];
gout[n*48+16] += - s[2];
gout[n*48+17] += - s[7];
gout[n*48+18] += - s[8];
gout[n*48+19] += - s[1];
gout[n*48+20] += 0;
gout[n*48+21] += - s[2] + s[6];
gout[n*48+22] += 0;
gout[n*48+23] += + s[8] + s[0];
gout[n*48+24] += + s[0];
gout[n*48+25] += + s[1];
gout[n*48+26] += + s[6];
gout[n*48+27] += - s[7];
gout[n*48+28] += - s[1];
gout[n*48+29] += + s[0] + s[8];
gout[n*48+30] += - s[7];
gout[n*48+31] += - s[6] + s[2];
gout[n*48+32] += + s[1];
gout[n*48+33] += + s[4];
gout[n*48+34] += + s[5];
gout[n*48+35] += - s[2];
gout[n*48+36] += - s[0];
gout[n*48+37] += - s[3];
gout[n*48+38] += - s[2];
gout[n*48+39] += - s[5];
gout[n*48+40] += 0;
gout[n*48+41] += 0;
gout[n*48+42] += + s[1] - s[3];
gout[n*48+43] += + s[4] + s[0];
gout[n*48+44] += - s[2];
gout[n*48+45] += - s[5];
gout[n*48+46] += + s[0] + s[4];
gout[n*48+47] += + s[3] - s[1];
}}}
void int2e_cg_ssa10ssp2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_cg_ssa10ssp2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_cg_ssa10ssp2;
envs.common_factor *= 1;
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_cg_ssa10ssp2_cart
int int2e_cg_ssa10ssp2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_cg_ssa10ssp2;
envs.common_factor *= 1;
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_cg_ssa10ssp2_sph
int int2e_cg_ssa10ssp2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_cg_ssa10ssp2;
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1, &c2s_si_2e2i);
} // int2e_cg_ssa10ssp2_spinor
ALL_CINT(int2e_cg_ssa10ssp2)
ALL_CINT_FORTRAN_(int2e_cg_ssa10ssp2)
/* <k R CROSS SIGMA i|GAUNT |j SIGMA DOT P l> : i,j \in electron 1; k,l \in electron 2
 * = (R CROSS SIGMA i j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_int2e_giao_ssa10ssp2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
G2E_D_L(g1, g0, envs->i_l+1, envs->j_l+0, envs->k_l+0, envs->l_l+0);
G2E_R_I(g2, g0, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_R_I(g3, g1, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
double s[9];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 9; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[n*48+0] = + s[5] - s[7];
gout[n*48+1] = 0;
gout[n*48+2] = 0;
gout[n*48+3] = + s[8] + s[4];
gout[n*48+4] = + s[6];
gout[n*48+5] = + s[5];
gout[n*48+6] = + s[8];
gout[n*48+7] = - s[3];
gout[n*48+8] = - s[3];
gout[n*48+9] = - s[4];
gout[n*48+10] = - s[7];
gout[n*48+11] = - s[6];
gout[n*48+12] = + s[4] + s[8];
gout[n*48+13] = - s[3];
gout[n*48+14] = - s[6];
gout[n*48+15] = + s[7] - s[5];
gout[n*48+16] = - s[2];
gout[n*48+17] = - s[7];
gout[n*48+18] = - s[8];
gout[n*48+19] = - s[1];
gout[n*48+20] = 0;
gout[n*48+21] = - s[2] + s[6];
gout[n*48+22] = 0;
gout[n*48+23] = + s[8] + s[0];
gout[n*48+24] = + s[0];
gout[n*48+25] = + s[1];
gout[n*48+26] = + s[6];
gout[n*48+27] = - s[7];
gout[n*48+28] = - s[1];
gout[n*48+29] = + s[0] + s[8];
gout[n*48+30] = - s[7];
gout[n*48+31] = - s[6] + s[2];
gout[n*48+32] = + s[1];
gout[n*48+33] = + s[4];
gout[n*48+34] = + s[5];
gout[n*48+35] = - s[2];
gout[n*48+36] = - s[0];
gout[n*48+37] = - s[3];
gout[n*48+38] = - s[2];
gout[n*48+39] = - s[5];
gout[n*48+40] = 0;
gout[n*48+41] = 0;
gout[n*48+42] = + s[1] - s[3];
gout[n*48+43] = + s[4] + s[0];
gout[n*48+44] = - s[2];
gout[n*48+45] = - s[5];
gout[n*48+46] = + s[0] + s[4];
gout[n*48+47] = + s[3] - s[1];
} else {
gout[n*48+0] += + s[5] - s[7];
gout[n*48+1] += 0;
gout[n*48+2] += 0;
gout[n*48+3] += + s[8] + s[4];
gout[n*48+4] += + s[6];
gout[n*48+5] += + s[5];
gout[n*48+6] += + s[8];
gout[n*48+7] += - s[3];
gout[n*48+8] += - s[3];
gout[n*48+9] += - s[4];
gout[n*48+10] += - s[7];
gout[n*48+11] += - s[6];
gout[n*48+12] += + s[4] + s[8];
gout[n*48+13] += - s[3];
gout[n*48+14] += - s[6];
gout[n*48+15] += + s[7] - s[5];
gout[n*48+16] += - s[2];
gout[n*48+17] += - s[7];
gout[n*48+18] += - s[8];
gout[n*48+19] += - s[1];
gout[n*48+20] += 0;
gout[n*48+21] += - s[2] + s[6];
gout[n*48+22] += 0;
gout[n*48+23] += + s[8] + s[0];
gout[n*48+24] += + s[0];
gout[n*48+25] += + s[1];
gout[n*48+26] += + s[6];
gout[n*48+27] += - s[7];
gout[n*48+28] += - s[1];
gout[n*48+29] += + s[0] + s[8];
gout[n*48+30] += - s[7];
gout[n*48+31] += - s[6] + s[2];
gout[n*48+32] += + s[1];
gout[n*48+33] += + s[4];
gout[n*48+34] += + s[5];
gout[n*48+35] += - s[2];
gout[n*48+36] += - s[0];
gout[n*48+37] += - s[3];
gout[n*48+38] += - s[2];
gout[n*48+39] += - s[5];
gout[n*48+40] += 0;
gout[n*48+41] += 0;
gout[n*48+42] += + s[1] - s[3];
gout[n*48+43] += + s[4] + s[0];
gout[n*48+44] += - s[2];
gout[n*48+45] += - s[5];
gout[n*48+46] += + s[0] + s[4];
gout[n*48+47] += + s[3] - s[1];
}}}
void int2e_giao_ssa10ssp2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_giao_ssa10ssp2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_giao_ssa10ssp2;
envs.common_factor *= 1;
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_giao_ssa10ssp2_cart
int int2e_giao_ssa10ssp2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_giao_ssa10ssp2;
envs.common_factor *= 1;
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_giao_ssa10ssp2_sph
int int2e_giao_ssa10ssp2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 1, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_giao_ssa10ssp2;
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1, &c2s_si_2e2i);
} // int2e_giao_ssa10ssp2_spinor
ALL_CINT(int2e_giao_ssa10ssp2)
ALL_CINT_FORTRAN_(int2e_giao_ssa10ssp2)
/* <k G i|GAUNT |SIGMA DOT P j SIGMA DOT P l> : i,j \in electron 1; k,l \in electron 2
 * = (G i SIGMA DOT P j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_int2e_gssp1ssp2(double *gout,
double *g, int *idx, CINTEnvVars *envs, int gout_empty) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
double *g4 = g3 + envs->g_size * 3;
double *g5 = g4 + envs->g_size * 3;
double *g6 = g5 + envs->g_size * 3;
double *g7 = g6 + envs->g_size * 3;
double rirj[3];
rirj[0] = envs->ri[0] - envs->rj[0];
rirj[1] = envs->ri[1] - envs->rj[1];
rirj[2] = envs->ri[2] - envs->rj[2];
double c[3];
c[0] = 1 * rirj[0];
c[1] = 1 * rirj[1];
c[2] = 1 * rirj[2];
G2E_D_L(g1, g0, envs->i_l+1, envs->j_l+1, envs->k_l+0, envs->l_l+0);
G2E_D_J(g2, g0, envs->i_l+1, envs->j_l+0, envs->k_l, envs->l_l);
G2E_D_J(g3, g1, envs->i_l+1, envs->j_l+0, envs->k_l, envs->l_l);
G2E_R0I(g4, g0, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_R0I(g5, g1, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_R0I(g6, g2, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
G2E_R0I(g7, g3, envs->i_l+0, envs->j_l, envs->k_l, envs->l_l);
double s[27];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 27; i++) { s[i] = 0; }
for (i = 0; i < nrys_roots; i++) {
s[0] += g7[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g6[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g6[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g5[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g4[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g4[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g5[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g4[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g4[ix+i] * g0[iy+i] * g3[iz+i];
s[9] += g3[ix+i] * g4[iy+i] * g0[iz+i];
s[10] += g2[ix+i] * g5[iy+i] * g0[iz+i];
s[11] += g2[ix+i] * g4[iy+i] * g1[iz+i];
s[12] += g1[ix+i] * g6[iy+i] * g0[iz+i];
s[13] += g0[ix+i] * g7[iy+i] * g0[iz+i];
s[14] += g0[ix+i] * g6[iy+i] * g1[iz+i];
s[15] += g1[ix+i] * g4[iy+i] * g2[iz+i];
s[16] += g0[ix+i] * g5[iy+i] * g2[iz+i];
s[17] += g0[ix+i] * g4[iy+i] * g3[iz+i];
s[18] += g3[ix+i] * g0[iy+i] * g4[iz+i];
s[19] += g2[ix+i] * g1[iy+i] * g4[iz+i];
s[20] += g2[ix+i] * g0[iy+i] * g5[iz+i];
s[21] += g1[ix+i] * g2[iy+i] * g4[iz+i];
s[22] += g0[ix+i] * g3[iy+i] * g4[iz+i];
s[23] += g0[ix+i] * g2[iy+i] * g5[iz+i];
s[24] += g1[ix+i] * g0[iy+i] * g6[iz+i];
s[25] += g0[ix+i] * g1[iy+i] * g6[iz+i];
s[26] += g0[ix+i] * g0[iy+i] * g7[iz+i];
}
if (gout_empty) {
gout[n*48+0] = - c[1]*s[26] + c[2]*s[17] - c[1]*s[22] + c[2]*s[13];
gout[n*48+1] = + c[1]*s[19] - c[2]*s[10];
gout[n*48+2] = + c[1]*s[20] - c[2]*s[11];
gout[n*48+3] = - c[1]*s[23] + c[2]*s[14] + c[1]*s[25] - c[2]*s[16];
gout[n*48+4] = + c[1]*s[21] - c[2]*s[12];
gout[n*48+5] = - c[1]*s[26] + c[2]*s[17] - c[1]*s[18] + c[2]*s[9];
gout[n*48+6] = + c[1]*s[23] - c[2]*s[14];
gout[n*48+7] = + c[1]*s[20] - c[2]*s[11] - c[1]*s[24] + c[2]*s[15];
gout[n*48+8] = + c[1]*s[24] - c[2]*s[15];
gout[n*48+9] = + c[1]*s[25] - c[2]*s[16];
gout[n*48+10] = - c[1]*s[22] + c[2]*s[13] - c[1]*s[18] + c[2]*s[9];
gout[n*48+11] = - c[1]*s[19] + c[2]*s[10] + c[1]*s[21] - c[2]*s[12];
gout[n*48+12] = - c[1]*s[25] + c[2]*s[16] + c[1]*s[23] - c[2]*s[14];
gout[n*48+13] = + c[1]*s[24] - c[2]*s[15] - c[1]*s[20] + c[2]*s[11];
gout[n*48+14] = - c[1]*s[21] + c[2]*s[12] + c[1]*s[19] - c[2]*s[10];
gout[n*48+15] = - c[1]*s[18] + c[2]*s[9] - c[1]*s[22] + c[2]*s[13] - c[1]*s[26] + c[2]*s[17];
gout[n*48+16] = - c[2]*s[8] + c[0]*s[26] - c[2]*s[4] + c[0]*s[22];
gout[n*48+17] = + c[2]*s[1] - c[0]*s[19];
gout[n*48+18] = + c[2]*s[2] - c[0]*s[20];
gout[n*48+19] = - c[2]*s[5] + c[0]*s[23] + c[2]*s[7] - c[0]*s[25];
gout[n*48+20] = + c[2]*s[3] - c[0]*s[21];
gout[n*48+21] = - c[2]*s[8] + c[0]*s[26] - c[2]*s[0] + c[0]*s[18];
gout[n*48+22] = + c[2]*s[5] - c[0]*s[23];
gout[n*48+23] = + c[2]*s[2] - c[0]*s[20] - c[2]*s[6] + c[0]*s[24];
gout[n*48+24] = + c[2]*s[6] - c[0]*s[24];
gout[n*48+25] = + c[2]*s[7] - c[0]*s[25];
gout[n*48+26] = - c[2]*s[4] + c[0]*s[22] - c[2]*s[0] + c[0]*s[18];
gout[n*48+27] = - c[2]*s[1] + c[0]*s[19] + c[2]*s[3] - c[0]*s[21];
gout[n*48+28] = - c[2]*s[7] + c[0]*s[25] + c[2]*s[5] - c[0]*s[23];
gout[n*48+29] = + c[2]*s[6] - c[0]*s[24] - c[2]*s[2] + c[0]*s[20];
gout[n*48+30] = - c[2]*s[3] + c[0]*s[21] + c[2]*s[1] - c[0]*s[19];
gout[n*48+31] = - c[2]*s[0] + c[0]*s[18] - c[2]*s[4] + c[0]*s[22] - c[2]*s[8] + c[0]*s[26];
gout[n*48+32] = - c[0]*s[17] + c[1]*s[8] - c[0]*s[13] + c[1]*s[4];
gout[n*48+33] = + c[0]*s[10] - c[1]*s[1];
gout[n*48+34] = + c[0]*s[11] - c[1]*s[2];
gout[n*48+35] = - c[0]*s[14] + c[1]*s[5] + c[0]*s[16] - c[1]*s[7];
gout[n*48+36] = + c[0]*s[12] - c[1]*s[3];
gout[n*48+37] = - c[0]*s[17] + c[1]*s[8] - c[0]*s[9] + c[1]*s[0];
gout[n*48+38] = + c[0]*s[14] - c[1]*s[5];
gout[n*48+39] = + c[0]*s[11] - c[1]*s[2] - c[0]*s[15] + c[1]*s[6];
gout[n*48+40] = + c[0]*s[15] - c[1]*s[6];
gout[n*48+41] = + c[0]*s[16] - c[1]*s[7];
gout[n*48+42] = - c[0]*s[13] + c[1]*s[4] - c[0]*s[9] + c[1]*s[0];
gout[n*48+43] = - c[0]*s[10] + c[1]*s[1] + c[0]*s[12] - c[1]*s[3];
gout[n*48+44] = - c[0]*s[16] + c[1]*s[7] + c[0]*s[14] - c[1]*s[5];
gout[n*48+45] = + c[0]*s[15] - c[1]*s[6] - c[0]*s[11] + c[1]*s[2];
gout[n*48+46] = - c[0]*s[12] + c[1]*s[3] + c[0]*s[10] - c[1]*s[1];
gout[n*48+47] = - c[0]*s[9] + c[1]*s[0] - c[0]*s[13] + c[1]*s[4] - c[0]*s[17] + c[1]*s[8];
} else {
gout[n*48+0] += - c[1]*s[26] + c[2]*s[17] - c[1]*s[22] + c[2]*s[13];
gout[n*48+1] += + c[1]*s[19] - c[2]*s[10];
gout[n*48+2] += + c[1]*s[20] - c[2]*s[11];
gout[n*48+3] += - c[1]*s[23] + c[2]*s[14] + c[1]*s[25] - c[2]*s[16];
gout[n*48+4] += + c[1]*s[21] - c[2]*s[12];
gout[n*48+5] += - c[1]*s[26] + c[2]*s[17] - c[1]*s[18] + c[2]*s[9];
gout[n*48+6] += + c[1]*s[23] - c[2]*s[14];
gout[n*48+7] += + c[1]*s[20] - c[2]*s[11] - c[1]*s[24] + c[2]*s[15];
gout[n*48+8] += + c[1]*s[24] - c[2]*s[15];
gout[n*48+9] += + c[1]*s[25] - c[2]*s[16];
gout[n*48+10] += - c[1]*s[22] + c[2]*s[13] - c[1]*s[18] + c[2]*s[9];
gout[n*48+11] += - c[1]*s[19] + c[2]*s[10] + c[1]*s[21] - c[2]*s[12];
gout[n*48+12] += - c[1]*s[25] + c[2]*s[16] + c[1]*s[23] - c[2]*s[14];
gout[n*48+13] += + c[1]*s[24] - c[2]*s[15] - c[1]*s[20] + c[2]*s[11];
gout[n*48+14] += - c[1]*s[21] + c[2]*s[12] + c[1]*s[19] - c[2]*s[10];
gout[n*48+15] += - c[1]*s[18] + c[2]*s[9] - c[1]*s[22] + c[2]*s[13] - c[1]*s[26] + c[2]*s[17];
gout[n*48+16] += - c[2]*s[8] + c[0]*s[26] - c[2]*s[4] + c[0]*s[22];
gout[n*48+17] += + c[2]*s[1] - c[0]*s[19];
gout[n*48+18] += + c[2]*s[2] - c[0]*s[20];
gout[n*48+19] += - c[2]*s[5] + c[0]*s[23] + c[2]*s[7] - c[0]*s[25];
gout[n*48+20] += + c[2]*s[3] - c[0]*s[21];
gout[n*48+21] += - c[2]*s[8] + c[0]*s[26] - c[2]*s[0] + c[0]*s[18];
gout[n*48+22] += + c[2]*s[5] - c[0]*s[23];
gout[n*48+23] += + c[2]*s[2] - c[0]*s[20] - c[2]*s[6] + c[0]*s[24];
gout[n*48+24] += + c[2]*s[6] - c[0]*s[24];
gout[n*48+25] += + c[2]*s[7] - c[0]*s[25];
gout[n*48+26] += - c[2]*s[4] + c[0]*s[22] - c[2]*s[0] + c[0]*s[18];
gout[n*48+27] += - c[2]*s[1] + c[0]*s[19] + c[2]*s[3] - c[0]*s[21];
gout[n*48+28] += - c[2]*s[7] + c[0]*s[25] + c[2]*s[5] - c[0]*s[23];
gout[n*48+29] += + c[2]*s[6] - c[0]*s[24] - c[2]*s[2] + c[0]*s[20];
gout[n*48+30] += - c[2]*s[3] + c[0]*s[21] + c[2]*s[1] - c[0]*s[19];
gout[n*48+31] += - c[2]*s[0] + c[0]*s[18] - c[2]*s[4] + c[0]*s[22] - c[2]*s[8] + c[0]*s[26];
gout[n*48+32] += - c[0]*s[17] + c[1]*s[8] - c[0]*s[13] + c[1]*s[4];
gout[n*48+33] += + c[0]*s[10] - c[1]*s[1];
gout[n*48+34] += + c[0]*s[11] - c[1]*s[2];
gout[n*48+35] += - c[0]*s[14] + c[1]*s[5] + c[0]*s[16] - c[1]*s[7];
gout[n*48+36] += + c[0]*s[12] - c[1]*s[3];
gout[n*48+37] += - c[0]*s[17] + c[1]*s[8] - c[0]*s[9] + c[1]*s[0];
gout[n*48+38] += + c[0]*s[14] - c[1]*s[5];
gout[n*48+39] += + c[0]*s[11] - c[1]*s[2] - c[0]*s[15] + c[1]*s[6];
gout[n*48+40] += + c[0]*s[15] - c[1]*s[6];
gout[n*48+41] += + c[0]*s[16] - c[1]*s[7];
gout[n*48+42] += - c[0]*s[13] + c[1]*s[4] - c[0]*s[9] + c[1]*s[0];
gout[n*48+43] += - c[0]*s[10] + c[1]*s[1] + c[0]*s[12] - c[1]*s[3];
gout[n*48+44] += - c[0]*s[16] + c[1]*s[7] + c[0]*s[14] - c[1]*s[5];
gout[n*48+45] += + c[0]*s[15] - c[1]*s[6] - c[0]*s[11] + c[1]*s[2];
gout[n*48+46] += - c[0]*s[12] + c[1]*s[3] + c[0]*s[10] - c[1]*s[1];
gout[n*48+47] += - c[0]*s[9] + c[1]*s[0] - c[0]*s[13] + c[1]*s[4] - c[0]*s[17] + c[1]*s[8];
}}}
void int2e_gssp1ssp2_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 1, 0, 1, 3, 4, 4, 3};
CINTall_2e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int2e_gssp1ssp2_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 1, 0, 1, 3, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_gssp1ssp2;
envs.common_factor *= 0.5;
envs.common_factor *= 0.5;
int i, nout;
int counts[4];
if (out != NULL && envs.shls[0] == envs.shls[1]) {
counts[0] = envs.nfi * envs.x_ctr[0];
counts[1] = envs.nfj * envs.x_ctr[1];
counts[2] = envs.nfk * envs.x_ctr[2];
counts[3] = envs.nfl * envs.x_ctr[3];
if (dims == NULL) { dims = counts; }
nout = dims[0] * dims[1] * dims[2] * dims[3];
for (i = 0; i < envs.ncomp_e1 * envs.ncomp_e2 * envs.ncomp_tensor; i++) {
c2s_dset0(out+nout*i, dims, counts); }
return 0; }
return CINT2e_cart_drv(out, dims, &envs, opt, cache);
} // int2e_gssp1ssp2_cart
int int2e_gssp1ssp2_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 1, 0, 1, 3, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_gssp1ssp2;
envs.common_factor *= 0.5;
envs.common_factor *= 0.5;
int i, nout;
int counts[4];
if (out != NULL && envs.shls[0] == envs.shls[1]) {
counts[0] = (envs.i_l*2+1) * envs.x_ctr[0];
counts[1] = (envs.j_l*2+1) * envs.x_ctr[1];
counts[2] = (envs.k_l*2+1) * envs.x_ctr[2];
counts[3] = (envs.l_l*2+1) * envs.x_ctr[3];
if (dims == NULL) { dims = counts; }
nout = dims[0] * dims[1] * dims[2] * dims[3];
for (i = 0; i < envs.ncomp_e1 * envs.ncomp_e2 * envs.ncomp_tensor; i++) {
c2s_dset0(out+nout*i, dims, counts); }
return 0; }
return CINT2e_spheric_drv(out, dims, &envs, opt, cache);
} // int2e_gssp1ssp2_sph
int int2e_gssp1ssp2_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 1, 0, 1, 3, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_int2e_gssp1ssp2;
envs.common_factor *= 0.5;
int i, nout;
int counts[4];
if (out != NULL && envs.shls[0] == envs.shls[1]) {
counts[0] = CINTcgto_spinor(envs.shls[0], envs.bas);
counts[1] = CINTcgto_spinor(envs.shls[1], envs.bas);
counts[2] = CINTcgto_spinor(envs.shls[2], envs.bas);
counts[3] = CINTcgto_spinor(envs.shls[3], envs.bas);
if (dims == NULL) { dims = counts; }
nout = dims[0] * dims[1] * dims[2] * dims[3];
for (i = 0; i < envs.ncomp_tensor; i++) {
c2s_zset0(out+nout*i, dims, counts); }
return 0; }
return CINT2e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_2e1, &c2s_si_2e2i);
} // int2e_gssp1ssp2_spinor
ALL_CINT(int2e_gssp1ssp2)
ALL_CINT_FORTRAN_(int2e_gssp1ssp2)
