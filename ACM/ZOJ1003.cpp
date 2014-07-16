#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>

int m, n;
std::vector<std::vector<int> > vv;

void decompose(int a,int i, std::vector<int> v)
{
    if (i > 100)
        return;

    if (a == 1)
    {
        vv.push_back(v);
        return;
    }

    if (0 == a % i)
    {
        v.push_back(i);
        a = a / i;
        decompose(a, i+1, v);
        a = a * i;
        v.erase(std::find(v.begin(), v.end(), i));
    }
    decompose(a, i+1, v);
}

int vv[150][150];
int l;

void decompose_c(int a, int i, int *v, int k)
{
    if (i > 100)
        return;

    if (a == 1)
    {
        memcpy(vv[l], v, sizeof(v));
        return;
    }

    if (0 == a % i)
    {
        v[k] = i;
        a = a / i;
        decompose_c(a, i+1, *v, k+1);
        a = a * i;
        k = k - 1;
    }
    decompose_c(a, i+1, *v, k);
}



int main()
{
    freopen("ZOJ1003.input", "r", stdin);
    while (scanf("%d %d", &m, &n) == 2)
    {
        if (m < n)
            std::swap(m, n);

        int v[150];
        decompose_c(m, 2, v, 0);
    }
}

        // std::vector<int> v;
        // std::vector<std::vector<int> > tmp;
        // decompose(m, 2, v);
        // tmp = vv;
        // decompose(n, 2, v);

        // for (std::vector<std::vector<int> >::iterator it = tmp.begin(); it != tmp.end(); it++)
        // {
        //     if ()
        // }


/*        for (std::vector<std::vector<int> >::iterator it = vv.begin(); it != vv.end(); it++)
        {
            for (std::vector<int>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)
            {
                printf("%d ", *itt);
            }
            printf("\n");
// }
//     }
// }

// std::vector<int> m_vec;
// std::vector<int> n_vec;

/**
 * 数组a在n_vec中
 * @param  a [description]
 * @return   [true就是在，false就是不在]
 */
// int int_In_vector(int a)
// {
//     if (n_vec.end() == std::find(n_vec.begin(), n_vec.end(), a))
//         return -1;
//     else
//         return ;
// }

// std::vector<int> 

/**
 * 数组v_int1中的任意一个数，假如它在n_vec中
 * @param  v_int1 [m_vec]
 * @return        [true就是在，false就是不在]
 */
// bool v_In_v(std::vector<int> v_int1)
// {
//     if (v_int1.end() == std::find_if(v_int1.begin(), v_int1.end(), ptr_fun(a_In_v)))
//         return false;
//     else
//         return true;
// }

// bool vv_In_vv(std::vector<std::vector<int> > vv)
// {
//     for (std::vector<std::vector<int> >::iterator a = vv.begin(); a != vv.end(); a++)
//     {
//         for (std::vector<std::vector<int> >::iterator b = vv.begin(); a != vv.end(); a++)
//         if (v_In_v(*it))
//             return true;
//         else
//             return false;
//     }
// }