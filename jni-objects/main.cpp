/* 
 * File:   main.cpp
 * Author: Cristina Yenyxe Gonzalez Garcia <cyenyxe@ebi.ac.uk>
 *
 * Created on 19 November 2014, 10:58
 */

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "VcfRecord.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    vector<string> alternate_alleles = {"T", "AG"};
    vector<string> samples = {"1/1:20:30", "0/1:40:15"};
    
    VcfRecord record { "1", 1000, "rs666", "A", alternate_alleles, 1.0, "PASS", "DP=50;AN=4", "GT:DP:GQ", samples};
    
    assert(record.alternate_alleles == alternate_alleles);
    cout << "Old alternates: " << alternate_alleles.size() << "\t" << &alternate_alleles << endl;
    cout << "New alternates: " << record.alternate_alleles.size() << "\t" << &(record.alternate_alleles) << endl;
    // How can this be implemented?
//    assert(&(record.alternate_alleles) == (&alternate_alleles));
    
    VcfRecord copied {record};
    assert(copied == record);
    
    VcfRecord moved {std::move(record)};
    assert(moved != record);
    
    cout << "Original: " << record.chromosome << ":" << record.position << endl;
    cout << "New:      " << moved.chromosome << ":" << moved.position << endl;
    
    cout << "Original is empty: " << record.samples.empty() << endl;
    cout << "New samples:       ";
    for (auto s : moved.samples) {
        cout << s << "\t";
    }
    cout << endl;
    
    return 0;
}

