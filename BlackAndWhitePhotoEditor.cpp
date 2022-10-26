// Program Description: Photo editor application that allows you to use filters
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

unsigned char image[SIZE][SIZE];

//Main application loops
int main() {
    bool cont = true;
    cout<<"Ahlan ya user ya habibi \n";
    bool new_image = true;
    while (cont){
        if(new_image){
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
                cout<<"Choose 1 to continue or anything else to exit\n";
                cin>>temp;
                if(temp=="1"){
                    new_image = true;
                }
                else{
                    cont = false;
                }
                break;
        }
    }
    cout<<"Thanks for using FCAI photo editor application";
}

void loadImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    while(readGSBMP(imageFileName, image)){
        cout<<"Invalid image please enter a bmp image file name: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }
}

//Display options function which returns the option chosen by the user
string display_choices(){
    set<string>choices={"1","2","3","4","5","6","7","8","9","a","b","c","s","0"};
    cout<<"\nPlease select a filter to apply or 0 to exit:\n";
    cout<<"1- Black & White Filter\n"
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
    cin>>choice;
    choice[0]= tolower(choice[0]);

    //Ensuring the choice is valid
    while (!choices.count(choice)){
        cout<<"Invalid choice please enter a valid one\n";
        cout<<"Please select a filter to apply or 0 to exit:\n";
        cout<<"1- Black & White Filter\n"
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
        cin>>choice;
        choice[0]= tolower(choice[0]);
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
    writeGSBMP(imageFileName, image);
    cout<<"Your image has been saved\n";
}

void invert() {
    //Substract each pixel value from 255 and save it in the pixel
    for (auto & i : image) {
        for (unsigned char & j : i) {
            j = 255 - j;
        }
    }
}


void blackWhite() {
    //If the pixel is more than 128 make it white else make it black
    for (auto & i : image) {
        for (unsigned char & j : i) {
            j = (j>128? 255:0);
        }
    }
}


void flip() {
    string flip;
    //Let the user choose to flip horizontal or vertical.
    cout<<"Flip (h)orizontally or (v)ertically ?\n";
    cin>>flip;
    flip[0] = tolower(flip[0]);

    //If the user choosed anything else than h or v take input again.
    while (flip.size()!=1 || (flip[0]!='h' && flip[0]!='v')){
        cout<<"Invalid choice please enter a valid one\n";
        cout<<"Flip (h)orizontally or (v)ertically ?\n";
        cin>>flip;
        flip[0] = tolower(flip[0]);
    }

    if(flip[0] == 'h'){
        //If the user chose to flip horizontally swap the first column with  the last column and
        // so on until half of the columns.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE/2; j++) {
                swap(image[i][j], image[i][SIZE-j-1]);
            }
        }
    }
    else if(flip[0] =='v'){
        //If the user chose to flip vertically swap the first row with the last row and
        //so on until half of the rows.
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                swap(image[i][j], image[SIZE-i-1][j]);
            }
        }
    }
}


void merge() {
    char imageFileName[100];
    unsigned char imageToMerge[SIZE][SIZE];
    // Get gray scale image target file name to merge
    cout << "Enter the source image file name to merge: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    while(readGSBMP(imageFileName, imageToMerge)){
        cout<<"Invalid image please enter a bmp image file name to merge: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }

    //Get the average of every pixel and the corresponding pixel values from both images
    //and put it in the image we will save
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (image[i][j] + imageToMerge[i][j])/2;
        }
    }
}


void darkenLighten() {
    char darkenOrLighten;
    cout << "Do you want to darken or lighten the picture by 50%? (Enter D or L): ";
    cin >> darkenOrLighten;
    //Choose darken or lighten and take only d and l as input
    while (tolower(darkenOrLighten) != 'd' && tolower(darkenOrLighten) != 'l') {
        cout << "Enter D or L: ";
        cin >> darkenOrLighten;
    }
    bool darken = tolower(darkenOrLighten) == 'd';
    int avg = 0;

    //Calculate the average grayscale value for the whole picture
    for (auto & i : image)
        for (unsigned char j : i)
            avg += j;


    avg /= (SIZE * SIZE);

    //Calculate the ratio to add which is half the average we calculated
    //and handle maximum and minimum values (0 and 255)
    for (auto & i : image) {
        for (unsigned char & j : i) {
            int ratioToAdd = (darken ? (-avg / 2) : (avg / 2));
            if (j + ratioToAdd > 255){
                j = 255;
            }
            else if (j + ratioToAdd < 0){
                j = 0;
            }
            else{
                j += ratioToAdd;
            }
        }
    }
}


void rotate(){
    // Check Validty of input
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
            // Get image transpose
            for (int i = 0; i < SIZE; i++) {
                for (int j = i; j < SIZE; j++) {
                    swap(image[i][j], image[j][i]);
                }
            }
            // Flip image horizontally
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE/2; j++) {
                    swap(image[i][j], image[i][SIZE-j]);
                }
            }
            break;
        case 180:
            // Transpose and Reverse each element in coloum Twice
            for(int i = 0; i < 2; i++){
                // Get image Transpose
                for(int r = 0; r < SIZE; r++){
                    for(int c = r; c < SIZE; c++){
                        swap(image[r][c], image[c][r]);
                    }
                }
                // Reverse each element in coloums
                for(int r = 0; r < SIZE; r++){
                    for(int c = 0,c2 = SIZE - 1; c < c2; c++,c2--){
                        swap(image[c][r], image[c2][r]);
                    }
                }
            }
            break;
        case 270 :
            // Rotate image by 180 degree
            for(int i = 0; i < 2; i++){

                for(int r = 0; r < SIZE; r++){
                    for(int c = r; c < SIZE; c++){
                        swap(image[r][c], image[c][r]);
                    }
                }

                for(int r = 0; r < SIZE; r++){
                    for(int c = 0,c2 = SIZE - 1; c < c2; c++,c2--){
                        swap(image[c][r], image[c2][r]);
                    }
                }
            }
            // Rotate image by 90 degree
            for (int i = 0; i < SIZE; i++) {
                for (int j = i; j < SIZE; j++) {
                    swap(image[i][j], image[j][i]);
                }
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE/2; j++) {
                    swap(image[i][j], image[i][SIZE-j]);
                }
            }
            break;
    }
}

void detect_edge(){
    unsigned char imageNew[SIZE][SIZE];
    for (int i = 0;i<SIZE;i++) {
        for (int j = 0;j<SIZE;j++) {
            image[i][j] = (image[i][j] > 127? 255 : 0);
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imageNew[i][j] =  (image[i][j - 1] * 1) + (image[i - 1][j] * 1)
                            + (image[i][j] * -4) + (image[i + 1][j] * 1)
                            + (image[i][j + 1] * 1);
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - imageNew[i][j];
        }
    }
}




void enlarge(){
    unsigned char imageNew[SIZE][SIZE];
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
                imageNew[i+dx[k]][j+dy[k]] = image[row][col]; 
            }
        }
    }

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = imageNew[i][j];
        }
    }
}

void mirror(){
    set<string>choices={"L","R","U","D"};
    string choice;
    cout<<"Choose to Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n>>";
    cin >> choice;
    choice[0] = toupper(choice[0]);
    while (!choices.count(choice)){
        cout<<"Invalid input\n";
        cout<<"Choose to Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n>>";
        cin >> choice;
        choice[0] = toupper(choice[0]);
    }
    if(choice=="L"){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 128; j < SIZE; ++j) {
                image[i][j] = image[i][SIZE-j-1];
            }
        }
    }
    else if(choice=="R"){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < 128; ++j) {
                image[i][j] = image[i][SIZE-j-1];
            }
        }
    }
    else if(choice=="D"){
        for (int i = 0; i < 128; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[SIZE-i-1][j];
            }
        }
    }
    else if(choice=="U"){
        for (int i = 128; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[SIZE-i-1][j];
            }
        }
    }
}


void shrinkImage() {
    int shrinkRate;//Change it to 1/x and maybe enhance quality
    unsigned char imageNew[SIZE][SIZE];
    cout << "Shrink rate: (1/X)";
    cin >> shrinkRate;
    while (!(shrinkRate == 2 || shrinkRate == 3 || shrinkRate == 4)) {
        cout << "Please enter 1/x (2 or 3 or 4): ";
        cin >> shrinkRate;
    }
    for (int i = 0; i < SIZE; i+=shrinkRate)
        for (int j = 0; j < SIZE; j+=shrinkRate)
            imageNew[i/shrinkRate][j/shrinkRate] = ((image[i][j] + image[i][j+1] + image[i+1][j] + image[i+1][j+1]) / 4);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = imageNew[i][j];
        }
    }
}


void shuffle(){
    unsigned char imageNew[SIZE][SIZE];
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
                
                imageNew[i][j] = image[row][col];
            }
        }
        //Take second order part puts it in second quarter
        quarter = order[1];
        //Determine row and column for second order quarter
        row = (quarter < 3) ? 0 : SIZE/2;
        col = (quarter % 2) ? 0 : SIZE/2;

        for(int i = 0; i < SIZE/2; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = SIZE/2; j < SIZE; j++, col++){

                imageNew[i][j] = image[row][col];
            }
        }

        //Take third order part puts it in third quarter
        quarter = order[2];
        //Determine row and column for third order quarter
        row = (quarter < 3) ? 0 : SIZE/2;
        col = (quarter % 2) ? 0 : SIZE/2;

        for(int i = SIZE/2; i < SIZE; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = 0 ; j < SIZE/2; j++, col++){ 

                imageNew[i][j] = image[row][col];
            }
        }
        //Take fourth order part puts it in fourth quarter
        quarter = order[3];
        //Determine row and column for fourth order quarter
        row = (quarter < 3) ? 0 : SIZE/2;
        col = (quarter % 2) ? 0 : SIZE/2;

        for(int i = SIZE/2; i < SIZE; i++, row++, col = (quarter % 2) ? 0 : SIZE/2){
            for(int j = SIZE/2 ; j < SIZE; j++, col++){      

                imageNew[i][j] = image[row][col];
            }
        }
    
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = imageNew[i][j];
        }
    }
}


int getAverageForNextTen(bool horizontal, int i, int j) {
    int avg = 0;
    for (int k = 0; k < 10; ++k) {
        avg += horizontal ? (j+k < SIZE ? image[i][j+k] : image[i][SIZE-1]) : (i+k < SIZE ? image[i+k][j] : image[SIZE-1][j]);
    }
    avg /= 10;
    return avg;
}

void blurImage() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = getAverageForNextTen(true, i, j);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = getAverageForNextTen(false, i, j);
}
