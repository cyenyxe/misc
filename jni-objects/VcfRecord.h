/* 
 * File:   VcfRecord.h
 * Author: Cristina Yenyxe Gonzalez Garcia <cyenyxe@ebi.ac.uk>
 *
 * Created on 19 November 2014, 10:12
 */

#ifndef VCFRECORD_H
#define	VCFRECORD_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

struct VcfRecord {
    string chromosome;
    int position;
    string id;
    
    string reference_allele;
    vector<string> alternate_alleles;
    
    float quality;
    string filters;
    string info;
    string format;
    
    vector<string> samples;
    
    VcfRecord(const string & chromosome, const int position, const string & id, const string & reference_allele, 
        const vector<string> & alternate_alleles, const float quality, const string & filter, const string & info, 
        const string & format, const vector<string> & samples);
    
    bool operator==(const VcfRecord &);
    
    bool operator!=(const VcfRecord &);
};

#endif	/* VCFRECORD_H */

