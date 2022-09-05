#include <iostream>
#include "cont.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    // ��������� ������ �� 10 ���������
    cont array(10);
     //��������� ������ ������� �� 1 �� 10
    for (int i{ 0 }; i < 10; ++i)
        array[i] = i + 1;

    // ������� ������ ������� �� 8 ���������
        array.resize(8);
   

    // ��������� ����� 20 ����� ��������� � �������� 5
        try
        {
            array.insertBefore(20, -1);
        }
        catch (const std::exception&)
        {
            cout << "������ � ������� �������!" << endl;
        }

    // ������� ������� � �������� 3
    try
    {
        array.remove(-1);
    }
    catch (const std::exception&)
    {
        cout << "������ � ������� �������!" << endl;
    }

    // ��������� 30 � 40 � ����� � ������
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    // ������������� ��� �����
    for (int i{ 0 }; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';

    return 0;
}