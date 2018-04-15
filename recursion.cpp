/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
#include <unistd.h>
#include "tokenscanner.h"

using namespace std;

int gcd(int a, int b) {
    // your code here
    if(b == 0){
        cout << "gcd(" << a << ", " << b << ") = " << a << endl;
        return a;
    }else{
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a % b);
    }
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
//     cout << leftX << " " << leftY << " " << size << endl;
    if(order == 1){ // draw triangle
        double rightX = leftX + size;
        double bottomX = leftX + size / 2;
        double height = sqrt(size * size - (size / 2) * (size / 2));
        double bottomY = leftY + height;
        w.drawLine(leftX, leftY, rightX, leftY);
        w.drawLine(rightX, leftY, bottomX, bottomY);
        w.drawLine(bottomX, bottomY, leftX, leftY);
//        sleep(1);
    } else {
        order--;
        double newsize = size / 2;
        double newheight = sqrt(newsize * newsize - (newsize / 2) * (newsize / 2));
        serpinskii(w, leftX, leftY, newsize, order); //draw small triangle top-left
        serpinskii(w, leftX + newsize, leftY, newsize, order); // top-right
        serpinskii(w, leftX + newsize / 2, leftY + newheight, newsize, order); //bottom
    }
}

int dofill(GBufferedImage& image, int x, int y, int newColor, int color, int num){
    if(image.inBounds(x, y) && image.getRGB(x, y) == color){
        num++;
//        cout << num << endl;
        image.setRGB(x, y, newColor);
        dofill(image, x+1, y, newColor, color, num);
        dofill(image, x, y+1, newColor, color, num);
        dofill(image, x-1, y, newColor, color, num);
        dofill(image, x, y-1, newColor, color, num);
    }
    return num;
}
int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    // your code here
    int color = image.getRGB(x,y);
    int num = 0;
    if(newColor == color){
        return num;
    }
    return dofill(image, x, y, newColor, color, num);
}

void course(Map<string, Vector<string>> & prereqMap, string goal, set<string> printed){
    if(prereqMap.containsKey(goal)){
        for(int i = 0; i < prereqMap[goal].size(); i++){
            string concept = prereqMap[goal][i];
            course(prereqMap, concept, printed);
        }
    }
    if(printed.count(goal) == 0){
        cout << goal << endl;
        printed.insert(goal);
    }
}

void personalCurriculum(Map<string, Vector<string>> & prereqMap, string goal) {
    set<string> printed;
    course(prereqMap, goal, printed);
}


string generate(Map<string, Vector<string> > & grammar, string symbol) {
    string sentence;
    if(!grammar.containsKey(symbol)){ // symbol is not exist => terminal
        sentence += symbol;
    }
    else{
        string next = grammar[symbol][randomInteger(0, grammar[symbol].size() - 1)];
        TokenScanner scanner(next); //tokenscanner divides a string into individual tokens
        while(scanner.hasMoreTokens()){ // there are additional tokens
            string token = scanner.nextToken();
            string text = generate(grammar, token);
            sentence += text;
        }
    }
    return sentence;

}

