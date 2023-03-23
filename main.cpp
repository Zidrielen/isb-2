#include <math.h>

#include <iostream>
#include <random>
#include <string>


//Программный код генерации псевдослучайного числа
void num_generate() {
    std::random_device rd;

    // В качестве генератора псевдослучайных чисел используем вихрь Мерсенна
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    std::vector<int> v;
    generate_n(back_inserter(v), 128,
        [&distrib, &gen] {return distrib(gen); });
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ""));
}

//Частотный побитовый тест
void test_1(std::string s)
{
    double sum_n = 0;
    for (int i = 0; i < 128; i++)
    {
        if (s[i] == '0') sum_n += -1;
        else sum_n += 1;
    }
    sum_n /= sqrt(128);
    std::cout << erfc(sum_n / sqrt(2));

    //Для данной последовательности получаем 0.0770999
}

//Тест на одинаковые подряд идущие биты
void test_2(std::string s)
{
    double psi = 0;
    for (int i = 0; i < 128; i++) if (s[i] == '1') psi++;
    psi /= 128;

    if (fabs(psi - 0.5) >= 2 / sqrt(128)) std::cout << 0;
    else
    {
        int V_n = 0;
        for (int i = 0; i < 127; i++) if (s[i] != s[i + 1]) V_n++;
        std::cout << erfc(fabs(V_n - 256 * psi * (1 - psi)) / (32 * psi * (1 - psi)));
    }

    //Для данной последовательности получаем 0.324488
}

//Тест на самую длинную последовательность единиц в блоке
void test_3(std::string s)
{
    //10011011 11000110 00011110 01011100 11110101 00111111 00011100 00001110
    //01011101 00010110 10110111 00101111 01101111 11000101 10011111 10011100

    int v[4] = { 0, 4, 6, 6 };
    double pi[4] = {0.2148, 0.3672, 0.2305, 0.1875}, xi = 0;
   
    for (int i = 0; i < 4; i++) xi += pow(v[i] - 16 * pi[i], 2) / (16 * pi[i]);
    std::cout << xi / 2 << " -> " << 0.03698781 << "\n\n";

    //Для данной последовательности получаем 0.03698781
}


int main()
{
    //Псевдосдучайное число, поделённая на две части для удобства
    std::string part_1 = "1001101111000110000111100101110011110101001111110001110000001110";
    std::string part_2 = "0101110100010110101101110010111101101111110001011001111110011100";

    test_1(part_1 + part_2);
    std::cout << "\n\n";
    test_2(part_1 + part_2);
    std::cout << "\n\n";
    test_3(part_1 + part_2);

    return 0;
}