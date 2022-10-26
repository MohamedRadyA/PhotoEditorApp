// Program Description: Photo editor application that allows you to use filters on RGB photos
// Last Modification Date: 23/04/2022
// Purpose: This program allows you to apply multiple filters on images which include inverting, merging and other filters.

#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;

void loadImage();

void saveImage();

void blackWhite();

void invert();

void flip();

void merge();

void darkenLighten();

void rotate();

void shrinkImage();

void detect_edge();

void enlarge();

void mirror();

void shuffle();

void blurImage();

string display_choices();

unsigned char image[SIZE][SIZE][RGB];

//Main application loops
int main() {
    bool cont = true;
    cout << "Ahlan ya user ya habibi (RGB Edition)\n";
    bool new_image = true;
    while (cont) {
        if (new_image) {
            loadImage();
            new_image = false;
        }
        //Display all the filter options
        string choice = display_choices();

        //Handle all the filter options
        switch (choice[0]) {
            case '1':
                blackWhite();
                break;
            case '2':
                invert();
                break;
            case '3':
                merge();
                break;
            case '4':
                flip();
                break;
            case '5':
                rotate();
                break;
            case '6':
                darkenLighten();
                break;
            case '7':
                detect_edge();
                break;
            case '8':
                enlarge();
                break;
            case '9':
                shrinkImage();
                break;
            case 'a':
                mirror();
                break;
            case 'b':
                shuffle();
                break;
            case 'c':
                blurImage();
                break;
            case '0':
                cont = false;
                break;
            case 's':
                saveImage();
                string temp;
                cout << "Choose 1 to continue or anything else to exit\n";
                cin >> temp;
                if (temp == "1") {
                    new_image = true;
                } else {
                    cont = false;
                }
                break;
        }
    }
    cout << "Thanks for using FCAI photo editor application (RGB Edition)";
}

void loadImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    while (readRGBBMP(imageFileName, image)) {
        cout << "Invalid image please enter a bmp image file name: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }
}

//Display options function which returns the option chosen by the user
string display_choices() {
    set<string> choices = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "s", "0"};
    cout << "\nPlease select a filter to apply or 0 to exit:\n";
    cout << "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "3- Merge Filter\n"
            "4- Flip Image\n"
            "5- Rotate Image\n"
            "6- Darken and Lighten Image\n"
            "7- Detect Image Edges\n"
            "8- Enlarge Image\n"
            "9- Shrink Image\n"
            "a- Mirror Image\n"
            "b- Shuffle Image\n"
            "c- Blur Image\n"
            "s- Save the image to a file\n"
            "0- Exit\n";
    string choice;
    cin >> choice;
    choice[0] = tolower(choice[0]);

    //Ensuring the choice is valid
    while (!choices.count(choice)) {
        cout << "Invalid choice please enter a valid one\n";
        cout << "Please select a filter to apply or 0 to exit:\n";
        cout << "1- Black & White Filter\n"
                "2- Invert Filter\n"
                "3- Merge Filter\n"
                "4- Flip Image\n"
                "5- Rotate Image\n"
                "6- Darken and Lighten Image\n"
                "7- Detect Image Edges\n"
                "8- Enlarge Image\n"
                "9- Shrink Image\n"
                "a- Mirror Image\n"
                "b- Shuffle Image\n"
                "c- Blur Image\n"
                "s- Save the image to a file\n"
                "0- Exit\n";
        cin >> choice;
        choice[0] = tolower(choice[0]);
    }
    return choice;
}

void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and write image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
    cout << "Your image has been saved\n";
}


void blackWhite() {
    for (auto &i: image) {
        for (auto &j: i) {
            int temp = j[0] + j[1] + j[2];
            if (temp > 384) {
                for (unsigned char &k: j) {
                    k = 255;
                }
            } else {
                for (unsigned char &k: j) {
                    k = 0;
                }
            }
        }
    }
}


void invert() {
    //Get correspondence for each color
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < 3; k++){
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}


void merge() {
    char imageFileName[100];
    unsigned char imageToMerge[SIZE][SIZE][RGB];
    // Get gray scale image target file name to merge
    cout << "Enter the source image file name to merge: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    while (readRGBBMP(imageFileName, imageToMerge)) {
        cout << "Invalid image please enter a bmp image file name to merge: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = (image[i][j][k] + imageToMerge[i][j][k]) / 2;
            }
        }
    }
}


void flip() {
    string flip;
    //Let the user choose to flip horizontal or vertical.
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    cin >> flip;
    flip[0] = tolower(flip[0]);

    //If the user choosed anything else than h or v take input again.
    while (flip.size() != 1 || (flip[0] != 'h' && flip[0] != 'v')) {
        cout << "Invalid choice please enter a valid one\n";
        cout << "Flip (h)orizontally or (v)ertically ?\n";
        cin >> flip;
        flip[0] = tolower(flip[0]);
    }

    if (flip[0] == 'h') {
        //If the user chose to flip horizontally swap the first column with  the last column and
        // so on until half of the columns.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < 3; ++k) {
                    swap(image[i][j][k], image[i][SIZE - j - 1][k]);
                }
            }
        }
    } else if (flip[0] == 'v') {
        //If the user chose to flip vertically swap the first row with the last row and
        //so on until half of the rows.
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    swap(image[i][j][k], image[SIZE - i - 1][j][k]);
                }
            }
        }
    }
}


void rotate(){
    string option;
    int optionInt;
    cout << "Enter rotation degree 90, 180 or 270: ";
    cin >> option;
    while(option != "90" && option != "180" && option != "270"){
        cout << "Invalid input, You can only rotate by 90, 180 or 270: ";
        cin >> option;
    }
    optionInt = stoi(option);

    switch(optionInt){
        case 90:
            // Rotate image by 90 degrees by get transpose
            // Then invert column

                for (int i = 0; i < SIZE; i++) {
                    for (int j = i; j < SIZE; j++) {
                        for(int k = 0; k < 3; k++){
                            swap(image[i][j][k], image[j][i][k]);
                        }
                    }
                }
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j< SIZE/2; j++) {
                        for(int k = 0; k < 3; k++){
                            swap(image[i][j][k], image[i][SIZE-j][k]);
                        }
                    }
                } 
            break;
        case 180:
            //Flip image Verticle
            for (int i = 0; i < SIZE/2; i++) {
                for (int j = 0; j< SIZE; j++) {
                    for(int k = 0; k < 3; k++){
                        swap(image[i][j][k],image[SIZE-i-1][j][k]);
                    }
                }
            }
            //Flip image horizontal to get 180
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE/2; j++) {
                    for(int k = 0; k < 3; k++){
                        swap(image[i][j][k],image[i][SIZE-j-1][k]);
                    }
                }
            }
            break;
        case 270:
        // Rotate image by 90 then by 180 to get 270
            // Rotate image by 90 degrees by get transpose
            // Then invert column

            for (int i = 0; i < SIZE; i++) {
                for (int j = i; j < SIZE; j++) {
                    for(int k = 0; k < 3; k++){
                        swap(image[i][j][k], image[j][i][k]);
                    }
                }
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE/2; j++) {
                    for(int k = 0; k < 3; k++){
                        swap(image[i][j][k], image[i][SIZE-j][k]);
                    }
                }
            }  
            //Flip image Verticle
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k = 0; k < 3; k++){
                    swap(image[i][j][k],image[SIZE-i-1][j][k]);
                }
            }
        }
        //Flip image horizontal to get 180
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE/2; j++) {
                for(int k = 0; k < 3; k++){
                    swap(image[i][j][k],image[i][SIZE-j-1][k]);
                }
            }   
        }                    
            break;
    }
}


void darkenLighten() {
    char darkenOrLighten;
    cout << "Do you want to darken or lighten the picture by 50%? (Enter D or L): ";
    cin >> darkenOrLighten;
    while (tolower(darkenOrLighten) != 'd' && tolower(darkenOrLighten) != 'l') {
        cout << "Enter D or L: ";
        cin >> darkenOrLighten;
    }
    bool darken = tolower(darkenOrLighten) == 'd';
    long avg = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                avg += image[i][j][k];
            }
        }
    }
    avg /= (SIZE * SIZE * RGB);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                int ratioToAdd = (darken ? (-avg / 2) : (avg / 2));
                if (image[i][j][k] + ratioToAdd > 255)
                    image[i][j][k] = 255;
                else if (image[i][j][k] + ratioToAdd < 0)
                    image[i][j][k] = 0;
                else
                    image[i][j][k] += ratioToAdd;
            }
        }
    }
}


void detect_edge() {
    unsigned char image2[SIZE][SIZE][RGB];
    for (auto &i: image) {
        for (auto &j: i) {
            int temp = j[0] + j[1] + j[2];
            if (temp > 384) {
                for (unsigned char &k: j) {
                    k = 255;
                }
            } else {
                for (unsigned char &k: j) {
                    k = 0;
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k) {
                image2[i][j][k] = (image[i][j - 1][k] * 1) + (image[i - 1][j][k] * 1)
                                  + (image[i][j][k] * -4) + (image[i + 1][j][k] * 1)
                                  + (image[i][j + 1][k] * 1);
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k) {
                image[i][j][k] = 255 - image2[i][j][k];
            }
        }
    }
}


void enlarge(){
    unsigned char imageNew[SIZE][SIZE][RGB];
    set<string>options={"1","2","3","4"};
    string option; int quarter;
    // Take part from user to enlarge
    cout << "Choose which Part to Enlarge ";
    cout << "1,2,3 or 4:  ";
    cin >> option;
    // Check validity of input
    while (!options.count(option)){
        cout << "Invalid input..Try again\n";
        cout << "Choose which Part to Enlarge.";
        cout << "1,2,3 or 4:  ";
        cin >> option;
    }

    quarter = stoi(option);
    //Determine row and column of input's quarter
    int row, col;
    row = (quarter<3? 0:SIZE/2);
    col = (quarter%2? 0:SIZE/2);
    //Repeat each pixel 4 times in following direction.
    //Jump 2 pixel at a time in newImage to avoid merging
    int dx[] = {0,1,0,1};
    int dy[] = {0,0,1,1};

    for(int i = 0; i < SIZE; i+=2,row++,col = (quarter%2 ? 0: SIZE/2)){
        for(int j = 0; j < SIZE; j+=2,col++){
            for(int k = 0; k < 4; k++){
                for(int rgb = 0; rgb < 3; rgb++){
                    imageNew[i+dx[k]][j+dy[k]][rgb] = image[row][col][rgb]; 
                }
            }
        }
    }

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                image[i][j][k] = imageNew[i][j][k];
            }
        }
    }
}


void shrinkImage() {
    unsigned char shrinkImage[SIZE][SIZE][RGB] = {{{0}}};
    int shrinkRate;//Change it to 1/x and maybe enchance quality
    cout << "Shrink rate: ";
    cin >> shrinkRate;
    for (int i = 0; i < SIZE; i += shrinkRate)
        for (int j = 0; j < SIZE; j += shrinkRate)
            for (int k = 0; k < RGB; k++)
                shrinkImage[i / shrinkRate][j / shrinkRate][k] = (
                        (image[i][j][k] + image[i][j + 1][k] + image[i + 1][j][k] + image[i + 1][j + 1][k]) / 4);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = shrinkImage[i][j][k];
            }
        }
    }
}



void mirror() {
    set<string> choices = {"L", "R", "U", "D"};
    string choice;
    cout << "Choose to Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n>>";
    cin >> choice;
    choice[0] = toupper(choice[0]);
    while (!choices.count(choice)) {
        cout << "Invalid input\n";
        cout << "Choose to Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n>>";
        cin >> choice;
        choice[0] = toupper(choice[0]);
    }
    if (choice == "L") {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 128; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[i][SIZE - j - 1][k];
                }

            }
        }
    } else if (choice == "R") {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < 128; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[i][SIZE - j - 1][k];
                }

            }
        }
    } else if (choice == "D") {
        for (int i = 0; i < 128; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[SIZE - i - 1][j][k];
                }

            }
        }
    } else if (choice == "U") {
        for (int i = 128; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[SIZE - i - 1][j][k];
                }
            }
        }
    }
}


void shuffle(){
    unsigned char imageNew[SIZE][SIZE][RGB];
    //Vector to take order from user
    vector <int> order;
    set <char> keys = {'1','2','3','4'};
    string key; int option;
    cout << "Enter Order to shuffle Image: ";
    cin.clear();
    cin.sync();
  getline(cin,key);
  key.erase(remove(key.begin(), key.end(),' '), key.end());
  
  while(true){
    vector <char> optionKey;
    for(int i = 0; i < 4; i++){
        if(keys.count(key[i])){
            optionKey.push_back(key[i]);
        }
        else
            break;
    }
    if(optionKey.size() == 4)
        break;
    else{
        cin.clear();
        cin.sync();
        cout << "Invalid Input .. Try again\n";
        cout << "Enter Order to shuffle Image: ";
        getline(cin,key);
        key.erase(remove(key.begin(), key.end(),' '), key.end());
    }

  }
  for(int i = 0; i < 4; i++){
      order.push_back((key[i]-'0'));
  }
    //Take first order part puts it in first quarter
    int quarter = order[0];

    //Determine row and column for first order quarter
    int row = (quarter < 3) ? 0 : SIZE/2;
    int col = (quarter % 2) ? 0 : SIZE/2;
    
        for(int i = 0; i < SIZE/2; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = 0; j < SIZE/2; j++, col++){
                for(int k = 0; k < 3; k++){
                imageNew[i][j][k] = image[row][col][k];
                }
            }
        }
        //Take second order part puts it in second quarter
        quarter = order[1];

        //Determine row and column for second order quarter
        row = (quarter < 3) ? 0 : SIZE/2;
        col = (quarter % 2) ? 0 : SIZE/2;

        for(int i = 0; i < SIZE/2; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = SIZE/2; j < SIZE; j++, col++){
                for(int k = 0; k < 3; k++){
                imageNew[i][j][k] = image[row][col][k];
                }
            }
        }
        //Take third order part puts it in third quarter
        quarter = order[2];

        //Determine row and column for third order quarter
        row = (quarter < 3) ? 0 : SIZE/2;
        col = (quarter % 2) ? 0 : SIZE/2;

        for(int i = SIZE/2; i < SIZE; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = 0 ; j < SIZE/2; j++, col++){ 
                for(int k = 0; k < 3; k++){
                imageNew[i][j][k] = image[row][col][k];
                }
            }
        }
        //Take fourth order part puts it in fourth quarter
        quarter = order[3];

        //Determine row and column for fourth order quarter
        row = (quarter < 3) ? 0 : SIZE/2;
        col = (quarter % 2) ? 0 : SIZE/2;

        for(int i = SIZE/2; i < SIZE; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = SIZE/2 ; j < SIZE; j++, col++){      
                for(int k = 0; k < 3; k++){
                imageNew[i][j][k] = image[row][col][k];
                }
            }
        }

    // Save new image back to image
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                image[i][j][k] = imageNew[i][j][k];
            }
        }
    }
}


int getAverageForNextTen(bool horizontal, int i, int j, int k) {
    int avg = 0;
    for (int z = 0; z < 10; ++z) {
        avg += horizontal ? (j + z < SIZE ? image[i][j + z][k] : image[i][SIZE - 1][k]) : (i + z < SIZE ? image[i +
                                                                                                                z][j][k]
                                                                                                        : image[SIZE -
                                                                                                                1][j][k]);
    }
    avg /= 10;
    return avg;
}

void blurImage() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < RGB; k++)
                image[i][j][k] = getAverageForNextTen(true, i, j, k);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < RGB; k++)
                image[i][j][k] = getAverageForNextTen(false, i, j, k);
}
