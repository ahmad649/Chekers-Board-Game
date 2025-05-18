using namespace std;
#include <iostream>
     //  Made by: Ahmad Hasan (2019041)  and  Ali Abdul Razzaq (2019058)
int ptr_array[8][8];
void array_initialization()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ptr_array[i][j] = NULL;
        }
    }
}
void Display_test()
{
     
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
          cout<<  ptr_array[i][j]<<" ";
        }
        cout << endl;
    }
}
int white_player_kill_count;
int red_player_kill_count;
void grid_representation()
{
    bool alternator = false;
    //-1 for dark spaces
    //-2 for light spaces
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (alternator == false)
            {
                ptr_array[i][j] = -1;
                alternator = true;
            }
            else if (alternator == true)
            {
                ptr_array[i][j] = -2;
                alternator = false;
            }
        }
        if (alternator == false)
        {
            alternator = true;
        }
        else if (alternator == true)
        {
            alternator = false;
        }
    }
}
void Initial_board()
{
    //-1 for dark spaces
   //-2 for light spaces
    int position_no = 32;
    cout << " ";
    for (int index_no = 0; index_no < 8; index_no++)
    {
        cout << "   " << index_no << "  ";
    }
    cout << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl; 
    for (int i = 0; i < 8; i++)
    {
        cout <<" "<<i;
        for (int j = 0; j < 8; j++)
        {
            if (ptr_array[i][j] == -1)
            {
                cout << "| " << "." << "   ";
            }
            else if (ptr_array[i][j] == -2)
            {
                cout << "| " << "    ";
            }
            else  if (ptr_array[i][j] == 5)
            {
                cout << "| " << "$" << "   ";
            }
            else if (ptr_array[i][j] == 10)
            {
                cout << "| " << "X" << "   ";
            }
        }
        cout << "|" << endl;
        cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}
class pieces
{

public:
    int X_position;
    int Y_position;
    bool isKing;


    pieces()
    {
        X_position = -1;
        Y_position = -1;
        isKing = false;
    }
    void Set_Location(int x_coordinate, int y_coordinate)
    {
        X_position = x_coordinate;
        Y_position = y_coordinate;
    }
    void setIsKing(bool flag_input)
    {
        isKing = flag_input;
    }
    int  Get_X_position()
    {
        return  X_position;
    }
    int  Get_Y_position()
    {
        return  Y_position;
    }
    bool Get_IsKing() 
    {
        return  isKing;
    }
};

class red_pieces
{
private:
    pieces red[12];
       int row_number = 0;
       int column_number = 1;
       int counter = 0;     // tells us when the row is complete
       bool alternator = 1;
public:
    red_pieces()
    {
       
        for (int i = 0; i < 12; i++)
        {
            red[i].Set_Location(row_number, column_number);
            counter++;
            column_number += 2;
            if (counter == 4)
            {
                if (alternator == 1) 
                {
                    column_number = 0;
                    alternator = 0;
                }
                else
                {
                    column_number = 1;
                    alternator = 1;
                }
                row_number++;
                counter = 0;
            }
        }
        for (int i = 0; i < 12; i++)
        {
           ptr_array[red[i].Get_X_position()][red[i].Get_Y_position()] = 5;
        }
    }
    void take_move()
    {
        int X_input = 0;
        int Y_input = 0;
        bool move_vaalidity = false;            // becomes true if move was made successfully
        bool first_kill = false;
        while (move_vaalidity == false) 
        {
            validate_piece(X_input, Y_input);
            validate_possibilities(X_input, Y_input, move_vaalidity, first_kill);
            if (first_kill == true) 
            {
                cout << "Opponents piece killed! Choose your next move" << endl;
                validate_possibilities(X_input, Y_input, move_vaalidity, first_kill);
            }

        }
    }
    void validate_piece(int& X_input, int& Y_input)
    {
        bool white_piece = true;


        while (white_piece == true)
        {
            cout << "Enter coordinates of piece you want to move \n";
            cout << "Enter row number  : ";
            cin >> X_input;
            cout << "Enter column number : ";
            cin >> Y_input;
            while (!((X_input >= 0 && X_input <= 7) && (Y_input >= 0 && Y_input <= 7)))
            {
                cout << "Invalid coordinates, Please enter again : " << endl;
                cout << "Enter coordinates of piece you want to move \n";
                cout << "Enter row number: ";
                cin >> X_input;
                cout << "Enter column number : ";
                cin >> Y_input;
            }

            if (!(ptr_array[X_input][Y_input] == 5))
            {
                cout << "\nThis is not your piece, please re-enter the coordinates " << endl;
            }
            else if (ptr_array[X_input][Y_input] == 5)
            {
                white_piece = false;
            }

        }
    }
    void validate_possibilities(int& X_input, int& Y_input, bool& move_vaalidity, bool& first_kill)
    {
        //max four posible directions to move to.....
        int possible_row1, possible_row2, possible_row3, possible_row4, possible_column1, possible_column2, possible_column3, possible_column4, piece_index;
        bool lilkely_kill_1 = false, lilkely_kill_2 = false, lilkely_kill_3 = false, lilkely_kill_4 = false;

        for (int i = 0; i < 12; i++)
        {
            if ((red[i].Get_X_position() == X_input) && (red[i].Get_Y_position() == Y_input))
            {
                piece_index = i;
            }
        }
        bool location_D_possibility = false;
        //down right  (D)
        possible_row1 = red[piece_index].Get_X_position() + 1;
        possible_column1 = red[piece_index].Get_Y_position() + 1;
        bool location_C_possibility = false;
        //down left  (C)
        possible_row2 = red[piece_index].Get_X_position() + 1;
        possible_column2 = red[piece_index].Get_Y_position() - 1;
        bool location_A_possibility = false;
        //top left (A)
        possible_row3 = red[piece_index].Get_X_position() - 1;
        possible_column3 = red[piece_index].Get_Y_position() - 1;
        bool location_B_possibility = false;
        //top right (B)
        possible_row4 = red[piece_index].Get_X_position() - 1;
        possible_column4 = red[piece_index].Get_Y_position() + 1;

        if (first_kill == true)
        {
            validate_move2(X_input, Y_input, first_kill, possible_row1, possible_row2, possible_row3, possible_row4, possible_column1, possible_column2, possible_column3, possible_column4, move_vaalidity, lilkely_kill_1, lilkely_kill_2, lilkely_kill_3, lilkely_kill_4, location_D_possibility, location_C_possibility, location_A_possibility, location_B_possibility);
        }
        else
        {
            validate_move1(X_input, Y_input, first_kill, possible_row1, possible_row2, possible_row3, possible_row4, possible_column1, possible_column2, possible_column3, possible_column4, move_vaalidity, lilkely_kill_1, lilkely_kill_2, lilkely_kill_3, lilkely_kill_4, location_D_possibility, location_C_possibility, location_A_possibility, location_B_possibility);
        }
        if (red[piece_index].Get_IsKing() == false)
        {
            location_A_possibility = false;
            location_B_possibility = false;
        }

        //Border check
        if (possible_row1 > 7 || possible_column1 > 7)
        {
            location_D_possibility = false;
        }
        if (possible_row2 > 7 || possible_column2 < 0)
        {
            location_C_possibility = false;
        }
        if (possible_row3 < 0 || possible_column3 < 0)
        {
            location_A_possibility = false;
        }
        if (possible_row4 < 0 || possible_column4 > 7)
        {
            location_B_possibility = false;
        }


        if (location_A_possibility == true || location_B_possibility == true || location_C_possibility == true || location_D_possibility == true)
        {
            char choice = ' ';

            if (location_C_possibility == true)
            {
                cout << "\nEnter c to move to (" << possible_row2 << " , " << possible_column2 << ")" << endl;
            }
            else
            {
                cout << "\nOption c is not availaible \n";
            }
            if (location_D_possibility == true)
            {
                cout << "\nEnter d to move to (" << possible_row1 << " , " << possible_column1 << ")" << endl;
            }
            else
            {
                cout << "\nOption d is not availaible \n";
            }


            if (red[piece_index].Get_IsKing() == true)
            {
                if (location_A_possibility == true)
                {
                    cout << "\nEnter a to move to (" << possible_row3 << " , " << possible_column3 << ")" << endl;
                }
                else
                {
                    cout << "\nOption a is not availaible \n";
                }
                if (location_B_possibility == true)
                {
                    cout << "\nEnter b to move to (" << possible_row4 << " , " << possible_column4 << ")" << endl;
                }
                else
                {
                    cout << "\nOption b is not availaible \n";
                }
            }

            if (red[piece_index].Get_IsKing() == false)
            {

                while (choice != 'c' && choice != 'd')
                {
                    cin >> choice;
                    if (choice != 'c' && choice != 'd')
                    {
                        cout << "\nIncorrect choice enter again" << endl;
                    }
                    if ((choice == 'c' && location_C_possibility == false) || (choice == 'd' && location_D_possibility == false))
                    {
                        cout << "\nChoose from availaible options" << endl;
                        cin >> choice;
                    }
                }

            }
            else if (red[piece_index].Get_IsKing() == true)
            {

                while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
                {
                    cin >> choice;
                    if (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
                    {
                        cout << "\nIncorrect choice, enter again !" << endl;
                    }
                    if ((choice == 'a' && location_A_possibility == false) || (choice == 'b' && location_B_possibility == false) || (choice == 'c' && location_C_possibility == false) || (choice == 'd' && location_D_possibility == false))
                    {
                        cout << "choose from availaible options" << endl;
                        cin >> choice;
                    }
                }
            }



            if (choice == 'b')
            {
                first_kill = lilkely_kill_2;
                Move_on_board(piece_index, possible_row4, possible_column4, X_input, Y_input, lilkely_kill_2, (possible_row4 - 1), (possible_column4 + 1));
            }
            else if (choice == 'a')
            {
                first_kill = lilkely_kill_1;
                Move_on_board(piece_index, possible_row3, possible_column3, X_input, Y_input, lilkely_kill_1, (possible_row3 - 1), (possible_column3 - 1));
            }
            else if (choice == 'd')
            {
                first_kill = lilkely_kill_4;
                Move_on_board(piece_index, possible_row1, possible_column1, X_input, Y_input, lilkely_kill_4, (possible_row1 + 1), (possible_column1 + 1));
            }
            else 
            {
                first_kill = lilkely_kill_3;
                Move_on_board(piece_index, possible_row2, possible_column2, X_input, Y_input, lilkely_kill_3, (possible_row2 + 1), (possible_column2 - 1));
            }
            move_vaalidity = true;
        }
        else
        {
            cout << "\nNo moves are possible for the selected piece" << endl;
            move_vaalidity = false;
            if (first_kill == true)
            {
                move_vaalidity = true;
                cout << "\nMove validity is declined" << endl;
            }
        }
    }
    void Move_on_board(int piece_index, int x_coordinate, int y_coordinate, int& X_input, int& Y_input, bool likely_kill, int x_coordinate2, int y_coordinate2)
    {
        red[piece_index].Set_Location(x_coordinate,y_coordinate);
        ptr_array[X_input][Y_input] = -2;
        ptr_array[x_coordinate][y_coordinate] = 5;
        X_input = x_coordinate;
        Y_input = y_coordinate;

        if (X_input == 7)
        {
            red[piece_index].setIsKing(true);
            cout << "\nSelected piece is now a king piece!" << endl;
        }
        if (likely_kill == true)
        {
            white_player_kill_count++;
            ptr_array[x_coordinate2][y_coordinate2] = -2;
        }
    }

    void validate_move1(int &X_input,int &Y_input, bool &first_kill, int &possible_row1, int& possible_row2, int& possible_row3, int& possible_row4, int& possible_column1, int& possible_column2, int& possible_column3, int& possible_column4, bool &move_vaalidity, bool &lilkely_kill_1, bool& lilkely_kill_2, bool& lilkely_kill_3, bool& lilkely_kill_4, bool &location_D_possibility, bool& location_C_possibility , bool& location_A_possibility, bool& location_B_possibility)
    {
        if (ptr_array[possible_row1][possible_column1] == -2) 
        {  
            location_D_possibility = true;
        }
        else if (ptr_array[possible_row1][possible_column1] == 5)
        {   
             location_D_possibility = false;
        }
        else if (ptr_array[possible_row1][possible_column1] == 10)
        { 
            if (ptr_array[possible_row1 + 1][possible_column1 + 1] == -2) 
            {
                location_D_possibility = true;
                possible_row1++; 
                possible_column1++;
                lilkely_kill_4 = true;
            }
            else 
            {
                location_D_possibility = false;
            }
        }


        if (ptr_array[ possible_row2][possible_column2] == -2) 
        {   
            location_C_possibility = true;
        }
        else if (ptr_array[ possible_row2][possible_column2] == 5) 
        {   
            location_C_possibility = false;
        }
        else if (ptr_array[ possible_row2][possible_column2] == 10) 
        { 
            if (ptr_array[ possible_row2 + 1][possible_column2 - 1] == -2)
            {   
                location_C_possibility = true;
                 lilkely_kill_3 = true;
                 possible_row2++; 
                 possible_column2--;
            }
            else
            {
                location_C_possibility = false;
            }
        }

        if (ptr_array[possible_row3][possible_column3] == -2)
        {   
            location_A_possibility = true;
        }
        else if (ptr_array[possible_row3][possible_column3] == 5) 
        {   
            location_A_possibility = false;

        }
        else if (ptr_array[possible_row3][possible_column3] == 10) 
        { 

            if (ptr_array[possible_row3 - 1][possible_column3 - 1] == -2)
            {   
                location_A_possibility = true;
                lilkely_kill_1 = true;
                possible_row3--; 
                possible_column3--;
            }
            else
            {
                location_A_possibility = false;
            }
        }


        if (ptr_array[possible_row4][possible_column4] == -2) 
        {
            location_B_possibility = true;
        }
        else if (ptr_array[possible_row4][possible_column4] == 5)
        {
            location_B_possibility = false;

        }
        else if (ptr_array[possible_row4][possible_column4] == 10)
        {

            if (ptr_array[possible_row4 - 1][possible_column4 + 1] == -2) 
            {
                location_B_possibility = true;
                lilkely_kill_2 = true;
                possible_row4--; 
                possible_column4++;
            }
            else 
            {
                location_B_possibility = false;
            }
        }
    }
    void validate_move2(int& X_input, int& Y_input, bool& first_kill, int& possible_row1, int& possible_row2, int& possible_row3, int& possible_row4, int& possible_column1, int& possible_column2, int& possible_column3, int& possible_column4, bool& move_vaalidity, bool& lilkely_kill_1, bool& lilkely_kill_2, bool& lilkely_kill_3, bool& lilkely_kill_4, bool& location_D_possibility, bool& location_C_possibility, bool& location_A_possibility, bool& location_B_possibility)
    {
        if (ptr_array[possible_row3][possible_column3] == 10) 
        { 
            if (ptr_array[possible_row3 - 1][possible_column3 - 1] == -2) 
            {  
                location_A_possibility = true;
                possible_row3--;
                possible_column3--;
                lilkely_kill_1 = true;
            }
            else 
            {
                location_A_possibility = false;
            }
        }

        if (ptr_array[possible_row4][possible_column4] == 10)
        {
            if (ptr_array[possible_row4 - 1][possible_column4 + 1] == -2)
            {
                location_B_possibility = true;
                possible_row4--;
                possible_column4++;
                lilkely_kill_2 = true;
            }
            else
            {
                location_B_possibility = false;
            }
        }
        if (ptr_array[possible_row2][possible_column2] == 10)
        {
            if (ptr_array[possible_row2 + 1][possible_column2 - 1] == -2)
            {
                location_C_possibility = true;
                possible_row2++;
                possible_column2--;
                lilkely_kill_3 = true;
            }
            else
            {
                location_C_possibility = false;
            }
        }
        if (ptr_array[possible_row1][possible_column1] == 10)
        {
            if (ptr_array[possible_row1 + 1][possible_column1 + 1] == -2)
            {
                location_D_possibility = true;
                possible_row1++;
                possible_column1++;
                lilkely_kill_4 = true;
            }
            else
            {
                location_D_possibility = false;
            }
        }
    
    }

};
class white_pieces
{
private:
    pieces white[12];
    int row_number = 7;
    int column_number = 6;
    int counter = 0;     // tells us when the row is complete
    bool alternator = 0;
public:
    white_pieces()
    {

        for (int i = 0; i < 12; i++)
        {
            white[i].Set_Location(row_number, column_number);
            counter++;
            column_number -= 2;
            if (counter == 4)
            {
                if (alternator == 1)
                {
                    column_number = 6;
                    alternator = 0;
                }
                else
                {
                    column_number = 7;
                    alternator = 1;
                }
                row_number--;
                counter = 0;
            }
        }
        for (int i = 0; i < 12; i++)
        {
            ptr_array[white[i].Get_X_position()][white[i].Get_Y_position()] = 10;
        }
    }
    void take_move()
    {
        int X_input = 0;
        int Y_input = 0;
        bool move_vaalidity = false;            // becomes true if move was made successfully
        bool first_kill = false;
        while (move_vaalidity == false)
        {
            validate_piece(X_input, Y_input);
            validate_possibilities(X_input, Y_input, move_vaalidity, first_kill);
            if (first_kill == true)
            {
                cout << "Opponents piece killed! Choose your next move" << endl;
                validate_possibilities(X_input, Y_input, move_vaalidity, first_kill);
            }

        }
    }
    void validate_piece(int& X_input, int& Y_input)
    {
        bool red_piece = true;


        while (red_piece == true)
        {
            cout << "Enter coordinates of piece you want to move \n";
            cout << "Enter row number : ";
            cin >> X_input;
            cout << "Enter column number : ";
            cin >> Y_input;
            while (!((X_input >= 0 && X_input <= 7) && (Y_input >= 0 && Y_input <= 7)))
            {
                cout << "\nInvalid coordinates, Please enter again : " << endl;
                cout << "Enter coordinates of piece you want to move \n";
                cout << "Enter row number : ";
                cin >> X_input;
                cout << "Enter column number : ";
                cin >> Y_input;
            }

            if (!(ptr_array[X_input][Y_input] == 10))
            {
                cout << "\nThis is not your piece, please re-enter the coordinates " << endl;
            }
            else if (ptr_array[X_input][Y_input] == 10)
            {
                red_piece = false;
            }

        }
    }
    void validate_possibilities(int& X_input, int& Y_input, bool& move_vaalidity, bool& first_kill)
    {
        //max four posible directions to move to.....
        int possible_row1, possible_row2, possible_row3, possible_row4, possible_column1, possible_column2, possible_column3, possible_column4, piece_index;
        bool lilkely_kill_1 = false, lilkely_kill_2 = false, lilkely_kill_3 = false, lilkely_kill_4 = false;

        for (int i = 0; i < 12; i++)
        {
            if ((white[i].Get_X_position() == X_input) && (white[i].Get_Y_position() == Y_input))
            {
                piece_index = i;
            }
        }
        bool location_D_possibility = false;
        //down right  (D)
        possible_row1 = white[piece_index].Get_X_position() + 1;
        possible_column1 = white[piece_index].Get_Y_position() + 1;
        bool location_C_possibility = false;
        //down left  (C)
        possible_row2 = white[piece_index].Get_X_position() + 1;
        possible_column2 = white[piece_index].Get_Y_position() - 1;
        bool location_A_possibility = false;
        //top left (A)
        possible_row3 = white[piece_index].Get_X_position() - 1;
        possible_column3 = white[piece_index].Get_Y_position() - 1;
        bool location_B_possibility = false;
        //top right (B)
        possible_row4 = white[piece_index].Get_X_position() - 1;
        possible_column4 = white[piece_index].Get_Y_position() + 1;

        if (first_kill == true)
        {
            validate_move2(X_input, Y_input, first_kill, possible_row1, possible_row2, possible_row3, possible_row4, possible_column1, possible_column2, possible_column3, possible_column4, move_vaalidity, lilkely_kill_1, lilkely_kill_2, lilkely_kill_3, lilkely_kill_4, location_D_possibility, location_C_possibility, location_A_possibility, location_B_possibility);
        }
        else
        {
            validate_move1(X_input, Y_input, first_kill, possible_row1, possible_row2, possible_row3, possible_row4, possible_column1, possible_column2, possible_column3, possible_column4, move_vaalidity, lilkely_kill_1, lilkely_kill_2, lilkely_kill_3, lilkely_kill_4, location_D_possibility, location_C_possibility, location_A_possibility, location_B_possibility);
        }
        if (white[piece_index].Get_IsKing() == false)
        {
            location_D_possibility = false;
            location_C_possibility = false;
        }

        //Border check
        if (possible_row1 > 7 || possible_column1 > 7)
        {
            location_D_possibility = false;
        }
        if (possible_row2 > 7 || possible_column2 < 0)
        {
            location_C_possibility = false;
        }
        if (possible_row3 < 0 || possible_column3 < 0)
        {
            location_A_possibility = false;
        }
        if (possible_row4 < 0 || possible_column4 > 7)
        {
            location_B_possibility = false;
        }


        if (location_A_possibility == true || location_B_possibility == true || location_C_possibility == true || location_D_possibility == true)
        {
            char choice = ' ';

            if (location_A_possibility == true)
            {
                cout << "\nEnter a to move to (" << possible_row3 << " , " << possible_column3 << ")" << endl;
            }
            else
            {
                cout << "\nOption a is not availaible \n";
            }
            if (location_B_possibility == true)
            {
                cout << "\nEnter b to move to (" << possible_row4 << " , " << possible_column4 << ")" << endl;
            }
            else
            {
                cout << "\nOption b is not availaible \n";
            }


            if (white[piece_index].Get_IsKing() == true)
            {
                if (location_C_possibility == true)
                {
                    cout << "\nEnter c to move to (" << possible_row2 << " , " << possible_column2 << ")" << endl;
                }
                else
                {
                    cout << "\nOption c is not availaible \n";
                }
                if (location_D_possibility == true)
                {
                    cout << "\nEnter d to move to (" << possible_row1 << " , " << possible_column1 << ")" << endl;
                }
                else
                {
                    cout << "\nOption d is not availaible \n";
                }
            }

            if (white[piece_index].Get_IsKing() == false)
            {

                while (choice != 'a' && choice != 'b')
                {
                    cin >> choice;
                    if (choice != 'a' && choice != 'b')
                    {
                        cout << "\nIncorrect choice enter again" << endl;
                    }
                    if ((choice == 'a' && location_A_possibility == false) || (choice == 'b' && location_B_possibility == false))
                    {
                        cout << "\nChoose from availaible options" << endl;
                        cin >> choice;
                    }
                }

            }
            else if (white[piece_index].Get_IsKing() == true)
            {

                while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
                {
                    cin >> choice;
                    if (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
                    {
                        cout << "\nIncorrect choice, enter again !" << endl;
                    }
                    if ((choice == 'a' && location_A_possibility == false) || (choice == 'b' && location_B_possibility == false) || (choice == 'c' && location_C_possibility == false) || (choice == 'd' && location_D_possibility == false))
                    {
                        cout << "choose from availaible options" << endl;
                        cin >> choice;
                    }
                }
            }



            if (choice == 'b')
            {
                first_kill = lilkely_kill_2;
                Move_on_board(piece_index, possible_row4, possible_column4, X_input, Y_input, lilkely_kill_2, (possible_row4 - 1), (possible_column4 + 1));
            }
            else if (choice == 'a')
            {
                first_kill = lilkely_kill_1;
                Move_on_board(piece_index, possible_row3, possible_column3, X_input, Y_input, lilkely_kill_1, (possible_row3 - 1), (possible_column3 - 1));
            }
            else if (choice == 'd')
            {
                first_kill = lilkely_kill_4;
                Move_on_board(piece_index, possible_row1, possible_column1, X_input, Y_input, lilkely_kill_4, (possible_row1 + 1), (possible_column1 + 1));
            }
            else 
            {
                first_kill = lilkely_kill_3;
                Move_on_board(piece_index, possible_row2, possible_column2, X_input, Y_input, lilkely_kill_3, (possible_row2 + 1), (possible_column2 - 1));
            }
            move_vaalidity = true;
        }
        else
        {
            cout << "\nNo moves are possible for the selected piece" << endl;
            move_vaalidity = false;
            if (first_kill == true)
            {
                move_vaalidity = true;
                cout << "\nMove validity is declined" << endl;
                system("pause");
            }
        }
    }
    void Move_on_board(int piece_index, int x_coordinate, int y_coordinate, int& X_input, int& Y_input, bool likely_kill, int x_coordinate2, int y_coordinate2)
    {
        white[piece_index].Set_Location(x_coordinate, y_coordinate);
        ptr_array[X_input][Y_input] = -2;
        ptr_array[x_coordinate][y_coordinate] = 10;
        X_input = x_coordinate;
        Y_input = y_coordinate;

        if (X_input == 7)
        {
            white[piece_index].setIsKing(true);
            cout << "\nSelected piece is now a king piece!" << endl;
        }
        if (likely_kill == true)
        {
            red_player_kill_count++;
            ptr_array[x_coordinate2][y_coordinate2] = -2;
        }
    }

    void validate_move1(int& X_input, int& Y_input, bool& first_kill, int& possible_row1, int& possible_row2, int& possible_row3, int& possible_row4, int& possible_column1, int& possible_column2, int& possible_column3, int& possible_column4, bool& move_vaalidity, bool& lilkely_kill_1, bool& lilkely_kill_2, bool& lilkely_kill_3, bool& lilkely_kill_4, bool& location_D_possibility, bool& location_C_possibility, bool& location_A_possibility, bool& location_B_possibility)
    {
        if (ptr_array[possible_row1][possible_column1] == -2)
        {
            location_D_possibility = true;
        }
        else if (ptr_array[possible_row1][possible_column1] == 10)
        {
            location_D_possibility = false;
        }
        else if (ptr_array[possible_row1][possible_column1] == 5)
        {
            if (ptr_array[possible_row1 + 1][possible_column1 + 1] == -2)
            {
                location_D_possibility = true;
                possible_row1++;
                possible_column1++;
                lilkely_kill_4 = true;
            }
            else
            {
                location_D_possibility = false;
            }
        }


        if (ptr_array[possible_row2][possible_column2] == -2)
        {
            location_C_possibility = true;
        }
        else if (ptr_array[possible_row2][possible_column2] == 10)
        {
            location_C_possibility = false;
        }
        else if (ptr_array[possible_row2][possible_column2] == 5)
        {
            if (ptr_array[possible_row2 + 1][possible_column2 - 1] == -2)
            {
                location_C_possibility = true;
                lilkely_kill_3 = true;
                possible_row2++;
                possible_column2--;
            }
            else
            {
                location_C_possibility = false;
            }
        }

        if (ptr_array[possible_row3][possible_column3] == -2)
        {
            location_A_possibility = true;
        }
        else if (ptr_array[possible_row3][possible_column3] == 10)
        {
            location_A_possibility = false;

        }
        else if (ptr_array[possible_row3][possible_column3] == 5)
        {

            if (ptr_array[possible_row3 - 1][possible_column3 - 1] == -2)
            {
                location_A_possibility = true;
                lilkely_kill_1 = true;
                possible_row3--;
                possible_column3--;
            }
            else
            {
                location_A_possibility = false;
            }
        }


        if (ptr_array[possible_row4][possible_column4] == -2)
        {
            location_B_possibility = true;
        }
        else if (ptr_array[possible_row4][possible_column4] == 10)
        {
            location_B_possibility = false;

        }
        else if (ptr_array[possible_row4][possible_column4] == 5)
        {

            if (ptr_array[possible_row4 - 1][possible_column4 + 1] == -2)
            {
                location_B_possibility = true;
                lilkely_kill_2 = true;
                possible_row4--;
                possible_column4++;
            }
            else {
                location_B_possibility = false;
            }
        }
    }
    void validate_move2(int& X_input, int& Y_input, bool& first_kill, int& possible_row1, int& possible_row2, int& possible_row3, int& possible_row4, int& possible_column1, int& possible_column2, int& possible_column3, int& possible_column4, bool& move_vaalidity, bool& lilkely_kill_1, bool& lilkely_kill_2, bool& lilkely_kill_3, bool& lilkely_kill_4, bool& location_D_possibility, bool& location_C_possibility, bool& location_A_possibility, bool& location_B_possibility)
    {
        if (ptr_array[possible_row3][possible_column3] == 5)
        {
            if (ptr_array[possible_row3 - 1][possible_column3 - 1] == -2)
            {
                location_A_possibility = true;
                possible_row3--;
                possible_column3--;
                lilkely_kill_1 = true;
            }
            else
            {
                location_A_possibility = false;
            }
        }

        if (ptr_array[possible_row4][possible_column4] == 5)
        {
            if (ptr_array[possible_row4 - 1][possible_column4 + 1] == -2)
            {
                location_B_possibility = true;
                possible_row4--;
                possible_column4++;
                lilkely_kill_2 = true;
            }
            else
            {
                location_B_possibility = false;
            }
        }
        if (ptr_array[possible_row2][possible_column2] == 5)
        {
            if (ptr_array[possible_row2 + 1][possible_column2 - 1] == -2)
            {
                location_C_possibility = true;
                possible_row2++;
                possible_column2--;
                lilkely_kill_3 = true;
            }
            else
            {
                location_C_possibility = false;
            }
        }
        if (ptr_array[possible_row1][possible_column1] == 5)
        {
            if (ptr_array[possible_row1 + 1][possible_column1 + 1] == -2)
            {
                location_D_possibility = true;
                possible_row1++;
                possible_column1++;
                lilkely_kill_4 = true;
            }
            else
            {
                location_D_possibility = false;
            }
        }
    }
};

int main()
{
    system("Color 03");
    cout << "                WELCOME TO CHECKERS !!!                  Made by: Ahmad Hasan (2019041)  and  Ali Abdul Razzaq (2019058)";
    cout << "\n\n                                                                     '$' signs on the board are the red peices.";
    cout << "\n                                                                     'X' signs on the board are the white peices.";
    array_initialization();  
    grid_representation();


    bool turn_flag = false;
    bool end_of_game = false;
    red_pieces s;
    white_pieces z;
    cout << endl;
    
    while (end_of_game == false) 
    {
        Initial_board();
        cout << "********************************************************************\n";
        cout << "     White pieces kill count : " << white_player_kill_count << "  Red pieces kill count :  " << red_player_kill_count <<endl;
        cout << "********************************************************************\n";
        if (turn_flag == false) 
        {
            cout << "Player X's turn" << endl;
            z.take_move();
            turn_flag = true;
        }
        else 
        {
            cout << "Player $'s turn" << endl;
            s.take_move();
            turn_flag = false;
        }
        system("CLS");
        if (red_player_kill_count == 12 || white_player_kill_count == 12)
        {
            cout << "\n                                                             Game Over !!!" << endl;
            end_of_game = true;
        }
        if (end_of_game)
        {
            if (red_player_kill_count == 12)
            {
                cout << "\n'X' player has won the game!!";
            }
            else if (white_player_kill_count == 12)
            {
                cout << "\n'$' player has won the game!!";
            }
            cout << "\nCONGRATULATIONS !!";
        }
    }
}