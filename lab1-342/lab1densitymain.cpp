/**
 * \file lab1densitymain.cpp
 * \breif This function calculates countries population densities
 *
 * This function calculates countries population densities by
 * reading a file of areas and populations.  The file must have
 * one country per line and be in the format
 * <country name> <population> <area>
 * Population and Area should be non-negative and country
 * names must not have any spaces.
 *
 * \author James Murphree
 * \bug No know bugs
 *
 * 10/11/2014 CSS 342
 */

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

/**< MAXRECORDS is the maximum number of countries allowed*/
int const MAXRECORDS = 250;
/**< MAXLENGTH is the maximum number of character in a country name */
int const MAXLENGTH = 32;
/**< INPUTFILE is the file that will be read from */
char const INPUTFILE[] = "lab1data1.txt" ;

/** \brief CountryStats holds the information for each country
 * Population, Area, Density, and Country Name
 */
struct CountryStats  {
   int population;
   int area;
   double density;
   char countryName[MAXLENGTH];
};

/** \brief Prints the into text
 *
 * \return void
 *
 */
void printIntro();

/** \brief Sorts the input from the file
 *
 * \param input ifstream& the file to be read from
 * \param countries[] CountryStats the array to sort CountryStats into
 * \param countriesProcessed int& number of Countries sorted
 * \return void
 *
 */
void sortInput(ifstream& input, CountryStats countries[], int& countriesProcessed);

/** \brief Loads the information from the file into a CountryStats
 *
 * \param input ifstream& the file to be read from
 * \param newCountry CountryStats& the new CountryStats to write to
 * \return void
 *
 */
void loadCountry(ifstream& input, CountryStats& newCountry);

/** \brief Processes the Country by running calcPopDensity and insertionSort
 *
 * \param countries[] CountryStats array to sort the new country Stats into
 * \param countriesProcessed int& count of countries processed so far
 * \param newCountry CountryStats& the new country
 * \return void
 *
 */
void processCountry(CountryStats countries[], int& countriesProcessed, CountryStats& newCountry);

/** \brief Calculates the countries density
 *
 * \param newCountry CountryStats& country to calculate density for
 * \return void
 *
 */
void calcPopDensity(CountryStats& newCountry);

/** \brief inserts the CountryStats into the array in order
 *
 * \param countries[] CountryStats array to insert into
 * \param countriesProcessed int number of previously sorted CountryStats
 * \param newCountry CountryStats new CountryStats
 * \return void
 *
 */
void insertionSort(CountryStats countries[], int countriesProcessed, CountryStats newCountry);




/** \brief Prints out the statistics for all the countries
 *
 * \param countries[] CountryStats array of CountryStats
 * \param meanDensity double average density of the countries
 * \param countriesProcessed int number of CountryStats in the array
 * \param worldDensity double Density of all the countries combined
 * \return void
 *
 */
void printStats(CountryStats countries[], double meanDensity, int countriesProcessed,
                double worldDensity);

/** \brief Calculates the statistics to print out
 *
 * \param countries[] CountryStats array of CountryStats
 * \param countriesProcessed int number of CountryStats in the array
 * \return void
 *
 */
void calcOutput(CountryStats countries[], int countriesProcessed);

/** \brief The main function of lab1densitymain.cpp
 *
 * The main function does not take in any arguments from the command line.
 * It tries to reads the input file specified by INPUTFILE and checks it
 * it exists.
 *
 * \param argc int
 * \param argv[] char*
 * \return int returns 0 if it terminates successfully and 1
 * if the file does not exist.
 *
 */
int main(int argc, char* argv[]) {
    printIntro();
    CountryStats countries[MAXRECORDS];
    int countriesProcessed = 0;
    ifstream input(INPUTFILE);
    if (!input)  {
        cerr << "File could not be opened." << endl;
        return 1;
    }
    sortInput(input, countries, countriesProcessed);
    calcOutput(countries, countriesProcessed);
    return 0;
}

/** printIntro prints the Author, Title, and short description of
 * the programs function.
 */
void printIntro() {
    cout << "Author: James Murphree" << endl;
    cout << "Title: Country Density Calculator (lab1densitymain)" << endl;
    cout << "Calculates and displays countries densities,\n"
            << "arithmetic average density, total density,\n"
            << "and median density.\n" << endl;
}


/** sortInput takes the input stream, CountryStats array, and the number of
 * countriesProcessed so far and passes them into loadCountry and
 * processCountry.  Along with a temporary CountryStats holder.
 */
void sortInput(ifstream& input, CountryStats countries[], int& countriesProcessed) {
    CountryStats newCountry;
    loadCountry(input, newCountry);
    processCountry(countries, countriesProcessed, newCountry);
    while (!input.eof()) {
        loadCountry(input, newCountry);
        processCountry(countries, countriesProcessed, newCountry);
    }
}

/** loadCountry takes information from the input stream and
 * puts it into the temporary CountryStats for sorting.
 */
void loadCountry(ifstream& input, CountryStats& newCountry) {
    input >> newCountry.countryName
        >> newCountry.population
        >> newCountry.area;
}

/** processCountry takes the temporary CountryStats and sends it to the calcPopDensity
 * method, then it sends the CountryStats array, temporary CountryStats, and number of
 * countries processed to have the new CountryStats inserted into the CountryStats array.
 * Also increments countriesProcessed when finished.
 */
void processCountry(CountryStats countries[], int& countriesProcessed, CountryStats& newCountry) {
    calcPopDensity(newCountry);
    insertionSort(countries, countriesProcessed, newCountry);
    countriesProcessed++;
}

/** calcPopDensity calculates the population density of the passed
 * in country.  If the area is 0 the density is set to the population
 * number.  If the area or population are negative the density is set
 * to 0 and labeled with an ERROR in the printing process.
 */
void calcPopDensity(CountryStats& newCountry) {
    if (newCountry.area == 0) {
        newCountry.density = newCountry.population * 100.00;
    } else if (newCountry.area < 0 || newCountry.population < 0) {
        newCountry.density = 0;
    } else {
        newCountry.density =
                newCountry.population * 100.00 / newCountry.area;
    }
    newCountry.density = round(newCountry.density) / 100.00;
}

/** insertionSort sorts the temporary CountryStats into the array of
 * CountryStats by density (low to high) and then country name alphabetically.
 */
void insertionSort(CountryStats countries[], int countriesProcessed, CountryStats newCountry) {
    int i = countriesProcessed - 1;
    bool found = false;
    while (i > -1 && !found) {
        if (newCountry.density < countries[i].density) {
            countries[i + 1] = countries[i];
        } else if (newCountry.density == countries[i].density &&
                   strcmp(newCountry.countryName, countries[i].countryName) < 0) {
            countries[i + 1] = countries[i];
        } else {
            countries[i + 1] = newCountry;
            found = true;
        }
        i--;
    }
    if (!found) {
        countries[0] = newCountry;
    }
}

/** printCountry prints out the country and it's stats to
 * the console.  If the density is 0 an ERROR message is
 * printed.
 */
void printCountry(CountryStats country) {
    cout << "Country: " << country.countryName
            << ", population: " <<  country.population
            << ", area: " << country.area;
    if (country.density == 0) {
        cout << ", density: ERROR (Illegal POPULATION and/or AREA value(s))" << endl;
    } else {
        cout << ", density:  " << fixed << setprecision(2) << country.density << endl;
    }
}

/** printStats prints out statistics about the countries as a whole and
 * also prints an explanation of the difference between Arithmetic Average and
 * the average of all the countries combined.
 */
void printStats(CountryStats countries[], double meanDensity, int countriesProcessed,
                double worldDensity) {
    cout << "\nLeast Dense Country: " << countries[0].countryName << endl;
    cout << "Most Dense Country: " << countries[countriesProcessed - 1].countryName << endl;
    cout << "Median Density: " << countries[countriesProcessed / 2].density << endl;
    cout << "Arithmetic Average Density: " << meanDensity << endl;
    cout << "Total World Density: " << fixed << setprecision(2)
            << worldDensity << "\n" << endl;
    cout << "The reason that the Total World Density and the Arithmetic Average\n"
            << "Density of all the countries are different is because\n"
            << "of the mathematical principle that...\n"
            << "A/B + C/D != (A+C)/(B+D)\ti.e. 5/8 + 3/8 (1) != 8/16 (1/2)\n";
}

/** calcOutput calculates the statistics for printStats and also calls each
 * of the printStats and printCountry functions.
 */
void calcOutput(CountryStats countries[], int countriesProcessed) {
    long long int totalPop = 0;
    int totalArea = 0;
    double totalDensity = 0;
    for (int i = 0; i < countriesProcessed; i++) {
        printCountry(countries[i]);
        totalPop += countries[i].population;
        totalArea += countries[i].area;
        totalDensity += countries[i].density;
    }
    double worldDensity = round(totalPop * 100.00 / totalArea) / 100.00;
    double meanDensity = totalDensity / countriesProcessed;
    printStats(countries, meanDensity, countriesProcessed, worldDensity);
}