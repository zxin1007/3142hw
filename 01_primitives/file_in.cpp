// This file shows basic functions of reading in a CSV file using C++98
// Please add your name to your code! 

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.

All programs must be able to compile in C++98 standard (the default version on Linux Machine). That means you cannot use the new features of C++11! :(

*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std; 

int main() {

  // define variables
  string sku, brand, category, year, price; 
  vector<int>vSKU;
  vector<string>vBrand;
  vector<string>vCategory;
  vector<int>vYear;
  vector<float>vPrice;

  ifstream in_stream;
  in_stream.open("data.csv"); //opening the file.
  ofstream myfile;
  myfile.open ("lab01_output.txt");

  if (!in_stream.fail()) { //if the file is open

    string line;
    //skip the header
    getline(in_stream,line);
    while (getline(in_stream,line)) { //while the end of file is NOT reached

     // Fields: sku,brand,category,year,price
    stringstream str(line);
    // cout << line;

    getline(str,sku,',');
    stringstream ssku(sku); 
    int iSKU = 0;
    ssku >> iSKU;
    vSKU.push_back(iSKU);

    getline(str, brand, ',');
    vBrand.push_back(brand);

    getline(str, category, ',');
    vCategory.push_back(category);

    getline(str, year, ','); 
    stringstream syear(year);
    int iYear;
    syear >> iYear;
    vYear.push_back(iYear);

    getline(str, price); 
    stringstream sprice(price);
    float fPrice;
    sprice >> fPrice;
    vPrice.push_back(fPrice);
    }

    in_stream.close(); //closing the file cout << "Number of entries: " << i-1 << endl;

   } else {
    myfile << "Unable to open file"; 
   }
 
  //output values sku,brand,category,year,price
  myfile << "SKU" << "\t\t" << "Brand" << "\t" << "Category" << "\t" << "Year" << "\t" << "Price" << endl; 

  for (int j = 0; j < vSKU.size(); j++) {
    myfile << vSKU[j] << "\t\t" << vBrand[j] << "\t\t" << vCategory[j] << "\t\t\t" << vYear[j] << "\t" << vPrice[j] << endl;
  }
  myfile << endl;

  vector<string> :: iterator it;

  vector<string> uniqueBrand = vBrand;
  sort(uniqueBrand.begin(), uniqueBrand.end());
  it = unique(uniqueBrand.begin(), uniqueBrand.end());
  uniqueBrand.resize(distance(uniqueBrand.begin(), it));

  for (int j=0; j<uniqueBrand.size(); j++){
    float sum= 0;
    int count =0;
    for (int x=0; x<vBrand.size(); x++){
      if (uniqueBrand[j]==vBrand[x]){
        sum+=vPrice[x];
        count+=1;
      }
    }
    myfile << uniqueBrand[j] << " with average price: " << sum/count << endl;
  }
  myfile << endl;

  vector<string> uniqueCatagory = vCategory;
  sort(uniqueCatagory.begin(), uniqueCatagory.end());
  it = unique(uniqueCatagory.begin(), uniqueCatagory.end());
  uniqueCatagory.resize(distance(uniqueCatagory.begin(), it));

  for (int j=0; j<uniqueCatagory.size(); j++){
    float sum= 0;
    int count = 0;
    for (int x=0; x<vCategory.size(); x++){
      if (uniqueCatagory[j]==vCategory[x]){
        sum+=vPrice[x];
        count+=1;
      }
    }
    myfile << uniqueCatagory[j] << " with average price: " << sum/count << endl;
  }

  myfile << endl;

  vector<int> unqiueYear = vYear;
  vector<int> :: iterator itSKU;
  sort(unqiueYear.begin(), unqiueYear.end());
  itSKU = unique(unqiueYear.begin(), unqiueYear.end());
  unqiueYear.resize(distance(unqiueYear.begin(), itSKU));

  for (int j=0; j<unqiueYear.size(); j++){
    string skus= "";
    int count =0;
    for (int x=0; x<vYear.size(); x++){
      if (unqiueYear[j]==vYear[x]){
        skus += to_string(vSKU[x]);
        skus += " ";
        count+=1;
      }
    }
    myfile << unqiueYear[j] << " ( " << count << " ) " << skus << endl;
  }
  in_stream.close();
  myfile.close();
}
