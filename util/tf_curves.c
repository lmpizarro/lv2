#include <math.h>
#include <stdlib.h>
#include "tf_curves.h"

void CMPR_Set_RBT(CMPR * f){

   if (f->dbThr < -50.0f )
	   f->N = 1.05f;
   else if (f->dbThr >= 50.0f && f->dbThr < 30.0f)
	   f->N = 0.045f * f->dbThr + 3.35f;
   else if (f->dbThr >= 30.0f && f->dbThr < 5.0f)
	   f->N = 0.32f * f->dbThr + 11.6f;
   else if (f->dbThr >= 5.0f && f->dbThr <= 0.0f)
	   f->N = 2.0f * f->dbThr + 20.0f;
   else
	   f->N = 25.0f;
}

void CMPR_Set_T(CMPR * f, const float dbThr){
  f->dbThr = dbThr;
  f->dbThrK1 = f->dbThr - f->dbKn;
  if (f->dbThrK1 < -60.0f) f->dbThrK1 = -60.0f;
  f->dbThrK2 = f->dbThr + f->dbKn;
  if (f->dbThrK2 > 0.0f) f->dbThrK2 = 0.0f;

  f->linThr =  pow(10.0f, f->dbThr / 20.0f);
  f->linThrK1 =  pow(10.0f, (f->dbThrK1) / 20.0f);
  f->linThrK2 =  pow(10.0f, (f->dbThrK2) / 20.0f);
}

void CMPR_Set_Kn(CMPR * f, const float dbKn){
  f->dbKn = dbKn;
  CMPR_Set_T(f, f->dbThr);
}

void CMPR_Set_TNK(CMPR * f, const float dbThr, const float N, const float dbKn){

  f->dbKn = dbKn;
 
  CMPR_Set_T(f, dbThr);

  f->N = N;
  f->Np = 2 * N/ (1 + N);
}


CMPR *CMPR_C (const float dbThr, const float N, const float dbKn)
{

  CMPR *f = (CMPR *) calloc(1, sizeof(CMPR));

  CMPR_Set_TNK(f, dbThr, N, dbKn);

  return f;
}

void CMPR_D (CMPR *f){
   free(f);
}

float sign(const float n){
   int s;
   if (n<0) s = -1.0f;
   if (n>=0) s = 1.0f;
   return s;
}

float CMPR_R (CMPR *f, const float inp){
   float out, absInp;
   out = 0.0f;

   absInp = fabs(inp);

   if (absInp <= f->linThrK1)
      out = absInp;
   else if (absInp > f->linThrK1 && absInp <= f->linThrK2)
      out = pow(absInp, 1.0f/f->Np) * pow(f->linThrK1 , (f->Np - 1.0f)/f->Np);
   else if (absInp > f->linThrK2 && absInp <= 1.0f)
      out = pow(absInp, 1.0f/f->N) * pow(f->linThr, (f->N - 1.0f)/f->N);

   out = out * sign(inp);

   return out;
}


