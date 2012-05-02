/*! \file quadrature.c
 *  \brief Quadrature rules
 */

#include <stdio.h>

#include "fasp.h"
#include "fasp_functs.h"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/**
 * \fn void fasp_quad2d (INT num_qp, INT ncoor, REAL (*quad)[3])
 *
 * \brief Initialize Lagrange quadrature points and weights
 *
 * \param num_qp    Number of quadrature points
 * \param ncoor     Dimension of space
 * \param quad      Quadrature points and weights
 * 
 * \author Xuehai Huang, Chensong Zhang, Ludmil Zikatanov
 * \date 10/21/2008
 * 
 * \note quad[*][0] -- quad point x in ref coor
 *     quad[*][1] -- quad point y in ref coor
 *       quad[*][2] -- quad weight
 */
void fasp_quad2d (INT num_qp, 
                  INT ncoor, 
                  REAL (*quad)[3])
{
    if (num_qp<=0) fasp_chkerr(ERROR_QUAD_TYPE, "fasp_quad2d");
    
    if (ncoor!=2) fasp_chkerr(ERROR_QUAD_DIM, "fasp_quad2d");
    
    switch (num_qp) {
    case 1:  // 1-point Gauss rule
        quad[0][0] = 1.0/3;
        quad[0][1] = 1.0/3;
        quad[0][2] = 0.5000000000000000000000000;
        break;
    case 0:  // 3-point mid-point rule
        quad[0][0] = 0.5000000000000000000000000;
        quad[0][1] = 0.5000000000000000000000000;
        quad[0][2] = 0.1666666666666666666666667;
    
        quad[1][0] = 0.0000000000000000000000000;
        quad[1][1] = 0.5000000000000000000000000;
        quad[1][2] = 0.1666666666666666666666667;
    
        quad[2][0] = 0.5000000000000000000000000;
        quad[2][1] = 0.0000000000000000000000000;
        quad[2][2] = 0.1666666666666666666666667;
        break;
    case 3:  // 3-point Lagrange rule
        quad[0][0] = 1.0000000000000000000000000;
        quad[0][1] = 0.0000000000000000000000000;
        quad[0][2] = 0.1666666666666666666666667;
    
        quad[1][0] = 0.0000000000000000000000000;
        quad[1][1] = 1.0000000000000000000000000;
        quad[1][2] = 0.1666666666666666666666667;
    
        quad[2][0] = 0.0000000000000000000000000;
        quad[2][1] = 0.0000000000000000000000000;
        quad[2][2] = 0.1666666666666666666666667;
        break;
    case 6:  // 6-point Newton-Cotes rule
        quad[0][0] = 1;
        quad[0][1] = 0;
        quad[0][2] = 1.0/24;
    
        quad[1][0] = 0;
        quad[1][1] = 1;
        quad[1][2] = 1.0/24;
    
        quad[2][0] = 0;
        quad[2][1] = 0;
        quad[2][2] = 1.0/24;
    
        quad[3][0] = 0.5;
        quad[3][1] = 0.5;
        quad[3][2] = 0.125;
    
        quad[4][0] = 0;
        quad[4][1] = 0.5;
        quad[4][2] = 0.125;
    
        quad[5][0] = 0.5;
        quad[5][1] = 0;
        quad[5][2] = 0.125;
        break;
    case 7:  // 7-point Newton-Cotes rule
        quad[0][0] = 1;
        quad[0][1] = 0;
        quad[0][2] = 1.0/18;
    
        quad[1][0] = 0;
        quad[1][1] = 1;
        quad[1][2] = 1.0/18;
    
        quad[2][0] = 0;
        quad[2][1] = 0;
        quad[2][2] = 1.0/18;
    
        quad[3][0] = 0.5;
        quad[3][1] = 0.5;
        quad[3][2] = 1.0/18;
    
        quad[4][0] = 0;
        quad[4][1] = 0.5;
        quad[4][2] = 1.0/18;
    
        quad[5][0] = 0.5;
        quad[5][1] = 0;
        quad[5][2] = 1.0/18;
    
        quad[6][0] = 1.0/3;
        quad[6][1] = 1.0/3;
        quad[6][2] = 1.0/6;
        break;
    case 15:  // 15-point Lagrange rule
        quad[0][0] = 1;
        quad[0][1] = 0;
        quad[0][2] = 1.0/96;
    
        quad[1][0] = 0;
        quad[1][1] = 1;
        quad[1][2] = 1.0/96;
    
        quad[2][0] = 0;
        quad[2][1] = 0;
        quad[2][2] = 1.0/96;
    
        quad[3][0] = 0.75;
        quad[3][1] = 0.25;
        quad[3][2] = 1.0/32;
    
        quad[4][0] = 0.5;
        quad[4][1] = 0.5;
        quad[4][2] = 1.0/32;
    
        quad[5][0] = 0.25;
        quad[5][1] = 0.75;
        quad[5][2] = 1.0/32;
    
        quad[6][0] = 0;
        quad[6][1] = 0.75;
        quad[6][2] = 1.0/32;
    
        quad[7][0] = 0;
        quad[7][1] = 0.5;
        quad[7][2] = 1.0/32;
    
        quad[8][0] = 0;
        quad[8][1] = 0.25;
        quad[8][2] = 1.0/32;
    
        quad[9][0] = 0.25;
        quad[9][1] = 0;
        quad[9][2] = 1.0/32;
    
        quad[10][0] = 0.5;
        quad[10][1] = 0;
        quad[10][2] = 1.0/32;
    
        quad[11][0] = 0.75;
        quad[11][1] = 0;
        quad[11][2] = 1.0/32;
    
        quad[12][0] = 0.5;
        quad[12][1] = 0.25;
        quad[12][2] = 1.0/16;
    
        quad[13][0] = 0.25;
        quad[13][1] = 0.5;
        quad[13][2] = 1.0/16;
    
        quad[14][0] = 0.25;
        quad[14][1] = 0.25;
        quad[14][2] = 1.0/16;
        break;
    default:
        fasp_chkerr(ERROR_QUAD_TYPE, "fasp_quad2d");
        break;
    }
    
    return;
}

/**
 * \fn void fasp_gauss2d (INT num_qp, INT ncoor,  REAL (*gauss)[3])
 *
 * \brief Initialize Gauss quadrature points and weights
 *
 * \param num_qp   Number of quadrature points
 * \param ncoor    Dimension of space
 * \param gauss    Quadrature points and weight
 * 
 * \author Xuehai Huang, Chensong Zhang, Ludmil Zikatanov
 * \date 10/21/2008
 * 
 * \note gauss[*][0] -- quad point x in ref coor
 *     gauss[*][1] -- quad point y in ref coor
 *       gauss[*][2] -- quad weight
 */
void fasp_gauss2d (INT num_qp, 
                   INT ncoor, 
                   REAL (*gauss)[3])
{
    if(num_qp<=0) fasp_chkerr(ERROR_QUAD_TYPE, "fasp_gauss2d");
    
    if(ncoor!=2) fasp_chkerr(ERROR_QUAD_DIM, "fasp_gauss2d");
    
    switch (num_qp) {
    case 1:  // 1-point Gauss rule
        gauss[0][0] = 1.0/3;
        gauss[0][1] = 1.0/3;
        gauss[0][2] = 0.5000000000000000000000000;
        break;
    case 3:  // 3-point Gauss rule
        gauss[0][0] = 0.1666666666666666666666667;
        gauss[0][1] = 0.1666666666666666666666667;
        gauss[0][2] = 0.1666666666666666666666667;
    
        gauss[1][0] = 0.1666666666666666666666667;
        gauss[1][1] = 0.6666666666666666666666667;
        gauss[1][2] = 0.1666666666666666666666667;
    
        gauss[2][0] = 0.6666666666666666666666667;
        gauss[2][1] = 0.1666666666666666666666667;
        gauss[2][2] = 0.1666666666666666666666667;
        break;
    case 4:  // 4-point Gauss rule
        gauss[0][0] = 0.7503111022260811817747560e-01;
        gauss[0][1] = 0.6449489742783178098197284e+00;
        gauss[0][2] = 0.9097930912801141530281550e-01;
    
        gauss[1][0] = 0.2800199154990740720027960e+00;
        gauss[1][1] = 0.6449489742783178098197284e+00;
        gauss[1][2] = 0.9097930912801141530281550e-01;
    
        gauss[2][0] = 0.1785587282636164231170351e+00;
        gauss[2][1] = 0.1550510257216821901802716e+00;
        gauss[2][2] = 0.1590206908719885846971845e+00;
    
        gauss[3][0] = 0.6663902460147013867026933e+00;
        gauss[3][1] = 0.1550510257216821901802716e+00;
        gauss[3][2] = 0.1590206908719885846971845e+00;
        break;
    case 9:  // 9-point Gauss rule
        gauss[0][0] = 0.2393113228708061896738275e-01;
        gauss[0][1] = 0.7876594617608470560252419e+00;
        gauss[0][2] = 0.1939638330595947848163369e-01;
    
        gauss[1][0] = 0.1061702691195764719873791e+00;
        gauss[1][1] = 0.7876594617608470560252419e+00;
        gauss[1][2] = 0.3103421328953516557061390e-01;
    
        gauss[2][0] = 0.1884094059520723250073754e+00;
        gauss[2][1] = 0.7876594617608470560252419e+00;
        gauss[2][2] = 0.1939638330595947848163369e-01;
    
        gauss[3][0] = 0.6655406783916450412865057e-01;
        gauss[3][1] = 0.4094668644407347108649263e+00;
        gauss[3][2] = 0.6367808509988506852608905e-01;
    
        gauss[4][0] = 0.2952665677796326445675369e+00;
        gauss[4][1] = 0.4094668644407347108649263e+00;
        gauss[4][2] = 0.1018849361598161096417425e+00;
    
        gauss[5][0] = 0.5239790677201007850064232e+00;
        gauss[5][1] = 0.4094668644407347108649263e+00;
        gauss[5][2] = 0.6367808509988506852608905e-01;
    
        gauss[6][0] = 0.1027176548096262680160926e+00;
        gauss[6][1] = 0.8858795951270394739554614e-01;
        gauss[6][2] = 0.5581442048304434188116615e-01;
    
        gauss[7][0] = 0.4557060202436480263022269e+00;
        gauss[7][1] = 0.8858795951270394739554614e-01;
        gauss[7][2] = 0.8930307277287094700986584e-01;
    
        gauss[8][0] = 0.8086943856776697845883612e+00;
        gauss[8][1] = 0.8858795951270394739554614e-01;
        gauss[8][2] = 0.5581442048304434188116615e-01;
        break;
    case 16:  // 16-point Gauss rule
        gauss[0][0] = 0.9703785126946112175961724e-02;
        gauss[0][1] = 0.8602401356562194478479129e+00;
        gauss[0][2] = 0.5423225910525254453528332e-02;
    
        gauss[1][0] = 0.4612207990645204861943693e-01;
        gauss[1][1] = 0.8602401356562194478479129e+00;
        gauss[1][2] = 0.1016725956447878663340924e-01;
    
        gauss[2][0] = 0.9363778443732850353265015e-01;
        gauss[2][1] = 0.8602401356562194478479129e+00;
        gauss[2][2] = 0.1016725956447878663340924e-01;
    
        gauss[3][0] = 0.1300560792168344399761254e+00;
        gauss[3][1] = 0.8602401356562194478479129e+00;
        gauss[3][2] = 0.5423225910525254453528332e-02;
    
        gauss[4][0] = 0.2891208422438901271682135e-01;
        gauss[4][1] = 0.5835904323689168200566977e+00;
        gauss[4][2] = 0.2258404928236993135842135e-01;
    
        gauss[5][0] = 0.1374191041345743684268067e+00;
        gauss[5][1] = 0.5835904323689168200566977e+00;
        gauss[5][2] = 0.4233972452174628905480675e-01;
    
        gauss[6][0] = 0.2789904634965088115164956e+00;
        gauss[6][1] = 0.5835904323689168200566977e+00;
        gauss[6][2] = 0.4233972452174628905480675e-01;
    
        gauss[7][0] = 0.3874974834066941672264810e+00;
        gauss[7][1] = 0.5835904323689168200566977e+00;
        gauss[7][2] = 0.2258404928236993135842135e-01;
    
        gauss[8][0] = 0.5021012321136977210504381e-01;
        gauss[8][1] = 0.2768430136381238276800460e+00;
        gauss[8][2] = 0.3538806789808594616389450e-01;
    
        gauss[9][0] = 0.2386486597314429209541046e+00;
        gauss[9][1] = 0.2768430136381238276800460e+00;
        gauss[9][2] = 0.6634421610704973423180774e-01;
    
        gauss[10][0] = 0.4845083266304332513658494e+00;
        gauss[10][1] = 0.2768430136381238276800460e+00;
        gauss[10][2] = 0.6634421610704973423180774e-01;
    
        gauss[11][0] = 0.6729468631505064002149102e+00;
        gauss[11][1] = 0.2768430136381238276800460e+00;
        gauss[11][2] = 0.3538806789808594616389450e-01;
    
        gauss[12][0] = 0.6546699455501446386445480e-01;
        gauss[12][1] = 0.5710419611451768219312119e-01;
        gauss[12][2] = 0.2356836819338233236742181e-01;
    
        gauss[13][0] = 0.3111645522443570344411343e+00;
        gauss[13][1] = 0.5710419611451768219312119e-01;
        gauss[13][2] = 0.4418508852236172573671028e-01;
    
        gauss[14][0] = 0.6317312516411252833657445e+00;
        gauss[14][1] = 0.5710419611451768219312119e-01;
        gauss[14][2] = 0.4418508852236172573671028e-01;
    
        gauss[15][0] = 0.8774288093304678539424240e+00;
        gauss[15][1] = 0.5710419611451768219312119e-01;
        gauss[15][2] = 0.2356836819338233236742181e-01;
        break;
    case 0: // 16-point Gauss rule by Young-Ju
        gauss[0][0] = 5.710419640e-2;   
        gauss[0][1] = 6.546699187e-2;   
        gauss[0][2] = 2.356836864e-2;
    
        gauss[1][0] = 2.768430114e-1;
        gauss[1][1] = 5.021012132e-2;
        gauss[1][2] = 3.538806860e-2;
    
        gauss[2][0] = 5.835904479e-1;
        gauss[2][1] = 2.891208197e-2;
        gauss[2][2] = 2.258404870e-2;
    
        gauss[3][0] = 8.602401614e-1;
        gauss[3][1] = 9.703829427e-3;
        gauss[3][2] = 5.423225927e-3;
    
        gauss[4][0] = 5.710419640e-2;
        gauss[4][1] = 3.111645635e-1;
        gauss[4][2] = 4.418508789e-2;
    
        gauss[5][0] = 2.768430114e-1;
        gauss[5][1] = 2.386486692e-1;
        gauss[5][2] = 6.634421523e-2;
    
        gauss[6][0] = 5.835904479e-1;
        gauss[6][1] = 1.374191040e-1;
        gauss[6][2] = 4.233972202e-2;
    
        gauss[7][0] = 8.602401614e-1;
        gauss[7][1] = 4.612207309e-2;
        gauss[7][2] = 1.016725926e-2;
    
        gauss[8][0] = 5.710419640e-2;  
        gauss[8][1] = 6.317312682e-1;   
        gauss[8][2] = 4.418508789e-2;
    
        gauss[9][0] = 2.768430114e-1;
        gauss[9][1] = 4.845083410e-1;   
        gauss[9][2] = 6.634421523e-2;
    
        gauss[10][0] = 5.835904479e-1;
        gauss[10][1] = 2.789904605e-1;
        gauss[10][2] = 4.233972202e-2;
    
        gauss[11][0] = 8.602401614e-1;   
        gauss[11][1] = 9.363776966e-2;   
        gauss[11][2] = 1.016725926e-2;
    
        gauss[12][0] = 5.710419640e-2;   
        gauss[12][1] = 8.774288117e-1;   
        gauss[12][2] = 2.356836864e-2;
    
        gauss[13][0] = 2.768430114e-1;
        gauss[13][1] = 6.729468673e-1;   
        gauss[13][2] = 3.538806860e-2;
    
        gauss[14][0] = 5.835904479e-1;
        gauss[14][1] = 3.874974701e-1;
        gauss[14][2] = 2.258404870e-2;
    
        gauss[15][0] = 8.602401614e-1;  
        gauss[15][1] = 1.300560556e-1;
        gauss[15][2] = 5.423225927e-3;
        break;
    case 25:  // 25-point Gauss rule
        gauss[0][0] = 0.4622288465046428525209780e-02;
        gauss[0][1] = 0.9014649142011735738765011e+00;
        gauss[0][2] = 0.1865552166877838436183754e-02;
    
        gauss[1][0] = 0.2273848306376403459813202e-01;
        gauss[1][1] = 0.9014649142011735738765011e+00;
        gauss[1][2] = 0.3768701695327620376776386e-02;
    
        gauss[2][0] = 0.4926754289941321306174945e-01;
        gauss[2][1] = 0.9014649142011735738765011e+00;
        gauss[2][2] = 0.4479406797281358559372037e-02;
    
        gauss[3][0] = 0.7579660273506239152536687e-01;
        gauss[3][1] = 0.9014649142011735738765011e+00;
        gauss[3][2] = 0.3768701695327620376776386e-02;
    
        gauss[4][0] = 0.9391279733377999759828912e-01;
        gauss[4][1] = 0.9014649142011735738765011e+00;
        gauss[4][2] = 0.1865552166877838436183754e-02;
    
        gauss[5][0] = 0.1428579439557138533782080e-01;
        gauss[5][1] = 0.6954642733536360945146148e+00;
        gauss[5][2] = 0.8755499182163831736919008e-02;
    
        gauss[6][0] = 0.7027629200828172118339338e-01;
        gauss[6][1] = 0.6954642733536360945146148e+00;
        gauss[6][2] = 0.1768745211048346587741866e-01;
    
        gauss[7][0] = 0.1522678633231819527426926e+00;
        gauss[7][1] = 0.6954642733536360945146148e+00;
        gauss[7][2] = 0.2102296748732207512195789e-01;
    
        gauss[8][0] = 0.2342594346380821843019918e+00;
        gauss[8][1] = 0.6954642733536360945146148e+00;
        gauss[8][2] = 0.1768745211048346587741866e-01;
    
        gauss[9][0] = 0.2902499322507925201475644e+00;
        gauss[9][1] = 0.6954642733536360945146148e+00;
        gauss[9][2] = 0.8755499182163831736919008e-02;
    
        gauss[10][0] = 0.2636464494447091747928250e-01;
        gauss[10][1] = 0.4379748102473861440050125e+00;
        gauss[10][2] = 0.1734150643136570012831098e-01;
    
        gauss[11][0] = 0.1296959367822541214837999e+00;
        gauss[11][1] = 0.4379748102473861440050125e+00;
        gauss[11][2] = 0.3503250450337172031698701e-01;
    
        gauss[12][0] = 0.2810125948763069279974937e+00;
        gauss[12][1] = 0.4379748102473861440050125e+00;
        gauss[12][2] = 0.4163896521519496780744188e-01;
    
        gauss[13][0] = 0.4323292529703597345111876e+00;
        gauss[13][1] = 0.4379748102473861440050125e+00;
        gauss[13][2] = 0.3503250450337172031698701e-01;
    
        gauss[14][0] = 0.5356605448081429385157050e+00;
        gauss[14][1] = 0.4379748102473861440050125e+00;
        gauss[14][2]= 0.1734150643136570012831098e-01;
    
        gauss[15][0] = 0.3762125234511119174727219e-01;
        gauss[15][1] = 0.1980134178736081725357921e+00;
        gauss[15][2] = 0.1980408313204735378039807e-01;
    
        gauss[16][0] = 0.1850707102673894331855753e+00;
        gauss[16][1] = 0.1980134178736081725357921e+00;
        gauss[16][2] = 0.4000728738616042409551254e-01;
    
        gauss[17][0] = 0.4009932910631959137321039e+00;
        gauss[17][1] = 0.1980134178736081725357921e+00;
        gauss[17][2] = 0.4755189705795400973985440e-01;
    
        gauss[18][0] = 0.6169158718590023942786325e+00;
        gauss[18][1] = 0.1980134178736081725357921e+00;
        gauss[18][2] = 0.4000728738616042409551254e-01;
    
        gauss[19][0] = 0.7643653297812806357169357e+00;
        gauss[19][1] = 0.1980134178736081725357921e+00;
        gauss[19][2] = 0.1980408313204735378039807e-01;
    
        gauss[20][0] = 0.4504259356980372309546899e-01;
        gauss[20][1] = 0.3980985705146874234080669e-01;
        gauss[20][2] = 0.1146508035159254779675419e-01;
    
        gauss[21][0] = 0.2215786095523792017723069e+00;
        gauss[21][1] = 0.3980985705146874234080669e-01;
        gauss[21][2] = 0.2316122192949838634362829e-01;
    
        gauss[22][0] = 0.4800950714742656288295967e+00;
        gauss[22][1] = 0.3980985705146874234080669e-01;
        gauss[22][2] = 0.2752898566446981099359601e-01;
    
        gauss[23][0] = 0.7386115333961520558868864e+00;
        gauss[23][1] = 0.3980985705146874234080669e-01;
        gauss[23][2] = 0.2316122192949838634362829e-01;
    
        gauss[24][0] = 0.9151475493787275345637243e+00;
        gauss[24][1] = 0.3980985705146874234080669e-01;
        gauss[24][2] = 0.1146508035159254779675419e-01;
        break;
    case 36:  // 36-point Gauss rule
        gauss[0][0] = 0.2466697152670243054005080e-02;
        gauss[0][1] = 0.9269456713197411148518740e+00;
        gauss[0][2] = 0.7485425612363183140950521e-03;
    
        gauss[1][0] = 0.1237506041744003817266408e-01;
        gauss[1][1] = 0.9269456713197411148518740e+00;
        gauss[1][2] = 0.1576221754023588582963184e-02;
    
        gauss[2][0] = 0.2781108211536058069826929e-01;
        gauss[2][1] = 0.9269456713197411148518740e+00;
        gauss[2][2] = 0.2044386591544858980950415e-02;
    
        gauss[3][0] = 0.4524324656489830444985675e-01;
        gauss[3][1] = 0.9269456713197411148518740e+00;
        gauss[3][2] = 0.2044386591544858980950415e-02;
    
        gauss[4][0] = 0.6067926826281884697546196e-01;
        gauss[4][1] = 0.9269456713197411148518740e+00;
        gauss[4][2] = 0.1576221754023588582963184e-02;
    
        gauss[5][0] = 0.7058763152758864209412095e-01;
        gauss[5][1] = 0.9269456713197411148518740e+00;
        gauss[5][2] = 0.7485425612363183140950521e-03;
    
        gauss[6][0] = 0.7791874701286432033793818e-02;
        gauss[6][1] = 0.7692338620300545009168834e+00;
        gauss[6][2] = 0.3765298212691672929234314e-02;
    
        gauss[7][0] = 0.3909070073282424404541472e-01;
        gauss[7][1] = 0.7692338620300545009168834e+00;
        gauss[7][2] = 0.7928667333796484710025645e-02;
    
        gauss[8][0] = 0.8785045497599719116592015e-01;
        gauss[8][1] = 0.7692338620300545009168834e+00;
        gauss[8][2] = 0.1028361722876633011482835e-01;
    
        gauss[9][0] = 0.1429156829939483079171965e+00;
        gauss[9][1] = 0.7692338620300545009168834e+00;
        gauss[9][2] = 0.1028361722876633011482835e-01;
    
        gauss[10][0] = 0.1916754372371212550377019e+00;
        gauss[10][1] = 0.7692338620300545009168834e+00;
        gauss[10][2] = 0.7928667333796484710025645e-02;
    
        gauss[11][0] = 0.2229742632686590670493228e+00;
        gauss[11][1] = 0.7692338620300545009168834e+00;
        gauss[11][2] = 0.3765298212691672929234314e-02;
    
        gauss[12][0] = 0.1490156336667116035714823e-01;
        gauss[12][1] = 0.5586715187715501320813933e+00;
        gauss[12][2] = 0.8451535796943121648933723e-02;
    
        gauss[13][0] = 0.7475897346264909767772818e-01;
        gauss[13][1] = 0.5586715187715501320813933e+00;
        gauss[13][2] = 0.1779657599702627725499296e-01;
    
        gauss[14][0] = 0.1680095191211918575326299e+00;
        gauss[14][1] = 0.5586715187715501320813933e+00;
        gauss[14][2] = 0.2308246365135823315636558e-01;
    
        gauss[15][0] = 0.2733189621072580103859768e+00;
        gauss[15][1] = 0.5586715187715501320813933e+00;
        gauss[15][2] = 0.2308246365135823315636558e-01;
    
        gauss[16][0] = 0.3665695077658007702408785e+00;
        gauss[16][1] = 0.5586715187715501320813933e+00;
        gauss[16][2] = 0.1779657599702627725499296e-01;
    
        gauss[17][0] = 0.4264269178617787075614584e+00;
        gauss[17][1] = 0.5586715187715501320813933e+00;
        gauss[17][2] = 0.8451535796943121648933723e-02;
    
        gauss[18][0] = 0.2238687297803063445050099e-01;
        gauss[18][1] = 0.3369846902811542990970530e+00;
        gauss[18][2] = 0.1206060640426510907696060e-01;
    
        gauss[19][0] = 0.1123116817809536957220250e+00;
        gauss[19][1] = 0.3369846902811542990970530e+00;
        gauss[19][2] = 0.2539627158904765582035844e-01;
    
        gauss[20][0] = 0.2524035680765180133752919e+00;
        gauss[20][1] = 0.3369846902811542990970530e+00;
        gauss[20][2] = 0.3293939890078669916221938e-01;
    
        gauss[21][0] = 0.4106117416423276875276552e+00;
        gauss[21][1] = 0.3369846902811542990970530e+00;
        gauss[21][2] = 0.3293939890078669916221938e-01;
    
        gauss[22][0] = 0.5507036279378920051809220e+00;
        gauss[22][1] = 0.3369846902811542990970530e+00;
        gauss[22][2] = 0.2539627158904765582035844e-01;
    
        gauss[23][0] = 0.6406284367408150664524460e+00;
        gauss[23][1] = 0.3369846902811542990970530e+00;
        gauss[23][2] = 0.1206060640426510907696060e-01;
    
        gauss[24][0] = 0.2876533301255912843698113e-01;
        gauss[24][1] = 0.1480785996684842918499769e+00;
        gauss[24][2] = 0.1161087476699751443083611e-01;
    
        gauss[25][0] = 0.1443114869504166464557392e+00;
        gauss[25][1] = 0.1480785996684842918499769e+00;
        gauss[25][2] = 0.2444926225805781423674754e-01;
    
        gauss[26][0] = 0.3243183045887760364106504e+00;
        gauss[26][1] = 0.1480785996684842918499769e+00;
        gauss[26][2] = 0.3171111159070397975276155e-01;
    
        gauss[27][0] = 0.5276030957427396717393727e+00;
        gauss[27][1] = 0.1480785996684842918499769e+00;
        gauss[27][2] = 0.3171111159070397975276155e-01;
    
        gauss[28][0] = 0.7076099133810990616942839e+00;
        gauss[28][1] = 0.1480785996684842918499769e+00;
        gauss[28][2] = 0.2444926225805781423674754e-01;
    
        gauss[29][0] = 0.8231560673189565797130420e+00;
        gauss[29][1] = 0.1480785996684842918499769e+00;
        gauss[29][2] = 0.1161087476699751443083611e-01;
    
        gauss[30][0] = 0.3277536661445989520154516e-01;
        gauss[30][1] = 0.2931642715978489197205028e-01;
        gauss[30][2] = 0.6194265352658849860014235e-02;
    
        gauss[31][0] = 0.1644292415948274481657064e+00;
        gauss[31][1] = 0.2931642715978489197205028e-01;
        gauss[31][2] = 0.1304339433008283128737061e-01;
    
        gauss[32][0] = 0.3695299243723766991833510e+00;
        gauss[32][1] = 0.2931642715978489197205028e-01;
        gauss[32][2] = 0.1691750568001266068034231e-01;
    
        gauss[33][0] = 0.6011536484678384088445987e+00;
        gauss[33][1] = 0.2931642715978489197205028e-01;
        gauss[33][2] = 0.1691750568001266068034231e-01;
    
        gauss[34][0] = 0.8062543312453876598622433e+00;
        gauss[34][1] = 0.2931642715978489197205028e-01;
        gauss[34][2] = 0.1304339433008283128737061e-01;
    
        gauss[35][0] = 0.9379082062257552128264046e+00;
        gauss[35][1] = 0.2931642715978489197205028e-01;
        gauss[35][2] = 0.6194265352658849860014235e-02;
        break;
    case 49:  // 49-point Gauss rule
        gauss[0][0] = 0.1431659581332948445688999e-02;
        gauss[0][1] = 0.9437374394630778535343478e+00;
        gauss[0][2] = 0.3375907567113747844459523e-03;
    
        gauss[1][0] = 0.7271058658560282492949164e-02;
        gauss[1][1] = 0.9437374394630778535343478e+00;
        gauss[1][2] = 0.7292426106515660112115446e-03;
    
        gauss[2][0] = 0.1671433656946750295425480e-01;
        gauss[2][1] = 0.9437374394630778535343478e+00;
        gauss[2][2] = 0.9955000916249671892041120e-03;
    
        gauss[3][0] = 0.2813128026846107323282610e-01;
        gauss[3][1] = 0.9437374394630778535343478e+00;
        gauss[3][2] = 0.1089695284831588119968157e-02;
    
        gauss[4][0] = 0.3954822396745464351139739e-01;
        gauss[4][1] = 0.9437374394630778535343478e+00;
        gauss[4][2] = 0.9955000916249671892041120e-03;
    
        gauss[5][0] = 0.4899150187836186397270303e-01;
        gauss[5][1] = 0.9437374394630778535343478e+00;
        gauss[5][2] = 0.7292426106515660112115446e-03;
    
        gauss[6][0] = 0.5483090095558919801996319e-01;
        gauss[6][1] = 0.9437374394630778535343478e+00;
        gauss[6][2] = 0.3375907567113747844459523e-03;
    
        gauss[7][0] = 0.4586412541637882763079511e-02;
        gauss[7][1] = 0.8197593082631076350124201e+00;
        gauss[7][2] = 0.1774485071438049608442658e-02;
    
        gauss[8][0] = 0.2329329894998979644828858e-01;
        gauss[8][1] = 0.8197593082631076350124201e+00;
        gauss[8][2] = 0.3833132573484684075609282e-02;
    
        gauss[9][0] = 0.5354544045728325221282914e-01;
        gauss[9][1] = 0.8197593082631076350124201e+00;
        gauss[9][2] = 0.5232667115687632726379401e-02;
    
        gauss[10][0] = 0.9012034586844618249378997e-01;
        gauss[10][1] = 0.8197593082631076350124201e+00;
        gauss[10][2] = 0.5727787200652742623468366e-02;
    
        gauss[11][0] = 0.1266952512796091127747508e+00;
        gauss[11][1] = 0.8197593082631076350124201e+00;
        gauss[11][2] = 0.5232667115687632726379401e-02;
    
        gauss[12][0] = 0.1569473927869025685392914e+00;
        gauss[12][1] = 0.8197593082631076350124201e+00;
        gauss[12][2] = 0.3833132573484684075609282e-02;
    
        gauss[13][0] = 0.1756542791952544822245004e+00;
        gauss[13][1] = 0.8197593082631076350124201e+00;
        gauss[13][2] = 0.1774485071438049608442658e-02;
    
        gauss[14][0] = 0.8972904006716703697492974e-02;
        gauss[14][1] = 0.6473752828868303626260922e+00;
        gauss[14][2] = 0.4297910087982423247056434e-02;
    
        gauss[15][0] = 0.4557124628029494113490578e-01;
        gauss[15][1] = 0.6473752828868303626260922e+00;
        gauss[15][2] = 0.9284078756888546352613518e-02;
    
        gauss[16][0] = 0.1047568427084817262927626e+00;
        gauss[16][1] = 0.6473752828868303626260922e+00;
        gauss[16][2] = 0.1267383600209279954896470e-01;
    
        gauss[17][0] = 0.1763123585565848186869539e+00;
        gauss[17][1] = 0.6473752828868303626260922e+00;
        gauss[17][2] = 0.1387304677156393168637868e-01;
    
        gauss[18][0] = 0.2478678744046879110811452e+00;
        gauss[18][1] = 0.6473752828868303626260922e+00;
        gauss[18][2] = 0.1267383600209279954896470e-01;
    
        gauss[19][0] = 0.3070534708328746962390020e+00;
        gauss[19][1] = 0.6473752828868303626260922e+00;
        gauss[19][2] = 0.9284078756888546352613518e-02;
    
        gauss[20][0] = 0.3436518131064529336764148e+00;
        gauss[20][1] = 0.6473752828868303626260922e+00;
        gauss[20][2] = 0.4297910087982423247056434e-02;
    
        gauss[21][0] = 0.1392289515659608599518407e-01;
        gauss[21][1] = 0.4528463736694446169985514e+00;
        gauss[21][2] = 0.6935542753734072742362389e-02;
    
        gauss[22][0] = 0.7071107454632530338118497e-01;
        gauss[22][1] = 0.4528463736694446169985514e+00;
        gauss[22][2] = 0.1498172921938941357190799e-01;
    
        gauss[23][0] = 0.1625469900128696646167676e+00;
        gauss[23][1] = 0.4528463736694446169985514e+00;
        gauss[23][2] = 0.2045178462250981418417614e-01;
    
        gauss[24][0] = 0.2735768131652776915007243e+00;
        gauss[24][1] = 0.4528463736694446169985514e+00;
        gauss[24][2] = 0.2238695250460706899401921e-01;
    
        gauss[25][0] = 0.3846066363176857183846809e+00;
        gauss[25][1] = 0.4528463736694446169985514e+00;
        gauss[25][2] = 0.2045178462250981418417614e-01;
    
        gauss[26][0] = 0.4764425517842300796202636e+00;
        gauss[26][1] = 0.4528463736694446169985514e+00;
        gauss[26][2] = 0.1498172921938941357190799e-01;
    
        gauss[27][0] = 0.5332307311739592970062645e+00;
        gauss[27][1] = 0.4528463736694446169985514e+00;
        gauss[27][2] = 0.6935542753734072742362389e-02;
    
        gauss[28][0] = 0.1868274434884273534596982e-01;
        gauss[28][1] = 0.2657898227845894684767894e+00;
        gauss[28][2] = 0.8247603013529574038759331e-02;
    
        gauss[29][0] = 0.9488521701286283095347225e-01;
        gauss[29][1] = 0.2657898227845894684767894e+00;
        gauss[29][2] = 0.1781596040067579543578056e-01;
    
        gauss[30][0] = 0.2181172683502983220175448e+00;
        gauss[30][1] = 0.2657898227845894684767894e+00;
        gauss[30][2] = 0.2432083637489711574352285e-01;
    
        gauss[31][0] = 0.3671050886077052657616053e+00;
        gauss[31][1] = 0.2657898227845894684767894e+00;
        gauss[31][2] = 0.2662209772138335648260900e-01;
    
        gauss[32][0] = 0.5160929088651122095056658e+00;
        gauss[32][1] = 0.2657898227845894684767894e+00;
        gauss[32][2] = 0.2432083637489711574352285e-01;
    
        gauss[33][0] = 0.6393249602025477005697384e+00;
        gauss[33][1] = 0.2657898227845894684767894e+00;
        gauss[33][2] = 0.1781596040067579543578056e-01;
    
        gauss[34][0] = 0.7155274328665677961772408e+00;
        gauss[34][1] = 0.2657898227845894684767894e+00;
        gauss[34][2] = 0.8247603013529574038759331e-02;
    
        gauss[35][0] = 0.2252791561566364109969225e-01;
        gauss[35][1] = 0.1146790531609042319096402e+00;
        gauss[35][2] = 0.7154643779096141969509067e-02;
    
        gauss[36][0] = 0.1144139277467613129097319e+00;
        gauss[36][1] = 0.1146790531609042319096402e+00;
        gauss[36][2] = 0.1545501766273406746103162e-01;
    
        gauss[37][0] = 0.2630088665758011781230588e+00;
        gauss[37][1] = 0.1146790531609042319096402e+00;
        gauss[37][2] = 0.2109787781815243944540462e-01;
    
        gauss[38][0] = 0.4426604734195478840451799e+00;
        gauss[38][1] = 0.1146790531609042319096402e+00;
        gauss[38][2] = 0.2309417967090930466923013e-01;
    
        gauss[39][0] = 0.6223120802632945899673009e+00;
        gauss[39][1] = 0.1146790531609042319096402e+00;
        gauss[39][2] = 0.2109787781815243944540462e-01;
    
        gauss[40][0] = 0.7709070190923344551806278e+00;
        gauss[40][1] = 0.1146790531609042319096402e+00;
        gauss[40][2] = 0.1545501766273406746103162e-01;
    
        gauss[41][0] = 0.8627930312234321269906675e+00;
        gauss[41][1] = 0.1146790531609042319096402e+00;
        gauss[41][2] = 0.7154643779096141969509067e-02;
    
        gauss[42][0] = 0.2487403237606075687067163e-01;
        gauss[42][1] = 0.2247938643871249810882550e-01;
        gauss[42][2] = 0.3623466079725786927077026e-02;
    
        gauss[43][0] = 0.1263292970196692449335864e+00;
        gauss[43][1] = 0.2247938643871249810882550e-01;      
        gauss[43][2] = 0.7827186648495094067212433e-02;
    
        gauss[44][0] = 0.2903993060879903088904502e+00;
        gauss[44][1] = 0.2247938643871249810882550e-01;      
        gauss[44][2] = 0.1068501060131496739994062e-01;
    
        gauss[45][0] = 0.4887603067806437509455873e+00;
        gauss[45][1] = 0.2247938643871249810882550e-01;     
        gauss[45][2] = 0.1169603676441935436310196e-01;
    
        gauss[46][0] = 0.6871213074732971930007243e+00;
        gauss[46][1] = 0.2247938643871249810882550e-01;
        gauss[46][2] = 0.1068501060131496739994062e-01;
    
        gauss[47][0] = 0.8511913165416182569575881e+00;
        gauss[47][1] = 0.2247938643871249810882550e-01;
        gauss[47][2] = 0.7827186648495094067212433e-02;
    
        gauss[48][0] = 0.9526465811852267450205029e+00;
        gauss[48][1] = 0.2247938643871249810882550e-01;
        gauss[48][2] = 0.3623466079725786927077026e-02;
        break;
    default:
        fasp_chkerr(ERROR_QUAD_TYPE, "fasp_gauss2d");
        break;
    }
    
    return;
}

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/
