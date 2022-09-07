#pragma once
#include <climits>
#include <exception>
class cont
{
private:
    int c_length{};
    int* c_data{};
public:
    cont() = default;

    cont(int length) : c_length{ length }
    {
        c_data = new int[length] {};
        if (length <= 0)
        {
            throw "������! ����� ������� �� ����� ���� ������ ��� ����� 0";
        }
            //c_data = new int[length] {};
    }


    ~cont()
    {
        delete[] c_data;
        // ����� ��� �� ����� ������������� m_data � �������� null
        // ��� m_length � 0, ��� ��� ������ � ����� ������ �����
        // ��������� ����� ����� ���� �������
    }

    void erase()
    {
        delete[] c_data;

        // ��� ����� ���������, ��� �� ���������� ����� c_data
        // ������ nullptr, ����� ��� ������� ��������� 
        // ����������� �� ������������� ������!
        c_data = nullptr;
        c_length = 0;
    }

    int& operator[](int index)
    {
        return c_data[index];
    }

    int getLength() const 
    { 
        return c_length; 
    }

    // reallocate �������� ������ �������. ����� ������������ ��������
// ����� ����������. ��� ������� �������� ������.
    void reallocate(int newLength)
    {
        // ������� �� ������� ��� ������������ ��������
        erase();

        // ���� ������ ��� ������ ����� ������, ������������ ������
        if (newLength <= 0)
            return;

        // ����� ��� ����� ���������� ����� ��������
        c_data = new int[newLength];
        c_length = newLength;
    }

    // resize �������� ������ �������. ����� ������������ ��������
    // ����� ���������. ��� ������� �������� ��������.
    void resize(int newLength)
    {
        // ���� ������ ��� ����� ������ �����, �� ���������
        if (newLength == c_length)
            return;

        // ���� �� �������� ������ �� ������� �������, ������ ��� � ������������
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // ������ �� ����� ������������, ��� newLength - ��� ��� ������� 1 �������.
        // ���� �������� �������� ��������� �������:
        // ������� ��������� ����� ������.
        // ����� �������� �������� �� ������������� ������� � ����� ������.
        // ��� ������ ��� ����� �������, ����� ���������� ������ ������
        // � ��������� c_data ��������� �� ����� ������.

        // ������� �� ������ ���������� ����� ������
        int* data{ new int[newLength] };

        // ����� ��� ����� ��������, ������� ��������� ����������� ��
        // ������������� ������� � ����� ������. �� ����� �����������
        // ������� ���������, ������� ���� � ������� �� ���� ��������.
        if (c_length > 0)
        {
            int elementsToCopy{ (newLength > c_length) ? c_length : newLength };

            // ������ �������� �������� ���� �� ������
            for (int index{ 0 }; index < elementsToCopy; ++index)
                data[index] = c_data[index];
        }

        // ������ �� ����� ������� ������ ������, ������ ��� �� ��� ������ �� �����
        delete[] c_data;

        // � ������ ���� ���������� ����� ������! �������� ��������, ��� ��� ������
        // ���������� c_data ��������� �� ����� ������ �������, ������� ��
        // ���������� �����������. ��������� ������ ���� ��������� �����������,
        // ��� �� ����� ����������, ����� ������ �� ������� ������� ���������.
        c_data = data;
        c_length = newLength;
    }
    void insertBefore(int value, int index)
    {
        // ��������� �������� ������ ������� �� ������������
        if (index < 0 || index > c_length)
        {
            throw "������! �������� / �������������� ������";
        }
        // ������� ������� ����� ������ �� ���� ������� ������ ������� �������
        int* data{ new int[c_length + 1] };

        // �������� ��� �������� �� �������
        for (int before{ 0 }; before < index; ++before)
            data[before] = c_data[before];

        // ��������� ��� ����� ������� � ����� ������
        data[index] = value;

        // �������� ��� �������� ����� ������������ ��������
        for (int after{ index }; after < c_length; ++after)
            data[after + 1] = c_data[after];

        // �������, ������� ������ ������ � ���������� ������ ���� �����
        delete[] c_data;
        c_data = data;
        ++c_length;
    }

    void remove(int index)
    {
        // ��������� �������� ������ ������� �� ������������
        if (index < 0 || index > c_length)
        {
            throw "������! �������� / �������������� ������";
        }

        // ���� ��� ��������� ������� � �������,
        // ������ ������ ������ � �������
        if (c_length == 1)
        {
            erase();
            return;
        }

        // ������� ������� ����� ������ �� ���� ������� ������ ������� �������
        int* data{ new int[c_length - 1] };

        // �������� ��� �������� �� �������
        for (int before{ 0 }; before < index; ++before)
            data[before] = c_data[before];

        // �������� ��� �������� ����� ���������� ��������
        for (int after{ index + 1 }; after < c_length; ++after)
            data[after - 1] = c_data[after];

        // �������, ������� ������ ������ � ���������� ������ ���� �����
        delete[] c_data;
        c_data = data;
        --c_length;
    }

    // ���� �������������� ������� ��� ��������
    void insertAtBeginning(int value) 
    { 
        insertBefore(value, 0); 
    }
    void insertAtEnd(int value) 
    { 
        insertBefore(value, c_length); 
    }
};
