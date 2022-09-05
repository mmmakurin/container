#include <iostream>
#include "cont.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    // Объявляем массив из 10 элементов
    cont array(10);
     //Заполняем массив числами от 1 до 10
    for (int i{ 0 }; i < 10; ++i)
        array[i] = i + 1;

    // Изменим размер массива до 8 элементов
        array.resize(8);
   

    // Вставляем число 20 перед элементом с индексом 5
        try
        {
            array.insertBefore(20, -1);
        }
        catch (const std::exception&)
        {
            cout << "Ошибка в индексе массива!" << endl;
        }

    // Удаляем элемент с индексом 3
    try
    {
        array.remove(-1);
    }
    catch (const std::exception&)
    {
        cout << "Ошибка в индексе массива!" << endl;
    }

    // Добавляем 30 и 40 в конец и начало
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    // Распечатываем все числа
    for (int i{ 0 }; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';

    return 0;
}