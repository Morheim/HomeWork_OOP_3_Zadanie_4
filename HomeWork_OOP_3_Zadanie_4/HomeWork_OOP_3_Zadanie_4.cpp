#include <iostream>

    /* DZ4
    Создать класс Card, описывающий карту в игре БлэкДжек.
    У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой).
    Сделать поля масть и значение карты типом перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два метода: 
        • метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
        • метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
    */

enum Suits
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum Ranks
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

class Card
{
private:
    Suits suit;
    Ranks rank;
    bool isFaceUp;
public:

    void Flip()
    {
        isFaceUp = !isFaceUp;
    }

    Ranks getValue()
    {
        return rank;
    }
};
int main()
{
    return 0;
}