#pragma once
#include <iostream>
#include <vector>

    /* HW_3_DZ4
    Создать класс Card, описывающий карту в игре БлэкДжек.
    У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой).
    Сделать поля масть и значение карты типом перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два метода: 
        • метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
        • метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
    */

enum Suits {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum Ranks {
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
protected:
    Suits suit = CLUBS;
    Ranks rank = ACE;
    bool isFaceUp = false;
public:
    Card() {}
    Card(Ranks inputRank, Suits inputSuit)
        : suit(inputSuit), rank(inputRank)
    {

    }
    void Flip()
    {
        isFaceUp = !isFaceUp;
    }

    Ranks getValue()
    {
        return rank;
    }

    Suits getSuit()
    {
        return suit;
    }

    /*  HW6_DZ3
    Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
        • virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.
    Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
        • void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
        • void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
        • void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.
    */

class Player : virtual public GenericPlayer
{
public:
    Player(std::string inputName)
        : GenericPlayer(inputName) {}
    virtual bool IsHitting() const override
    {
        while (true)
        {
            std::cout << "\nTake another card? (Y/N): ";
            char* input = 0;
            std::cin >> input;
            if (std::cin && input == "Y") return true;
            else if (std::cin && input == "N") return false;
            else
            {
                system("cls");
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Incorrect input!";
            }
        }
    }

    void Win() const
    {
        std::cout << "\n" << name << " have Won!";
    }

    void Lose() const
    {
        std::cout << "\n" << name << " have Lost.";
    }

    void Push() const
    {
        std::cout << "\n" << name << " played a Draw";
    }
};

    /*  HW6_DZ4
    Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
        • virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не больше 16 очков, то он берет еще одну карту.
        • void FlipFirstCard() - метод переворачивает первую карту дилера.
    */

class House : virtual public GenericPlayer
{
public:
    House()
        : GenericPlayer("Diler") {}

    virtual bool IsHitting() const override
    {
        if (GetValue() <= 16) return true;
        else return false;
    }

    void FlipFirstCard()
    {
        hand.front()->Flip();
    }
};
    /*HW6_DZ5
        Написать перегрузку оператора вывода для класса Card.
        Если карта перевернута рубашкой вверх (мы ее не видим),
    вывести ХХ, если мы ее видим, вывести масть и номинал карты.
        Также для класса GenericPlayer написать перегрузку оператора вывода,
    который должен отображать имя игрока и его карты, а также общую сумму очков его карт.
    */

friend std::ostream& operator<<(std::ostream& out, const Card& card);
};

std::ostream& operator<<(std::ostream& out, const Card& card)
{
    if (card.isFaceUp)
    {
        out << "\n" << card.rank << " " << card.suit;
    }
    else out << "XX";
    return out;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/ 

class Hand
{
protected:
    std::vector<Card*> hand;
public:
    void Add(Card* input)
    {
        hand.push_back(input);
    }

    void Clear()
    {
        hand.clear();
    }

    int GetValue() const
    {
        int sum = 0;
        for (Card* card : hand)
        {
            sum += card->getValue();
        }
        return sum;
    }
};

class GenericPlayer : public Hand
{
protected:
    std::string name;
public:
    GenericPlayer(std::string inputName)
        : name(inputName) {}

    virtual bool IsHitting() const = 0;

    bool IsBoosted() const
    {
        if (GetValue() > 21) return true;
        else return false;
    }

    void Bust()
    {
        std::cout << "\n" << name << " is Bust!\n";
    }

    /* HW6_DZ5 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/ 

    friend std::ostream& operator<<(std::ostream& out, const GenericPlayer& genericPlayer);
};

std::ostream& operator<<(std::ostream& out, const GenericPlayer& genericPlayer)
{
    out << "\n" << genericPlayer.name << " has:\n";
    for (Card* card : genericPlayer.hand)
    {
        out << card->getValue() << " " << card->getSuit() << "\n";
    }
    out << genericPlayer.GetValue();
    return out;
};
