#ifndef _TF_CURVES_H
#define _TF_CURVES_H

typedef struct {
   float dbThr;
   float dbKn;
   float dbThrK1;
   float dbThrK2;

   float N;
   float Np;

   float linThr;
   float linThrK1;
   float linThrK2;

}CMPR;

CMPR *CMPR_C (const float dbThr, const float dbN, const float dbKn);
void CMPR_D (CMPR *);
float CMPR_R (CMPR *, const float inp);
void CMPR_Set_TNK(CMPR * f, const float dbThr, const float N, const float dbKn);
void CMPR_Set_RBT(CMPR * f);
void CMPR_Set_T(CMPR * f, const float dbThr);
void CMPR_Set_Kn(CMPR * f, const float dbKn);

#endif
