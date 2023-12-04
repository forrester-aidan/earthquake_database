#pragma once

#include <iostream>
#include <string>
#include <set>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/EarthquakeUSGS.h"
#include <bits/stdc++.h>

using namespace std;
using namespace bridges;

class Operations {
private: 
  void merge(vector<EarthquakeUSGS>& arr, int left, int mid, int right);
  void swap(vector<EarthquakeUSGS>& array, int i1, int i2);
  int partition(vector<EarthquakeUSGS>& earthquakes, int low, int high);

public:
  void printMenu();
  void printEarthquakeDetails(const EarthquakeUSGS& earthquake);
  void mergeSort(vector<EarthquakeUSGS>& arr, int left, int right);
  void quickSort(vector<EarthquakeUSGS>& earthquakes, int low, int high);
  void displayTop10Locations(vector<EarthquakeUSGS>& earthquakes);
  void printTopTenMagnitudes(vector<EarthquakeUSGS>& eq_list);
  void printMostRecent(vector<EarthquakeUSGS>& earthquakes);
  void displayAllEarthquakesAtLocation(vector<EarthquakeUSGS>& earthquakes, string city);
};

void Operations::printMenu() { 
    cout << "\n*****************************************************" << endl;
    cout << "╰（‵□′）╯ Welcome to the Earthquake Database! ╰（‵□′）╯\n"
         << "*****************************************************\n\n"
         << "**Note The Earthquake Data Is Based on the 50,000\n"
         << "Most Recent Earthquakes as Recorded by USGS**\n\n"
         << "Please select an option below:\n"
         << "1) Display the 10 Least Powerful Earthquakes by Magnitude\n"
         << "2) Display a Random Earthquake's Information\n"
         << "3) Top 10 Biggest Recent Earthquakes\n"
         << "4) Top 10 Most Recent Earthquakes\n"
         << "5) Top 10 Most Frequent Locations for Earthquakes\n"
         << "6) Display All Earthquakes at a Location\n"
         << "7) Quit\n" << endl;
    cout << "Selection Number: ";
}

// prints earthquake details
void Operations::printEarthquakeDetails(const EarthquakeUSGS& earthquake) { 
    cout << "Location: " << earthquake.getLocation() << endl;
    cout << "Magnitude: " << earthquake.getMagnitude() << endl;
    cout << "Date: " << earthquake.getDateStr() << endl;
    cout << "Latitude/Longitude: " << earthquake.getLatit() << ", " << earthquake.getLongit() << endl;
    cout << "---------------------------------" << endl;
    cout << "\n";
}

// sorts the database using merge sort
void Operations::mergeSort(vector<EarthquakeUSGS>& arr, int left, int right) {
    if (left >= right) {
        return; 
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// merge sort helper function that assists in merge sort
void Operations::merge(vector<EarthquakeUSGS>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  
  // Create temp arrays
  vector<EarthquakeUSGS> L(n1), R(n2);
  
  // Copy data to temp arrays L[] and R[]
  for (int i = 0; i < n1; i++)
      L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
      R[j] = arr[mid + 1 + j];
  
  // Merge the temp arrays back into arr[left..right]
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
      if (L[i].getMagnitude() <= R[j].getMagnitude()) {
          arr[k] = L[i];
          i++;
      } else {
          arr[k] = R[j];
          j++;
      }
      k++;
  }
  // copy the remaining eles of L[] if  any
  while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
  }
  // copy the remaining elements of right side if  any
  while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
  }
}

// sorts the database using quick sort
void Operations::quickSort(vector<EarthquakeUSGS>& earthquakes, int low, int high){
  if (low < high) {
    int pivot = partition(earthquakes, low, high);
    quickSort(earthquakes, low, pivot - 1);
    quickSort(earthquakes, pivot + 1, high);
  }
}

// quick sort helper function that swaps two elements in an array
void Operations::swap(vector<EarthquakeUSGS>& array, int i1, int i2) {
  EarthquakeUSGS temp = array[i2];
  array[i2] = array[i1];
  array[i1] = temp;
}

// quick sort helper function that complete one pass through the array
int Operations::partition(vector<EarthquakeUSGS>& earthquakes, int low, int high) {
  double pivot = earthquakes[low].getMagnitude();
  int up = low, down = high;

  while (up < down) {
    for (int i = up; i < high; i++) {
      if (earthquakes[up].getMagnitude() > pivot) {
        break;
      }
      up++;
    }
    for (int j = high; j > low; j--) {
      if (earthquakes[down].getMagnitude() < pivot) {
        break;
      }
      down--;
    }
    if (up < down) {
      swap(earthquakes, up, down);
    }
  }
  swap(earthquakes, low, down);
  return down;
}

// displays the top 10 earthquake locations by frequency
void Operations::displayTop10Locations(vector<EarthquakeUSGS>& earthquakes) {
     // Use a map to store all locations with their corresponding earthquake count.
     map<string, int> locationCounts;
     for (const auto& eq : earthquakes) {
         locationCounts[eq.getLocation()]++;
     }

     // create copy vector for sorting
     vector<pair<string, int>> sortedLocations(locationCounts.begin(), locationCounts.end());

     // sort by frequency decending 
     sort(sortedLocations.begin(), sortedLocations.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });

     // display locations with their corresponding counts 
     cout << "Top 10 Earthquake Locations:" << endl;
     for (int i = 0; i < 10 && i < sortedLocations.size(); ++i) {
         // Display the location alongside the number of times it has appeared.
         cout << (i + 1) << ". " << sortedLocations[i].first << " - " 
              << sortedLocations[i].second << " times" << endl;
     }
}

// displays the top 10 earthquakes by magnitude
void Operations::printTopTenMagnitudes(vector<EarthquakeUSGS>& eq_list) {
    mergeSort(eq_list, 0, eq_list.size() - 1);
    for (int i = eq_list.size() - 1; i >= eq_list.size() - 10; i--) {
      printEarthquakeDetails(eq_list[i]);
    }
    cout << "\n" << endl;
}

// displays the 10 most recent earthquakes
void Operations::printMostRecent(vector<EarthquakeUSGS>& earthquakes) {
    for (int i = 0; i < 10; i++) {
      printEarthquakeDetails(earthquakes[i]);
    }
}

// displays all earthquakes that occured at an inputted location
void Operations::displayAllEarthquakesAtLocation(vector<EarthquakeUSGS>& earthquakes, string city) {
    for (int i = 0; i < city.length(); i++){
      if (i == 0){
        city[i] = toupper(city[i]);
      }
      else if (city[i-1] == ' '){
        city[i] = toupper(city[i]);
      }
    }
    string location = city + ",";
    bool found = false;
    for (int i = 0; i < earthquakes.size(); i++) {
      if (earthquakes[i].getLocation().find(location) != string::npos) {
        printEarthquakeDetails(earthquakes[i]);
        found = true;
      }
    }
    if (!found) {cout << "No Earthquakes Found at This City: " << city << endl;}
}
