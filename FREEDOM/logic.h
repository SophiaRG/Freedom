#pragma once
#pragma once
// laba4_FREEDOM.cpp 

#include <iostream>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class Cell {
private:
    char symbol;
    int x;
    int y;
public:
    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    char getSymbol() {
        return symbol;
    }

    void Draw(Graphics^ g) {
        Bitmap^ img;
        int bitMapSize = 70;

        switch (symbol)
        {
        case ' ':
            img = gcnew Bitmap("grey.jpg");
            break;
        case 'X':
            img = gcnew Bitmap("red_x.jpg");
            break;
        case '0':
            img = gcnew Bitmap("blue_o.jpg");
            break;
        default:
            img = gcnew Bitmap("grey.jpg");
            break;
        }

        g->DrawImage(img, (int)(x * bitMapSize), (int)(y * bitMapSize));
    }

    Cell() {
        x = 0;
        y = 0;
        symbol = ' ';
    }

    Cell(int coordinateX, int coordinateY, char character) {
        x = coordinateX;
        y = coordinateY;
        symbol = character;
    }
};

ref struct Element {
    Cell^ cell;
    Element^ next;
};

ref class Container {
private:
    Element^ firstElem;
public:
    Container() {
        firstElem = nullptr;
    }

    Element^ getFirstElem() {
        return firstElem;
    }

    void Add(Cell^ anotherCell) {
        Element^ temp = gcnew Element;
        temp->cell = anotherCell;
        temp->next = firstElem;
        firstElem = temp;
    }

    Element^ FindElement(int indexX, int indexY) {
        Element^ temp = firstElem;
        while (temp != nullptr) {
            if ((indexX == temp->cell->getX()) && (indexY == temp->cell->getY())) {
                return temp;
            }
            temp = temp->next;
        }
    }

    ~Container() {
        Element^ temp = firstElem;
        while (temp != nullptr) {
            firstElem = firstElem->next;
            delete temp;
            temp = firstElem;
        }
    }
};

ref class Board {
private:
    array<Cell^, 2>^ cells;
    PictureBox^ pb;
    Container^ container;
    Cell^ prevCell;
    bool game_over;
    char currentStep;
public:
    void DrawBoard() {
        Bitmap^ bmp = gcnew Bitmap(pb->Width, pb->Height);
        Graphics^ g = Graphics::FromImage(bmp);

        if (game_over) {
            int winsX = CountWinsX(container);
            int wins0 = CountWins0(container);
            if (winsX > wins0) {
                bmp = gcnew Bitmap("X_vins.jpg");
            }
            else if (winsX < wins0) {
                bmp = gcnew Bitmap("0_vins.jpg");
            }
            else {
                bmp = gcnew Bitmap("draw_wins.jpg");
            }
        }
        else {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    Element^ element = container->FindElement(i, j);
                    if (element != nullptr) {
                        cells[i, j] = element->cell;
                    }
                    else {
                        cells[i, j] = gcnew Cell(i, j, ' ');
                    }
                }
            }

            for each (Cell ^ var in cells)
            {
                var->Draw(g);
            }
        }

        pb->Image = bmp;
    }

    void updateStep() {
        if (currentStep == 'X') {
            currentStep = '0';
        }
        else if (currentStep == '0') {
            currentStep = 'X';
        }
    }

    void MakeMove(System::Windows::Forms::MouseEventArgs^ e) {
        int x = e->X / 70;
        int y = e->Y / 70;

        if (prevCell == nullptr) {
            Cell^ cell = gcnew Cell(x, y, currentStep);
            container->Add(cell);
            updateStep();
            DrawBoard();
            prevCell = cell;
        }

        if (PossibleStep(x, y, container, prevCell)) {
            Cell^ cell = gcnew Cell(x, y, currentStep);
            container->Add(cell);
            updateStep();
            DrawBoard();
            prevCell = cell;
        }
    }

    void FinishGame() {
        Element^ temp = container->getFirstElem();
        int counter = 0;
        while (temp != nullptr) {
            counter++;
            temp = temp->next;
        }

        if (counter >= 99) {
            game_over = true;
        }
    }

    bool ChekingCell(int indexX, int indexY, Container^ container) {

        Element^ temp = container->getFirstElem();
        while (temp != nullptr) {
            if ((indexX == temp->cell->getX()) && (indexY == temp->cell->getY())) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    bool CellIsEmpty(int indexX, int indexY, Container^ container) {
        if (indexX < 0) return false;
        if (indexX > 9) return false;
        if (indexY < 0) return false;
        if (indexY > 9) return false;
        if (container->FindElement(indexX, indexY) != nullptr) return false;
        return true;
    }

    bool CheckIfAroundIsFull(Cell^ prev_cell, Container^ container) {


        if (!CellIsEmpty(prev_cell->getX(), prev_cell->getY() + 1, container) &&
            !CellIsEmpty(prev_cell->getX(), prev_cell->getY() - 1, container) &&
            !CellIsEmpty(prev_cell->getX() - 1, prev_cell->getY() + 1, container) &&
            !CellIsEmpty(prev_cell->getX() - 1, prev_cell->getY(), container) &&
            !CellIsEmpty(prev_cell->getX() - 1, prev_cell->getY() - 1, container) &&
            !CellIsEmpty(prev_cell->getX() + 1, prev_cell->getY() + 1, container) &&
            !CellIsEmpty(prev_cell->getX() + 1, prev_cell->getY(), container) &&
            !CellIsEmpty(prev_cell->getX() + 1, prev_cell->getY() - 1, container)
            ) {
            return true;
        }

        return false;
    }

    bool CheckIfMoveIsAround(int indexX, int indexY, Cell^ prev_cell, Container^ container) {
        if ((indexX == prev_cell->getX()) && (indexY == prev_cell->getY() + 1) ||
            (indexX == prev_cell->getX()) && (indexY == prev_cell->getY() - 1) ||
            (indexX == prev_cell->getX() - 1) && (indexY == prev_cell->getY() + 1) ||
            (indexX == prev_cell->getX() - 1) && (indexY == prev_cell->getY()) ||
            (indexX == prev_cell->getX() - 1) && (indexY == prev_cell->getY() - 1) ||
            (indexX == prev_cell->getX() + 1) && (indexY == prev_cell->getY() + 1) ||
            (indexX == prev_cell->getX() + 1) && (indexY == prev_cell->getY()) ||
            (indexX == prev_cell->getX() + 1) && (indexY == prev_cell->getY() - 1)
            ) {
            return true;
        }
        else {
            return false;
        }
    }

    bool PossibleStep(int indexX, int indexY, Container^ container, Cell^ pre_cell) {
        if (container->FindElement(indexX, indexY) != nullptr) return false;
        if (CheckIfAroundIsFull(pre_cell, container)) return true;

        return CheckIfMoveIsAround(indexX, indexY, pre_cell, container);
    }

    int CountWinsX(Container^ container) {
        int global_counter = 0;
        // count X axises
        for (int i = 0; i < 10; i++) {
            int local_counter = 0;

            for (int j = 0; j < 10; j++) {
                Element^ element = container->FindElement(i, j);

                if (element->cell->getSymbol() == 'X') {
                    local_counter++;
                    if ((j == 9) && (local_counter == 4)) global_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                    continue;
                }
            }
        }

        // count Y axises
        for (int i = 0; i < 10; i++) {
            int local_counter = 0;

            for (int j = 0; j < 10; j++) {
                Element^ element = container->FindElement(j, i);

                if (element->cell->getSymbol() == 'X') {
                    local_counter++;
                    if ((i == 9) && (local_counter == 4)) global_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                    continue;
                }
            }
        }

        // count D1
        for (int n = 0; n < 7; n++) {
            int local_counter = 0;
            int k = n;
            int i = 0;
            int j = 3 + k;
            Element^ element;


            while ((j >= 0) && (i <= 3 + k)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == 'X') {
                    local_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                }

                i++;
                j--;
            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }

        }

        for (int n = 3; n < 10; n++) {
            int local_counter = 0;
            int k = n;
            int i = 9 - k;
            int j = 9;
            Element^ element;


            while ((j >= 9 - k) && (i <= 9)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == 'X') {
                    local_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                }

                i++;
                j--;

            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }
        }

        //d2
        for (int n = 1; n < 7; n++) {
            int local_counter = 0;
            int k = n;
            int j = n;
            int i = 0;
            Element^ element;


            while ((i <= 9 - k) && (j <= 9)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == 'X') {
                    local_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                }

                j++;
                i++;
            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }

        }

        for (int n = 3; n < 10; n++) {
            int local_counter = 0;
            int k = n;
            int j = 0;
            int i = 9 - k;
            Element^ element;


            while ((i <= 9) && (j <= k)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == 'X') {
                    local_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                }

                j++;
                i++;

            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }
        }

        return global_counter;
    }

    int CountWins0(Container^ container) {
        int global_counter = 0;
        // count X axises
        for (int i = 0; i < 10; i++) {
            int local_counter = 0;

            for (int j = 0; j < 10; j++) {
                Element^ element = container->FindElement(i, j);

                if (element->cell->getSymbol() == '0') {
                    local_counter++;
                    if ((j == 9) && (local_counter == 4)) global_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                    continue;
                }
            }
        }

        // count Y axises
        for (int i = 0; i < 10; i++) {
            int local_counter = 0;

            for (int j = 0; j < 10; j++) {
                Element^ element = container->FindElement(j, i);

                if (element->cell->getSymbol() == '0') {
                    local_counter++;
                    if ((i == 9) && (local_counter == 4)) global_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                    continue;
                }
            }
        }

        // count D1
        for (int n = 0; n < 7; n++) {
            int local_counter = 0;
            int k = n;
            int i = 0;
            int j = 3 + k;
            Element^ element;


            while ((j >= 0) && (i <= 3 + k)) {
                element = container->FindElement(i, j);

                if (element->cell->getSymbol() == '0') {
                    local_counter++;
                }
                else {
                    if (local_counter == 4) global_counter++;
                    local_counter = 0;
                }

                i++;
                j--;
            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }
        }

        for (int n = 3; n < 9; n++) {
            int local_counter = 0;
            int k = n;
            int i = 9 - k;
            int j = 9;
            Element^ element;


            while ((j >= 9 - k) && (i <= 9)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == '0') {
                    local_counter++;
                }
                else {
                    if (element->cell->getSymbol() == 'X') {
                        if (local_counter == 4) global_counter++;
                        local_counter = 0;
                    }
                }

                i++;
                j--;

            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }
        }

        //d2
        for (int n = 0; n < 7; n++) {
            int local_counter = 0;
            int k = n;
            int j = n;
            int i = 0;
            Element^ element;


            while ((i <= 9 - k) && (j <= 9)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == '0') {
                    local_counter++;
                }
                else {
                    if (element->cell->getSymbol() == 'X') {
                        if (local_counter == 4) global_counter++;
                        local_counter = 0;
                    }
                }

                i++;
                j++;
            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }
        }

        for (int n = 3; n < 9; n++) {
            int local_counter = 0;
            int k = n;
            int j = 0;
            int i = 9 - k;
            Element^ element;


            while ((i <= 9) && (j <= k)) {
                element = container->FindElement(i, j);
                if (element->cell->getSymbol() == '0') {
                    local_counter++;
                }
                else {
                    if (element->cell->getSymbol() == 'X') {
                        if (local_counter == 4) global_counter++;
                        local_counter = 0;
                    }
                }

                j++;
                i++;
            }

            if (local_counter == 4) {
                global_counter++;
                local_counter = 0;
            }
        }

        return global_counter;
    }

    Container^ getContainer() {
        return container;
    }

public:
    Board(PictureBox^ pb1) {
        cells = gcnew array<Cell^, 2>(10, 10);
        container = gcnew Container;
        prevCell = nullptr;
        currentStep = 'X';
        game_over = false;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cells[i, j] = gcnew Cell(i, j, ' ');
            }
        }
        pb = pb1;
    }
};