#include <iostream>
#include <cmath>
#include <limits>

extern double rtGetInf(void);
extern double rtGetInfF(void);
extern double rtGetMinusInf(void);
extern double rtGetMinusInfF(void);

extern double rtInf;
extern double rtMinusInf;
extern double rtNaN;
extern double rtInfF;
extern double rtMinusInfF;
extern double rtNaNF;

double rtNaN{std::numeric_limits<double>::quiet_NaN()};
double rtInf{std::numeric_limits<double>::infinity()};
double rtMinusInf{-std::numeric_limits<double>::infinity()};
double rtNaNF{std::numeric_limits<double>::quiet_NaN()};
double rtInfF{std::numeric_limits<double>::infinity()};
double rtMinusInfF{-std::numeric_limits<double>::infinity()};

static const double RT_PI{3.14159265358979323846};
static const double RT_PIF{3.1415927F};
static const double RT_LN_10{2.30258509299404568402};
static const double RT_LN_10F{2.3025851F};
static const double RT_LOG10E{0.43429448190325182765};
static const double RT_LOG10EF{0.43429449F};
static const double RT_E{2.7182818284590452354};
static const double RT_EF{2.7182817F};

// Function Declarations
extern void FK_function(double a, double b, double c, double output1_data[],
                        int output1_size[1], double output2[3]);

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
static double rt_atan2d_snf(double u0, double u1)
{
    double y;
    if (std::isnan(u0) || std::isnan(u1)) {
        y = rtNaN;
    } else if (std::isinf(u0) && std::isinf(u1)) {
        int i;
        int i1;
        if (u0 > 0.0) {
            i = 1;
        } else {
            i = -1;
        }
        if (u1 > 0.0) {
            i1 = 1;
        } else {
            i1 = -1;
        }
        y = std::atan2(static_cast<double>(i), static_cast<double>(i1));
    } else if (u1 == 0.0) {
        if (u0 > 0.0) {
            y = RT_PI / 2.0;
        } else if (u0 < 0.0) {
            y = -(RT_PI / 2.0);
        } else {
            y = 0.0;
        }
    } else {
        y = std::atan2(u0, u1);
    }
    return y;
}

void FK_function(double a, double b, double c, double output1_data[],
                 int output1_size[1], double output2[3])
{
    static const double c_a[16]{0.92718385456678742,
                                0.374606593415912,
                                0.0,
                                0.0,
                                0.374549539017287,
                                -0.92704263997482106,
                                0.017452406437283512,
                                0.0,
                                0.00653778652238071,
                                -0.016181589471986741,
                                -0.99984769515639127,
                                0.0,
                                -0.09,
                                -0.684,
                                0.0,
                                1.0};
    static const double BCQ[3]{-0.09, -0.684, 0.0};
    static const signed char iv[4]{0, 0, 0, 1};
    double BP_blue_data[4];
    double b_a[4];
    double B_Qbr[3];
    double Vn_idx_0;
    double Vn_idx_1;
    double Vn_idx_2;
    double Y_new_axis_idx_1;
    double absxk;
    double cy;
    double cySq;
    double scale;
    double t;
    double y;
    // Translation between the robot base and the custom frame, findes på selve
    // roboten
    // Rotation from robot base to custom frame is given in Z-Y-X Euler angles in
    // degress findes også på selve robotten
    // Opbygning af transformationsmatrix fra base til custom
    // Making the point vektors a 4*1 so the can work with the transformation
    // matrix
    // Calculating the points in the robot frame, using X(4,1)=[] to remove the
    // 4th row to give a 3x1 position vektor
    for (int i{0}; i < 4; i++) {
        b_a[i] = (((c_a[i] * a + c_a[i + 4] * b) + c_a[i + 8] * c) + c_a[i + 12]) -
                 static_cast<double>(iv[i]);
    }
    BP_blue_data[0] = b_a[0];
    BP_blue_data[1] = b_a[1];
    BP_blue_data[2] = b_a[2];
    // Calculate a vector from origo to the point so we can allign the x akis
    // trough the point
    // Recreating a rotation matrix that alings the z akse through the point
    // The z axis is the negative of the normal workplane vector
    Vn_idx_0 = b_a[1] * 0.0 - b_a[2] * -0.684;
    Vn_idx_1 = b_a[2] * -0.09 - b_a[0] * 0.0;
    Vn_idx_2 = b_a[0] * -0.684 - b_a[1] * -0.09;
    scale = 3.3121686421112381E-170;
    absxk = std::abs(Vn_idx_0);
    if (absxk > 3.3121686421112381E-170) {
        y = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        y = t * t;
    }
    absxk = std::abs(Vn_idx_1);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    absxk = std::abs(Vn_idx_2);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    y = scale * std::sqrt(y);
    scale = 3.3121686421112381E-170;
    cySq = Vn_idx_0 / y;
    Vn_idx_0 = cySq;
    absxk = std::abs(cySq);
    if (absxk > 3.3121686421112381E-170) {
        cy = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        cy = t * t;
    }
    cySq = Vn_idx_1 / y;
    Vn_idx_1 = cySq;
    absxk = std::abs(cySq);
    if (absxk > scale) {
        t = scale / absxk;
        cy = cy * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        cy += t * t;
    }
    cySq = Vn_idx_2 / y;
    absxk = std::abs(cySq);
    if (absxk > scale) {
        t = scale / absxk;
        cy = cy * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        cy += t * t;
    }
    cy = scale * std::sqrt(cy);
    Vn_idx_0 /= cy;
    Vn_idx_1 /= cy;
    Vn_idx_2 = cySq / cy;
    // The y axis is the vector for blue to red per the assignemt description
    for (int i{0}; i < 3; i++) {
        B_Qbr[i] = BP_blue_data[i] - BCQ[i];
    }
    scale = 3.3121686421112381E-170;
    absxk = std::abs(B_Qbr[0]);
    if (absxk > 3.3121686421112381E-170) {
        y = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        y = t * t;
    }
    absxk = std::abs(B_Qbr[1]);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    absxk = std::abs(B_Qbr[2]);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    y = scale * std::sqrt(y);
    B_Qbr[0] /= y;
    B_Qbr[1] /= y;
    B_Qbr[2] /= y;
    // The new x axis can now be found from the new z and y axis
    Y_new_axis_idx_1 = Vn_idx_0 * B_Qbr[2] - B_Qbr[0] * Vn_idx_2;
    Vn_idx_0 = B_Qbr[0] * Vn_idx_1 - Vn_idx_0 * B_Qbr[1];
    scale = 3.3121686421112381E-170;
    absxk = std::abs(B_Qbr[1] * Vn_idx_2 - Vn_idx_1 * B_Qbr[2]);
    if (absxk > 3.3121686421112381E-170) {
        y = 1.0;
        scale = absxk;
    } else {
        t = absxk / 3.3121686421112381E-170;
        y = t * t;
    }
    absxk = std::abs(Y_new_axis_idx_1);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    absxk = std::abs(Vn_idx_0);
    if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
    } else {
        t = absxk / scale;
        y += t * t;
    }
    y = scale * std::sqrt(y);
    // Creating the rotation matrix
    // Since to TCP should be on top of the Blue point with can use the know
    // value of the blue point and the new rotation matrix to create the
    // transformation matrix
    cySq = B_Qbr[0] * B_Qbr[0] + B_Qbr[1] * B_Qbr[1];
    cy = std::sqrt(cySq);
    output2[0] = rt_atan2d_snf(Vn_idx_0 / y, Vn_idx_2);
    output2[1] = rt_atan2d_snf(-B_Qbr[2], cy);
    output2[2] = rt_atan2d_snf(B_Qbr[1], B_Qbr[0]);
    if (cySq < 2.2204460492503131E-15) {
        cySq = rt_atan2d_snf(-B_Qbr[2], cy);
        output2[0] = rt_atan2d_snf(-Vn_idx_1, Y_new_axis_idx_1 / y);
        output2[1] = cySq;
        output2[2] = 0.0;
    }
    cySq = output2[0];
    output2[0] = output2[2];
    output2[2] = cySq;
    output1_size[0] = 3;
    for (int i{0}; i < 3; i++) {
        output1_data[i] = BP_blue_data[i];
    }
    //std::cout<<"Z Eulervinkel "<<output2[0]<<" Y Eulervinkel "<<output2[1]<<" X Eulervinkel "<<output2[2]<<std::endl;
    //std::cout<<"X koordinat "<<output1_data[0]<<" Y koordinat "<<output1_data[1]<<" Z koordinat "<<output1_data[2]<<" Alle koordinater er i m"<<std::endl;
}

// Function Declarations
extern int main(int argc, char **argv);

extern void main_FK_function();

void main_FK_function()
{
    double dv[3]={0.3, 0, 0};
    double output1_data[3];
    double output2[3];
    int output1_size;
    // Initialize function 'FK_function' input arguments.
    // Initialize function input argument 'P'.
    // Call the entry-point 'FK_function'.
    FK_function(dv[0],dv[1],dv[2], output1_data, *(int(*)[1]) & output1_size, output2);
    std::cout<<"Z Eulervinkel "<<output2[0]<<" Y Eulervinkel "<<output2[1]<<" X Eulervinkel "<<output2[2]<<std::endl;
    std::cout<<"X koordinat "<<output1_data[0]<<" Y koordinat "<<output1_data[1]<<" Z koordinat "<<output1_data[2]<<" Alle koordinater er i m"<<std::endl;
}

int main(int, char **)
{
    // The initialize function is being called automatically from your entry-point
    // function. So, a call to initialize is not included here. Invoke the
    // entry-point functions.
    // You can call entry-point functions multiple times.
    main_FK_function();
    return 0;
}

