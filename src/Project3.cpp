#include <string>
#include <iostream>
#include <chrono>
#include <set>

#include "Bridges.h"
#include "DataSource.h"
#include "data_src/EarthquakeUSGS.h"
#include "Operations.h"


#include <cstdlib>  // for random number generator
#include <ctime>    //for seed and srand

using namespace std;
using namespace bridges;

// auto start = chrono::steady_clock::now( );
// auto elapsed = chrono::duration_cast<chrono::milliseconds>( chrono::steady_clock::now( ) - start );
// cout << elapsed.count( ) << '\n';

int main(int argc, char **argv) {
    Operations ops;
    Bridges bridges(1, getenv("UserID"), getenv("MyAPI"));
    bridges.setTitle("Accessing USGIS Earthquake Data (USGIS Data)");

    int max_quakes = 50000;

    DataSource ds(&bridges);
    vector<EarthquakeUSGS> eq_list = ds.getEarthquakeUSGSData(max_quakes); 
    vector<double> magnitudes; 

    string selection_num = "0";
    while (selection_num != "7") {
        ops.printMenu(); // Call the menu function from operations.h; we can move it back to main if you want.
        cin >> selection_num;

        if (selection_num == "1") {
            cout << "Select the sorting algorithm:\n"
                 << "1) Merge Sort\n"
                 << "2) Quick Sort\n"
                 << "Selection: ";
            string sorting_method;
            cin >> sorting_method;

            if (sorting_method == "1") {
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "Sorting the earthquakes by magnitude using Merge Sort...\n" << endl;
                auto start = chrono::steady_clock::now( );
                ops.mergeSort(eq_list, 0, eq_list.size() - 1);
                auto elapsed = chrono::duration_cast<chrono::milliseconds>( chrono::steady_clock::now( ) - start );
                // Print sorted earthquake data
                for (int e = 0; e < 10; e++) {
                    ops.printEarthquakeDetails(eq_list[e]); // Call the print function from Operations.h

                }
                cout << elapsed.count( ) << " milliseconds";
            } else if (sorting_method == "2") {
               //AIDANs code
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "Sorting earthquake magnitudes using Quick Sort...\n" << endl;
                auto start = chrono::steady_clock::now( );
                ops.quickSort(eq_list, 0, eq_list.size() - 1);
                auto elapsed = chrono::duration_cast<chrono::milliseconds>( chrono::steady_clock::now( ) - start );

                for (int i = 0; i < 10; i++) {
                  ops.printEarthquakeDetails(eq_list[i]); // Call the print function from Operations.h
                }
                cout << "\n" << elapsed.count( ) << " milliseconds";

            }
          cout << "\n\n";
        } 
        else if (selection_num == "2") {
            srand(time(0)); // SET SEED
            // generate and display random earthquake data from the vector
            cout << "\nDisplaying random earthquake... (°ロ°)\n" <<endl;
            int randomIndex = rand() % eq_list.size(); 
            ops.printEarthquakeDetails(eq_list[randomIndex]); 
            cout << endl;
        } 
        else if(selection_num == "3") {
          cout << "\nTop 10 Earthquakes by Magnitude:\n" << endl;
          ops.printTopTenMagnitudes(eq_list);
        } 
        else if(selection_num == "4") {
          cout << "\nTop 10 Most Recent Earthquakes:\n" << endl;
          ops.printMostRecent(eq_list);
        } 
        else if (selection_num == "5"){
          cout << "\nTop 10 Most Frequent Locations for Earthquakes:\n" << endl;
           ops.displayTop10Locations(eq_list);
          cout << endl;

        } 
        else if (selection_num == "6") {
          cout << "\nDisplay All Earthquakes at a Location\n" << endl;
          string city;
          cout << "Enter a City Name: "<< endl;
          cin.ignore(); 
          getline(cin, city);
          ops.displayAllEarthquakesAtLocation(eq_list, city);
          cout << endl;
         } 
        else if (selection_num == "7") {
            cout << "\nThank you for using the Earthquake Databaseヾ(￣▽￣) Bye~Bye~" << endl;
          break;
        } 
        else {
            cout << "\nINVALID SELECTION! CHOOSE BETWEEN 1 AND 7!!\n" << endl;
        }

      bool return_menu = false;
      while (true) {
        cout << "\nReturn to main menu? (Y/N): ";
        string answer;
        cin >> answer;

        if (answer == "N" || answer == "n") {
          cout << "\nThank you for using the Earthquake Databaseヾ(￣▽￣) Bye~Bye~" << endl;
          break;
        } else if (answer == "Y" || answer == "y") {
          return_menu = true;
          break;
        } else {
          cout << "\nINVALID SELECTION! CHOOSE BETWEEN Y/N!! " << endl;
        }
      }
      if (!return_menu){break;}
  }
  return 0;
}
