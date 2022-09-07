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
            throw "Ошибка! Длина массива не может быть меньше или равна 0";
        }
            //c_data = new int[length] {};
    }


    ~cont()
    {
        delete[] c_data;
        // здесь нам не нужно устанавливать m_data в значение null
        // или m_length в 0, так как объект в любом случае будет
        // уничтожен сразу после этой функции
    }

    void erase()
    {
        delete[] c_data;

        // Нам нужно убедиться, что мы установили здесь c_data
        // равным nullptr, иначе это оставит указатель 
        // указывающим на освобожденную память!
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

    // reallocate изменяет размер массива. Любые существующие элементы
// будут уничтожены. Эта функция работает быстро.
    void reallocate(int newLength)
    {
        // Сначала мы удаляем все существующие элементы
        erase();

        // Если теперь наш массив будет пустым, возвращаемся отсюда
        if (newLength <= 0)
            return;

        // Затем нам нужно разместить новые элементы
        c_data = new int[newLength];
        c_length = newLength;
    }

    // resize изменяет размер массива. Любые существующие элементы
    // будут сохранены. Эта функция работает медленно.
    void resize(int newLength)
    {
        // если массив уже имеет нужную длину, мы закончили
        if (newLength == c_length)
            return;

        // Если мы изменяем размер до пустого массива, делаем это и возвращаемся
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Теперь мы можем предположить, что newLength - это как минимум 1 элемент.
        // Этот алгоритм работает следующим образом:
        // Сначала размешаем новый массив.
        // Затем копируем элементы из существующего массива в новый массив.
        // Как только это будет сделано, можно уничтожить старый массив
        // и заставить c_data указывать на новый массив.

        // Сначала мы должны разместить новый массив
        int* data{ new int[newLength] };

        // Затем нам нужно выяснить, сколько элементов скопировать из
        // существующего массива в новый массив. Мы хотим скопировать
        // столько элементов, сколько есть в меньшем из двух массивов.
        if (c_length > 0)
        {
            int elementsToCopy{ (newLength > c_length) ? c_length : newLength };

            // Теперь копируем элементы один за другим
            for (int index{ 0 }; index < elementsToCopy; ++index)
                data[index] = c_data[index];
        }

        // Теперь мы можем удалить старый массив, потому что он нам больше не нужен
        delete[] c_data;

        // И вместо него используем новый массив! Обратите внимание, что это просто
        // заставляет c_data указывать на адрес нового массива, который мы
        // разместили динамически. Поскольку данные были размещены динамически,
        // они не будут уничтожены, когда выйдут за пределы области видимости.
        c_data = data;
        c_length = newLength;
    }
    void insertBefore(int value, int index)
    {
        // Проверяем значение нашего индекса на корректность
        if (index < 0 || index > c_length)
        {
            throw "Ошибка! Неверный / несуществующий индекс";
        }
        // Сначала создаем новый массив на один элемент больше старого массива
        int* data{ new int[c_length + 1] };

        // Копируем все элементы до индекса
        for (int before{ 0 }; before < index; ++before)
            data[before] = c_data[before];

        // Вставляем наш новый элемент в новый массив
        data[index] = value;

        // Копируем все значения после вставленного элемента
        for (int after{ index }; after < c_length; ++after)
            data[after + 1] = c_data[after];

        // Наконец, удаляем старый массив и используем вместо него новый
        delete[] c_data;
        c_data = data;
        ++c_length;
    }

    void remove(int index)
    {
        // Проверяем значение нашего индекса на корректность
        if (index < 0 || index > c_length)
        {
            throw "Ошибка! Неверный / несуществующий индекс";
        }

        // Если это последний элемент в массиве,
        // делаем массив пустым и выходим
        if (c_length == 1)
        {
            erase();
            return;
        }

        // Сначала создаем новый массив на один элемент меньше старого массива
        int* data{ new int[c_length - 1] };

        // Копируем все элементы до индекса
        for (int before{ 0 }; before < index; ++before)
            data[before] = c_data[before];

        // Копируем все значения после удаленного элемента
        for (int after{ index + 1 }; after < c_length; ++after)
            data[after - 1] = c_data[after];

        // Наконец, удаляем старый массив и используем вместо него новый
        delete[] c_data;
        c_data = data;
        --c_length;
    }

    // Пара дополнительных функций для удобства
    void insertAtBeginning(int value) 
    { 
        insertBefore(value, 0); 
    }
    void insertAtEnd(int value) 
    { 
        insertBefore(value, c_length); 
    }
};
