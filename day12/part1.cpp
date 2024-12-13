#include "../core.h"

long long Get_Min(long long Tx, long long Ty, long long Ax, long long Ay, long long Bx, long long By){

    long long det = Ay * Bx - Ax * By;
    if(det == 0){
        if((Ty%By != 0 || Tx%Bx != 0) && (Ty%Ay != 0 || Tx%Ax != 0)) return 0;
        if((By * 3 >= Ay)) return Ty/By;
        return (Ty/Ay)*3 + (Ty%Ay)/By;
    }


    long long det1 = Ty * Bx - Tx * By;
    long long det2 = Ay * Tx - Ax * Ty;

    if(det1%det != 0 || det2%det != 0){
        return 0;
    }

    long long k1 = det1/det;
    long long k2 = det2/det;

    return k1*3 + k2;
}

int main() {

    std::vector<std::vector<long long>> input_data;
    Read_Data("../input.txt", input_data);

    long long result = 0;
    for(int i = 0; i < input_data.size(); i += 4){

        if(input_data.empty()) continue;

        long long Ty = input_data[i+2][1];
        long long Tx = input_data[i+2][0];
        long long Ax = input_data[i][0];
        long long Ay = input_data[i][1];
        long long Bx = input_data[i+1][0];
        long long By = input_data[i+1][1];

        result += Get_Min(Tx, Ty, Ax, Ay, Bx, By);

    }
    std::cout<<result<<'\n';
    return 0;
}
